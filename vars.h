#ifndef VARS_h
#define VARS_h

#include <stdint.h>
#include <stdbool.h>


extern int MON_P22;
extern bool UPDATING;

extern bool MqttUp;
extern bool MsgOK;

struct VARSFILT_T{
int count;
int V1;
int I1;
int P1;
int WHT;
int WHD;
};
extern struct VARSFILT_T VarsFilt;

struct MQTTDATA_T {
  float realpower;
  float apparentPower;
  float powerFactor;
  float supplyVoltage;
  float Irms;

  int WHourT;
 
  int WHourDay;

  bool MsgOK;

  
};

extern struct MQTTDATA_T mqttData;




#endif
