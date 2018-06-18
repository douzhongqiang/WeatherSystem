#ifndef WEATHER_CITY_CHANGE_WINDOW_H
#define WEATHER_CITY_CHANGE_WINDOW_H
#include "UIBase/UIBaseWindow.h"
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include "UIBase/UIChinaCity.h"

class WeatherCityChangeWindow : public UIBaseWindow
{
    Q_OBJECT

public:
    WeatherCityChangeWindow(QWidget *parent = nullptr);
    ~WeatherCityChangeWindow();

private:
    QComboBox *m_StateComboBox = nullptr;
    QComboBox *m_CityComboBox = nullptr;
    QComboBox *m_RegionComboBox = nullptr;

    QLabel *m_StateLabel;
    QLabel *m_CityLabel;
    QLabel *m_RegionLabel;

    QPushButton *m_OKButton;
    QPushButton *m_CannelButton;

    UIChinaCity *chinaCityManager = nullptr;

private slots:
    void onStateComboBoxIndexChanged(int);
    void onCityComboBoxIndexChanged(int);
    void onOKClicked(void);
    void onCannelClicked(void);

signals:
    void changeCity(void);
};

#endif
