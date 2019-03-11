#ifndef GPSRECEIVER_H
#define GPSRECEIVER_H

#include <dcCoordinate.h>
#include <QtNetwork/QUdpSocket>
#include <QObject>

class GPSReceiver:public QObject
{
  Q_OBJECT
public:

  GPSReceiver();
  ~GPSReceiver();

  bool requestConnect(QString ip,QString port);
  bool requestDisconnect();

  void sendMessage(QString msg);

private slots:
  void connected();
  void disconnected();

  void bytesWritten(qint64 bytes);
  void readyRead();

  void socketError(QAbstractSocket::SocketError error);
  void socketStateChanged(QAbstractSocket::SocketState state);

signals:
  void onDataReceived(QString);
  void onUDPConnect(bool);
  void error(QString err);
private:
  QUdpSocket *m_pSocket;
  QAbstractSocket::SocketState m_State;
};

#endif // GPSRECEIVER_H
