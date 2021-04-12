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
char *hour;
char *min;

char *TimeZone;
char *Location;

int SorWTime = 0;

void time_init()
{
    initialize_sntp();
    // wait for time to be set
    int retry = 0;
    int retry_count = 10;
    while (sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET && ++retry < retry_count)
    {
        printf("Waiting for system time to be set... (%d/%d) \n", retry, retry_count);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }

    getZone("TZ", "CET-1CEST,M3.5.0,M10.5.0/3" );
    getTime();
}

void setLocalSummerTime()
{
    SorWTime = 0;
};

void setLocalWinterTime()
{
    SorWTime = 1;
};

static char itis_loc[40] = {
    "/sdcard/res/itis.mp3"};

static char hour_arr[12][40] = {
    "/sdcard/res/12.mp3", // 12
    "/sdcard/res/1.mp3",  // 1
    "/sdcard/res/2.mp3",  // 2
    "/sdcard/res/3.mp3",  // 3
    "/sdcard/res/4.mp3",  // 4
    "/sdcard/res/5.mp3",  // 5
    "/sdcard/res/6.mp3",  // 6
    "/sdcard/res/7.mp3",  // 7
    "/sdcard/res/8.mp3",  // 8
    "/sdcard/res/9.mp3",  // 9
    "/sdcard/res/10.mp3", // 10
    "/sdcard/res/11.mp3", // 11
};

static char min_arr[4][40] = {
    "/sdcard/res/uur.mp3",  // Uur
    "/sdcard/res/kwO.mp3",  // Kwart over
    "/sdcard/res/half.mp3", // Half
    "/sdcard/res/kwV.mp3",  // Kwart voor
};

char *substr(const char *src, int m, int n)
{
    // get length of the destination string
    int len = n - m;

    // allocate (len + 1) chars for destination (+1 for extra null character)
    char *dest = (char *)malloc(sizeof(char) * (len + 1));

    // extracts characters between m'th and n'th index from source string
    // and copy them into the destination string
    for (int i = m; i < n && (*(src + i) != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }

    // null-terminate the destination string
    *dest = '\0';

    // return the destination string
    return dest - len;
}

char *dest_buff = "";
char *dest2_buff = "";
char hourPlayed[4] = "";
int firstRun = 1;

void getZone(char *tz, char *Code ){
    TimeZone = tz;
    Location = Code;
}

void getTime()
{
        time(&now);
        setenv(TimeZone, Location, 1);
        tzset();
        localtime_r(&now, &timeinfo);
        strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);

        vTaskDelay(30 / portTICK_PERIOD_MS);
        char *dest = substr(strftime_buf, 11, 20);
        vTaskDelay(30 / portTICK_PERIOD_MS);
        char *dest2 = substr(strftime_buf, 0, 4);

        if (strcmp(dest2, dest2_buff) != 0)
        {
            writeToLineAndCol(dest2, 0, 0);
            dest2_buff = dest2;
        }

        vTaskDelay(30 / portTICK_PERIOD_MS);

        if (strcmp(dest, dest_buff) != 0)
        {
            writeToLineAndCol(dest, 0, 4);
            dest_buff = dest;
        }
        hour = substr(strftime_buf, 11, 13);

        min = substr(strftime_buf, 14, 16);


    if (strcmp(hourPlayed, hour))
    {
        strcpy(hourPlayed, hour);
        if (firstRun)
        {
            firstRun = 0;
        }
        else
        {
            play_time();
        }
    }
}

void initialize_sntp(void)
{
    ESP_LOGI(TAG, "Initializing SNTP");
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_init();
}

void play_time()
{
    int hour_int = atoi(hour);
    int min_int = atoi(min);
    int flip2and3 = 0;
    char playQueue[3][40] = {
        "",
        "",
        ""};

    if (hour_int >= 12)
    {
        hour_int -= 12;
    }

    char *min_file = "";
    if ((min_int >= 53 && min_int <= 59))
    {
        min_file = min_arr[0];
        flip2and3 = 1;
        if (hour_int == 11)
        {
            hour_int = 0;
        }
        else
        {
            hour_int += 1;
        }
    }
    else if (min_int >= 0 && min_int < 07)
    {
        min_file = min_arr[0];
        flip2and3 = 1;
    }
    else if (min_int >= 07 && min_int <= 22)
    {
        min_file = min_arr[1];
    }
    else if (min_int >= 23 && min_int <= 37)
    {
        min_file = min_arr[2];
        if (hour_int == 11)
        {
            hour_int = 0;
        }
        else
        {
            hour_int += 1;
        }
    }
    else if (min_int >= 38 && min_int <= 52)
    {
        min_file = min_arr[3];
        if (hour_int == 11)
        {
            hour_int = 0;
        }
        else
        {
            hour_int += 1;
        }
    }

    char *hour_file = hour_arr[hour_int];

    //Construct queue

    int wait1 = 1500;
    int wait2 = 1500;
    int wait3 = 1500;
    if (flip2and3)
    {
        strcpy(playQueue[0], itis_loc);
        wait1 = 1500;
        strcpy(playQueue[1], hour_file);
        wait2 = 550;
        strcpy(playQueue[2], min_file);
        wait3 = 1150;
    }
    else
    {
        strcpy(playQueue[0], itis_loc);
        wait1 = 1500;
        strcpy(playQueue[1], min_file);
        wait2 = 1150;
        strcpy(playQueue[2], hour_file);
        wait3 = 550;
    }

    ESP_LOGI(TAG, "0 %s", playQueue[0]);
    ESP_LOGI(TAG, "1 %s", playQueue[1]);
    ESP_LOGI(TAG, "2 %s", playQueue[2]);

    audiocontroller_setSource(4);
    audiocontroller_setTarget(playQueue[0]);
    vTaskDelay(wait1 / portTICK_PERIOD_MS);
    audiocontroller_setTarget(playQueue[1]);
    vTaskDelay(wait2 / portTICK_PERIOD_MS);
    audiocontroller_setTarget(playQueue[2]);
    vTaskDelay(wait3 / portTICK_PERIOD_MS);
    audiocontroller_setSource(3);
}
