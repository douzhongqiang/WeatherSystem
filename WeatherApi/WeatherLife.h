#ifndef WEATHER_LIFE_H
#define WEATHER_LIFE_H

#include "WeatherBaseInfo.h"
#include <QMap>

class WeatherLife : public WeatherBaseInfo
{
    Q_OBJECT
public:
    enum LifeStyleType
    {
        LifeStyle_Comf,             // 舒适度指数
        LifeStyle_Cw,               // 洗车指数
        LifeStyle_Drsg,             // 穿衣指数
        LifeStyle_Flu,              // 感冒指数
        LifeStyle_Sport,            // 运动指数
        LifeStyle_Trav,             // 旅游指数
        LifeStyle_Uv,               // 紫外线指数
        LifeStyle_Air,              // 空气污染扩散条件指数
        LifeStyle_Ac,               // 空调开启指数
        LifeStyle_Ag,               // 过敏指数
        LifeStyle_Gl,               // 太阳镜指数
        LifeStyle_Mu,               // 化妆指数
        LifeStyle_Airc,             // 晾晒指数
        LifeStyle_Ptfc,             // 交通指数
        LifeStyle_Fsh,              // 钓鱼指数
        LifeStyle_Spi               // 防晒指数
    };

    struct LifeStyleData
    {
        QString brf;
        QString valueText;
        LifeStyleType lifeStyleType;
    };

public:
    WeatherLife();
    ~WeatherLife();

    // 处理生活指数的数据
    void disposeWeatherInfo(QJsonObject &jsonObject) override;
    // 获取生活指数列表
    QList<LifeStyleData> getLifeStyleInfoList(void);
    // 枚举类型转换为字符串
    static QString convertToString(LifeStyleType);

private:
    QList<LifeStyleData> m_LifeStyleDataList;

    // 指数字符串转换为枚举类型
    LifeStyleType lifeStyleStringToType(QString);
};

#endif
