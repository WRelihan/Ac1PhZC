
#include "secrets.h"
//char version[]="Ac1PhZC3";

#include "version.h"
/////////////////////////////////
////////  Elegant OTA  //////////
////  10.0.0.1xxx:8xxx/update ///
/////////////////////////////////
#define ACMON2


// AC1PhZC3     -  Try to use Github and claude
//                  update adc channels to corespond to ESP32 Power board
// AC1PhZC2     -  put interrupt code
// AC1PhZC1     -  Try to see if hardware interrupt for zero cross works better

// Ac1PhMon52   - try to do 200 samples per cycle (up from 166)
//              -   Seems to work lekka

//  Ac1PhMon51  -  Try to save a current and voltage waveform.
//              -  works lekka.  Req new waveform for voltage and current with button in node-red


//  Ac1PhMon50  -  try to do EmonWar with integer Accumulation to 1 sec scale
//              -  Seems to work lekka


//  Ac1PhMon48  -  Change to ELEGANT OTA 
//              -  Wifi as per Heater with callbacks, multi processor etc

//////  NOT YET CHANGED TO ELEGANT OTA !!!!!!!!!!!  ////
//  Ac1PhMon47  - CHANGE IP  ADRESS TO 10.0.0.51:8151  FROM 10.0.0.151:8151
//              -  Also add RelihanMesh to wifiMulti
//  Ac1PhMon46  - CHANGE MQTT SERVER TO 10.0.0.80


//  Ac1PhMon45  - remove timer start when mqtt goes down, as the timer  was never "XtimerCreated"
//              -  Restart mqtt if it is down in the 1 per sec loop
// Ac1PhMon44   - subscribe to reset
// Ac1PhMon43   - add remote reset on page
// Ac1PhMon42   -  Add total WH to JSON
// Ac1PhMon41   - clean up unused variables
//              - Added filtering on Json Data

//Ac1PhMon40    - change to UBserve

//Ac1PhMon36    - add kwH for the day to Json
//Ac1PhMon35    -  put data in Json

//Ac1PhMon30    -   add MQTT

//===============================

// Ac1PhMon22     - send response to ----server.on("/ACstat",ACstatSend);

// Ac1PhMon21     -   fixup viewport to resize
//                    fixup orange line

/// Ac1PhMon20    -  change bar graph  color to blue

/// Ac1PhMon19    -   change data to 144 samples i.e.  10min -> 6*24=144

/// Ac1PhMon18    -   fix bargraph display

/// Ac1PhMon17    - plot kwh in 12 min steps on bar graph
///               -  must detect last bargraph -  make a negative fault value

///  Ac1PhMon16 -  detect mains fail/load shedding
///                  - update graph in sections out1 is basic graph that does not change
///                   - Show in orange where load shedding is

/// Ac1PhMon15  - write Access Point name in WEB TABLE

/// Ac1PhMon14  - use MultiWifi


/// Ac1PhMon13b   - Try to disable sampling etc during update

/// Ac1PhMon13   - Try adding something for OTA update - add RSSi
//              - does not reset to new code???

//  Ac1PhMon12   - Do OTA update ---
//                =============  HOW TO UPDATE ======
//                10.0.0.151:8151/serverIndex
//                choose file & upload
//                GIVE TIME TO UPDATE
//                call site again normally
//                ====================================



////  Ac1PhMon12 - do OTA update
//
/// Ac1PhMon11  - copy from Ac1PhMon1 -  try to get freq acurate
/// call in tmr interupt

/// Ac1PhMon1   - coppy from TmrIntAD60F --------------
//=============================================================

/// TmrIntAD6  -  do sqV calc, get Pos and Neg Pk etc
/// TmrIntAD7  -  use fixed point to get average DC value of waveform - works fine
/// TmrIntAD8 -  calculate rms at end of cycle -- works fine
/// TmrIntAD9 -  filter Vrms value over 1 sec  - 50 cycles
///           -   check sqV for no mains detection
/// TmrIntAD10- do current processing -  works fine
/// TmrIntAD11 - do power calculations V * I
/// TmrIntAD12  - calc aparent power Vrms * Irms, Calc Power factor


/// TmrIntAD20  -    Try writing it as a class - works ok
/// TmrIntAD21  -  Calculate Freq

