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
    
    iError = PIDServo.SetPoint - NextPoint;       //ƫ��
    PIDServo.SumError += iError;       //����
    dError = iError - PIDServo.LastError;     //΢��
    PIDServo.LastError = iError;

    servo = (int)(SERVOMEDIAN + PIDServo.Proportion * iError            //������
//           + PIDServo.Integral * PIDServo.SumError   //������
           + PIDServo.Derivative * dError
           );
    Servo_Duty(servo);
//    sprintf(txt,"%04d",server);
//    LCD_P6x8Str(40,1,(u8*)txt);

}


void MotorLeftLocPIDCalc(int NextPoint){
    int  iError,dError;
    char txt[16];

    iError = PIDMotorLeft.SetPoint - NextPoint;       //ƫ��
    PIDMotorLeft.SumError += iError;       //����
    dError = iError - PIDMotorLeft.LastError;     //΢��
    PIDMotorLeft.LastError = iError;

    speedLeft = (int)(PIDMotorLeft.SetPoint + PIDMotorLeft.Proportion * iError            //������
           + PIDMotorLeft.Integral * PIDMotorLeft.SumError   //������
           + PIDMotorLeft.Derivative * dError
           );
    Motor_Duty(MotL,speedLeft);
    
}

void MotorRightLocPIDCalc(int NextPoint){
    int  iError,dError;
    char txt[16];

    iError = PIDMotorRight.SetPoint - NextPoint;       //ƫ��
    PIDMotorRight.SumError += iError;       //����
    dError = iError - PIDMotorRight.LastError;     //΢��
    PIDMotorRight.LastError = iError;

    speedRight = (int)( PIDMotorRight.SetPoint + PIDMotorRight.Proportion * iError            //������
           + PIDMotorRight.Integral * PIDMotorRight.SumError   //������
           + PIDMotorRight.Derivative * dError
           );
    Motor_Duty(MotR,speedRight);
}
