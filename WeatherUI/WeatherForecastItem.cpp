#include "WeatherForecastItem.h"
#include <QPainter>
#include <QStyleOption>
#include "WeatherApi/WeatherInterface.h"

WeatherForecastItem::WeatherForecastItem(int index, QWidget *parent)
    :QWidget(parent)
{
    m_Index = index;
    this->setProperty("ItemWidget", "ItemWidget");
}

WeatherForecastItem::~WeatherForecastItem()
{

}

void WeatherForecastItem::paintEvent(QPaintEvent *event)
{
    updateData();
    QPainter painter(this);

    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    int width = this->width();
    int height = this->height();

    // 绘制时间
    drawDateTime(&painter, QRect(0, 2, width, height * 1.0 / 4));
    // 绘制图片
    int imageWidth = height / 2 - 8;
    int xPt = (width - imageWidth) / 2;
    int yPt = height * 1.0 / 4 + (height / 2 - imageWidth) / 2;
    drawWeatherImage(&painter, QRect(xPt, yPt, imageWidth, imageWidth));
    // 绘制天气和温度
    drawWeatherAndTemperature(&painter, QRect(0, height * 1.0 / 4 * 3, width, height * 1.0 / 4 - 2));

    return QWidget::paintEvent(event);
}

void WeatherForecastItem::drawDateTime(QPainter *painter, QRect rect)
{
    QDate currentDate = QDate::currentDate();
    int days = currentDate.daysTo(m_DateTime);
    QString dayString = "";
    if (days == 0)
        dayString = "今天";
    else if (days == 1)
        dayString = "明天";
    else if (days == 2)
        dayString = "后天";
    QString dateTimeString = m_DateTime.toString("MM/dd");

    QTextOption o;
    o.setAlignment(Qt::AlignCenter);
    painter->drawText(QRect(rect.x(), rect.y(), rect.width(), rect.height() / 2), dayString, o);
    painter->drawText(QRect(rect.x(), rect.y() + rect.height() / 2, rect.width(), rect.height() / 2), \
                      dateTimeString, o);

}

void WeatherForecastItem::drawWeatherImage(QPainter *painter, QRect rect)
{
    QImage image(m_IconPath);
    painter->drawImage(rect, image);
}

void WeatherForecastItem::drawWeatherAndTemperature(QPainter *painter, QRect rect)
{
    QTextOption o;
    o.setAlignment(Qt::AlignCenter);
    painter->drawText(QRect(rect.x(), rect.y(), rect.width(), rect.height() / 2), m_WeatherString, o);
    painter->drawText(QRect(rect.x(), rect.y() + rect.height() / 2, rect.width(), rect.height() / 2), \
                      m_TemperatureString, o);
}

void WeatherForecastItem::updateData(void)
{
    if (g_WeatherInterface->getDailyForecast().count() <= 0)
        return;

    m_DateTime = g_WeatherInterface->getDailyForecast().at(m_Index).date;
    int weatherCode = g_WeatherInterface->getDailyForecast().at(m_Index).cond_code_d;
    m_IconPath = g_WeatherInterface->getWeatherIcon(weatherCode);
    m_WeatherString = g_WeatherInterface->getDailyForecast().at(m_Index).cond_txt_d;

    // 设置温度字符串
    QString temperatureString = "%1-%2℃";
    int minTmp = g_WeatherInterface->getDailyForecast().at(m_Index).tmp_min;
    int maxTmp = g_WeatherInterface->getDailyForecast().at(m_Index).tmp_max;
    temperatureString = temperatureString.arg(minTmp).arg(maxTmp);
    m_TemperatureString = temperatureString;
}