/// TmrIntAD30  - Add webserver for displaying values - works ok
/// TmrIntAD31  -  Ad ADCAL procedure (check ADcal1 sketch) - works ok
///                 check some way for detecting no power : Try zcCount in EmonWar to check
///                 for multiple zero crossings in 50Hz waveform.
///                 also check if sqV < 10000 -> set NoMains = 1 -> zero variables
/// TmrIntAD32  -  add switchable WiFi settings
///             -   Disable WiFi connect while doing tests on sensors
/// TmrIntAD33  -   calc kwh values : wsec calculated - seems ok
/// TmrIntAD34  -   calc whour every second from wsec
///                 Use Whour in 20Q12 format to keep a decimal value
///                 Use WSec20Q12 to keep remainder of div(3600) and + wsec<<12
///                 Seems to work ok
/// TmrIntAD35  -   Use #include "TmrClk.h" for doing timer interrupt - works fine
///             -  Test Wh  :722W heater :        esp32             kwH Meter       % esp32/kwhmeter
///                               Load:         1Hr 722.91Wh          702           +2.978%
///                                Gen:         1Hr   716.1Wh         693           3.333% ??
///             -      kwH meter not fine enough to read Wh
///             -----  Accuracy OK.  Later try find better cal ref for V & I
/// TmrIntAD36  -   Find out how graphs work
///             -   Added drawGraph2 procedure to draw bar graphs of energy usage
/// TmrIntAD37  -   Use real data to show on Graph works fine
///             -   put in box and try out -- works fine adjust Vcal somewhat
/// TmrIntAD38  -   Add KWh for day line graph    -- works fine, to many points
/// TmrIntAD39  -  Change whHourly10 to 120 points, i.e every 12 minutes a point
///             -   Make the y values autoscale if it reach the graph limmits
/// TmrIntAD40  -   Put axis scaling on the graph

/// TmrIntAD50  -   Try putting NPTsimple in the code  - works  somewhat
/// TmrIntAD51  -   Set NTP time update once a day, retry for 10 sec if not successfull. - works ok
/// TmrIntAD52  -   whDays array to keep the last days consumption
///             -   format html to display data in tables
/// TmrIntAD53  -   Display last few days usage
///             -  Make Isense R = 50 ohm for larger power msrmnts. change Iscale 
/// TmrIntAD54  -   Change typecasting when working out wHourT and wHourDay
///             -   Add a display for WhourlyZ
///             - change  time to go over 0:00 in 15min
///             - change time again at 0:15:00 to 23:45:00 to simulate quick day
///             - Display time err when NTP update occurs
/// TmrIntAD55  - Change  daily time update to 00:30:00 
///             - add a correction every hour after NTP update
///             -  Add a lockout on the hour to update and correct only once on half hour
///             - PROBLEM: hour graph shows next hour data , random value??
///             - set hourly data to zero again at midnight
///             -  have a lockout so that can only go once a day through zero code - DayZero


/// TmrIntAD60  - Print output in CSV format for importing into excel
/// TmrIntAD60b -  include some features like TimeOK
///             - include graph not return to zero line always
/// TmrIntAD60c - reset scales at 0:00:00
/// TmrIntAD60d -  change voltage scale 238.9/240.99
/// TmrIntAD60E -  change port to 8151 for port forwarding
/// TmrIntAD60F-  change to new router 
//==================== RENAME =============================

/// Ac1PhMon1   - coppy from TmrIntAD60F --------------


#include "EmonWar.h"      // include Emon library
#include "vars.h"
#include <WiFi.h>
#include "esp32/rom/rtc.h"

//#include <WiFiMulti.h>
extern "C" {
  #include "freertos/FreeRTOS.h"
  #include "freertos/timers.h"
}

#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

#include <driver/adc.h>

#include "time.h"
#include "TmrClk.h"

#include <AsyncMqttClient.h>
#include <ArduinoJson.h>

//#include <ESP8266WiFiMulti.h>
//#include <WiFiClient.h>
//#include <WebServer.h>
//#include <ESPmDNS.h>
//#include <Update.h>
//#include <esp_task_wdt.h>

///=====================================  WiFi credentials ========================
//#define HOMEWIFI
#define TIMENTP
//#define QUICKDAY

//#define WIFIDISABLE

