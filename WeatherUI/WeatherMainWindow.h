#ifndef WEATHER_MAINWINDOW_H
#define WEATHER_MAINWINDOW_H

#include "UIBase/UIBaseWindow.h"
#include <QTextEdit>
#include "WeatherForecastItem.h"
#include "WeatherCenterWidget.h"

class WeatherMainWindow : public UIBaseWindow
{
    Q_OBJECT

public:
    WeatherMainWindow(QWidget *parent = nullptr);
    ~WeatherMainWindow();

    void setTextEditText(QString);

private:
    QTextEdit *m_TextEdit = nullptr;
    WeatherCenterWidget *m_CenterWidget = nullptr;
};

#endif
