#include "WeatherCenterWidget.h"
#include <QPainter>
#include <QDate>
#include <QDebug>
#include <QTimer>
#include <QMouseEvent>
#include "WeatherApi/WeatherInterface.h"

WeatherCenterWidget::WeatherCenterWidget(QWidget *parent)
    :QWidget(parent)
{
    m_CurrentCity = "北京";
    m_ChangeCityRect = QRect(50, 20, 30, 25);
    this->setMouseTracking(true);

    refreshImage = QPixmap("./Icons/refresh.png");
    refreshImageH = QPixmap("./Icons/refreshH.png");

    m_WeatherCityChangeWindow = new WeatherCityChangeWindow;
    m_WeatherCityChangeWindow->hide();
    QObject::connect(m_WeatherCityChangeWindow, SIGNAL(changeCity()), this, SLOT(onUpdateChangeCity()));
    //m_WeatherCityChangeWindow->show();
}

WeatherCenterWidget::~WeatherCenterWidget()
{

}

void WeatherCenterWidget::paintEvent(QPaintEvent *event)
{
    // 更新数据信息
    updateData();

    QPainter painter(this);
    // 设置画笔和画刷
    painter.setPen(QPen(QColor(230, 230, 230)));
    QLinearGradient lineGradient(0, 0, 0, this->rect().height());
    lineGradient.setColorAt(0.0, QColor(80, 80, 80));
    lineGradient.setColorAt(1.0, QColor(200, 200, 200));
    painter.fillRect(this->rect(), QBrush(lineGradient));
    // 绘制城市信息
    drawCityInfo(&painter, QRect(10, 20, 80, 50));
    // 绘制刷新
    drawRefreshIcon(&painter, QRect(this->width() - 10 - 50, 28, 32, 32));
    // 绘制天气基本信息
    drawWeatherBaseInfo(&painter, QRect(0, 0, this->width(), this->height()));
    // 绘制生活指数
    painter.setPen(QPen(QColor(60, 60, 60)));
    drawLifeStyleInfo(&painter, QRect(5, this->height() - 30, this->width(), 30));

    return QWidget::paintEvent(event);
}

void WeatherCenterWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    if (m_ChangeCityRect.contains(pos))
    {
        m_IsHoverChanged = true;
        this->setCursor(Qt::PointingHandCursor);
    }
    else if (m_RefreshRect.contains(pos))
    {
        m_IsHoverRefresh = true;
        this->setCursor(Qt::PointingHandCursor);
    }
    else
    {
        m_IsHoverChanged = false;
        m_IsHoverRefresh = false;
        this->setCursor(Qt::ArrowCursor);
    }

    this->repaint();
    return QWidget::mouseMoveEvent(event);
}

void WeatherCenterWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_IsHoverChanged)
        m_WeatherCityChangeWindow->show();
    else if (m_IsHoverRefresh)
    {
        g_WeatherInterface->updateWeatherInfo();
        this->repaint();
    }
    return QWidget::mouseReleaseEvent(event);
}

void WeatherCenterWidget::resizeEvent(QResizeEvent *event)
{
    m_RefreshRect = QRect(this->width() - 10 - 50, 28, 32, 32);
    return QWidget::resizeEvent(event);
}

void WeatherCenterWidget::drawCityInfo(QPainter *painter, QRect rect)
{
    painter->save();
    QTextOption o;
    o.setAlignment(Qt::AlignLeft);

    // 绘制城市
    painter->drawText(QRect(rect.x(), rect.y(), rect.width(), rect.height() / 2), m_CurrentCity, o);

    // 绘制更换
    if (m_IsHoverChanged)
        painter->setPen(QPen(QColor(100, 100, 200)));
    o.setAlignment(Qt::AlignRight);
    painter->drawText(QRect(rect.x(), rect.y(), rect.width(), rect.height() / 2), "更换", o);

    // 绘制时间信息
    painter->setPen(QPen(QColor(230, 230, 230)));
    o.setAlignment(Qt::AlignLeft);
    QString currentTimeString = QDate::currentDate().toString("yyyy-MM-dd");
    painter->drawText(QRect(rect.x(), rect.y() + rect.height() / 2, rect.width(), rect.height() / 2), \
                      currentTimeString, o);
    painter->restore();
}

