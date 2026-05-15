/*  EmonWar.cpp  lib for energy monitor
 *   
 */

#include "EmonWar.h"
#include <driver/adc.h>

EMonitor* EMonitor::_instance = nullptr;

void IRAM_ATTR EMonitor::_zeroCrossISR() {
    if (_instance) {
        _instance->ac_posI = digitalRead(_instance->_zeroCrossPin);
        digitalWrite(_instance->_zeroCrossDebugPin, _instance->ac_posI);
    }
}

void EMonitor::attachZeroCross(unsigned int pin, unsigned int debugPin) {
    _instance = this;
    _zeroCrossPin = pin;
    _zeroCrossDebugPin = debugPin;
    pinMode(pin, INPUT);
    attachInterrupt(pin, _zeroCrossISR, CHANGE);
}


//------------------------------------------------
// Set Pins for voltage and current sensors
//-----------------------------------------------

void EMonitor::setup(void)
{
 

//adc1_adc_mode_acquire();
//adc_power_on();

//portENTER_CRITICAL(&rtc_spinlock);
//disable peripherals
//adc1_hadc1_fsm_disable();

adc1_config_width(ADC_WIDTH_BIT_12);
//adc2_config_width(ADC_WIDTH_BIT_12);
 adc1_config_channel_atten(ADC1_CHANNEL_4,ADC_ATTEN_DB_11);
 adc1_config_channel_atten(ADC1_CHANNEL_7,ADC_ATTEN_DB_11);
 //adc1_config_channe2_atten(ADC2_CHANNEL_8,ADC_ATTEN_DB_11);
 
}


void EMonitor::voltage(unsigned int _inPinV,double _VCAL)
{
  inPinV = _inPinV;
  VCAL = _VCAL;
  offsetV = ADC_COUNTS>>1;
  
}

void EMonitor::current(unsigned int _inPinI,double _ICAL)
{
  inPinI=_inPinI;
  ICAL=_ICAL;
  offsetI=ADC_COUNTS>>1;
  
}

void EMonitor::wattsec(int _TSUS)
{
double tempfloat;
TSUS= _TSUS;
PCAL=VCAL*ICAL;
Serial.print(VCAL,8 );
Serial.print("  ");
Serial.print(ICAL,8);
Serial.print("   ");
Serial.print(PCAL,8);
Serial.print("   ");
Serial.print(TSUS,6);
Serial.print("   ");
tempfloat=1000000/PCAL;
tempfloat=tempfloat/(double)TSUS;
WSCAL=(long)tempfloat;
Serial.println(WSCAL);

  
}

void EMonitor::power(double _PCAL)
{
PCAL = _PCAL;  
}


void EMonitor::monpin(unsigned int _monPin1)
{
monPin1 = _monPin1;
pinMode(monPin1,OUTPUT);  
}

void EMonitor::freq(double _FCAL)
{
  FCAL= _FCAL;
}

void EMonitor::calcVI()
{

 // digitalWrite(monPin1,HIGH);
 //  sample_I=ADcal(analogRead(inPinI));
    sample_I=ADcal(adc1_get_raw(ADC1_CHANNEL_4));
   // sample_V=ADcal(analogRead(inPinV));
  // sample_V=ADcal(adc2_get_raw(ADC2_CHANNEL_8));
   sample_V=ADcal(adc1_get_raw(ADC1_CHANNEL_7));
 // digitalWrite(monPin1,LOW);  
 // digitalWrite(MON_P22,LOW);
    //offsetV = offsetV + ((sample_V-offsetV)/1024);
    
    offsetVQ15=offsetVQ15 +(((sample_V<<4)-offsetVQ15)/1024);
    offsetV = offsetVQ15>>4;
    filtered_V = sample_V-offsetV;  
    
    offsetIQ15=offsetIQ15 +(((sample_I<<4)-offsetIQ15)/1024);
    offsetI = offsetIQ15>>4;
    filtered_I = sample_I-offsetI;
   


        
    if(ac_posI && !lastACPos)             // rising edge: negative to positive transition
        {
        if(sampleCnt<100) zcCount++;
        else if(sampleCnt>100)
            {
            sqVmem = sqV;
            sqV = 0;
            sqImem=sqI;
            sqI=0;
            sumPmem=sumP;
            sumP=0;
            sampleCntmem=sampleCnt;
            sumSample+=sampleCnt;
            sampleCnt=0;
            if(zcCount>5 || sqVmem < 10000)NoMains=1;
            else NoMains=0;
            zcCount=0;
            cycleDone=1;
            }
        }
    sampleCnt++;
////==========================================  sample a v & I  waveform here ============================
// In calcVI() — clean state machine
if(captureReq)
{
    captureState = WAITING_ZC;
    captureDone  = false;
    captureReq   = false;
}

switch(captureState)
{
    case IDLE:
        break;

    case WAITING_ZC:
        if(ac_posI && !lastACPos)             // rising edge: start capture
        {
            waveIdx      = 0;
            captureState = CAPTURING;
        }
        break;

    case CAPTURING:
        vWave[waveIdx] = filtered_V;
        iWave[waveIdx] = filtered_I;
        waveIdx++;
        if(waveIdx >= CYCLE_SAMPLES)
        {
            captureDone  = true;
            captureState = IDLE;
            waveIdx      = 0;
        }
        break;
} 
lastACPos = ac_posI;


//=================================================================


    sqV += ((long)filtered_V * (long)filtered_V); 

//digitalWrite(MON_P22,LOW);   

    sqI += ((long)filtered_I *(long)filtered_I);

    instP =(long)filtered_I * (long)filtered_V;
    sumP += instP;
//digitalWrite(monPin1,LOW); 
}

