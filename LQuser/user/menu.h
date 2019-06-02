#ifndef __MENU_H__
#define __MENU_H__

void Menu();
void MenuInit();
void MenuAdd(u8 size,char text, unsigned char x, unsigned char y );
void MenuPageAdd(void (*aPage)(void));


void MenuOfCameraImage();
void MenuOfServo();
void MenuOfMotorLeft();
void MenuOfMotorRight();
void MenuOfGyro();
void MenuOfADCshow();
void MenuOfADCMedia();
void MenuOfSpeedMeasure();
void MenuOfERECT();

typedef struct menues{
  void (*page)(void);
  struct menues *next;
  struct menues *last;
}menu;

typedef struct{
  double value[5];
}menuValue;

#endif 
