//
// Created by Mick on 19/03/2021.
//
#include "rawStream.h"

static const char *TAG = "RawStream";

static audio_element_handle_t i2s_stream_reader, filter, raw_read;

void readStream();

int running = 0;

void rawStream_init(audio_pipeline_handle_t *pipeline) {

    i2s_stream_cfg_t i2s_cfg = I2S_STREAM_CFG_DEFAULT();
    i2s_cfg.type = AUDIO_STREAM_READER;
    i2s_stream_reader = i2s_stream_init(&i2s_cfg);

    rsp_filter_cfg_t rsp_cfg = DEFAULT_RESAMPLE_FILTER_CONFIG();
    rsp_cfg.src_rate = AUDIO_SAMPLE_RATE;
    rsp_cfg.src_ch = 2;
    rsp_cfg.dest_rate = GOERTZEL_SAMPLE_RATE_HZ;
    rsp_cfg.dest_ch = 1;
    filter = rsp_filter_init(&rsp_cfg);

    raw_stream_cfg_t raw_cfg = {
            .out_rb_size = 8 * 1024,
            .type = AUDIO_STREAM_READER,
    };
    raw_read = raw_stream_init(&raw_cfg);

    audio_pipeline_register(*pipeline, i2s_stream_reader, "i2s");
    audio_pipeline_register(*pipeline, filter, "filter");
    audio_pipeline_register(*pipeline, raw_read, "raw");

    //ESP_LOGI(TAG, "[ 4 ] Link elements together [codec_chip]-->i2s_stream-->filter-->raw-->[VAD]");
    const char *link_tag[3] = {"i2s", "filter", "raw"};
    audio_pipeline_link(*pipeline, &link_tag[0], 3);
}

void rawStream_settarget(audio_pipeline_handle_t *pipeline, char* target) {

    ESP_LOGI(TAG, "Stopping pipeline");
    audio_pipeline_stop(*pipeline);
    audio_pipeline_wait_for_stop(*pipeline);

    ESP_LOGI(TAG, "Resetting ringbuffer");
    audio_pipeline_reset_ringbuffer(*pipeline);
    ESP_LOGI(TAG, "Resetting elements");
    audio_pipeline_reset_elements(*pipeline);
    ESP_LOGI(TAG, "Resetting states");
    audio_pipeline_reset_items_state(*pipeline);
    ESP_LOGI(TAG, "Restarting pipeline");
    audio_pipeline_run(*pipeline);
    ESP_LOGI(TAG, "Done restarting pipeline");
    running = 1;
    xTaskCreate(readStream, "rawStream_read_task", configMINIMAL_STACK_SIZE * 5, NULL, 5, NULL);
}

void rawStream_destroy(audio_pipeline_handle_t *pipeline) {
    running = 0;
    vTaskDelay(100 / portTICK_PERIOD_MS);

    ESP_LOGI(TAG, "Stopping pipeline.");
    audio_pipeline_stop(*pipeline);
    audio_pipeline_wait_for_stop(*pipeline);

    ESP_LOGI(TAG, "Unregistering audio ");
    audio_pipeline_unregister(*pipeline, i2s_stream_reader);
    audio_pipeline_unregister(*pipeline, filter);
    audio_pipeline_unregister(*pipeline, raw_read);

    ESP_LOGI(TAG, "Deinitializing audio elements");
    audio_element_deinit(i2s_stream_reader);
    audio_element_deinit(filter);
    audio_element_deinit(raw_read);
    ESP_LOGI(TAG, "Destroyed elements in pipeline");
}

void readStream() {
    int16_t *raw_buff = (int16_t *)malloc(GOERTZEL_BUFFER_LENGTH * sizeof(short));
    while (running) {
        raw_stream_read(raw_read, (char *)raw_buff, GOERTZEL_BUFFER_LENGTH);
            recognizeAudio(raw_buff);
        vTaskDelay(1 / portTICK_PERIOD_MS);
    }
    free(raw_buff);
    vTaskDelete(NULL);
}
