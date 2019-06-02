#include "include.h"

#define NUMBER_OF_MENUS 7
#define NUMBER_OF_SPEED 2
#define NUMBER_OF_PID 4
#define NUMBER_OF_MOTOR 4
#define NUMBER_OF_ERECT 4
#define NUMBER_OF_ADC 5
#define VARIATION_SPEED_PID 0.1
#define VARIATION_SERVO_PID 0.001
#define VARIATION_ERECT_PID 0.001
#define VARIATION_SPEED 10
#define VARIATION_ERECT 20
#define VARIATION_SERVO_MEDIA 10




short menuSelection = 0;
short menuSwitch = 0;
short temp;

menu *head = NULL, *menus;
short menuPages = 0;
char txt[16];

void MenuInit(){
  MenuPageAdd(MenuOfCameraImage);
  MenuPageAdd(MenuOfServo);
  MenuPageAdd(MenuOfMotorLeft);
  MenuPageAdd(MenuOfMotorRight);
  MenuPageAdd(MenuOfERECT);
  MenuPageAdd(MenuOfGyro);
  MenuPageAdd(MenuOfADCshow);
//  MenuPageAdd(MenuOfADCMedia);
//  MenuPageAdd(menuOfSpeedMeasure);
  menus = head;
}

void Menu(){

  if(!KEY_Read(left)){
      time_delay_ms(70);
      if(!KEY_Read(left)){
        menus = menus->last;
        LCD_CLS();
      }
    }else if(!KEY_Read(right)){
      time_delay_ms(70);
      if(!KEY_Read(right)){
        menus = menus->next;
        LCD_CLS();
      }
    }
    

    (*menus->page)();
}

void MenuPageAdd(void (*aPage)(void)) {
  menu *node = NULL;
  node = (menu *)malloc(sizeof(menu));
  if(!head){
    head = node;
  }

  menus = head;
  node->next = head;
  node->page = aPage;

  while(!(menus->next == head)){
    menus = menus->next;
  }
  node->last = menus;
  menus->next = node;
  head->last = node;
}


void MenuOfCameraImage(){
  LCD_Show_Frame100();
  Draw_Road();
  LCD_P8x16Str(0,0,"GraphP");
  sprintf(txt,"%03d",threshold);
  LCD_P6x8Str(100,1,(u8*)txt);
}


void MenuOfERECT(){
  if (!KEY_Read(middle)) {
    time_delay_ms(100);
    if (!KEY_Read(middle)) {
      menuSwitch++;
      LCD_CLS();
    }
  }

  if (!KEY_Read(up)) {
    time_delay_ms(100);
    if (!KEY_Read(up)) {
      if (menuSwitch == 0) {
        PIDErect.proportion += VARIATION_ERECT_PID;
      } else if (menuSwitch == 1) {
        PIDErect.integral += VARIATION_ERECT_PID;
      } else if (menuSwitch == 2) {
        PIDErect.derivative += VARIATION_ERECT_PID;
      } else if (menuSwitch == 3) {
        PIDErect.setPoint += VARIATION_ERECT;
      }
    }
  }else if(!KEY_Read(down)) {
    time_delay_ms(100);
    if (!KEY_Read(down)) {
      if (menuSwitch == 0) {
        PIDErect.proportion -= VARIATION_ERECT_PID;
      } else if (menuSwitch == 1) {
        PIDErect.integral -= VARIATION_ERECT_PID;
      } else if (menuSwitch == 2) {
        PIDErect.derivative -= VARIATION_ERECT_PID;
      } else if (menuSwitch == 3) {
        PIDErect.setPoint -= VARIATION_ERECT;
      }
    }
  }

  menuSwitch = menuSwitch % NUMBER_OF_ERECT;

  temp = (int) (PIDErect.proportion * (1/VARIATION_ERECT_PID));
  sprintf(txt, "P:%04d", temp);
  LCD_P8x16Str(10, 2, (u8*) txt);

  temp = (int) (PIDErect.integral * (1/VARIATION_ERECT_PID));
  sprintf(txt, "I:%04d", temp);
  LCD_P8x16Str(10, 4, (u8*) txt);

  temp = (int) (PIDErect.derivative * (1/VARIATION_ERECT_PID));
  sprintf(txt, "D:%04d", temp);
  LCD_P8x16Str(10, 6, (u8*) txt);


  sprintf(txt, "%04d", PIDErect.setPoint);
  LCD_P8x16Str(80, 4, (u8*) txt);

  sprintf(txt, "%04d", speedRightGet);
  LCD_P8x16Str(80, 6, (u8*) txt);

  LCD_P8x16Str(0, 0, "Erect");
  LCD_P8x16Str(70, 2, "Bary");
  if ((menuSwitch + 1) * 2 < 8) {
    LCD_P8x16Str(0, (menuSwitch + 1) * 2, ">");
  } else {
    LCD_P8x16Str(70, (menuSwitch + 1) * 2 - 4, ">");
  }


}