#ifdef ACMON2

const char* ssid = SECRET_WIFI_SSID;
const char* password = SECRET_WIFI_PASSWORD;
IPAddress ip(10,0,0,61);         //CHANGED FROM 151
IPAddress gateway(10,0,0,254);
IPAddress subnet(255,255,255,0);
IPAddress DNS(8,8,8,8);
int PortNr=8161;



#else
// WiFi Parameters

const char* ssid = SECRET_WIFI_SSID;
const char* password = SECRET_WIFI_PASSWORD;
IPAddress ip(10,0,0,51);         //CHANGED FROM 151
IPAddress gateway(10,0,0,254);   
IPAddress subnet(255,255,255,0);
IPAddress DNS(8,8,8,8);      
int PortNr=8151;
#endif
//-----------------------------------------------------------------------------------

// ============ MQTT BROKER STUFF ===========

#define UBServe

#ifdef UBServe
#define MQTT_HOST SECRET_MQTT_HOST_UBSERVE
#define MQTT_PORT SECRET_MQTT_PORT_UBSERVE
#define BROKER_USER SECRET_BROKER_USER_UBSERVE
#define BROKER_PASS SECRET_BROKER_PASS_UBSERVE


#else

#define MQTT_HOST SECRET_MQTT_HOST_ALT
#define MQTT_PORT SECRET_MQTT_PORT_ALT
#define BROKER_USER SECRET_BROKER_USER_ALT
#define BROKER_PASS SECRET_BROKER_PASS_ALT
#endif

//MQTT Topics
#ifdef ACMON2
#define MQTT_MNS_JSON "MNS2/JSON"
#define MQTT_WAVE_JSON "MNS2/WAVE"
#define MQTT_PUB_SUB_RST "MNS2/RST"
#define MQTT_PUB_SUB_WVR "MNS2/WVR"


#else

#define MQTT_MNS_JSON "MNS/JSON"
#define MQTT_WAVE_JSON "MNS/WAVE"
#define MQTT_PUB_SUB_RST "MNS/RST"
#define MQTT_PUB_SUB_WVR "MNS/WVR"
#endif



#define WAVE_JSON_SIZE  (CYCLE_SAMPLES * 24 + 64)  // 24 bytes per sample pair + overhead
//---------------------------------------
//==========  INSTANTIATIONS =======================
AsyncMqttClient mqttClient;
AsyncWebServer server (PortNr);
EMonitor emon1;           // create an instance

TimerHandle_t mqttReconnectTimer;
TimerHandle_t wifiReconnectTimer;
portMUX_TYPE mqttMux = portMUX_INITIALIZER_UNLOCKED;
//--------------------------------------------------

//=============== FUNCTION PROTOTYPES =============
void connectToMqtt();
void MQTTUPDATE(MQTTDATA_T d);
void MQTTWAVE(EMonitor &emon);



void onMqttPublish(uint16_t packetId);
void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);
void onMqttSubscribe(uint16_t packetId, uint8_t qos);
void onMqttUnsubscribe(uint16_t packetId);
void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);
void onMqttConnect(bool sessionPresent);


//--------------------------------------------------

const uint32_t connectTimeoutMs = 10000;


int ClientLast=10;



char AcSTR[6];



//const char *ssid = "RSDMWiFi";
//const char *password = "rSdM5678";

//const char *ssid = "Vodacom-5EMMCW7";
//const char *password = "93539128";



/*
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600*2;
const int   daylightOffset_sec = 0;       //3600;

struct tm timeinfo;
*/
//WiFiMulti wifiMulti;
// WiFi connect timeout per AP. Increase when connecting takes longer.




//WebServer server(PortNr);

TaskHandle_t Task1;

byte mac[6];




#define ANALOG_PIN_0 36
#define ANALOG_PIN_3 39
#define I1z  14

#define ZERO_CROSSOVER 0X800-100
#define FREQ_CAL 80e6/TIMER_PRESCALE/TIMER_ALM
/*
#define NRSAMPLES 144
#define SAMPLESPERHOUR (int)NRSAMPLES/24
#define MINPERSAMPLE     10   //(int)(60/SAMPLESPERHOUR)
*/

int PubCnt=0;
int cntSec = 0;
int lastSec = 0;
int lastMin = 0;
int lastHour = 0;

