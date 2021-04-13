#include "time.h"

#define SDA_GPIO 18
#define SCL_GPIO 23
#define I2C_ADDR 0x27


static const char *TAG = "Time";

struct tm timeinfo = {0};
char strfTimeBuf[64];
time_t now = 0;
char *hour;
char *min;

char *TimeZone;
char *Location;


int setNewTime = 0;

void timeInit()
{
    initializeSntp();
    // wait for time to be set
    int retry = 0;
    int retryCount = 10;
    while (sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET && ++retry < retryCount)
    {
        printf("Waiting for system time to be set... (%d/%d) \n", retry, retryCount);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
    getZone("TZ", "CET-1CEST,M3.5.0,M10.5.0/3" );
    getTime();
}

static char itIsLoc[40] = {
    "/sdcard/res/itis.mp3"};

static char hourArr[12][40] = {
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


static char minArr[4][40] = {
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

char *destBuff = "";
char *dest2Buff = "";
char hourPlayed[4] = "";
int firstRun = 1;


void getZone(char *tz, char *Code ){
    setNewTime = 1;
    vTaskDelay(100 / portTICK_PERIOD_MS);
    TimeZone = tz;
    Location = Code;
    setNewTime = 0;

}


void getTime()
{
    if (!setNewTime) {
        time(&now);
        setenv(TimeZone, Location, 1);
        tzset();

        localtime_r(&now, &timeinfo);
        strftime(strfTimeBuf, sizeof(strfTimeBuf), "%c", &timeinfo);


        vTaskDelay(30 / portTICK_PERIOD_MS);
        char *dest = substr(strfTimeBuf, 11, 20);
        vTaskDelay(30 / portTICK_PERIOD_MS);
        char *dest2 = substr(strfTimeBuf, 0, 4);

        if (strcmp(dest2, dest2Buff) != 0) {
            writeToLineAndCol(dest2, 0, 0);
            dest2Buff = dest2;
        }

        vTaskDelay(30 / portTICK_PERIOD_MS);

        if (strcmp(dest, destBuff) != 0) {
            writeToLineAndCol(dest, 0, 4);
            destBuff = dest;
        }
        hour = substr(strfTimeBuf, 11, 13);

        min = substr(strfTimeBuf, 14, 16);

        printf("min");
    }
}

void initializeSntp(void)
{
    ESP_LOGI(TAG, "Initializing SNTP");
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_init();
}

void playTime()
{
    int hourInt = atoi(hour);
    int minInt = atoi(min);
    int flip2and3 = 0;
    char playQueue[3][40] = {
        "",
        "",
        ""};

    if (hourInt >= 12)
    {
        hourInt -= 12;
    }

    char *minFile = "";
    if ((minInt >= 53 && minInt <= 59))
    {
        minFile = minArr[0];
        flip2and3 = 1;
        if (hourInt == 11)
        {
            hourInt = 0;
        }
        else
        {
            hourInt += 1;
        }
    }
    else if (minInt >= 0 && minInt < 07)
    {
        minFile = minArr[0];
        flip2and3 = 1;
    }
    else if (minInt >= 07 && minInt <= 22)
    {
        minFile = minArr[1];
    }
    else if (minInt >= 23 && minInt <= 37)
    {
        minFile = minArr[2];
        if (hourInt == 11)
        {
            hourInt = 0;
        }
        else
        {
            hourInt += 1;
        }
    }
    else if (minInt >= 38 && minInt <= 52)
    {
        minFile = minArr[3];
        if (hourInt == 11)
        {
            hourInt = 0;
        }
        else
        {
            hourInt += 1;
        }
    }

    char *hourFile = hourArr[hourInt];

    //Construct queue

    int wait1 = 1500;
    int wait2 = 1500;
    int wait3 = 1500;

    if (flip2and3)
    {
        strcpy(playQueue[0], itIsLoc);
        wait1 = 1500;
        strcpy(playQueue[1], hourFile);
        wait2 = 550;
        strcpy(playQueue[2], minFile);
        wait3 = 1150;
    }
        else
        {
            strcpy(playQueue[0], itIsLoc);
        wait1 = 1500;
        strcpy(playQueue[1], minFile);
        wait2 = 1150;
        strcpy(playQueue[2], hourFile);
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
