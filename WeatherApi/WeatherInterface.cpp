#include "WeatherInterface.h"
#include <QNetworkProxy>
#include <QUrlQuery>
#include <QEventLoop>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

WeatherInterface::WeatherInterface(QObject *parent)
    :QObject(parent)
{
    m_PrivateKey = "898b4f748e104ca09cbd161125421a86";
    m_Manager = new QNetworkAccessManager(this);
    m_TypeInterfaceMap.clear();

    // 初始化数据
    initData();
}

WeatherInterface::~WeatherInterface()
{

}

WeatherInterface *WeatherInterface::getInstance(void)
{
    static WeatherInterface instance;
    return &instance;
}

void WeatherInterface::initData(void)
{
    m_WeatherGetType = Weather_Forecast_Type;
    //m_LocationCity = "auto_ip";
    m_LocationCity = "昌平";
    m_AirQualityCity = "北京";

    m_TypeInterfaceMap.insert(Weather_Forecast_Type, new WeatherForecast);
    m_TypeInterfaceMap.insert(Weather_Now_Type, new WeatherNow);
    m_TypeInterfaceMap.insert(Weather_LifeStyle_Type, new WeatherLife);
    m_TypeInterfaceMap.insert(Weather_AirQuality_Type, new WeatherAirNow);
}

QString WeatherInterface::getURLAttrStringByType(WeatherGetType type)
{
    if (type == Weather_Forecast_Type)
        return "weather/forecast";
    else if (type == Weather_Now_Type)
        return "weather/now";
    else if (type == Weather_LifeStyle_Type)
        return "weather/lifestyle";
    else if (type == Weather_AirQuality_Type)
        return "air/now";

    return "";
}

void WeatherInterface::disposeWeatherJsonData(QString jsonData)
{
    QJsonParseError jsonError;
    QByteArray byteArray = jsonData.toUtf8();
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);  // 转化为 JSON 文档
    if (doucment.isNull() || jsonError.error != QJsonParseError::NoError)
        return;

    // 获取JsonObject
    QJsonArray mainDataJsonArray;
    if (doucment.isObject())
    {
        QJsonObject jsonObject = doucment.object();
        if (jsonObject.contains("HeWeather6"))
        {
            QJsonValue jsonValue = jsonObject.value("HeWeather6");
            if (jsonValue.isArray())
                mainDataJsonArray = jsonValue.toArray();
            else
                return;
        }
    }

    QJsonObject mainDataJsonObject = mainDataJsonArray.at(0).toObject();

    // 解释Basic
    if (mainDataJsonObject.contains("basic"))
    {
        QJsonObject basicJsonObject = mainDataJsonObject.value("basic").toObject();
        m_WeatherBaseData.cid = basicJsonObject.value("cid").toString();
        m_WeatherBaseData.location = basicJsonObject.value("location").toString();
        m_WeatherBaseData.parent_city = basicJsonObject.value("parent_city").toString();
        m_WeatherBaseData.admin_area = basicJsonObject.value("admin_area").toString();
        m_WeatherBaseData.cnty = basicJsonObject.value("cnty").toString();
        m_WeatherBaseData.lat = basicJsonObject.value("lat").toString().toDouble();
        m_WeatherBaseData.lon = basicJsonObject.value("lon").toString().toDouble();
        m_WeatherBaseData.tz = basicJsonObject.value("tz").toString().toDouble();
    }

    // 解析更新时间
    if (mainDataJsonObject.contains("update"))
    {
        QJsonObject updateJsonObject = mainDataJsonObject.value("update").toObject();
        m_WeatherTime.localTime = QDateTime::fromString(updateJsonObject.value("loc").toString(), "yyyy-MM-dd hh:mm");
        m_WeatherTime.utcTime = QDateTime::fromString(updateJsonObject.value("utc").toString(), "yyyy-MM-dd hh:mm");
    }

    // 解析状态码
    if (mainDataJsonObject.contains("status"))
    {
        m_WeatherStatus.statusCode = mainDataJsonObject.value("status").toString();
        m_WeatherStatus.note = getStatusCodeNote(m_WeatherStatus.statusCode);
    }

    // 解析类型的信息
    m_TypeInterfaceMap[m_WeatherGetType]->disposeWeatherInfo(mainDataJsonObject);
}

QString WeatherInterface::getStatusCodeNote(QString statusCode)
{
    if ("ok" == statusCode)
        return "数据正常";
    else if ("invalid key" == statusCode)
        return "错误的key，请检查你的key是否输入以及是否输入有误";
    else if ("unknown location" == statusCode)
        return "未知或错误城市/地区";
    else if ("no data for this location" == statusCode)
        return "该城市/地区没有你所请求的数据";
    else if ("no more requests" == statusCode)
        return "超过访问次数";
    else if ("param invalid" == statusCode)
        return "参数错误，请检查你传递的参数是否正确";
    else if ("too fast" == statusCode)
        return "超过限定的QPM";
    else if ("dead" == statusCode)
        return "无响应或超时";
    else if ("permission denied" == statusCode)
        return "无访问权限，你没有购买你所访问的这部分服务";
    else if ("sign error" == statusCode)
        return "签名错误";
}