unsigned long previousMillis = 0;   // Stores last time a message was published
unsigned long previous1SecMillis=0;
const long interval1s= 1000;
const long interval = 10000;        // Interval at which to publish values



int resetreason0=0;
int resetreason1=0;
int resetreason=0;


int LED_P21 =21;
bool toggle = 0;
bool toggle2 = 0;
bool timeUpdate = 0;
bool DayZero=1;

bool UPDATING=1;
bool Connected=0;
int timeUpdateTry=0;
int MON_P22 = 22;
int MON_P19 = 19;
int MON_P23 =23;

float realpower;
float apparentPower;
float powerFactor;
float supplyVoltage;
float Irms;
float Freq;
float WHourT;       // total WH
float WHourDay;     // WH for the day
float whHourlyZF;
long whHourlyZ=0;
long whHourly[24]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//long whDeltaMin10[120];
//long whMin10[NRSAMPLES];
//bool ACon10[NRSAMPLES];
bool AConNow;
long whDays[31];
long TimeErr=0;     // logg the timeErr when NTP time update occur
int whDaysIndex=0;
int GscaleHr= 1000;        //  250;            // start off with 500wh scale over (keep left digit 0)
int GscaleMin=1000;     //250;         // start of with 1000wh scale over graph y (keep left digit 0)
int graphInit=0;

int hourAdjVal = (13<<8)/24;
int hourAdjAcc=0;



//double Pcal =  Vcal* Ical;         //0.002588;
bool TimeOK=0;
bool webServerStarted = false;
int AcOnCnt=0;

/////////////////////
//=========================== FUNCTION DEFINITIONS ====================




void mqttTask(void *parameter)
{

  MQTTDATA_T local;
  bool localMsgOK;

  while(true)
  {
    portENTER_CRITICAL(&mqttMux);
    localMsgOK=MsgOK;
    if(localMsgOK) local = mqttData;
    MsgOK=false;
    portEXIT_CRITICAL(&mqttMux);
    if (localMsgOK)
      {
      MQTTUPDATE(local);
      }

    MQTTWAVE(emon1);        // add this - checks captureDone internally


    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

////////// -------   Reconnect Timers -----------
void WiFiReconnectTimerCallback(TimerHandle_t xTimer) {
    connectToWifi();
}

void MqttReconnectTimerCallback(TimerHandle_t xTimer) {
    connectToMqtt();
}

/////////--- WiFi Handlers -------------------------

void connectToWifi() {
    Serial.println("Connecting to WiFi...");
    if (!WiFi.config(ip, gateway, subnet, DNS)) {
    Serial.println("STA Failed to configure");
    }
    WiFi.setHostname("ACmon_ESP32");
    WiFi.begin(ssid, password);
}

void onWifiConnect(WiFiEvent_t event, WiFiEventInfo_t info) {
    Serial.println("WiFi connected");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    xTimerStop(wifiReconnectTimer, 0);

    //==============================================
    if (!webServerStarted) {
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) 
    {
        std::string responseMessage = "Hi! I am ESP32:" + std::string(VERSION);  
        request->send(200, "text/plain", responseMessage.c_str());
    });

    AsyncElegantOTA.begin(&server);
    server.begin();
    Serial.println("HTTP server started");

    webServerStarted = true;
}




    mqttClient.connect();
}

void onWifiDisconnect(WiFiEvent_t event, WiFiEventInfo_t info) {
    Serial.println("WiFi lost connection");

    MqttUp = 0;

    xTimerStop(mqttReconnectTimer, 0);
    xTimerStart(wifiReconnectTimer, 0);
}


///////////////-------------  MQTT handlers ----------

void connectToMqtt() {
  Serial.println("Connecting to MQTT...");
  mqttClient.connect();
}

void onMqttConnect(bool sessionPresent) {
  Serial.println("Connected to MQTT.");
  Serial.print("Session present: ");
  Serial.println(sessionPresent);
  MqttUp=1;
  digitalWrite(LED_BUILTIN, HIGH);
uint16_t packetIdSub;

   // packetIdSub = mqttClient.subscribe("HTR/TEMP", 2);   /// Reset pump timeout
   // packetIdSub = mqttClient.subscribe("HTR/TMR", 2);   /// Reset pump timeout
   // packetIdSub = mqttClient.subscribe("HTR/RST", 2);   /// Reset pump timeout
   // packetIdSub = mqttClient.subscribe("HTR/LVL", 2);   /// Heater Level
   packetIdSub = mqttClient.subscribe(MQTT_PUB_SUB_RST, 2);
   packetIdSub = mqttClient.subscribe(MQTT_PUB_SUB_WVR, 2);
 // Serial.print("Subscribing at QoS 2, packetId: ");
 // Serial.println(packetIdSub);
}




