#-------------------------------------------------
#
# Project created by QtCreator 2018-06-16T16:36:31
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WeatherSystem
TEMPLATE = app
RC_ICONS = app.ico

CONFIG += c++11
MOC_DIR += $$PWD/temp
OBJECTS_DIR += $$PWD/temp
DESTDIR += $$PWD/bin

SOURCES += main.cpp \
    UIBase/UIBaseWindow.cpp \
    UIBase/UIGlobalConfig.cpp \
    UIBase/UIGlobalTool.cpp \
    UIBase/UIMessageBox.cpp \
    UIBase/UIProgressWindow.cpp \
    WeatherApi/WeatherInterface.cpp \
    WeatherApi/WeatherForecast.cpp \
    WeatherUI/WeatherMainWindow.cpp \
    WeatherApi/WeatherNow.cpp \
    WeatherApi/WeatherBaseInfo.cpp \
    WeatherApi/WeatherLife.cpp \
    WeatherApi/WeatherAirNow.cpp \
    WeatherUI/WeatherForecastItem.cpp \
    WeatherUI/WeatherCenterWidget.cpp \
    WeatherUI/WeatherCityChangeWindow.cpp \
    UIBase/UIChinaCity.cpp

HEADERS  += \
    UIBase/UIBaseWindow.h \
    UIBase/UIGlobalConfig.h \
    UIBase/UIGlobalTool.h \
    UIBase/UIMessageBox.h \
    UIBase/UIProgressWindow.h \
    WeatherApi/WeatherInterface.h \
    WeatherApi/WeatherForecast.h \
    WeatherUI/WeatherMainWindow.h \
    WeatherApi/WeatherNow.h \
    WeatherApi/WeatherBaseInfo.h \
    WeatherApi/WeatherLife.h \
    WeatherApi/WeatherAirNow.h \
    WeatherUI/WeatherForecastItem.h \
    WeatherUI/WeatherCenterWidget.h \
    WeatherUI/WeatherCityChangeWindow.h \
    UIBase/UIChinaCity.h
