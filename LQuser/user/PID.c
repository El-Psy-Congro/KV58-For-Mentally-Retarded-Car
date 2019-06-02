#include "include.h"

PID PIDServo, PIDMotorLeft, PIDMotorRight, PIDErect;
int speedSet = 0;

void PIDInit(){
  PIDServo.setPoint = 0;
  PIDServo.proportion = 1.75;  //0.27
  PIDServo.integral = 0;
  PIDServo.derivative = 0;
  PIDServo.isDeviation = 0;

  PIDMotorLeft.setPoint = 200;
  PIDMotorLeft.proportion = 1;
  PIDMotorLeft.integral = 0.011;
  PIDMotorLeft.derivative = 0;
  PIDMotorLeft.isDeviation = 1;

  PIDMotorRight.setPoint = 200;
  PIDMotorRight.proportion = 1;
  PIDMotorRight.integral = 0.011;
  PIDMotorRight.derivative = 0;
  PIDMotorRight.isDeviation = 1;

  PIDErect.setPoint = 2100;
  PIDErect.proportion =0.8;
  PIDErect.integral = 0.000;
  PIDErect.derivative = 0;
  PIDErect.isDeviation = 0;
}


//λ��ʽPID
int PositionalPID(int NextPoint, PID *aPID){
  int  currentError,proportionVariable, integralVariable, derivativeVariable;

  currentError = aPID->setPoint - NextPoint;
  aPID->sumError += currentError;

  proportionVariable = currentError;
  integralVariable = aPID->sumError;
  derivativeVariable = currentError - aPID->lastError;

  aPID->prevError = aPID->lastError;
  aPID->lastError = currentError;

  if(aPID->isDeviation){
    return (int)( aPID->proportion * proportionVariable
                + aPID->integral * integralVariable
                + aPID->derivative * derivativeVariable);
  }else{
    return (int)(aPID->setPoint
               + aPID->proportion * proportionVariable
               + aPID->integral * integralVariable
               + aPID->derivative * derivativeVariable);
  }
}

//����ʽPID
int IncrementalPID(int NextPoint, PID *aPID){
  int  currentError, proportionVariable, integralVariable, derivativeVariable;
  
  currentError = aPID->setPoint - NextPoint;

  proportionVariable = currentError - aPID->lastError;
  integralVariable = currentError;
  derivativeVariable = currentError - 2*aPID->lastError + aPID->prevError;

  aPID->prevError = aPID->lastError;
  aPID->lastError = currentError;
  
  
  if(aPID->isDeviation){
    return (int)( aPID->proportion * proportionVariable
                + aPID->integral * integralVariable
                + aPID->derivative * derivativeVariable);
  }else{
    return (int)(aPID->setPoint
               + aPID->proportion * proportionVariable
               + aPID->integral * integralVariable
               + aPID->derivative * derivativeVariable);
  }
}



//int PositionalPID(int NextPoint, PID aPID){
//    int  iError,dError;
//    char txt[16];
//
//    iError = aPID->SetPoint - NextPoint;       //ƫ��
//    aPID->SumError += iError;       //����
//    dError = iError - aPID->LastError;     //΢��
//    aPID->LastError = iError;
//
//    return (int)(aPID->SetPoint + aPID->Proportion * iError            //������
//           + aPID->Integral * aPID->SumError   //������
//           + aPID->Derivative * dError
//           );
//}
//
//
//void MotorLeftLocPIDCalc(int NextPoint){
//    int  iError,dError;
//    char txt[16];
//
//    iError = PIDMotorLeft.SetPoint - NextPoint;       //ƫ��
//    PIDMotorLeft.SumError += iError;       //����
//    dError = iError - PIDMotorLeft.LastError;     //΢��
//    PIDMotorLeft.LastError = iError;
//
//    speedLeft = (int)(PIDMotorLeft.SetPoint + PIDMotorLeft.Proportion * iError            //������
//           + PIDMotorLeft.Integral * PIDMotorLeft.SumError   //������
//           + PIDMotorLeft.Derivative * dError
//           );
//    Motor_Duty(MotL,speedLeft);
//
//}
//
//void MotorRightLocPIDCalc(int NextPoint){
//    int  iError,dError;
//    char txt[16];
//
//    iError = PIDMotorRight.SetPoint - NextPoint;       //ƫ��
//    PIDMotorRight.SumError += iError;       //����
//    dError = iError - PIDMotorRight.LastError;     //΢��
//    PIDMotorRight.LastError = iError;
//
//    speedRight = (int)( PIDMotorRight.SetPoint + PIDMotorRight.Proportion * iError            //������
//           + PIDMotorRight.Integral * PIDMotorRight.SumError   //������
//           + PIDMotorRight.Derivative * dError
//           );
//    Motor_Duty(MotR,speedRight);
//}
//
//
//void ErectLocPIDCalc(int NextPoint){
//    int  iError,dError;
//    char txt[16];
//
//    iError = PIDErect.SetPoint - NextPoint;       //ƫ��
//    PIDErect.SumError += iError;       //����
//    dError = iError - PIDErect.LastError;     //΢��
//    PIDErect.LastError = iError;
//
//    angle = (int)(PIDErect.Proportion * iError            //������
//           + PIDErect.Integral * PIDErect.SumError   //������
//           + PIDErect.Derivative * dError
//           );
//
//    PIDMotorLeft.SetPoint = angle;
//    PIDMotorRight.SetPoint = angle;
//}


