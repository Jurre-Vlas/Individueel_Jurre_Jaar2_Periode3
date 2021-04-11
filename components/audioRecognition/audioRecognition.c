#include "audioRecognition.h"
#include <math.h>
void configureGoertzel();
void recognizeAudio(int16_t *raw_buff);
void goertzel_callback(goertzel_data_t* filter, float result);

goertzel_data_t** goertzel_filt;

void audioRecognition_init() {
    audiocontroller_setSource(2);
    audiocontroller_setTarget(recognizeAudio);
    configureGoertzel();
}

void recognizeAudio(int16_t *raw_buff) {
    //ESP_LOGI("RAW","[xx] reading goertzeling");
    //ESP_LOGI("RAW", "Raw data recieved: %d", *raw_buff);
    goertzel_proces(goertzel_filt, GOERTZEL_N_DETECTION,raw_buff,GOERTZEL_BUFFER_LENGTH * sizeof(short));
}

void configureGoertzel() {
    goertzel_filt = goertzel_malloc(GOERTZEL_N_DETECTION);
    for(int i = 0;i<GOERTZEL_N_DETECTION;i++){
        goertzel_data_t* currFilter = goertzel_filt[i];
        currFilter->samples= GOERTZEL_BUFFER_LENGTH;
        currFilter->sample_rate = GOERTZEL_SAMPLE_RATE_HZ;
        currFilter->target_frequency = GOERTZEL_DETECT_FREQUENCIES[i];
        currFilter->goertzel_cb = goertzel_callback;
    }
    goertzel_init_configs(goertzel_filt,GOERTZEL_N_DETECTION);
    float prev = 0.0;
    int error = 1;
    int16_t *raw_buff = (int16_t *)malloc(GOERTZEL_BUFFER_LENGTH * sizeof(short));

    if(raw_buff == NULL){
        error = 0;
    }
}
//TODO: create processing of data instead pf thos
void goertzel_callback(goertzel_data_t* filter, float result) {
    float logVal = 10.0f*log10f(result);
   if(logVal > 33.0f)ESP_LOGI("RAW ", "target: %d db: %f", filter->target_frequency,logVal);
}