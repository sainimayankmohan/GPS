#include "proxySetting.h"
#include "mainWidget.h"
#include <QApplication>
#include <QNetworkProxy>
#include <QAbstractSocket>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ProxySetting *proxySettings = new ProxySetting();
    if(QDialog::Accepted == proxySettings->exec())
    {
      QNetworkProxy proxy;
      proxy.setType(QNetworkProxy::Socks5Proxy);
      proxy.setType(QNetworkProxy::HttpProxy);
      proxy.setHostName(proxySettings->getProxyServer());
      proxy.setPort(proxySettings->getProxyPort().toUInt());
      proxy.setUser(proxySettings->getUserName());
      proxy.setPassword(proxySettings->getUserPassword());
      QNetworkProxy::setApplicationProxy(proxy);
    }
    delete proxySettings;

    MainWidget w;
    w.show();
    
    return a.exec();
}
