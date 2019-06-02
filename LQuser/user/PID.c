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


//位置式PID
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

//增量式PID
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
//    iError = aPID->SetPoint - NextPoint;       //偏差
//    aPID->SumError += iError;       //积分
//    dError = iError - aPID->LastError;     //微分
//    aPID->LastError = iError;
//
//    return (int)(aPID->SetPoint + aPID->Proportion * iError            //比例项
//           + aPID->Integral * aPID->SumError   //积分项
//           + aPID->Derivative * dError
//           );
//}
//
//
//void MotorLeftLocPIDCalc(int NextPoint){
//    int  iError,dError;
//    char txt[16];
//
//    iError = PIDMotorLeft.SetPoint - NextPoint;       //偏差
//    PIDMotorLeft.SumError += iError;       //积分
//    dError = iError - PIDMotorLeft.LastError;     //微分
//    PIDMotorLeft.LastError = iError;
//
//    speedLeft = (int)(PIDMotorLeft.SetPoint + PIDMotorLeft.Proportion * iError            //比例项
//           + PIDMotorLeft.Integral * PIDMotorLeft.SumError   //积分项
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
//    iError = PIDMotorRight.SetPoint - NextPoint;       //偏差
//    PIDMotorRight.SumError += iError;       //积分
//    dError = iError - PIDMotorRight.LastError;     //微分
//    PIDMotorRight.LastError = iError;
//
//    speedRight = (int)( PIDMotorRight.SetPoint + PIDMotorRight.Proportion * iError            //比例项
//           + PIDMotorRight.Integral * PIDMotorRight.SumError   //积分项
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
//    iError = PIDErect.SetPoint - NextPoint;       //偏差
//    PIDErect.SumError += iError;       //积分
//    dError = iError - PIDErect.LastError;     //微分
//    PIDErect.LastError = iError;
//
//    angle = (int)(PIDErect.Proportion * iError            //比例项
//           + PIDErect.Integral * PIDErect.SumError   //积分项
//           + PIDErect.Derivative * dError
//           );
//
//    PIDMotorLeft.SetPoint = angle;
//    PIDMotorRight.SetPoint = angle;
//}


