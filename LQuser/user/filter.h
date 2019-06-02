#ifndef _FILTER_H_
#define _FILTER_H_

typedef struct
{
 float Input_Butter[3];
 float Output_Butter[3];
}butterworthData;

typedef struct
{
  float a[3];
  float b[3];
}butterworthParameter;

#endif