void MenuOfMotorRight(){
  if (!KEY_Read(middle)) {
    time_delay_ms(100);
    if (!KEY_Read(middle)) {
      menuSwitch++;
      LCD_CLS();
    }
  }
  menuSwitch = menuSwitch % NUMBER_OF_MOTOR;

  if (!KEY_Read(up)) {
    time_delay_ms(100);
    if (!KEY_Read(up)) {
      if (menuSwitch == 0) {
        PIDMotorRight.proportion += VARIATION_SPEED_PID;
      } else if (menuSwitch == 1) {
        PIDMotorRight.integral += VARIATION_SPEED_PID;
      } else if (menuSwitch == 2) {
        PIDMotorRight.derivative += VARIATION_SPEED_PID;
      } else if (menuSwitch == 3) {
        PIDMotorRight.setPoint += VARIATION_SPEED;
      }
    }
  }else if(!KEY_Read(down)) {
    time_delay_ms(100);
    if (!KEY_Read(down)) {
      if (menuSwitch == 0) {
        PIDMotorRight.proportion -= VARIATION_SPEED_PID;
      } else if (menuSwitch == 1) {
        PIDMotorRight.integral -= VARIATION_SPEED_PID;
      } else if (menuSwitch == 2) {
        PIDMotorRight.derivative -= VARIATION_SPEED_PID;
      } else if (menuSwitch == 3) {
        PIDMotorRight.setPoint -= VARIATION_SPEED;
      }
    }
  }

  temp = (int) (PIDMotorRight.proportion * (1/VARIATION_SPEED_PID));
  sprintf(txt, "P:%04d", temp);
  LCD_P8x16Str(10, 2, (u8*) txt);

  temp = (int) (PIDMotorRight.integral * (1/VARIATION_SPEED_PID));
  sprintf(txt, "I:%04d", temp);
  LCD_P8x16Str(10, 4, (u8*) txt);

  temp = (int) (PIDMotorRight.derivative * (1/VARIATION_SPEED_PID));
  sprintf(txt, "D:%04d", temp);
  LCD_P8x16Str(10, 6, (u8*) txt);


  sprintf(txt, "%04d", PIDMotorRight.setPoint);
  LCD_P8x16Str(80, 4, (u8*) txt);

  sprintf(txt, "%04d", speedRightGet);
  LCD_P8x16Str(80, 6, (u8*) txt);

  LCD_P8x16Str(0, 0, "Right Motor");
  LCD_P8x16Str(80, 2, "Speed");
  if ((menuSwitch + 1) * 2 < 8) {
    LCD_P8x16Str(0, (menuSwitch + 1) * 2, ">");
  } else {
    LCD_P8x16Str(70, (menuSwitch + 1) * 2 - 4, ">");
  }

}

void MenuOfMotorLeft(){
  if (!KEY_Read(middle)) {
    time_delay_ms(100);
    if (!KEY_Read(middle)) {
      menuSwitch++;
      LCD_CLS();
    }
  }
  menuSwitch = menuSwitch % NUMBER_OF_MOTOR;

  if (!KEY_Read(up)) {
    time_delay_ms(100);
    if (!KEY_Read(up)) {
      if (menuSwitch == 0) {
        PIDMotorLeft.proportion += VARIATION_SPEED_PID;
      } else if (menuSwitch == 1) {
        PIDMotorLeft.integral += VARIATION_SPEED_PID;
      } else if (menuSwitch == 2) {
        PIDMotorLeft.derivative += VARIATION_SPEED_PID;
      } else if (menuSwitch == 3) {
        PIDMotorLeft.setPoint += VARIATION_SPEED;
      }
    }
  } else if (!KEY_Read(down)) {
    time_delay_ms(100);
    if (!KEY_Read(down)) {
      if (menuSwitch == 0) {
        PIDMotorLeft.proportion -= VARIATION_SPEED_PID;
      } else if (menuSwitch == 1) {
        PIDMotorLeft.integral -= VARIATION_SPEED_PID;
      } else if (menuSwitch == 2) {
        PIDMotorLeft.derivative -= VARIATION_SPEED_PID;
      } else if (menuSwitch == 3) {
        PIDMotorLeft.setPoint -= VARIATION_SPEED;
      }
    }
  }

  temp = (int) (PIDMotorLeft.proportion * (1/VARIATION_SPEED_PID));
  sprintf(txt, "P:%04d", temp);
  LCD_P8x16Str(10, 2, (u8*) txt);

  temp = (int) (PIDMotorLeft.integral * (1/VARIATION_SPEED_PID));
  sprintf(txt, "I:%04d", temp);
  LCD_P8x16Str(10, 4, (u8*) txt);

  temp = (int) (PIDMotorLeft.derivative * (1/VARIATION_SPEED_PID));
  sprintf(txt, "D:%04d", temp);
  LCD_P8x16Str(10, 6, (u8*) txt);


  sprintf(txt, "%04d", PIDMotorLeft.setPoint);
  LCD_P8x16Str(80, 4, (u8*) txt);

  sprintf(txt, "%04d", speedLeftGet);
  LCD_P8x16Str(80, 6, (u8*) txt);

  LCD_P8x16Str(0, 0, "Left Motor");
  LCD_P8x16Str(80, 2, "Speed");
  if ((menuSwitch + 1) * 2 < 8) {
    LCD_P8x16Str(0, (menuSwitch + 1) * 2, ">");
  } else {
    LCD_P8x16Str(70, (menuSwitch + 1) * 2 - 4, ">");
  }

}