void WeatherInterface::setConfigNetWorkProxy(bool visible)
{
    m_IsConfigNetWorkProxy = visible;

    if (m_IsConfigNetWorkProxy)
    {
        QNetworkProxy proxy;
        proxy.setType(QNetworkProxy::HttpProxy);
        proxy.setHostName("127.0.0.1");
        proxy.setPort(8888);
        m_Manager->setProxy(proxy);
    }
    else
        m_Manager->setProxy(QNetworkProxy::NoProxy);
}

void WeatherInterface::updateData(void)
{
    QString jsonData = getReplayData();
    disposeWeatherJsonData(jsonData);
}

void WeatherInterface::setCurrentWeatherInfoType(WeatherGetType type)
{
    m_WeatherGetType = type;
}

void WeatherInterface::setCurrentCityName(QString cityName)
{
    m_LocationCity = cityName;
}

void WeatherInterface::setAirQualityCityName(QString cityName)
{
    m_AirQualityCity = cityName;
}

QString WeatherInterface::getCurrentCityName(void)
{
    return m_LocationCity;
}

// 获取天气的基础信息
WeatherInterface::WeatherBaseData WeatherInterface::getBaseData(void)
{
    return m_WeatherBaseData;
}

// 获取更新时间信息
WeatherInterface::WeatherUpdateTime WeatherInterface::getUpdateTime(void)
{
    return m_WeatherTime;
}

QList<WeatherForecast::DailyForecast> WeatherInterface::getDailyForecast(void)
{
    WeatherForecast *pWeatherForecast = dynamic_cast<WeatherForecast*>(m_TypeInterfaceMap[Weather_Forecast_Type]);
    if (pWeatherForecast)
        return pWeatherForecast->getDailyForecast();
}

WeatherNow::WeatherNowInfo WeatherInterface::getNowWeatherInfo(void)
{
    WeatherNow *pWeatherNow = dynamic_cast<WeatherNow*>(m_TypeInterfaceMap[Weather_Now_Type]);
    if (pWeatherNow)
        return pWeatherNow->getNowWeatherInfo();
}

QList<WeatherLife::LifeStyleData> WeatherInterface::getLifeStyleInfoList(void)
{
    WeatherLife *pWeatherLifeStyle = dynamic_cast<WeatherLife*>(m_TypeInterfaceMap[Weather_LifeStyle_Type]);
    if (pWeatherLifeStyle)
        return pWeatherLifeStyle->getLifeStyleInfoList();
}

WeatherAirNow::AirQualityCity WeatherInterface::getAirQualityCity(void)
{
    WeatherAirNow *pWeatherAirNow = dynamic_cast<WeatherAirNow*>(m_TypeInterfaceMap[Weather_AirQuality_Type]);
    if (pWeatherAirNow)
        return pWeatherAirNow->getAirQualityCity();
}

QColor WeatherInterface::getAirQualityCityColor(void)
{
    QColor color = QColor(255, 255, 255);
    WeatherAirNow *pWeatherAirNow = dynamic_cast<WeatherAirNow*>(m_TypeInterfaceMap[Weather_AirQuality_Type]);
    if (pWeatherAirNow)
    {
        int nAqi = pWeatherAirNow->getAirQualityCity().aqi;
        if (nAqi <= 100)
            color = QColor(0, 255, 0);
        else if (nAqi <= 200)
            color = QColor(230, 230, 0);
        else
            color = QColor(255, 0, 0);
    }

    return color;
}

void WeatherInterface::updateWeatherInfo(void)
{
    // 天气预报
    setCurrentWeatherInfoType(Weather_Forecast_Type);
    updateData();
    // 实时天气
    setCurrentWeatherInfoType(Weather_Now_Type);
    updateData();
    // 生活指数
    setCurrentWeatherInfoType(Weather_LifeStyle_Type);
    updateData();
    // 空气质量
    setCurrentWeatherInfoType(Weather_AirQuality_Type);
    updateData();
}

QString WeatherInterface::getWeatherIcon(int code)
{
    QString weatherIconString = "./Icons/weather-icon/%1.png";
    weatherIconString = weatherIconString.arg(code);
    return weatherIconString;
}

QString WeatherInterface::getReplayData(QString attrValue, QMap<QString, QString> map)
{
    if (map.count() <= 0)
        return "";

    QString baseUrlString = WEATHER_INTERFACE_BASEURL;
    baseUrlString += attrValue;

    // 设置URL
    QUrl url(baseUrlString);
    QUrlQuery query;
    query.addQueryItem("key", m_PrivateKey);
    for (auto itor = map.begin(); itor != map.end(); ++itor)
    {
        QString key = itor.key();
        QString value = itor.value();

        query.addQueryItem(key, value);
    }
    url.setQuery(query);
    qDebug() <<url.toString();

    // 设置请求
    QNetworkRequest requset;
    requset.setUrl(url);

    // 发送get请求
    QNetworkReply *pReplay = m_Manager->get(requset);

    // 等待请求完成
    QEventLoop loop;
    QObject::connect(m_Manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QString replyString = QString(pReplay->readAll().data());
    return replyString;
}

QString WeatherInterface::getReplayData(void)
{
    QString attrValue = getURLAttrStringByType(m_WeatherGetType);

    QMap<QString, QString> map;
    map.clear();
    if (Weather_AirQuality_Type != m_WeatherGetType)
        map.insert("location", m_LocationCity);
    else
        map.insert("location", m_AirQualityCity);

    return getReplayData(attrValue, map);
}
