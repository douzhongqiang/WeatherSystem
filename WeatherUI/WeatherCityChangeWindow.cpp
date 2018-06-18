#include "WeatherCityChangeWindow.h"
#include <QVBoxLayout>
#include "WeatherApi/WeatherInterface.h"
#include "UIBase/UIGlobalTool.h"
#include <QListView>

WeatherCityChangeWindow::WeatherCityChangeWindow(QWidget *parent)
    :UIBaseWindow(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addSpacing(30);

    chinaCityManager = new UIChinaCity(this);

    QWidget *mainWidget = new QWidget(this);
    QVBoxLayout *bottomLayout = new QVBoxLayout(mainWidget);

    // 初始化下拉Tag
    QHBoxLayout *tagLabelLayout = new QHBoxLayout;
    m_StateLabel = new QLabel("省/直辖市");
    m_CityLabel = new QLabel("城市/直辖市区");
    m_RegionLabel = new QLabel("区/县");
    tagLabelLayout->addWidget(m_StateLabel, 0, Qt::AlignCenter);
    tagLabelLayout->addWidget(m_CityLabel, 0, Qt::AlignCenter);
    tagLabelLayout->addWidget(m_RegionLabel, 0, Qt::AlignCenter);

    // 初始化下拉按钮
    QHBoxLayout *comboLayout = new QHBoxLayout;
    m_StateComboBox = new QComboBox;
    m_StateComboBox->addItems(chinaCityManager->getProvinceName());
    m_StateComboBox->setView(new QListView(m_StateComboBox));
    comboLayout->addWidget(m_StateComboBox);

    m_CityComboBox = new QComboBox;
    comboLayout->addWidget(m_CityComboBox);
    m_CityComboBox->setView(new QListView(m_CityComboBox));

    m_RegionComboBox = new QComboBox;
    m_RegionComboBox->setView(new QListView(m_RegionComboBox));
    g_GlobalTool->addShadowEffect(m_StateComboBox);
    g_GlobalTool->addShadowEffect(m_CityComboBox);
    g_GlobalTool->addShadowEffect(m_RegionComboBox);

    comboLayout->addWidget(m_RegionComboBox);

    // 初始化按钮
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    m_OKButton = new QPushButton("确定");
    m_CannelButton = new QPushButton("取消");
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_OKButton);
    buttonLayout->addWidget(m_CannelButton);
    g_GlobalTool->addShadowEffect(m_OKButton);
    g_GlobalTool->addShadowEffect(m_CannelButton);

    // 添加布局
    bottomLayout->addLayout(tagLabelLayout);
    bottomLayout->addLayout(comboLayout);
    bottomLayout->addStretch();
    bottomLayout->addLayout(buttonLayout);
    layout->addWidget(mainWidget);
    this->resize(500, 200);

    // 建立信号和槽的连接
    QObject::connect(m_StateComboBox, SIGNAL(currentIndexChanged(int)), \
                     this, SLOT(onStateComboBoxIndexChanged(int)));
    QObject::connect(m_CityComboBox, SIGNAL(currentIndexChanged(int)), \
                     this, SLOT(onCityComboBoxIndexChanged(int)));
    QObject::connect(m_OKButton, SIGNAL(clicked(bool)), this, SLOT(onOKClicked()));
    QObject::connect(m_CannelButton, SIGNAL(clicked(bool)), this, SLOT(onCannelClicked()));

    // 初始化值
    m_StateComboBox->setCurrentText("北京");
    m_CityComboBox->setCurrentText("昌平");

    this->setCustomerWindowTitle("日丽天气 V1.0 - by Douzhq");
}

WeatherCityChangeWindow::~WeatherCityChangeWindow()
{

}

void WeatherCityChangeWindow::onStateComboBoxIndexChanged(int index)
{
    QString nProvinceName = m_StateComboBox->currentText();
    QList<QString> cityNameList = chinaCityManager->getCitysName(nProvinceName);
    m_CityComboBox->clear();
    m_RegionComboBox->clear();
    m_CityComboBox->addItems(cityNameList);
}

void WeatherCityChangeWindow::onCityComboBoxIndexChanged(int index)
{
    QString nProvinceName = m_StateComboBox->currentText();
    QString nCityName = m_CityComboBox->currentText();

    QList<QString> regionNameList = chinaCityManager->getRegionsName(nProvinceName, nCityName);
    m_RegionComboBox->clear();

    m_RegionComboBox->addItems(regionNameList);
}

void WeatherCityChangeWindow::onOKClicked(void)
{
    if (m_RegionComboBox->currentText().isEmpty())
    {
        g_WeatherInterface->setCurrentCityName(m_CityComboBox->currentText());
        g_WeatherInterface->setAirQualityCityName(m_StateComboBox->currentText());
    }
    else
    {
        g_WeatherInterface->setCurrentCityName(m_RegionComboBox->currentText());
        g_WeatherInterface->setAirQualityCityName(m_CityComboBox->currentText());
    }
    emit changeCity();
    this->close();
}

void WeatherCityChangeWindow::onCannelClicked(void)
{
    this->close();
}
