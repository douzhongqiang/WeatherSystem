#ifndef WEATHER_NOE_H
#define WEATHER_NOE_H

#include "WeatherBaseInfo.h"

class WeatherNow : public WeatherBaseInfo
{
    Q_OBJECT
public:
    struct WeatherNowInfo
    {
        int fl;                     //	体感温度，默认单位：摄氏度	23
        int tmp;                    //	温度，默认单位：摄氏度	21
        int cond_code;              //	实况天气状况代码	100
        QString cond_txt;           //	实况天气状况代码	晴
        int wind_deg;               //	风向360角度	305
        QString wind_dir;           //	风向	西北
        int wind_sc;                //	风力	3
        int wind_spd;               //	风速，公里/小时	15
        int hum;                    //	相对湿度	40
        int pcpn;                   //	降水量	0
        int pres;                   //	大气压强	1020
        int vis;                    //	能见度，默认单位：公里	10
        int cloud;                  //	云量	23
    };

public:
    WeatherNow();
    ~WeatherNow();

    // 获取天气数据
    WeatherNowInfo getNowWeatherInfo(void);

    // 处理预报的数据
    void disposeWeatherInfo(QJsonObject &jsonObject) override;

private:
    WeatherNowInfo m_WeatherNowInfo;
};

#endif
