#include <ArduinoJson.h>

int dStatus = 0;
int mStatus = 0;
int currentSpeed = 0;
int targetSpeed = 0;
int speedChangeRate = 10;
StaticJsonDocument<1024> jsonDoc;