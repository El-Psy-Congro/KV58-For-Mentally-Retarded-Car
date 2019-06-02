#include "include.h"

int servoMedian = 5140, graphMedian = 0, servo = 0, angle = 0;
int GraphProcessing(){
  if(fieldOverFlag)  {
    GetUseImage();    //采集图像数据存放数组
    threshold = GetOSTU(imageData); //OSTU大津法 获取全局阈值
    GetBinarizationValue();     //二值化图像数据

    GraphProcessingOfEdgeFluctuation();

    //EnableInterrupts
    fieldOverFlag = 0;
    
  }
  return graphMedian;
}

int GraphProcessingOfEdgeFluctuation(){
  //    Pixle[i][j]
}

int ElectromagnetismProcessing(){

}

int ElectromagnetismProcessingOfBasics(){
  ADC0_Ch_e ADCRemawp[] = {ADC0_DP1, ADC0_SE5a, ADC0_DP2, ADC0_DP3,  ADC0_SE11, ADC0_SE9, ADC0_SE4a, ADC0_SE10};
  return (int)(ADC0_Ave(ADCRemawp[3],ADC_16bit,10)-ADC0_Ave(ADCRemawp[0],ADC_16bit,10)+ADC0_Ave(ADCRemawp[2],ADC_16bit,10)-ADC0_Ave(ADCRemawp[1],ADC_16bit,10))*10000
             /(ADC0_Ave(ADCRemawp[3],ADC_16bit,10)+ADC0_Ave(ADCRemawp[0],ADC_16bit,10)+ADC0_Ave(ADCRemawp[2],ADC_16bit,10)+ADC0_Ave(ADCRemawp[1],ADC_16bit,10));
}

bool ElectromagnetismProcessingOfLoseDataForStop(){

}

void GyroAngleProcessing(){
  angle = ReadGyro() - PIDErect.setPoint;
  if(angle<900 && angle > -1600){
    PIDMotorRight.setPoint = PIDMotorLeft.setPoint = -angle;
  }


}



