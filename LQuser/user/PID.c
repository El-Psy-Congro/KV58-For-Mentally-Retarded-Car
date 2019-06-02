#include "include.h"

PID PIDServo, PIDMotorLeft, PIDMotorRight;
short servo, speedLeft, speedRight;
short SERVOMEDIAN = 1300, SPEEDLEFT, SPEEDRIGHT;
void PidSet(){
  PIDServo.SetPoint = 0;
  PIDServo.Proportion = 0.27;
  PIDServo.Integral = 0;
  PIDServo.Derivative = 0;

  PIDMotorLeft.SetPoint = 0;
  PIDMotorLeft.Proportion = 0.001;
  PIDMotorLeft.Integral = 0;
  PIDMotorLeft.Derivative = 0;

  PIDMotorRight.SetPoint = 200;
  PIDMotorRight.Proportion = 0.02;
  PIDMotorRight.Integral = 0;
  PIDMotorRight.Derivative = 0;
}

void ServoLocPIDCalc(int NextPoint){
    int  iError,dError;
    char txt[16];
    
    iError = PIDServo.SetPoint - NextPoint;       //偏差
    PIDServo.SumError += iError;       //积分
    dError = iError - PIDServo.LastError;     //微分
    PIDServo.LastError = iError;

    servo = (int)(SERVOMEDIAN + PIDServo.Proportion * iError            //比例项
//           + PIDServo.Integral * PIDServo.SumError   //积分项
           + PIDServo.Derivative * dError
           );
    Servo_Duty(servo);
//    sprintf(txt,"%04d",server);
//    LCD_P6x8Str(40,1,(u8*)txt);

}


void MotorLeftLocPIDCalc(int NextPoint){
    int  iError,dError;
    char txt[16];

    iError = PIDMotorLeft.SetPoint - NextPoint;       //偏差
    PIDMotorLeft.SumError += iError;       //积分
    dError = iError - PIDMotorLeft.LastError;     //微分
    PIDMotorLeft.LastError = iError;

    speedLeft = (int)(PIDMotorLeft.SetPoint + PIDMotorLeft.Proportion * iError            //比例项
           + PIDMotorLeft.Integral * PIDMotorLeft.SumError   //积分项
           + PIDMotorLeft.Derivative * dError
           );
    Motor_Duty(MotL,speedLeft);
    
}

void MotorRightLocPIDCalc(int NextPoint){
    int  iError,dError;
    char txt[16];

    iError = PIDMotorRight.SetPoint - NextPoint;       //偏差
    PIDMotorRight.SumError += iError;       //积分
    dError = iError - PIDMotorRight.LastError;     //微分
    PIDMotorRight.LastError = iError;

    speedRight = (int)( PIDMotorRight.SetPoint + PIDMotorRight.Proportion * iError            //比例项
           + PIDMotorRight.Integral * PIDMotorRight.SumError   //积分项
           + PIDMotorRight.Derivative * dError
           );
    Motor_Duty(MotR,speedRight);
}
