#include "audio_element.h"
#include "audio_pipeline.h"
#include "audio_event_iface.h"
#include "audio_common.h"
#include "http_stream.h"
#include "i2s_stream.h"
#include "mp3_decoder.h"
#include "fatfs_stream.h"
#include "mp3_decoder.h"
#include <string.h>
#include <stdlib.h>

#include "esp_log.h"

static const char *TAG = "timesource";

static audio_element_handle_t fatfs_stream_reader, i2s_stream_writer, mp3_decoder;

void timesource_init(audio_pipeline_handle_t *pipeline)
{
    //Configure http stream to download the mp3 data
    ESP_LOGI(TAG, "Create fatfs element");
    fatfs_stream_cfg_t fatfs_cfg = FATFS_STREAM_CFG_DEFAULT();
    fatfs_cfg.type = AUDIO_STREAM_READER;
    fatfs_stream_reader = fatfs_stream_init(&fatfs_cfg);

    //Configure configure i2s audio chip to decode our data
    ESP_LOGI(TAG, "Create i2s element");
    i2s_stream_cfg_t i2s_cfg = I2S_STREAM_CFG_DEFAULT();
    i2s_cfg.type = AUDIO_STREAM_WRITER;
    i2s_stream_writer = i2s_stream_init(&i2s_cfg);

    //Configure a decoder to decode the incoming mp3 stream data
    ESP_LOGI(TAG, "Create mp3 decoder element");
    mp3_decoder_cfg_t mp3_cfg = DEFAULT_MP3_DECODER_CONFIG();
    mp3_decoder = mp3_decoder_init(&mp3_cfg);

    //Register all components in the pipeline
    ESP_LOGI(TAG, "Register all elements to audio pipeline");
    audio_pipeline_register(*pipeline, fatfs_stream_reader, "fatfs");
    audio_pipeline_register(*pipeline, mp3_decoder, "mp3");
    audio_pipeline_register(*pipeline, i2s_stream_writer, "i2s");

    //Link the audio components in the right order.
    // our order is:
    // 1. Receive mp3 data using http stream
    // 2. Decode that mp3 data using our mp3 decoder.
    // 3. Send the decoded mp3 data to our i2s chip to play
    ESP_LOGI(TAG, "Link audio elements to pipeline fatfs-->mp3_decoder-->i2s_stream-->[codec_chip]");
    const char *link_tag[3] = {"fatfs", "mp3", "i2s"};
    audio_pipeline_link(*pipeline, &link_tag[0], 3);

    ESP_LOGI(TAG, "Done initializing");
}


void timesource_settarget(audio_pipeline_handle_t *pipeline, char *target)
{
    ESP_LOGI(TAG, "Stopping pipeline");
    audio_pipeline_stop(*pipeline);
    audio_pipeline_wait_for_stop(*pipeline);

    ESP_LOGI(TAG, "Resetting ringbuffer");
    audio_pipeline_reset_ringbuffer(*pipeline);
    ESP_LOGI(TAG, "Resetting elements");
    audio_pipeline_reset_elements(*pipeline);
    ESP_LOGI(TAG, "Resetting states");
    audio_pipeline_reset_items_state(*pipeline);

    ESP_LOGI(TAG, "Setting new URL");
    audio_element_set_uri(fatfs_stream_reader, target);
    ESP_LOGI(TAG, "playing %s", target);

    ESP_LOGI(TAG, "Restarting pipeline");
    audio_pipeline_run(*pipeline);
    ESP_LOGI(TAG, "Done restarting pipeline");
}

void timesource_destroy(audio_pipeline_handle_t *pipeline)
{
    ESP_LOGI(TAG, "Stopping pipeline.");
    audio_pipeline_stop(*pipeline);
    audio_pipeline_wait_for_stop(*pipeline);

    ESP_LOGI(TAG, "Unregistering audio ");
    audio_pipeline_unregister(*pipeline, fatfs_stream_reader);
    audio_pipeline_unregister(*pipeline, i2s_stream_writer);
    audio_pipeline_unregister(*pipeline, mp3_decoder);

    ESP_LOGI(TAG, "Deinitializing audio elements");
    audio_element_deinit(fatfs_stream_reader);
    audio_element_deinit(i2s_stream_writer);
    audio_element_deinit(mp3_decoder);
    ESP_LOGI(TAG, "Destroyed elements in pipeline");
}