void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  Serial.println("Disconnected from MQTT.");
  Serial.printf(" Reason: %d\n",reason);

  Serial.printf(" Pubs: %d \n",PubCnt);
MqttUp=0;
digitalWrite(LED_BUILTIN, LOW);
/*
  if (WiFi.isConnected()) {
    xTimerStart(mqttReconnectTimer, 0);
  }
*/
 if (WiFi.status() == WL_CONNECTED) {
        xTimerStart(mqttReconnectTimer, 0);
    }

}




void onMqttSubscribe(uint16_t packetId, uint8_t qos) {
/*
  Serial.println("Subscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
  Serial.print("  qos: ");
  Serial.println(qos);
*/
}

void onMqttUnsubscribe(uint16_t packetId) {
  Serial.println("Unsubscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
  // Do whatever you want when you receive a message
 String receivedMessage;
 Serial.println();

  Serial.print(topic);
  Serial.print(":");

  for (int i = 0; i < len; i++) {
  
    Serial.print((char)payload[i]);
    receivedMessage += (char)payload[i];
  }
  Serial.println();
  // Turn the LED on or off accordingly to the message content
  if (strcmp(topic, MQTT_PUB_SUB_RST) == 0) 
  {

  if (receivedMessage == "Reset"){
      //digitalWrite(LED_BUILTIN, HIGH);
      emon1.Whour=0;
      whHourlyZ=0;
    }
  
  }

if (strcmp(topic, MQTT_PUB_SUB_WVR) == 0) {
    if (receivedMessage == "true"){
      //digitalWrite(LED_BUILTIN, HIGH);
      emon1.captureReq=true;
    }
    if (receivedMessage == "false"){
      //digitalWrite(LED_BUILTIN, LOW);
    }
  }


}

void onMqttPublish(uint16_t packetId) {
  //Serial.println("Publish acknowledged.");
  //Serial.print("  packetId: ");
  //Serial.println(packetId);
}





float getDayUse(int index)
  {
  long temp;
  float tempfloat;
  if(index>=1)
    {
    temp=whDays[index]-whDays[index-1];
    tempfloat =(float)temp/4096;
    /*
    Serial.print(whDays[index]);
    Serial.print("  ");
    Serial.print(whDays[index-1]);
    Serial.print("  ");
    Serial.print(temp);
    Serial.print("  -  ");
    Serial.print(tempfloat);
    Serial.println();
    */
    return( tempfloat); 
    } 
  else
    {
    return( float(0));    
    }
  }



/*
void printLocalTime()
{
  //struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}
*/


/////////////////////////////////////////////  SETUP //////////////////////////////////////////////////
 
void setup() {
  resetreason0=(int)(rtc_get_reset_reason(0));
  resetreason1=(int)(rtc_get_reset_reason(1));
  resetreason =  (resetreason1<<8) | resetreason0;

delay(1000);   // wait 1 sec for voltage to become stable

  double tempfloat;
  int tempInt;

 
  Serial.begin(115200);
  pinMode(LED_P21,OUTPUT);
  pinMode(MON_P22,OUTPUT);
  pinMode(MON_P23,OUTPUT);
  
  pinMode (LED_BUILTIN, OUTPUT);
  MqttUp=0;
  emon1.setup();
  emon1.voltage(ANALOG_PIN_3,Vcal);
  emon1.current(ANALOG_PIN_0,Ical,2020);
  //emon1.power(Pcal);
  emon1.wattsec(TIMER_ALM);
  emon1.monpin(MON_P19);
  emon1.freq(FREQ_CAL);
  emon1.attachZeroCross(I1z, MON_P23);

for(whDaysIndex=0;whDaysIndex<31;whDaysIndex++)
      {
       whDays[whDaysIndex]=0; 
      }
 whDaysIndex=3;
 /*
VarsFilt.count=0;
 VarsFilt.AcV=0;
 VarsFilt.AcA=0;
 VarsFilt.PRl=0;
*/ 
VarsFilt = {};  // reset cleanly
  
  TmrSetup();
  clocktime.sec=1;      // prevent reseting array
 
  mqttReconnectTimer = xTimerCreate("mqttTimer", pdMS_TO_TICKS(2000), pdFALSE, (void*)0, MqttReconnectTimerCallback);
  wifiReconnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(2000), pdFALSE, (void*)0, WiFiReconnectTimerCallback);

  WiFi.onEvent(onWifiConnect, ARDUINO_EVENT_WIFI_STA_GOT_IP);
  WiFi.onEvent(onWifiDisconnect, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onSubscribe(onMqttSubscribe);
  mqttClient.onUnsubscribe(onMqttUnsubscribe);
  mqttClient.onMessage(onMqttMessage);
  mqttClient.onPublish(onMqttPublish);
  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  mqttClient.setCredentials(BROKER_USER, BROKER_PASS);
  mqttClient.setKeepAlive(30);  // seconds
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);

  connectToWifi();


//// -------------------  start MQTTPDATE task on second core ------------------------  
xTaskCreatePinnedToCore(
  mqttTask,
  "MQTT Task",
  16384,
  NULL,
  1,
  NULL,
  0   // run on Core 0
);

 UPDATING=0;
}     // end of Setup



 
void loop() 
{
  int tempInt;
  long tempLong,tempLongZ;

 TmrLoop();
 
//----------------------------------Code Runs every Sample time --------------
if(Vsample)
  {
 //  digitalWrite(MON_P22,HIGH); 
   Vsample=0;
   emon1.cycleCalc();      // goes in every time in endless loop, check CycleDone flag and returns 
  // emon1.calcVI();
 //  digitalWrite(MON_P22,LOW); 
  }
//--------------------------------- Code Runs Every Second --------------------
if(lastSec!=clocktime.sec)
  {
    lastSec=clocktime.sec;
    toggle^=1;
    
 //---------------------------  Do critical calculations first -----------------------   
      
  //  digitalWrite(LED_P21,toggle);
    digitalWrite(LED_P21,LOW);
    realpower= emon1.PrealScaled;
        apparentPower=emon1.Papparent;
        powerFactor = emon1.Pfactor;
        supplyVoltage = emon1.VrmsScaled;
        Irms = emon1.IrmsScaled;
        Freq=emon1.Freq;
 
 ///---------------------------------------------       
        tempLong=emon1.Whour;             // use tempLong to get emon1.Whour only once
        WHourT=((float)tempLong)/4096;       // emon1.Whour in Q20.12 format
       // tempLongZ=tempLong-whHourlyZ;          // 
       // WHourDay=((float)tempLongZ)/4096;
      //  tempLongZ=whHourlyZ;
       // whHourlyZF=((float)tempLongZ/4096);

        if(supplyVoltage>50)
        {
          if(AcOnCnt < 5)AcOnCnt++;
        }
        else 
        {
          if(AcOnCnt>0)AcOnCnt--;

        }
        if (AcOnCnt==5)AConNow=1;
        else if(AcOnCnt ==0) AConNow=0;        
                 
    
if(AConNow)sprintf(AcSTR,"On");
else sprintf(AcSTR,"Off");


Serial.printf("\n Vac: %.2f", supplyVoltage);
Serial.printf(" Iac:  %.2f" ,Irms  );
Serial.printf(" P:  %.2f" ,realpower  );
Serial.printf(" WHT:  %.2f" ,WHourT  );
Serial.printf(" Vofst:  %d" ,emon1.getOffsetV()  );
Serial.printf(" Iofst:  %d" ,emon1.getOffsetI()  );
///--------------  Copy measurements to data strcuture ------------
portENTER_CRITICAL(&mqttMux);
MsgOK=1;      // should be ok, calculated values complete ????
mqttData.realpower = realpower;
mqttData.apparentPower = apparentPower;
mqttData.powerFactor = powerFactor;
mqttData.supplyVoltage = supplyVoltage;
mqttData.Irms = Irms;



mqttData.WHourT = (int)(round(WHourT*10));
mqttData.WHourDay = (int)(round(WHourDay));

mqttData.MsgOK = MsgOK;

portEXIT_CRITICAL(&mqttMux);




    
  }   // end of sec

//----------------------------------- Code Runs Every Minut ---------------
if (lastMin!=clocktime.min)
  {
   lastMin=clocktime.min;
    
  }

//----------------------------------- Code Runs Every Hour ---------------
if (lastHour!=clocktime.hour)
  {
   lastHour=clocktime.hour;
   
    
  }



  

//----------------------------------Code Runs Every time through loop --------------- 
//emon1.cycleCalc();      // goes in every time in endless loop, check CycleDone flag and returns -- MOVED to Vsample

}

