#include "audioController.h"

#define DEFAULT_SOURCE 0;

static const char *TAG = "AudioController";

static esp_periph_set_handle_t *peripherals_poolPtr;
static audio_pipeline_handle_t pipeline;

static unsigned int sourceIndex = 0;
static unsigned int pipelineHasItems = 0;

static inputSource inputSources[] = {
    {"HTTP",
     &httpstream_init,
     &httpstream_settarget,
     &httpstream_destroy},
    {"WhiteNoise",
     &whitenoise_init,
     &whitenoise_settarget,
     &whitenoise_destroy},
    {"Raw",
     &rawStream_init,
     &rawStream_settarget,
     &rawStream_destroy},
    {"MP3",
     &mp3_init,
     &mp3_settarget,
     &mp3_destroy},
     {"Time",
     &timesource_init,
     &timesource_settarget,
     &timesource_destroy}};

void audiocontroller_init(esp_periph_set_handle_t * setPtr)
{
    peripherals_poolPtr = setPtr;

    // Initialize audio chip
    ESP_LOGI(TAG, "Start audio codec chip");
    audio_board_handle_t board_handle = audio_board_init();
    audio_hal_ctrl_codec(board_handle->audio_hal, AUDIO_HAL_CODEC_MODE_DECODE, AUDIO_HAL_CTRL_START);

    // Configure audio pipeline
    ESP_LOGI(TAG, "Create audio pipeline for playback");
    audio_pipeline_cfg_t pipeline_cfg = DEFAULT_AUDIO_PIPELINE_CONFIG();
    pipeline = audio_pipeline_init(&pipeline_cfg);
    mem_assert(pipeline);

    // TODO EVENT LISTENING
}

void audiocontroller_destroy()
{
    ESP_LOGI(TAG, "Destroying input source");
    if (pipelineHasItems)
        (*inputSources[sourceIndex].destroy)(&pipeline);
    pipelineHasItems = 0;
}

void audiocontroller_setTarget(void* callback)
{
    ESP_LOGI(TAG, "Set target on input source");
    (*inputSources[sourceIndex].settarget)(&pipeline, callback);
}

void audiocontroller_setSource(unsigned int id)
{
    ESP_LOGI(TAG, "Changing input source");
    if (pipelineHasItems)
        (*inputSources[sourceIndex].destroy)(&pipeline);
    sourceIndex = id;
    if (inputSources[sourceIndex].init == NULL){
    sourceIndex = 0;
    }
    else
    ESP_LOGI(TAG, "starting new pipeline");
    (*inputSources[sourceIndex].init)(&pipeline);
    pipelineHasItems = 1;
}