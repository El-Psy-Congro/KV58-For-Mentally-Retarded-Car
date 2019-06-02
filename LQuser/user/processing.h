#ifndef _PROCESSING_H
#define _PROCESSING_H


extern int32 servoMedian, servo, angle;

void GyroAngleProcessing();

int GraphProcessing();
int GraphProcessingOfEdgeFluctuation();

int ElectromagnetismProcessing();
int ElectromagnetismProcessingOfBasics();
bool ElectromagnetismProcessingOfLoseDataForStop();

#endif
