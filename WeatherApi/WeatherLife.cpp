#include "WeatherLife.h"
#include <QJsonArray>
#include <QJsonObject>

WeatherLife::WeatherLife()
{
    m_LifeStyleDataList.clear();
}

WeatherLife::~WeatherLife()
{

}

void WeatherLife::disposeWeatherInfo(QJsonObject &jsonObject)
{
    if (jsonObject.contains("lifestyle"))
    {
        if (!jsonObject.value("lifestyle").isArray())
            return;

        QJsonArray jsonArray = jsonObject.value("lifestyle").toArray();
        for (int i=0; i<jsonArray.count(); ++i)
        {
            LifeStyleData lifeStyleData;

            QJsonObject jsObj = jsonArray.at(i).toObject();
            lifeStyleData.brf = jsObj.value("brf").toString();
            lifeStyleData.valueText = jsObj.value("txt").toString();
            lifeStyleData.lifeStyleType = lifeStyleStringToType(jsObj.value("type").toString());

            m_LifeStyleDataList.push_back(lifeStyleData);
        }
    }
}

QList<WeatherLife::LifeStyleData> WeatherLife::getLifeStyleInfoList(void)
{
    return m_LifeStyleDataList;
}

QString WeatherLife::convertToString(LifeStyleType type)
{
    if (LifeStyle_Comf == type)
        return "舒适度指数";
    else if (LifeStyle_Cw == type)
        return "洗车指数";
    else if (LifeStyle_Drsg == type)
        return "穿衣指数";
    else if (LifeStyle_Flu == type)
        return "感冒指数";
    else if (LifeStyle_Sport == type)
        return "运动指数";
    else if (LifeStyle_Trav == type)
        return "旅游指数";
    else if (LifeStyle_Uv == type)
        return "紫外线指数";
    else if (LifeStyle_Air == type)
        return "空气污染扩散条件指数";
    else if (LifeStyle_Ac == type)
        return "空调开启指数";
    else if (LifeStyle_Ag == type)
        return "过敏指数";
    else if (LifeStyle_Gl == type)
        return "太阳镜指数";
    else if (LifeStyle_Mu == type)
        return "化妆指数";
    else if (LifeStyle_Airc == type)
        return "晾晒指数";
    else if (LifeStyle_Ptfc == type)
        return "交通指数";
    else if (LifeStyle_Fsh == type)
        return "钓鱼指数";
    else if (LifeStyle_Spi == type)
        return "防晒指数";
}

WeatherLife::LifeStyleType WeatherLife::lifeStyleStringToType(QString lifeStyleString)
{
    if (lifeStyleString == "comf")
        return LifeStyle_Comf;
    else if (lifeStyleString == "cw")
        return LifeStyle_Cw;
    else if (lifeStyleString == "drsg")
        return LifeStyle_Drsg;
    else if (lifeStyleString == "flu")
        return LifeStyle_Flu;
    else if (lifeStyleString == "sport")
        return LifeStyle_Sport;
    else if (lifeStyleString == "trav")
        return LifeStyle_Trav;
    else if (lifeStyleString == "uv")
        return LifeStyle_Uv;
    else if (lifeStyleString == "air")
        return LifeStyle_Air;
    else if (lifeStyleString == "ac")
        return LifeStyle_Ac;
    else if (lifeStyleString == "ag")
        return LifeStyle_Ag;
    else if (lifeStyleString == "gl")
        return LifeStyle_Gl;
    else if (lifeStyleString == "mu")
        return LifeStyle_Mu;
    else if (lifeStyleString == "airc")
        return LifeStyle_Airc;
    else if (lifeStyleString == "cw")
        return LifeStyle_Cw;
    else if (lifeStyleString == "ptfc")
        return LifeStyle_Ptfc;
    else if (lifeStyleString == "fsh")
        return LifeStyle_Fsh;
    else if (lifeStyleString == "spi")
        return LifeStyle_Spi;
}