//----------------------  END OF LOOP ---------------------------------


void MQTTUPDATE(MQTTDATA_T d)
{
  uint16_t packetIdPub;
  char uptimeString[9];
  unsigned long currentMillis = millis();





  if (currentMillis - previous1SecMillis < interval1s)
      return;

  previous1SecMillis = currentMillis;

  // ✅ Only check state, don't control it
  if (WiFi.status() != WL_CONNECTED || !MqttUp)
      return;

  if(d.MsgOK== false) return;

  VarsFilt.count++;

  VarsFilt.V1 += (int)(round(d.supplyVoltage*100));
  VarsFilt.I1 += (int)(round(d.Irms*100));
 
  VarsFilt.P1 += (int)(round(d.realpower*100));
 VarsFilt.WHT = d.WHourT;


  d.MsgOK=false;

  if (--ClientLast != 0)
      return;

  ClientLast = 10;

  if (VarsFilt.count == 0)
      return;


      int sec = millis() / 1000;
      int min = sec / 60;
      int hr = min / 60;

  StaticJsonDocument<512> doc;

  doc["device"] = "DB";
  //doc["sensorType"] = "VIL";
  doc["Ver"] = VERSION;
                              //doc["V1"] = (int)(round(supplyVoltage*100));
  doc["V1"] = VarsFilt.V1/VarsFilt.count;
                              //doc["V1"] = stringTmp;
                              //doc["I1"] = (int)(round(Irms*100));
  doc["I1"] = VarsFilt.I1/VarsFilt.count;
                              //doc["P1"] = (int)(round(realpower*100));
  doc["P1"] = VarsFilt.P1/VarsFilt.count;
                              //doc["A1"] = (int)(round(apparentPower*100));
  //doc["A1"] = VarsFilt.A1/VarsFilt.count;
                              //doc["PF1"] = (int)(round(powerFactor*100));
  //doc["PF1"] = VarsFilt.PF1/VarsFilt.count;
                              //doc["WL"]=  (int)(round(UltraCountMem*0.02058*100));
                              //doc["WL"] = VarsFilt.WL/VarsFilt.count;
  
  snprintf(uptimeString, sizeof(uptimeString), "%02d:%02d:%02d", hr, min%60, sec%60);
  doc["UpT"]=uptimeString;
                            //  if(ElmtOn==1) doc["BHP"]="true";
                            //  else doc["BHP"]="false";
  doc["Aon"]=AcSTR;
  doc["WhT"]= VarsFilt.WHT;
  doc["WhD"]= (int)round(VarsFilt.WHD*10);

                              
  
  doc["RSSI"]=WiFi.RSSI();
  doc["RST"]=resetreason;
                             // doc["PC"]=dpulseCount;
                             
  
  doc["SSID"]=WiFi.SSID();

                          //    Serial.printf(" Doc: %d", measureJson(doc));
 // doc["I2"] = VarsFilt.I2/VarsFilt.count;
 // doc["P2"] = VarsFilt.P2/VarsFilt.count;
 // doc["WH2"]= (int)round(WHourT2*100);
 // doc["T3INT"]=VarsFilt.T3/VarsFilt.count;

  char JSONmessageBuffer[512];
                              //  JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  serializeJson(doc,JSONmessageBuffer);
  JSONmessageBuffer[511] = '\0';

  packetIdPub = mqttClient.publish(MQTT_MNS_JSON, 0, false, JSONmessageBuffer);

  VarsFilt = {};  // reset cleanly

  Serial.print(".");
}


