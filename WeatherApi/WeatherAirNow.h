#ifndef WEATHER_AIRNOW_H
#define WEATHER_AIRNOW_H

#include "WeatherBaseInfo.h"
#include <QDateTime>

class WeatherAirNow : public WeatherBaseInfo
{
    Q_OBJECT

public:
    struct AirQualityCity
    {
        int aqi;                //	空气质量指数，AQI和PM25的关系	74
        QString main;           //	主要污染物	pm25
        QString qlty;           //	空气质量，取值范围:优，良，轻度污染，中度污染，重度污染，严重污染，查看计算方式	良
        int pm10;               //	pm10	78
        int pm25;               //	pm25	66
        float no2;                //	二氧化氮	40
        float so2;                //	二氧化硫	30
        float co;                 //	一氧化碳	33
        float o3;                 //	臭氧	20
    };
public:
    WeatherAirNow();
    ~WeatherAirNow();

    // 处理空气质量的数据
    void disposeWeatherInfo(QJsonObject &jsonObject) override;
    // 获取空气质量
    AirQualityCity getAirQualityCity(void);

private:
    AirQualityCity m_AirQualityCity;
};

#endif
