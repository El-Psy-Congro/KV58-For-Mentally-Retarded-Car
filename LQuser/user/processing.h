#ifndef _PROCESSING_H
#define _PROCESSING_H

extern int16 servoMedian;

void GyroAngleProcessing();
int GraphProcessingOfEdgeFluctuation();
int ElectromagnetismProcessingOfBasics();
uint8_t ElectromagnetismProcessingOfLoseDataForStop();

#endif
