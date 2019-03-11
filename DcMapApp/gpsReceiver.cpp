#include <gpsReceiver.h>
#include <QNetworkProxy>

GPSReceiver::GPSReceiver():m_State(QAbstractSocket::UnconnectedState)
{
  m_pSocket = new QUdpSocket(this);
  m_pSocket->setProxy(QNetworkProxy::NoProxy);
  connect(m_pSocket,SIGNAL(connected()),this,SLOT(connected()),Qt::UniqueConnection);
  connect(m_pSocket,SIGNAL(bytesWritten(qint64)),this,SLOT(bytesWritten(qint64)),Qt::UniqueConnection);
  connect(m_pSocket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::UniqueConnection);
  connect(m_pSocket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::UniqueConnection);
  connect(m_pSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this,SLOT(socketStateChanged(QAbstractSocket::SocketState)),Qt::UniqueConnection);
  connect(m_pSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(socketError(QAbstractSocket::SocketError)),Qt::UniqueConnection);
}

GPSReceiver::~GPSReceiver()
{
  disconnect(m_pSocket,SIGNAL(connected()),this,SLOT(connected()));
  disconnect(m_pSocket,SIGNAL(bytesWritten(qint64)),this,SLOT(bytesWritten(qint64)));
  disconnect(m_pSocket,SIGNAL(readyRead()),this,SLOT(readyRead()));
  disconnect(m_pSocket,SIGNAL(disconnected()),this,SLOT(disconnected()));
  disconnect(m_pSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this,SLOT(socketStateChanged(QAbstractSocket::SocketState)));
  disconnect(m_pSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(socketError(QAbstractSocket::SocketError)));

  delete m_pSocket;
}

bool GPSReceiver::requestConnect(QString ip,QString port)
{
  bool ret = false;
  if(m_State == QAbstractSocket::UnconnectedState)
  {
    qDebug()<<"Binding";
    m_pSocket->bind(QHostAddress(ip),port.toUInt());
    ret = true;
  }
  return ret;
}

bool GPSReceiver::requestDisconnect()
{
  bool ret = false;
  if(m_State == QAbstractSocket::BoundState)
  {
    m_pSocket->disconnectFromHost();
    ret = true;
  }
  return ret;
}

void GPSReceiver::connected()
{
  qDebug()<<"Connected to Server";
}

void GPSReceiver::disconnected()
{

}

void GPSReceiver::bytesWritten(qint64 bytes)
{
  qDebug()<<"Bytes written"<<bytes;
}

void GPSReceiver::readyRead()
{
  while (m_pSocket->hasPendingDatagrams()) {
          QByteArray buffer;
          buffer.resize(m_pSocket->pendingDatagramSize());
          QHostAddress sender;
          quint16 senderPort;
          m_pSocket->readDatagram(buffer.data(), buffer.size(),&sender, &senderPort);
          onDataReceived(buffer);
    }
}


void GPSReceiver::socketError(QAbstractSocket::SocketError error)
{
  qDebug()<<"Error in Socket"<<error;
}

void GPSReceiver::socketStateChanged(QAbstractSocket::SocketState state)
{
  qDebug()<<"Socket State Changed"<<state;
  if(state == QAbstractSocket::BoundState)
  {
    emit onUDPConnect(true);
  }
  else if(state == QAbstractSocket::UnconnectedState)
  {
    emit onUDPConnect(false);
  }
  m_State = state;
}

void GPSReceiver::sendMessage(QString msg)
{
  m_pSocket->write(msg.toLocal8Bit());
}
