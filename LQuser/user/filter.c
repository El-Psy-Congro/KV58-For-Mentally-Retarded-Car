#include "include.h"

#define PI 3.141592653589793f

void KalmanFiltering(){

}

int ButtterworthLowPassFiltering(){

}

int LinearRCLowPassFiltering(){

}


//���װ�����˹ ��ͨ�˲���ֹƵ���趨    �ο� �ɶ���Ϣ���̴�ѧ ����WD��      ��    CSDN����  https://blog.csdn.net/sszhouplus/article/details/43113505
void SetCutoffFrequency(float sampleFrequent, float cutoffFrequent,butterworthParameter *LowPassFilter){
    float fr = sampleFrequent / cutoffFrequent;
    float ohm = tanf(PI / fr);
    float c = 1.0f + 2.0f * cosf(PI / 4.0f) * ohm + ohm * ohm;
    if (cutoffFrequent <= 0.0f) {
        // no filtering
        return;
    }
    LowPassFilter->b[0] = ohm * ohm / c;
    LowPassFilter->b[1] = 2.0f * LowPassFilter->b[0];
    LowPassFilter->b[2] = LowPassFilter->b[0];
    LowPassFilter->a[0]=1.0f;
    LowPassFilter->a[1] = 2.0f * (ohm * ohm - 1.0f) / c;
    LowPassFilter->a[2] = (1.0f - 2.0f * cosf(PI / 4.0f) * ohm + ohm * ohm) / c;
}
