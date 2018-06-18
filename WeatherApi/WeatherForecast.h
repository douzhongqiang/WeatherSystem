#ifndef WATHER_FORECAST_H
#define WATHER_FORECAST_H
#include "WeatherBaseInfo.h"
#include <QDate>
#include <QTime>

class WeatherForecast : public WeatherBaseInfo
{
    Q_OBJECT

public:
    struct DailyForecast
    {
        QDate date;             //	预报日期	2013-12-30
        QTime sr;               //  日出时间	07:36
        QTime ss;               //	日落时间	16:58
        QTime mr;               //	月升时间	04:47
        QTime ms;               //	月落时间	14:59
        int tmp_max;            //	最高温度	4
        int tmp_min;            //	最低温度	-5
        int cond_code_d;        //	白天天气状况代码	100
        int cond_code_n;        //	晚间天气状况代码	100
        QString cond_txt_d;     //	白天天气状况描述	晴
        QString cond_txt_n;     //	晚间天气状况描述	晴
        int wind_deg;           //	风向360角度	310
        QString wind_dir;       //	风向	西北风
        QString wind_sc;        //	风力	1-2
        int wind_spd;           //	风速，公里/小时	14
        int hum;                //  相对湿度	37
        int pcpn;               //	降水量	0
        int pop;                //	降水概率	0
        int pres;               //	大气压强	1018
        int uv_index;           //	紫外线强度指数	3
        int vis;                //	能见度，单位：公里	10
    };

public:
    WeatherForecast();
    ~WeatherForecast();

    // 获取三天的天气数据
    QList<DailyForecast> getDailyForecast(void);

    // 处理预报的数据
    void disposeWeatherInfo(QJsonObject &jsonObject) override;

private:
    QList<DailyForecast> m_DailyForecastList;
};

#endif
