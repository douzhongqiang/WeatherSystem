#ifndef WEATHER_BASE_INFO_H
#define WEATHER_BASE_INFO_H

#include <QObject>
#include <QJsonObject>
class WeatherBaseInfo : public QObject
{
public:
    WeatherBaseInfo(QObject *parent = nullptr);
    ~WeatherBaseInfo();

public:
    virtual void disposeWeatherInfo(QJsonObject &jsonObject) = 0;
};

#endif
