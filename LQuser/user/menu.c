#include "include.h"

#define NUMBEROFMENUS 7
#define NUMBEROFSPEED 2
#define NUMBEROFPID 3
#define NUMBEROFMOTORPID 6

short menuSelection = 0;
short menuSwitch = 0;
short temp;

void menu(){
  char txt[16];
  

  


  if(!KEY_Read(left)){
    time_delay_ms(100);
    if(!KEY_Read(left)){
      menuSelection --;
      LCD_CLS();
    }
  }else if(!KEY_Read(right)){
    time_delay_ms(100);
    if(!KEY_Read(right)){
      menuSelection ++;
      LCD_CLS();
    }
  }

  if(menuSelection < 0){
    menuSelection = NUMBEROFMENUS - 1;
  }
  menuSelection = menuSelection%NUMBEROFMENUS;
  
  if(menuSelection == 0){
    LCD_Show_Frame100(); 
    Draw_Road();
    LCD_P8x16Str(0,0,"Camera Image");
    sprintf(txt,"%03d",Threshold);
    LCD_P6x8Str(100,1,(u8*)txt);
  }else if(menuSelection == 1){         //PID Adjust

    if(!KEY_Read(Middle)){
      time_delay_ms(100);
      if(!KEY_Read(Middle)){
        menuSwitch++;
        LCD_CLS();
      }
    }
    menuSwitch = menuSwitch%NUMBEROFPID;

    if(!KEY_Read(Up)){
      time_delay_ms(100);
      if(!KEY_Read(Up)){
        if(menuSwitch == 0){
          PIDServo.Proportion += 0.001;
        }else if(menuSwitch == 1){
          PIDServo.Integral += 0.001;
        }else{
          PIDServo.Derivative += 0.001;
        }
      }
    }else if(!KEY_Read(Down)){
      time_delay_ms(100);
      if(!KEY_Read(Down)){
        if(menuSwitch == 0){
          PIDServo.Proportion -= 0.001;
        }else if(menuSwitch == 1){
          PIDServo.Integral -= 0.001;
        }else{
          PIDServo.Derivative -= 0.001;
        }
      }
    }


    temp = (int)(PIDServo.Proportion*1000);
    sprintf(txt,"P:%04d",temp);
    LCD_P8x16Str(20,2,(u8*)txt);

    temp = (int)(PIDServo.Integral*1000);
    sprintf(txt,"I:%04d",temp);
    LCD_P8x16Str(20,4,(u8*)txt);

    temp = (int)(PIDServo.Derivative*1000);
    sprintf(txt,"D:%04d",temp);
    LCD_P8x16Str(20,6,(u8*)txt);


    LCD_P8x16Str(0,0,"PID Adjust");
    LCD_P8x16Str(0,(menuSwitch+1)*2,"->");

  }else if(menuSelection == 2){         //Speed Adjust
    if(!KEY_Read(Middle)){
      time_delay_ms(100);
      if(!KEY_Read(Middle)){
        menuSwitch ++;
        LCD_CLS();
      }
    }

    menuSwitch = menuSwitch%NUMBEROFSPEED;

    if(!KEY_Read(Up)){
      time_delay_ms(100);
      if(!KEY_Read(Up)){
        if(menuSwitch == 0){
          PIDMotorLeft.SetPoint += 10;
          LCD_CLS();
        }else{
          PIDMotorRight.SetPoint += 10;
          LCD_CLS();
        }
      }
    }else if(!KEY_Read(Down)){
      time_delay_ms(100);
      if(!KEY_Read(Down)){
        if(menuSwitch == 0){
          PIDMotorLeft.SetPoint -= 10;
          LCD_CLS();
        }else{
          PIDMotorRight.SetPoint -= 10;
          LCD_CLS();
        }
      }
    }




    sprintf(txt,"L:%04d   %04d",PIDMotorLeft.SetPoint, speedLeftGet);
    LCD_P8x16Str(10,4,(u8*)txt);

    sprintf(txt,"R:%04d   %04d",PIDMotorRight.SetPoint, speedRightGet);
    LCD_P8x16Str(10,6,(u8*)txt);


    LCD_P8x16Str(0,0,"Speed Adjust");
    LCD_P8x16Str(30,2,"SET");
    LCD_P8x16Str(80,2,"Actual");
    LCD_P8x16Str(0,(menuSwitch+1)*2+2,">");

  }else if(menuSelection == 3){         //Servo Adjust
    if(!KEY_Read(Up)){
      time_delay_ms(100);
      if(!KEY_Read(Up)){
        SERVOMEDIAN += 10;
      }
    }else if(!KEY_Read(Down)){
      time_delay_ms(100);
      if(!KEY_Read(Down)){
        SERVOMEDIAN -= 10;
      }
    }
    sprintf(txt," Median:%04d",SERVOMEDIAN);
    LCD_P8x16Str(20,4,(u8*)txt);

    sprintf(txt,"Current:%04d",servo);
    LCD_P8x16Str(20,2,(u8*)txt);

    LCD_P8x16Str(0,0,"Servo Adjust");

  }else if(menuSelection == 4){         //Speed Show

    if(!KEY_Read(Middle)){
      time_delay_ms(100);
      if(!KEY_Read(Middle)){
        menuSwitch++;
        LCD_CLS();
      }
    }
    menuSwitch = menuSwitch%NUMBEROFMOTORPID;

    if(!KEY_Read(Up)){
      time_delay_ms(100);
      if(!KEY_Read(Up)){
        if(menuSwitch == 0){
          PIDMotorLeft.Proportion += 0.001;
        }else if(menuSwitch == 1){
          PIDMotorLeft.Integral += 0.001;
        }else if(menuSwitch == 2){
          PIDMotorLeft.Derivative += 0.001;
        }else if(menuSwitch == 3){
          PIDMotorRight.Proportion += 0.001;
        }else if(menuSwitch == 4){
          PIDMotorRight.Integral += 0.001;
        }else if(menuSwitch == 5){
          PIDMotorRight.Derivative += 0.001;
        }
      }
    }else if(!KEY_Read(Down)){
      time_delay_ms(100);
      if(!KEY_Read(Down)){
        if(menuSwitch == 0){
          PIDMotorLeft.Proportion -= 0.001;
        }else if(menuSwitch == 1){
          PIDMotorLeft.Integral -= 0.001;
        }else if(menuSwitch == 2){
          PIDMotorLeft.Derivative -= 0.001;
        }else if(menuSwitch == 3){
          PIDMotorRight.Proportion -= 0.001;
        }else if(menuSwitch == 4){
          PIDMotorRight.Integral -= 0.001;
        }else if(menuSwitch == 5){
          PIDMotorRight.Derivative -= 0.001;
        }
      }
    }


    temp = (int)(PIDMotorLeft.Proportion*1000);
    sprintf(txt,"P:%04d",temp);
    LCD_P8x16Str(10,2,(u8*)txt);

    temp = (int)(PIDMotorLeft.Integral*1000);
    sprintf(txt,"I:%04d",temp);
    LCD_P8x16Str(10,4,(u8*)txt);

    temp = (int)(PIDMotorLeft.Derivative*1000);
    sprintf(txt,"D:%04d",temp);
    LCD_P8x16Str(10,6,(u8*)txt);

    temp = (int)(PIDMotorRight.Proportion*1000);
    sprintf(txt,"P:%04d",temp);
    LCD_P8x16Str(80,2,(u8*)txt);

    temp = (int)(PIDMotorRight.Integral*1000);
    sprintf(txt,"I:%04d",temp);
    LCD_P8x16Str(80,4,(u8*)txt);

    temp = (int)(PIDMotorRight.Derivative*1000);
    sprintf(txt,"D:%04d",temp);
    LCD_P8x16Str(80,6,(u8*)txt);


    LCD_P8x16Str(0,0,"MotorPID Adjust");
    if((menuSwitch+1)*2 < 8){
      LCD_P8x16Str(0,(menuSwitch+1)*2,">");
    }else{
      LCD_P8x16Str(70,(menuSwitch+1)*2-6,">");
    }

  }else if(menuSelection == 5){
    LCD_P6x8Str(40,1,"5");
  }else if(menuSelection == 6){
    LCD_P6x8Str(40,1,"6");
  }
  



}
