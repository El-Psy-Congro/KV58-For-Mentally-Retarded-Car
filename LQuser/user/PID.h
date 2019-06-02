#ifndef __PID_H__
#define __PID_H__

typedef struct{
    int  setPoint;              //�趨Ŀ�� Desired Value
    long sumError;              //����ۼ�
    double  proportion;         //�������� Proportional Cons
    double  integral;           //���ֳ��� Integral Const
    double  derivative;         //΢�ֳ��� Derivative Const
    int lastError;              //Error[-1]
    int prevError;              //Error[-2]
    u8  isDeviation;              //����ֵ�Ƿ�����趨ֵ     1Ϊ���ӣ�   2Ϊ�����趨ֵ
} PID;

void PIDInit(void);
int PositionalPID(int NextPoint, PID *aPID);
int IncrementalPID(int NextPoint, PID *aPID);
//void ServoLocPIDCalc(int NextPoint);
//void MotorLeftLocPIDCalc(int NextPoint);
//void MotorRightLocPIDCalc(int NextPoint);
//void ErectLocPIDCalc(int NextPoint);

extern PID PIDServo, PIDMotorLeft, PIDMotorRight, PIDErect;


#endif 
