#include "include.h"

int16 servoMedian = 5125;

int GraphProcessingOfEdgeFluctuation(){

}

int ElectromagnetismProcessingOfBasics(){
  ADC0_Ch_e ADCRemawp[] = {ADC0_DP1, ADC0_SE5a, ADC0_DP2, ADC0_DP3,  ADC0_SE11, ADC0_SE9, ADC0_SE4a, ADC0_SE10};
  return (int)(ADC0_Ave(ADCRemawp[3],ADC_16bit,10)-ADC0_Ave(ADCRemawp[0],ADC_16bit,10)+ADC0_Ave(ADCRemawp[2],ADC_16bit,10)-ADC0_Ave(ADCRemawp[1],ADC_16bit,10))*10000
             /(ADC0_Ave(ADCRemawp[3],ADC_16bit,10)+ADC0_Ave(ADCRemawp[0],ADC_16bit,10)+ADC0_Ave(ADCRemawp[2],ADC_16bit,10)+ADC0_Ave(ADCRemawp[1],ADC_16bit,10));
}

uint8_t ElectromagnetismProcessingOfLoseDataForStop(){

}

void GyroAngleProcessing(){
  PIDMotorRight.setPoint = PIDMotorLeft.setPoint = -PositionalPID(ReadGyro(), &PIDErect);

}



