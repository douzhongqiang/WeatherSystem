#ifndef UICHINACITY_H
#define UICHINACITY_H

#include <QObject>
#include <QMap>
class UIChinaCity : public QObject
{
    Q_OBJECT

public:
    UIChinaCity(QObject *parent = nullptr);
    ~UIChinaCity();

    struct CityInfo
    {
        QString cityName;                   // 城市名字
        QList<QString> regionName;          // 城市下的区的名字
    };

    // 获取所有的省份
    QList<QString> getProvinceName(void);
    // 获取某个省下的所有的城市
    QList<QString> getCitysName(QString);
    // 获取某个省下的某个市下的所有的县
    QList<QString> getRegionsName(QString, QString);

private:
    // 解析城市列表
    void disposeCityList(void);

    QMap<QString, QList<CityInfo>> m_ChinaCityInfo;
};

#endif
