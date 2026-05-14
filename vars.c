#include "vars.h"


bool MqttUp=0;
bool MsgOK=0;

struct VARSFILT_T VarsFilt;

struct MQTTDATA_T mqttData;

double Vcal=  0.180976272099; //0.22441316;  //0.22536768;            //0.22815;              //0.24374749;
double Ical =  0.028410384807;  //0.010669513*2;   // 0.011307;              //0.009014588;