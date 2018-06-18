#ifndef WEATHER_CENTER_WIDGET_H
#define WEATHER_CENTER_WIDGET_H

#include <QWidget>
#include "WeatherCityChangeWindow.h"

class WeatherCenterWidget : public QWidget
{
    Q_OBJECT

public:
    WeatherCenterWidget(QWidget *parent = nullptr);
    ~WeatherCenterWidget();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    // 当前所在城市
    QString m_CurrentCity;
    // 当前的温度
    QString m_CurrentTem;
    // 当前的天气情况
    QString m_CurrentWeather;
    // 空气质量
    QString m_AirQualityString;
    // 生活指数
    QString m_LifeStyleString;
    QTimer *m_Timer = nullptr;
    int m_LefeStyleIndex = 0;
    // 刷新图标
    QPixmap refreshImage;
    QPixmap refreshImageH;

    // 城市更改的区域位置
    QRect m_ChangeCityRect;
    bool m_IsHoverChanged = false;
    QRect m_RefreshRect;
    bool m_IsHoverRefresh = false;

    // 绘制城市信息
    void drawCityInfo(QPainter *painter, QRect rect);
    // 绘制温度等基本信息
    void drawWeatherBaseInfo(QPainter *painter, QRect rect);
    // 绘制生活指数
    void drawLifeStyleInfo(QPainter *painter, QRect rect);
    // 绘制刷新图标
    void drawRefreshIcon(QPainter *painter, QRect rect);

    // 更新信息
    void updateData(void);

    WeatherCityChangeWindow *m_WeatherCityChangeWindow = nullptr;

private slots:
    void onTimeOut(void);
    void onUpdateChangeCity(void);
};

#endif
