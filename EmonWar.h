/*  EmonWar.h  -  library for energy monitor
 *   
 */


#ifndef EmonWar_h
#define EmonWar_h

#include "Arduino.h"

#define ADC_BITS 12
#define ADC_COUNTS (1<<ADC_BITS)
#define CYCLE_SAMPLES 200

class EMonitor
{
public:
void setup(void);
void voltage(unsigned int _inPinV,double _VCAL);
void current(unsigned int _inPinI,double _ICAL);
void wattsec(int _TSUS);
void power(double _PCAL);
void monpin(unsigned int _Mon1);
void freq(double _FCAL);
void getWaveform(int16_t *vOut, int16_t *iOut, double &vcal, double &ical);
void attachZeroCross(unsigned int pin, unsigned int debugPin);

volatile bool captureReq  = false;  // sketch sets this to trigger
volatile bool captureDone = false;  // sketch polls this to know when ready
volatile bool ac_posI     = false;  // set by zero-cross ISR: true = positive half-cycle

//void sendWaveform(PubSubClient &mqtt);  // handles scaling internally



void calcVI();
void cycleCalc();
void serialprint();
// Useful value variables

double VrmsScaled,IrmsScaled;
double PrealScaled;
double Papparent;
double Pfactor;
float Freq;
long Whour=0;         // Whour in Q20.12 format i.e 20bits + 12bits fractional

private:

static EMonitor* _instance;
static void IRAM_ATTR _zeroCrossISR();
unsigned int _zeroCrossPin;
unsigned int _zeroCrossDebugPin;

//int Adc1_get_raw(adc1_channel_t channel);
int ADcal(int ADinput);

//Set Voltage and Current input pins
unsigned int inPinV;
unsigned int inPinI;
unsigned int monPin1;
// Calibration coefficients

double VCAL;              //0.24374749;
double ICAL;              //0.009014588;
int TSUS;       // sample time us

double PCAL;
double FCAL;
long  WSCAL;    // constant for Watt*Sec

// Variable decleration for emon procedure
int sample_V =0;
int sample_I =0;


int offsetV = ADC_COUNTS>>1;
int offsetVQ15 = ADC_COUNTS<<3;
int offsetI;
int offsetIQ15 = ADC_COUNTS<<3;
signed int filtered_V,filtered_I;

int sampleCnt,sampleCntmem=0;    // count nr of samples
int zcCount=0;
unsigned long sqV,sqVmem,sqI,sqImem = 0;
unsigned long sumSample;
long instP, sumP, sumPmem;
/////////////  Claude suggest for double long integer accumulate ////

unsigned long long sqVacc = 0;   // 64-bit to avoid overflow
unsigned long long sqIacc = 0;
long long sumPacc = 0;
long sampleCntacc = 0;


bool cycleDone=0;
bool NoMains=0;


double Vrms,Irms;
double Preal;

long Templong;


int cycleCount=0;
double VcycleSum=0,IcycleSum=0,PcycleSum;
//---------------------------- WATT SEC variables
long wsacc=0;

long wsec=0;
long WSec20Q12;

int cycleCountWS=0;

// claude suggest for capturing voltage and current waveforms

    int16_t vWave[CYCLE_SAMPLES];
    int16_t iWave[CYCLE_SAMPLES];
    uint16_t waveIdx = 0;
    enum CaptureState { IDLE, WAITING_ZC, CAPTURING } captureState = IDLE;
    bool lastACPos = 0;


};

#endif
