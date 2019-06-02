#ifndef __PID_H__
#define __PID_H__

void ServoLocPIDCalc(int NextPoint);
void MotorLeftLocPIDCalc(int NextPoint);
void MotorRightLocPIDCalc(int NextPoint);
void PidSet(void);

typedef struct
{
    int  SetPoint;              //�趨Ŀ�� Desired Value
    long SumError;              //����ۼ�
    double  Proportion;         //�������� Proportional Cons
    double  Integral;           //���ֳ��� Integral Const
    double  Derivative;         //΢�ֳ��� Derivative Const
    int LastError;              //Error[-1]
    int PrevError;              //Error[-2]
} PID;

extern PID PIDServo, PIDMotorLeft, PIDMotorRight;
extern short servo, speedRight, speedLeft, SERVOMEDIAN, SPEEDRIGHT, SPEEDLEFT;


#endif 
