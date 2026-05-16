//TmrClk.C  ??? h
// ---- #include "TmrClk.h" just before setup() function in sketch
// Call TmrSetup() in setup fuction (change defines for interupt time etc.)
// Call TmrLoop() in infinite loop to update values on interrupt
// Global variables used:
//        clocktime.hour
//        clocktime.min
//        clocktime.sec
//        clocktime.tenth
//        Vsample  -- set to one every interupt- must reset to 0 if sampling is done


// Code  for timer interrupt
#include "Arduino.h"
#include "vars.h"
#include "EmonWar.h"


extern EMonitor emon1;


#define TIMER_PRESCALE 80
#define TIMER_ALM 100   //166     //120= 166 samples per full cycle
#define TICKSpSEC 80000000/TIMER_PRESCALE/TIMER_ALM         ///
#define TICKSpTENTH TICKSpSEC/10
#define SAMPLETIME 1000000/TICKSpSEC


struct Ctime {
  byte hour;
  byte min;
  byte sec;
  byte tenth;
};

struct Ctime clocktime;




hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
int tickCnt=0;
int tickTenth=0;
volatile int interruptCounter;
bool Vsample=0;
bool Hchange=0;       
 
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter++;
  Vsample=1;
  if(UPDATING==0)
    {
    digitalWrite(MON_P22,HIGH);
  //  emon1.calcVI();
    digitalWrite(MON_P22,LOW);   
    }
  portEXIT_CRITICAL_ISR(&timerMux);
 
}


void TmrSetup()
{
timer = timerBegin(0, TIMER_PRESCALE, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, TIMER_ALM, true);
  timerAlarmEnable(timer);
  
}

void TmrLoop()
{
if (interruptCounter > 0)
    {
    portENTER_CRITICAL(&timerMux);
    interruptCounter--;
    portEXIT_CRITICAL(&timerMux); 

    if(++tickTenth==TICKSpTENTH)
        {
          tickTenth=0;
          if(++clocktime.tenth==10) clocktime.tenth=0;
          
        }


    
    if(++tickCnt==TICKSpSEC)
        {
        tickCnt=0;
        
        if(++clocktime.sec==60)
            {
              clocktime.sec=0;
              if(++clocktime.min==60)
                  {
                    clocktime.min=0;
                    ++clocktime.hour;
                     Hchange=1;
                     if(clocktime.hour==24) 
                      {
                      clocktime.hour=0;  
                      }
                  }
            }
           
        }
    }



  
}
