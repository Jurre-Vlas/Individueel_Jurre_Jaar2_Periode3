//
// Created by Davy on 17-3-2021.
//
#include "time.h"

#define SDA_GPIO 18
#define SCL_GPIO 23
#define I2C_ADDR 0x27

void initialize_sntp(void);

static const char *TAG = "Time";
static int started = 0;
struct tm timeinfo = {0};
char strftime_buf[64];
time_t now = 0;
char* hour;
char* min;
int SorWTime = 0;

void time_init() {
        initialize_sntp();
        // wait for time to be set
        int retry = 0;
        int retry_count = 10;
        while (sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET && ++retry < retry_count) {
            printf("Waiting for system time to be set... (%d/%d) \n", retry, retry_count);
            vTaskDelay(2000 / portTICK_PERIOD_MS);
        }
}

void setLocalSummerTime(){
    SorWTime = 0;
};

void setLocalWinterTime(){
    SorWTime = 1;
};

static char hour_arr[12][40] ={
        "12",
        "1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "10",
        "11",
};

static char min_arr[4][40] ={
        "uur",
        "kwart over",
        "half",
        "kwart voor",
};

char *substr(const char *src, int m, int n) {
    // get length of the destination string
    int len = n - m;

    // allocate (len + 1) chars for destination (+1 for extra null character)
    char *dest = (char *) malloc(sizeof(char) * (len + 1));

    // extracts characters between m'th and n'th index from source string
    // and copy them into the destination string
    for (int i = m; i < n && (*(src + i) != '\0'); i++) {
        *dest = *(src + i);
        dest++;
    }

    // null-terminate the destination string
    *dest = '\0';

    // return the destination string
    return dest - len;
}

void getTime() {
    //ESP_LOGI("@#@#@# The current winter or summer time is : ", "%i", SorWTime);


    if(!SorWTime) {
        time(&now);
        setenv("TZ", "CET-1CEST,M3.5.0,M10.5.0/3", 1);
        tzset();
        localtime_r(&now, &timeinfo);
        strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);

        vTaskDelay(30 / portTICK_PERIOD_MS);
        char *dest = substr(strftime_buf, 11, 20);
        vTaskDelay(30 / portTICK_PERIOD_MS);
        char *dest2 = substr(strftime_buf, 0, 4);

        writeToLineAndCol(dest2, 0, 0);

        vTaskDelay(30 / portTICK_PERIOD_MS);

        writeToLineAndCol(dest, 0, 4);

        hour = substr(strftime_buf, 11, 13);

        min = substr(strftime_buf, 14, 16);


//    ESP_LOGI("DEST1", "%s", dest);
//    vTaskDelay(30 / portTICK_PERIOD_MS);
        ESP_LOGI("DEST2", "%s", hour);
        ESP_LOGI("DEST3", "%s", min);
    }

    if(SorWTime) {
        time(&now);

        setenv("TZ", "MET-2METDST,M3.5.0/01,M10.5.0/0", 1);
        tzset();
        localtime_r(&now, &timeinfo);
        strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);

        vTaskDelay(30 / portTICK_PERIOD_MS);
        char *dest = substr(strftime_buf, 11, 20);
        vTaskDelay(30 / portTICK_PERIOD_MS);
        char *dest2 = substr(strftime_buf, 0, 4);

        writeToLineAndCol(dest2, 0, 0);

        vTaskDelay(30 / portTICK_PERIOD_MS);

        writeToLineAndCol(dest, 0, 4);

        hour = substr(strftime_buf, 11, 13);

        min = substr(strftime_buf, 14, 16);


//    ESP_LOGI("DEST1", "%s", dest);
//    vTaskDelay(30 / portTICK_PERIOD_MS);
        ESP_LOGI("DEST2", "%s", hour);
        ESP_LOGI("DEST3", "%s", min);

        play_time();
    }

    play_time();

}


void initialize_sntp(void) {
    ESP_LOGI(TAG, "Initializing SNTP");
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_init();
}

void play_time(){
    int hour_int = atoi(hour);
    int min_int = atoi(min);

    if (hour_int >= 12) {
        hour_int -= 12;
    }

    char *hour_file = hour_arr[hour_int];

    ESP_LOGI("HOUR", "%s", hour_file);

    char *min_file = "";
    if ((min_int >= 53 && min_int <= 59) || (min_int >= 0 && min_int < 07)){
        min_file = min_arr[0];
    } else if (min_int >= 07 && min_int <= 22){
        min_file = min_arr[1];
    } else if (min_int >= 23 && min_int <= 37){
        min_file = min_arr[2];
    } else if (min_int >= 38 && min_int <= 52){
        min_file = min_arr[3];
    }

    ESP_LOGI("MINUTE", "%s", min_file);

}