void EMonitor::cycleCalc()
{
 if(cycleDone)
    {
     digitalWrite(monPin1,HIGH); 
     // Serial.print(" sqV: ");
      //Serial.println(sqVmem);

      if(NoMains)
          {
           Vrms=0;
           Irms=0;
           Preal=0; 
          }
      
      if(sqVmem < 50000) 
        {
        Vrms=0;
       // Irms=0;
       // Preal=0;

        }
      else
        {
      //  Templong=sqVmem/sampleCntmem;
      //  Vrms=sqrt(Templong);      // Double Float
        sqVacc += sqVmem;
        }
     // VcycleSum+=Vrms;            // Double Float += Double Float


      if(sqImem<50000) Irms=0;
      else
        {
       // Templong=sqImem/sampleCntmem;
       // Irms=sqrt(Templong);      // Double Float
       sqIacc += sqImem;
        }
     // IcycleSum+=Irms;            // Double Float = Double Float

      sampleCntacc += sampleCntmem;

     // Templong=sumPmem/sampleCntmem;
      sumPacc += sumPmem;   // accumulate raw sum of instP products
     // Preal=Templong;             // Double Float = Long

     // PcycleSum+=Preal;
      wsacc+=sumPmem;           // add accumalator for Watt Sec
/*
      Serial.print("sumPmem:  ");
      Serial.print(sumPmem);
      Serial.println();
 */     
      
     // IrmsScaled=Irms*Ical;
      
      
      cycleDone=0;


/*
      Serial.print(" offsetIQ15: ");
      Serial.print(offsetIQ15>>4);
      Serial.print("  sqI: ");
      Serial.print(sqImem);
      Serial.print(" Irms: ");
      Serial.print(Irms);
      Serial.print(" IrmsScaled: ");
      Serial.print(IrmsScaled);
      
      
      
      Serial.println();
   */   

    
      if(++cycleCountWS==5)       // this part takes 50us -- updated every 5 cycles +-0.1sec
        {
         //digitalWrite(monPin1,HIGH); 
        long tempLong=wsacc/WSCAL;
       /* 
        Serial.print(sumPmem);
        Serial.print("  ");
        Serial.print(wsacc);
        Serial.print("  ");
        Serial.println(tempLong);
        */
       wsec+=tempLong;          /// ADD Watt seconds to wsec
        wsacc=wsacc%WSCAL;          /// keep remainder to add onto
        cycleCountWS=0;   
        //digitalWrite(monPin1,LOW);
        }


      
      if(++cycleCount==50)        // = 1 sec
        {
        cycleCount=0;
      //  VrmsScaled=VcycleSum/50;
      //  VrmsScaled=VrmsScaled*VCAL; 
       // VcycleSum=0; 
      //VrmsScaled=Vrms*Vcal;
        VrmsScaled = sqrt((double)sqVacc / sampleCntacc) * VCAL;


       // IrmsScaled=IcycleSum/50;
       // IrmsScaled=IrmsScaled*ICAL;
       // IcycleSum=0;
        IrmsScaled = sqrt((double)sqIacc / sampleCntacc) * ICAL;

        


       // PrealScaled= PcycleSum/50;
       // PrealScaled=PrealScaled*PCAL;
       // PcycleSum=0;
        PrealScaled = ((double)sumPacc / sampleCntacc) * PCAL;
        sumPacc = 0;

        sqVacc = 0;
        sqIacc = 0;
        sampleCntacc = 0;

        Papparent=VrmsScaled * IrmsScaled;
        
        if(Papparent>0) Pfactor = PrealScaled/Papparent;
        else Pfactor=0;
        if(Vrms>0)
          {
          Freq= FCAL/sumSample*50;
          }
        else
          {
           Freq=0; 
          }
        sumSample=0;  

        //Serial.print(WSec20Q12);
        //Serial.print("   ");
        

        //Serial.print(wsec);
      ///--------------------------- wsec -> Whour -----takes 250ns------------------------------  
 //digitalWrite(monPin1,HIGH); 
        Templong=wsec<<12;
        WSec20Q12+=Templong;
        Whour+=WSec20Q12/3600;
        WSec20Q12=WSec20Q12%3600;
        wsec=0;
//digitalWrite(monPin1,LOW);         
        //Serial.print("    ");
        //Serial.print(Whour);
      //  float tempFloat=(float)Whour/4096;
        //Serial.print("  ");
      //  Serial.print(tempFloat,4);
      //  Serial.println();
        
        //Serial.print(WSec20Q12);
        //Serial.println();
       // wsec=0;                 ///check if you can leave a remaining value
       
       // serialprint();
        }
     digitalWrite(monPin1,LOW); 
    } 
}