void MQTTWAVE(EMonitor &emon)
{
    // Check flag safely
    portENTER_CRITICAL(&mqttMux);
    bool doCapture = emon.captureDone;
    portEXIT_CRITICAL(&mqttMux);


    if(!doCapture) return;
    if(WiFi.status() != WL_CONNECTED || !MqttUp) return;

    // Small buffers - stack is fine
    int16_t vBuf[CYCLE_SAMPLES];
    int16_t iBuf[CYCLE_SAMPLES];
    double vcal, ical;

    // Safe copy out of class before any serialisation
    emon.getWaveform(vBuf, iBuf, vcal, ical);

// Clear flag safely after copy
    portENTER_CRITICAL(&mqttMux);
    emon.captureDone = false;
    portEXIT_CRITICAL(&mqttMux);


    // Signal capture is done and sampling core can reuse arrays
    emon.captureDone = false;

    // Large buffers on heap
    DynamicJsonDocument doc(6144);
    char *JSONmessageBuffer = (char*)malloc(6144);

    if(!JSONmessageBuffer)
    {
        Serial.println("MQTTWAVE: malloc failed");
        return;
    }

    doc["vcal"] = vcal;
    doc["ical"] = ical;

    JsonArray v = doc.createNestedArray("v");
    JsonArray i = doc.createNestedArray("i");

    for(int n = 0; n < CYCLE_SAMPLES; n++)
    {
        v.add(vBuf[n]);
        i.add(iBuf[n]);
    }

    serializeJson(doc, JSONmessageBuffer, WAVE_JSON_SIZE);
    JSONmessageBuffer[WAVE_JSON_SIZE-1] = '\0';

    mqttClient.publish(MQTT_WAVE_JSON, 0, false, JSONmessageBuffer);

    free(JSONmessageBuffer);

    Serial.println("MQTTWAVE: sent");
}

