void WeatherCenterWidget::drawWeatherBaseInfo(QPainter *painter, QRect rect)
{
    painter->save();

    QFont font;
    font.setPixelSize(85);
    painter->setFont(font);

    int midddleHeight = 60;
    QTextOption o;
    o.setAlignment(Qt::AlignCenter | Qt::AlignBottom);
    // 绘制温度
    painter->drawText(QRect(rect.x(), rect.y(), rect.width(), rect.height() / 2 - midddleHeight / 2), \
                      m_CurrentTem, o);

    // 绘制天气信息
    font.setPixelSize(40);
    painter->setFont(font);
    o.setAlignment(Qt::AlignCenter);
    painter->drawText(QRect(rect.x(), rect.y() + rect.height() / 2 - midddleHeight / 2, \
                            rect.width(), midddleHeight), m_CurrentWeather, o);

    // 绘制空气质量
    font.setPixelSize(30);
    painter->setFont(font);
    QColor color = g_WeatherInterface->getAirQualityCityColor();
    painter->setPen(QPen(color));
    o.setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    painter->drawText(QRect(rect.x(), rect.y() + rect.height() / 2 + midddleHeight / 2, \
                            rect.width(), rect.height() / 2 - midddleHeight / 2), \
                      m_AirQualityString, o);

    painter->restore();
}

void WeatherCenterWidget::drawLifeStyleInfo(QPainter *painter, QRect rect)
{
    QFont font;
    font.setPixelSize(15);
    painter->setFont(font);
    painter->drawText(rect, m_LifeStyleString);
}

void WeatherCenterWidget::drawRefreshIcon(QPainter *painter, QRect rect)
{
    if (!m_IsHoverRefresh)
        painter->drawPixmap(rect, refreshImage);
    else
        painter->drawPixmap(rect, refreshImageH);
}

void WeatherCenterWidget::updateData(void)
{
    m_CurrentCity = g_WeatherInterface->getCurrentCityName();
    m_CurrentTem = QString::number(g_WeatherInterface->getNowWeatherInfo().tmp) + "℃";

    QString currentWeatherString = "%1 / %2%3级";
    currentWeatherString = currentWeatherString.arg(g_WeatherInterface->getNowWeatherInfo().cond_txt).\
            arg(g_WeatherInterface->getNowWeatherInfo().wind_dir).\
            arg(g_WeatherInterface->getNowWeatherInfo().wind_sc);
    m_CurrentWeather =  currentWeatherString;

    QString airQualityString = "%1 %2";
    airQualityString = airQualityString.arg(g_WeatherInterface->getAirQualityCity().aqi). \
            arg(g_WeatherInterface->getAirQualityCity().qlty);
    m_AirQualityString = airQualityString;

    // 更新生活指数
    if (g_WeatherInterface->getLifeStyleInfoList().count() > 0)
    {
        if (m_Timer == nullptr)
        {
            QList<WeatherLife::LifeStyleData> lifeStyleList = g_WeatherInterface->getLifeStyleInfoList();
            m_LifeStyleString = WeatherLife::convertToString(lifeStyleList.at(0).lifeStyleType) + ": " + \
                            lifeStyleList.at(0).brf + "; " + lifeStyleList.at(0).valueText;
            m_Timer = new QTimer(this);
            m_Timer->setInterval(4000);
            m_Timer->start();
            QObject::connect(m_Timer, &QTimer::timeout, this, &WeatherCenterWidget::onTimeOut);
        }
    }
}

void WeatherCenterWidget::onTimeOut(void)
{
    QList<WeatherLife::LifeStyleData> lifeStyleList = g_WeatherInterface->getLifeStyleInfoList();
    if (++m_LefeStyleIndex >= lifeStyleList.count())
        m_LefeStyleIndex = 0;
    m_LifeStyleString = WeatherLife::convertToString(lifeStyleList.at(m_LefeStyleIndex).lifeStyleType) + ": " + \
                    lifeStyleList.at(m_LefeStyleIndex).brf + "; " + lifeStyleList.at(m_LefeStyleIndex).valueText;
    this->update();
}

void WeatherCenterWidget::onUpdateChangeCity(void)
{
    g_WeatherInterface->updateWeatherInfo();
    this->update();
}
