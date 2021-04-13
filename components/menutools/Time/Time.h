#ifndef SMARTSPEAKER_TIME_H
#define SMARTSPEAKER_TIME_H


void timeInit();

void getTime();

void setTime();

void getZone(char *tz, char *Code);

void initializeSntp(void);

void playTime();

#endif //SMARTSPEAKER_TIME_H
