#include "WeatherMainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

WeatherMainWindow::WeatherMainWindow(QWidget *parent)
    :UIBaseWindow(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addSpacing(30);

    m_TextEdit = new QTextEdit();
    //layout->addWidget(m_TextEdit, 4);
    m_CenterWidget = new WeatherCenterWidget(this);
    layout->addWidget(m_CenterWidget, 4);

    QWidget *bottomWidget = new QWidget(this);
    QHBoxLayout *bottomLayout = new QHBoxLayout(bottomWidget);
    bottomLayout->setSpacing(0);
    bottomLayout->setMargin(2);
    WeatherForecastItem *weatherForecastItem1 = new WeatherForecastItem(0, this);
    bottomLayout->addWidget(weatherForecastItem1, 1);
    WeatherForecastItem *weatherForecastItem2 = new WeatherForecastItem(1, this);
    bottomLayout->addWidget(weatherForecastItem2, 1);
    WeatherForecastItem *weatherForecastItem3 = new WeatherForecastItem(2, this);
    bottomLayout->addWidget(weatherForecastItem3, 1);

    layout->addWidget(bottomWidget, 1);
    layout->setContentsMargins(5, 5, 5, 5);
    layout->setSpacing(1);

    this->setCustomerWindowTitle("日丽天气 V1.0 - by Douzhq");
}

WeatherMainWindow::~WeatherMainWindow()
{

}

void WeatherMainWindow::setTextEditText(QString str)
{
    m_TextEdit->setText(str);
}
