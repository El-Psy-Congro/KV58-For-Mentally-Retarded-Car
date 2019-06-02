#ifndef _PROCESSING_H
#define _PROCESSING_H

#define L_0 ADC0_DP1
#define L_3 ADC0_SE5a
#define L_4 ADC0_DP2
#define L_5 ADC0_DP3
#define L_2 ADC0_SE11
#define L_1 ADC0_SE9
#define L_7 ADC0_SE4a
#define L_6 ADC0_SE10


extern int32 servoMedian, servo, angle, gyroLast;
extern float angleFromGyro, angleFromAcceleration;
extern s8 kernelImage[GRAPH_HIGHT][GRAPH_WIDTH], gaussianImage[GRAPH_HIGHT][GRAPH_WIDTH];
extern bool
isIslandLeft,
isIslandRight;



int DataFusion();

int GraphProcessing();
int GraphProcessingOfEdgeFluctuation();
void GraphProcessingOfLineEdgeFluctuation();
void GraphProcessingOfLineScanFromMedian(int i);
void GraphProcessingOfLineScanFromSettingPoint(int i, int m);
void GraphProcessingOfLineScanFromCentralDiffusion(int i);
s8 GraphProcessingOfLineScanFromEdge(int i);
s8 GraphProcessingOfLineScanFromQuarters(int i);
int GraphProcessingOfLineWhitePointCounting(int i, int n, int m);
int GraphProcessingOfSquareAreaWhitePointCounting(int x, int y, int area);
bool IsDisconnectRoad();
bool IsStaightLine(s8 line[], bool isExistence[], u8 initial, u8 half, u8 allowableError, float MIissing);
bool GraphProcessingOfEnteringIslandforLeft();
bool GraphProcessingOfEnteringIslandforRight();
int GraphProcessingOfCannyEdgeDetection();


int ElectromagnetismProcessing();
int ElectromagnetismProcessingOfBasics();
int ElectromagnetismProcessingOfIsland();
bool ElectromagnetismProcessingOfLoseDataForStop();

void GyroAngleProcessing();

#endif
