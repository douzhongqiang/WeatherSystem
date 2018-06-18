#ifndef WEATHER_FORECAST_ITEM_H
#define WEATHER_FORECAST_ITEM_H

#include <QWidget>
#include <QDate>
#include <QPaintEvent>
class WeatherForecastItem : public QWidget
{
    Q_OBJECT

public:
    WeatherForecastItem(int index, QWidget *parent = nullptr);
    ~WeatherForecastItem();

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QDate m_DateTime;
    QString m_IconPath;
    QString m_WeatherString;
    QString m_TemperatureString;

    int m_Index;

    // 绘制时间
    void drawDateTime(QPainter *painter, QRect rect);
    // 绘制天气图标
    void drawWeatherImage(QPainter *painter, QRect rect);
    // 绘制天气和温度
    void drawWeatherAndTemperature(QPainter *painter, QRect rect);
    // 更新数据
    void updateData(void);
};

#endif
