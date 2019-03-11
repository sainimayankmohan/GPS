#include "mainWidget.h"
#include <QScrollBar>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
  m_pMainLayout = new QHBoxLayout();
  m_pMapView = new DCMapView(DCMapView::RoadMap,
                           DcCoordinate(12.972442,77.580643),
                           9);
  m_pControlsWidget = new QWidget();
  buildControls();
  m_pMainLayout->addWidget(m_pMapView, 1);
  m_pMainLayout->addWidget(m_pControlsWidget, 1);
  setLayout(m_pMainLayout);

  resize(1200, 600);
  connect(m_pMapView, SIGNAL(mapLoaded()), this, SLOT(onMapLoaded()));
  connect(m_pMapView, SIGNAL(regionChanged(DcCoordinateRegion)),
          this, SLOT(onRegionChanged(DcCoordinateRegion)));
  connect(m_pMapView, SIGNAL(mapBecameIdle()), this, SLOT(onMapBecameIdle()));

  m_pGPSReceiver = new GPSReceiver();
  connect(m_pGPSReceiver,SIGNAL(onDataReceived(QString)),this,SLOT(onDataReceived(QString)));
  connect(m_pGPSReceiver,SIGNAL(onUDPConnect(bool)),this,SLOT(onUDPConnect(bool)));
}

MainWidget::~MainWidget()
{
  disconnect(m_pStartBtn,SIGNAL(pressed()),this,SLOT(onBtnClicked()));
  disconnect(m_pGPSReceiver,SIGNAL(onDataReceived(QString)),this,SLOT(onDataReceived(QString)));
  disconnect(m_pGPSReceiver,SIGNAL(onUDPConnect(bool)),this,SLOT(onUDPConnect(bool)));

  delete m_pUdpSocketIPLbl;
  delete m_pUdpSocketPortLbl;
  delete m_pUdpSocketIPEdit;
  delete m_pUdpSocketPortEdit;
  delete m_pUdpLayout;

  delete m_pStartBtn;
  delete m_pControlLayout;
  delete m_pGPSReceiver;
  delete m_pMainLayout;
}

void MainWidget::buildControls()
{
  m_pUdpSocketIPLbl = new QLabel("Server IP");
  m_pUdpSocketPortLbl = new QLabel("Server Port");

  m_pUdpSocketIPEdit = new QLineEdit;
  m_pUdpSocketPortEdit = new QLineEdit;

  m_pUdpLayout = new QGridLayout;

  m_pUdpLayout->addWidget(m_pUdpSocketIPLbl,0,0);
  m_pUdpLayout->addWidget(m_pUdpSocketIPEdit,0,1);
  m_pUdpLayout->addWidget(m_pUdpSocketPortLbl,1,0);
  m_pUdpLayout->addWidget(m_pUdpSocketPortEdit,1,1);

  m_pControlLayout = new QVBoxLayout();
  m_pStartBtn = new QPushButton("Start");
  connect(m_pStartBtn,SIGNAL(pressed()),this,SLOT(onBtnClicked()));
  m_pLogger = new QTextEdit();
  m_pLogger->setReadOnly(true);
  m_pControlLayout->addWidget(m_pLogger, 1);
  m_pControlLayout->addLayout(m_pUdpLayout);
  m_pControlLayout->addWidget(m_pStartBtn,1);
  m_pControlsWidget->setLayout(m_pControlLayout);
}

void MainWidget::log(QString text, QString delimiter)
{
    m_pLogger->setPlainText(m_pLogger->toPlainText() + delimiter + text);
    m_pLogger->verticalScrollBar()->setSliderPosition(    // Scroll to bottom
                m_pLogger->verticalScrollBar()->maximum());
}

void MainWidget::log(const char *text, QString delimiter)
{
    log(QString(text), delimiter);
}

void MainWidget::onMapLoaded()
{
    log("Loaded:");
    log(QString("Type %1 at (%2, %3) , zoom %4").arg(
            QString::number(m_pMapView->mapType()),
            QString::number(m_pMapView->center().latitude()),
            QString::number(m_pMapView->center().longitude()),
            QString::number(m_pMapView->zoomLevel())),
        " ");
}

void MainWidget::onMapBecameIdle()
{
    log("Idle");
}

void MainWidget::onRegionChanged(DcCoordinateRegion region)
{
    log("Region changed:");
    log(QString("((%1, %2), (%3, %4))").arg(
            QString::number(region.northWest().latitude()),
            QString::number(region.west()),
            QString::number(region.south()),
            QString::number(region.southEast().longitude())),
        " ");
}

void MainWidget::onBtnClicked()
{
  qDebug()<<"OnBtnClicked";
  if(m_pStartBtn->text() == "Start")
  {
    if(!m_pUdpSocketIPEdit->text().isEmpty() && !m_pUdpSocketPortEdit->text().isEmpty())
    {
      qDebug()<<"OnBtnClicked1";
      m_pGPSReceiver->requestConnect(m_pUdpSocketIPEdit->text(),m_pUdpSocketPortEdit->text());
    }
  }
  else
  {
    m_pGPSReceiver->requestDisconnect();
  }
}

void MainWidget::onDataReceived(QString data)
{
  QStringList list = data.split(",");
  QString lat = list.at(0);
  QString lng = list.at(1);
  DcCoordinate cord(lat.toDouble(),lng.toDouble());
  m_pMapView->setCenter(cord,true);
  m_pMapView->updateMarker(cord);
}

void MainWidget::onUDPConnect(bool isConnected)
{
  if(isConnected)
  {
    m_pUdpSocketIPEdit->setDisabled(true);
    m_pUdpSocketPortEdit->setDisabled(true);
    m_pStartBtn->setText("Stop");
  }
  else
  {
    m_pUdpSocketIPEdit->setEnabled(true);
    m_pUdpSocketPortEdit->setEnabled(true);
    m_pStartBtn->setText("Start");
  }
}