/*
void SerialprintCsv()
{
 Serial.printf("%d-%02d-%02d %02d:%02d:%02d",(timeinfo.tm_year)+1900,( timeinfo.tm_mon)+1, timeinfo.tm_mday,timeinfo.tm_hour , timeinfo.tm_min, timeinfo.tm_sec); 
 Serial.printf(",%.2f",WHourT);
 Serial.printf(",%.2f",supplyVoltage);
 Serial.printf(",%.2f",Irms);
Serial.printf(",%.2f",realpower);
Serial.printf(",%.2f",apparentPower);
Serial.printf(",%.2f",Freq);

 Serial.printf("\n"); 
}
*/
/*
void ACstatSend(void)
{
String StringOut;
if(AConNow) StringOut="AcOn";
else StringOut="AcOff";
StringOut+=",";
StringOut+=String(random(100));
server.send(200,"text/plain",StringOut);
}
*/
void serialprint()
{
float tempFloat;

       Serial.print("Time - ");
       Serial.print(clocktime.hour);
       Serial.print(":");
       Serial.print(clocktime.min);
       Serial.print(":");
       Serial.print(clocktime.sec);
       Serial.print("  ");
     
     //Serial.print("  - VrmsS: ");
    // Serial.print(supplyVoltage);
    // Serial.print(" Vrms  :");
    // Serial.print(" Irms: ");
    // Serial.print(Irms);
     //Serial.print("  IrmsS: ");
    // Serial.print(Irms);
    // Serial.print("Arms  :");
    
      //Serial.print(realpower);
     // Serial.print("W  ");
      

    
      //Serial.print(apparentPower);
      //Serial.print("VA  ");

    
      //Serial.print(powerFactor);
      //Serial.print(" PF  ");

      
      //Serial.print(Freq);
      //Serial.print("Hz  ");

      //Serial.print("  Wsec: ");
      Serial.print(WHourT);
      Serial.print(" Wh  ");

      Serial.print("Dayindex : ");
      Serial.print(whDaysIndex);

      Serial.print(" WhZ : ");
      tempFloat=((float)whHourlyZ/4096);
     // Serial.print(whHourlyZ);
     Serial.print(tempFloat);

      Serial.print(" Wh[0] : ");
      tempFloat=((float)whHourly[0]/4096);
      Serial.print(tempFloat);
      
      Serial.print(" Wh[23] : ");
      tempFloat=((float)whHourly[23]/4096);
      Serial.print(tempFloat);
    
     
     Serial.print("\n\r");  
}




