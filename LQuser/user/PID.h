#ifndef __PID_H__
#define __PID_H__

void ServoLocPIDCalc(int NextPoint);
void MotorLeftLocPIDCalc(int NextPoint);
void MotorRightLocPIDCalc(int NextPoint);
void PidSet(void);

typedef struct
{
    int  SetPoint;              //设定目标 Desired Value
    long SumError;              //误差累计
    double  Proportion;         //比例常数 Proportional Cons
    double  Integral;           //积分常数 Integral Const
    double  Derivative;         //微分常数 Derivative Const
    int LastError;              //Error[-1]
    int PrevError;              //Error[-2]
} PID;

extern PID PIDServo, PIDMotorLeft, PIDMotorRight;
extern short servo, speedRight, speedLeft, SERVOMEDIAN, SPEEDRIGHT, SPEEDLEFT;


#endif 
