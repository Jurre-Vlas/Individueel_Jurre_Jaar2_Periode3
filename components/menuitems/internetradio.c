//
// Created by Davy on 15-3-2021.
//
#include "internetradio.h"


static int size = 8;

static const char *TAG = "Internetradio";

static MenuItem menuItems[] = {
        {"NPO Radio 1", "NPO Radio 1", &NPORadio1},
        {"NPO Radio 2", "NPO Radio 2",&NPORadio2},
        {"NPO 3FM","NPO 3FM", &NPO3FM},
        {"Radio 10", "Radio 10",&RADIO10},
        {"QMusic","QMusic", &QMusic},
        {"Sky Radio", "Sky Radio",&SkyRadio},
        {"Radio 538 ", "Radio 538 ", &Radio538},
        {"Return", "Terug", &returnFromIR}};


void launchInternetRadioMenu() {
    audiocontroller_setSource(0);
    setMenu(menuItems, size, "| Select a radio |", "| Kies een radio |");
    ESP_LOGD(TAG, "audio controller set source");
    
}

void NPORadio1(){
    ESP_LOGI("NPORADIO1", "Liedje afspelen:)");
    ESP_LOGD("IR", "audio controller set target");
    audiocontroller_setTarget("http://icecast.omroep.nl/radio1-bb-mp3");
}

void NPORadio2(){
    ESP_LOGI("NPORADIO2", "Liedje afspelen:)");
    
    audiocontroller_setTarget("http://icecast.omroep.nl/radio2-bb-mp3");
}

void NPO3FM(){
    ESP_LOGI("NPO3FM", "Liedje afspelen:)");
    
    audiocontroller_setTarget("http://icecast.omroep.nl/3fm-bb-mp3");
}

void RADIO10(){
    ESP_LOGI("RADIO10", "Liedje afspelen:)");
    
    audiocontroller_setTarget("http://21263.live.streamtheworld.com/RADIO10.mp3");
}

void QMusic(){
    ESP_LOGI("QMusic", "Liedje afspelen:)");
    
    audiocontroller_setTarget("http://icecast-qmusicnl-cdp.triple-it.nl/Qmusic_nl_live_96.mp3");
}

void SkyRadio(){
    ESP_LOGI("SkyRadio", "Liedje afspelen:)");
    
    audiocontroller_setTarget("http://19993.live.streamtheworld.com/SKYRADIO.mp3");
}

void Radio538(){
    ESP_LOGI("Radio538", "Liedje afspelen:)");
    
    audiocontroller_setTarget("http://20403.live.streamtheworld.com/RADIO538.mp3");
}

void returnFromIR(){
    ESP_LOGI("RETURN", "RETURN");
    //DON'T FORGET TO TERMINATE ALL METHODS HERE.
    launchHomeMenu();
}