void MenuOfServo(){
  if(!KEY_Read(middle)){
    time_delay_ms(100);
    if(!KEY_Read(middle)){
      menuSwitch++;
      LCD_CLS();
    }
  }
  menuSwitch = menuSwitch%NUMBER_OF_PID;

  if(!KEY_Read(up)){
    time_delay_ms(100);
    if(!KEY_Read(up)){
      if(menuSwitch == 0){
        PIDServo.proportion += VARIATION_SERVO_PID;
      }else if(menuSwitch == 1){
        PIDServo.integral += VARIATION_SERVO_PID;
      }else if(menuSwitch == 2){
        PIDServo.derivative += VARIATION_SERVO_PID;
      }else if(menuSwitch == 3){
        servoMedian += VARIATION_SERVO_MEDIA;
      }
    }
  }else if(!KEY_Read(down)){
    time_delay_ms(100);
    if(!KEY_Read(down)){
      if(menuSwitch == 0){
        PIDServo.proportion -= VARIATION_SERVO_PID;
      }else if(menuSwitch == 1){
        PIDServo.integral -= VARIATION_SERVO_PID;
      }else if(menuSwitch == 2){
        PIDServo.derivative -= VARIATION_SERVO_PID;
      }else if(menuSwitch == 3){
        servoMedian -= VARIATION_SERVO_MEDIA;
      }
    }
  }

  temp = (int)(PIDServo.proportion * (1/VARIATION_SERVO_PID));
  sprintf(txt,"P:%04d",temp);
  LCD_P8x16Str(20,2,(u8*)txt);

  temp = (int)(PIDServo.integral * (1/VARIATION_SERVO_PID));
  sprintf(txt,"I:%04d",temp);
  LCD_P8x16Str(20,4,(u8*)txt);

  temp = (int)(PIDServo.derivative * (1/VARIATION_SERVO_PID));
  sprintf(txt,"D:%04d",temp);
  LCD_P8x16Str(20,6,(u8*)txt);

  sprintf(txt, "MEDIAN");
  LCD_P8x16Str(80, 2, (u8*) txt);

  sprintf(txt, "%04d", servoMedian);
  LCD_P8x16Str(80, 4, (u8*) txt);

  sprintf(txt, "%04d", servo);
  LCD_P8x16Str(80, 6, (u8*) txt);


  LCD_P8x16Str(0,0,"Servo Adjust");
    
  if(menuSwitch == 3){
  LCD_P8x16Str(70,4,">");
  }else{
    LCD_P8x16Str(0,(menuSwitch+1)*2,"->");
  }


}


void MenuOfGyro(){
//  u16 tem=0;
//  float fv=0.01;
//  char  txt[16]="X:";
//  Update9AX();
//  if (GYRO_X.MYBYTE.BYTEH > 0x7F)            //判断加速度X轴正负,此处为负值
//  {
//    tem = (~(GYRO_X.MYWORD >> 2) + 1) & 0X3FFF;  //把补码数值转换为有效值
//  } else                                    //正数情况处理
//  {
//    tem = (GYRO_X.MYWORD >> 2) & 0X3FFF;          //转换为有效值
//  }
//  sprintf(txt, "DJ0:%04d", GYRO_Y.MYWORD);             //数值转换为字符串
//  LCD_P8x16Str(10, 0, (uint8*) txt);          //OLED屏显示转向数值
//
//  //转换为加速度数值
//  Cvt_14bit_Str(txt, ACC_X);                //加速度数值专为固定格式字符串，方便屏幕显示
//  LCD_P6x8Str(10, 4, (uint8*) txt);           //OLED屏显示数值
//
//  //温度检测
//  if (LQ9AX_DAT[18] > 0x7F)                   //温度位正数0--125°
//  {
//    LCD_P6x8Str(10, 6, (uint8*) "low temp  ");    //OLED屏显示数值
//  } else {
//    sprintf(txt, "temp:+%03d ", LQ9AX_DAT[18]);  //转换为字符串
//    LCD_P6x8Str(10, 6, (uint8*) txt);             //OLED屏显示数值
//  }
//  time_delay_ms(100);

    sprintf(txt, "DJ0:%04d", angle);             //数值转换为字符串
    LCD_P8x16Str(10, 0, (uint8*) txt);
}



