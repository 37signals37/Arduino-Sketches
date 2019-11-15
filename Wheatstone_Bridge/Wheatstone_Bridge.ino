//https://www.instructables.com/id/Goophene-Hypersensitive-Graphene-Sensors/
#include <ADC.h>
ADC *adc = new ADC(); // adc object
int value = 0;

const int numReadings = 50;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
float average = 0;                // the average
int prevvalue = 0;
float prevAve = 0;
int latestreading = 0;

float deriv1=0;
float prevDeriv1=0;
float deriv2=0;
float derivIIR = 0;

//int value;
//int value2;
//IIR
float ETA=.9;

void setup() {

  pinMode(A10, INPUT); //Diff Channel 0 Positive
  pinMode(A11, INPUT); //Diff Channel 0 Negative
  
  analogWriteResolution(1); //12  // analogWrite value 0 to 4095, or 4096 for high
  analogWrite(A14,(int)4095);     //This is proper DAC // Good use was 20 and no resolutionchange // 4000 and resolution was good
  
  adc->setAveraging(100); //100 // set number of averages 
  adc->setResolution(32); //16 // set bits of resolution // can be 0, 4, 8, 16 or 32
  adc->setConversionSpeed(ADC_CONVERSION_SPEED::LOW_SPEED); //MED SPEED// change the conversion speed
  adc->setSamplingSpeed(ADC_SAMPLING_SPEED::HIGH_SPEED); // change the sampling speed
  
  // always call the compare functions after changing the resolution!
  adc->enableCompare(1.0/3.3*adc->getMaxValue(ADC_0), 0, ADC_0); // measurement will be ready if value < 1.0V
  adc->enableCompareRange(1.0*adc->getMaxValue(ADC_0)/3.3, 2.0*adc->getMaxValue(ADC_0)/3.3, 0, 1, ADC_0); // ready if value lies out of [1.0,2.0] V
  
  adc->enablePGA  (8,ADC_0); //2  //can be 1, 2, 4, 8, 16, 32 or 64   
  Serial.begin(9600);
}

void loop() {
  
  for(int i = 0; i < numReadings; i++){
    value = adc->adc0->analogReadDifferential(A10, A11); // read a new value, will return ADC_ERROR_VALUE if the comparison is false.  
    if(adc->adc0->fail_flag){
          adc->adc0->printError();
    }
  
    total = total - readings[readIndex];
    latestreading = value;
    readings[readIndex] = latestreading;
    total = total + readings[readIndex];
    readIndex = readIndex + 1;
    average = total / numReadings;
  
    if (readIndex >= numReadings){
      readIndex = 0;
    }

    deriv1=average-prevAve;
    deriv2=deriv1-prevDeriv1;
  
    //smooth that deriv? with an IIR
    derivIIR = ETA * (deriv1) + (1-ETA) * derivIIR;
  
    prevAve=average;
    prevvalue = value;
    prevDeriv1=deriv1;    
  }



//  Serial.println(value);
  Serial.println(average);
//  Serial.println(deriv1);
//  Serial.print(190);
//  Serial.print(" ");
//  Serial.println(abs(derivIIR));
//  Serial.print(" ");
//  Serial.println(deriv2);
  
//  delay(1);
}

void adc0_isr(void){
  adc->adc0->readSingle();  
}
