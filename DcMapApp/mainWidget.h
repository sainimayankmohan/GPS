/*****************************************************************************
 * Widget.h
 *
 * Created: 08/7 2013 by uranusjr
 *
 * Copyright 2013 uranusjr. All rights reserved.
 *
 * This file may be distributed under the terms of GNU Public License version
 * 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
 * license should have been included with this file, or the project in which
 * this file belongs to. You may also find the details of GPL v3 at:
 * http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
 *****************************************************************************/

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <dcMapView.h>
#include <dcCoordinateRegion.h>
#include <gpsReceiver.h>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

public slots:
    void log(QString text, QString delimiter = QString("\n"));
    void log(const char *text, QString delimiter = QString("\n"));

private slots:
    void onMapLoaded();
    void onMapBecameIdle();
    void onRegionChanged(DcCoordinateRegion region);
    void onBtnClicked();
    void onDataReceived(QString);
    void onUDPConnect(bool isConnected);

private:
    void buildControls();

private:
    QHBoxLayout *m_pMainLayout;

    QGridLayout *m_pUdpLayout;
    QLabel *m_pUdpSocketIPLbl;
    QLabel *m_pUdpSocketPortLbl;
    QLineEdit *m_pUdpSocketIPEdit;
    QLineEdit *m_pUdpSocketPortEdit;

    QVBoxLayout *m_pControlLayout;
    QPushButton *m_pStartBtn;
    DCMapView *m_pMapView;
    QWidget *m_pControlsWidget;
    QTextEdit *m_pLogger;
    GPSReceiver * m_pGPSReceiver;
};

#endif // MAINWIDGET_H