void MenuOfADCshow(){
//  ADC0_Ch_e ADCRemawp[] = {ADC0_SE5a, ADC0_SE9, ADC0_DP1, ADC0_SE11, ADC0_DP3, ADC0_SE4a, ADC0_SE10, ADC0_DP2};
  ADC0_Ch_e ADCRemawp[] = {ADC0_DP1, ADC0_SE5a, ADC0_DP2, ADC0_DP3,  ADC0_SE11, ADC0_SE9, ADC0_SE4a, ADC0_SE10};
//  if(!KEY_Read(Up)){
//    time_delay_ms(100);
//    if(!KEY_Read(Up)){
//      menuSwitch++;
//    }
//  }else if(!KEY_Read(Down)){
//    time_delay_ms(100);
//    if(!KEY_Read(Down)){
//      menuSwitch--;
//      if(menuSwitch<0){
//       menuSwitch = NUMBEROFADC-1;
//      }
//  }
//
//  menuSwitch = menuSwitch % NUMBEROFADC;


  if(!KEY_Read(up)){
    time_delay_ms(100);
    if(!KEY_Read(up)){
      menuSwitch += 1;
    }
  }else if(!KEY_Read(down)){
    time_delay_ms(100);
    if(!KEY_Read(down)){
      menuSwitch -= 1;
      if(menuSwitch<0){
        menuSwitch = NUMBER_OF_ADC;
      }
    }
  }

  LCD_CLS();

  sprintf(txt,"ADC%d:%d",(menuSwitch+0)%(NUMBER_OF_ADC),ADC0_Ave(ADCRemawp[(menuSwitch+0)%(NUMBER_OF_ADC)],ADC_16bit,10));  //2
  LCD_P8x16Str(0,0,(u8*)txt);

  sprintf(txt,"ADC%d:%d",(menuSwitch+1)%(NUMBER_OF_ADC),ADC0_Ave(ADCRemawp[(menuSwitch+1)%(NUMBER_OF_ADC)],ADC_16bit,10)); //0
  LCD_P8x16Str(0,2,(u8*)txt);

  sprintf(txt,"ADC%d:%d",(menuSwitch+2)%(NUMBER_OF_ADC),ADC0_Ave(ADCRemawp[(menuSwitch+2)%(NUMBER_OF_ADC)],ADC_16bit,10)); //7
  LCD_P8x16Str(0,4,(u8*)txt);

  sprintf(txt,"ADC%d:%d",(menuSwitch+3)%(NUMBER_OF_ADC),ADC0_Ave(ADCRemawp[(menuSwitch+3)%(NUMBER_OF_ADC)],ADC_16bit,10)); //4
  LCD_P8x16Str(0,6,(u8*)txt);


  time_delay_ms(10);

}

void MenuOfADCMedia(){
  ADC0_Ch_e ADCRemawp[] = {ADC0_DP1, ADC0_SE5a, ADC0_DP2, ADC0_DP3,  ADC0_SE11, ADC0_SE9, ADC0_SE4a, ADC0_SE10};
  sprintf(txt,"ADC:%d",(int)(ADC0_Ave(ADCRemawp[3],ADC_16bit,10)-ADC0_Ave(ADCRemawp[0],ADC_16bit,10)+ADC0_Ave(ADCRemawp[2],ADC_16bit,10)-ADC0_Ave(ADCRemawp[1],ADC_16bit,10))*10000
                           /(ADC0_Ave(ADCRemawp[3],ADC_16bit,10)+ADC0_Ave(ADCRemawp[0],ADC_16bit,10)+ADC0_Ave(ADCRemawp[2],ADC_16bit,10)+ADC0_Ave(ADCRemawp[1],ADC_16bit,10)));
  LCD_P8x16Str(0,3,(u8*)txt);
}


void MenuOfSpeedMeasure(){

}

