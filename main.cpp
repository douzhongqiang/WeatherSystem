#include <QApplication>
#include "WeatherUI/WeatherMainWindow.h"
#include "WeatherApi/WeatherForecast.h"
#include "WeatherApi/WeatherNow.h"
#include "WeatherApi/WeatherInterface.h"
#include "WeatherApi/WeatherLife.h"
#include "WeatherApi/WeatherAirNow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile nFile("./styles/DarkStyle.css");
    if (nFile.open(QFile::ReadOnly))
    {
        QString styleSheetString = nFile.readAll().data();
        a.setStyleSheet(styleSheetString);
        nFile.close();
    }

    // 刷新当前天气
    g_WeatherInterface->updateWeatherInfo();

    WeatherMainWindow w;
    w.resize(1000, 800);
    w.show();

    return a.exec();
}