void EMonitor::getWaveform(int16_t *vOut, int16_t *iOut, double &vcal, double &ical)
{
    memcpy(vOut, vWave, sizeof(vWave));
    memcpy(iOut, iWave, sizeof(iWave));
    vcal = VCAL;
    ical = ICAL;
}









int EMonitor::ADcal(int ADinput)
{
long TempLong;
TempLong= long(ADinput);
if(ADinput==0) TempLong=1;

if(TempLong<=2971)
  {
  TempLong-=1;
  TempLong<<=3;
  TempLong*=33832;      // Q15(1.032481) = 33832
  TempLong>>=18;
  TempLong+=170;
  }
else if (TempLong <= 3283)
  {
   TempLong-=2971;
   TempLong<<=3;
   TempLong*=25836;         // Q15(0.788462)) = 25836
  TempLong>>=18;
  TempLong+=3237;  
  }
 else
  {
   TempLong-=3283;
   TempLong<<=3;
   TempLong*=19854;         // Q15(0.605911)) = 19854
  TempLong>>=18;
  TempLong+=3483;    
  }

 if(TempLong> 4095) TempLong=4095; 
 return(int)TempLong ;
  
}

/*
int adc1_get_raw(adc1_channel_t channel)
{
uint16_t adc_value;
//RTC_MODULE_CHECK(channel<ADC_CHANNEL_MAX,"ADC Channel Err",ESP_ERR_INVALID_ARG);
//adc1_adc_mode_acquire();
//adc_power_on();

//portENTER_CRITICAL(&rtc_spinlock);
//disable peripherals
//adc1_hall_enable(false);
//adc1_fsm_disable();
adc1_set_controller(ADC_UNIT_1,channel);
//portEXIT_CRITICAL(&rtc_spinlock);
adc1_lock_release();
return adc_value;
  
}
*/

void EMonitor::serialprint()
{
   //  digitalWrite(MON_P22,LOW);
  //   Serial.print("SQV : ");
   //  Serial.print(sqVmem); 
  //   Serial.print("  - Vpkp: ");
  //   Serial.print(Vpkpmem-offsetV);
  //  Serial.print("  -Vpkn: ");
  //   Serial.print(Vpknmem-offsetV);
     Serial.print("  -Samples: ");
     Serial.print(sampleCntmem);
 //    Serial.print("  - offsetVQ15:  ");
 //    Serial.print(offsetVQ15>>4);
    // Serial.print("  - Vrms: ");
    // Serial.print(Vrms);
     Serial.print("  - VrmsS: ");
     Serial.print(VrmsScaled);
    // Serial.print(" Irms: ");
    // Serial.print(Irms);
     Serial.print("  IrmsS: ");
     Serial.print(IrmsScaled);
     Serial.print(" sumP:  ");
     Serial.print(sumPmem);
   //   Serial.print(" Preal: ");
   //   Serial.print(Preal);
      Serial.print(" PrealS: ");
      Serial.print(PrealScaled);

    //  Serial.print(" PappS: ");
    //  Serial.print(Papparent);

    //  Serial.print(" PF: ");
    //  Serial.print(Pfactor);

      Serial.print(" Freq: ");
      Serial.print(Freq);

      Serial.print("  Wsec: ");
      Serial.print(wsec);
     
     Serial.print("\n");  
}
