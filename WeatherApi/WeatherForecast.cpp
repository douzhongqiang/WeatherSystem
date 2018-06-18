#include "WeatherForecast.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonParseError>

WeatherForecast::WeatherForecast()
{
    m_DailyForecastList.clear();
}

WeatherForecast::~WeatherForecast()
{

}

QList<WeatherForecast::DailyForecast> WeatherForecast::getDailyForecast(void)
{
    return m_DailyForecastList;
}

void WeatherForecast::disposeWeatherInfo(QJsonObject &jsonObjects)
{
    // 解析天气预报
    if (jsonObjects.contains("daily_forecast"))
    {
        if (!jsonObjects.value("daily_forecast").isArray())
            return;

        m_DailyForecastList.clear();
        QJsonArray jsonArray = jsonObjects.value("daily_forecast").toArray();
        for (int i=0; i<jsonArray.count(); ++i)
        {
            QJsonObject jsonObject = jsonArray.at(i).toObject();
            DailyForecast dailyForecast;
            dailyForecast.date = QDate::fromString(jsonObject.value("date").toString(), "yyyy-MM-dd");
            dailyForecast.sr = QTime::fromString(jsonObject.value("sr").toString(), "hh:mm");  //  日出时间	07:36
            dailyForecast.ss = QTime::fromString(jsonObject.value("ss").toString(), "hh:mm");  //	日落时间	16:58
            dailyForecast.mr = QTime::fromString(jsonObject.value("mr").toString(), "hh:mm");  //	月升时间	04:47
            dailyForecast.ms = QTime::fromString(jsonObject.value("ms").toString(), "hh:mm");  //	月落时间	14:59
            dailyForecast.tmp_max = jsonObject.value("tmp_max").toString().toInt();            //	最高温度	4
            dailyForecast.tmp_min = jsonObject.value("tmp_min").toString().toInt();            //	最低温度	-5
            dailyForecast.cond_code_d = jsonObject.value("cond_code_d").toString().toInt();        //	白天天气状况代码	100
            dailyForecast.cond_code_n = jsonObject.value("cond_code_n").toString().toInt();        //	晚间天气状况代码	100
            dailyForecast.cond_txt_d = jsonObject.value("cond_txt_d").toString();     //	白天天气状况描述	晴
            dailyForecast.cond_txt_n = jsonObject.value("cond_txt_n").toString();     //	晚间天气状况描述	晴
            dailyForecast.wind_deg = jsonObject.value("wind_deg").toString().toInt();           //	风向360角度	310
            dailyForecast.wind_dir = jsonObject.value("wind_dir").toString();       //	风向	西北风
            dailyForecast.wind_sc = jsonObject.value("wind_sc").toString();        //	风力	1-2
            dailyForecast.wind_spd = jsonObject.value("wind_spd").toString().toInt();           //	风速，公里/小时	14
            dailyForecast.hum = jsonObject.value("hum").toString().toInt();                //  相对湿度	37
            dailyForecast.pcpn = jsonObject.value("pcpn").toString().toInt();               //	降水量	0
            dailyForecast.pop = jsonObject.value("pop").toString().toInt();                //	降水概率	0
            dailyForecast.pres = jsonObject.value("pres").toString().toInt();               //	大气压强	1018
            dailyForecast.uv_index = jsonObject.value("uv_index").toString().toInt();           //	紫外线强度指数	3
            dailyForecast.vis = jsonObject.value("vis").toString().toInt();                //	能见度，单位：公里	10
            m_DailyForecastList.push_back(dailyForecast);
        }
    }
}
