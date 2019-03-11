#ifndef PROXYSETTING_H
#define PROXYSETTING_H

#include <QObject>
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class ProxySetting : public QDialog
{
  Q_OBJECT
public:
  ProxySetting();
  ~ProxySetting();

  QString getProxyServer();
  QString getProxyPort();
  QString getUserName();
  QString getUserPassword();

private:
  QGridLayout *m_pProxyLayout;

  QLabel *m_pProxyServerLbl;
  QLineEdit *m_pProxyServerLEdit;

  QLabel *m_pProxyPortLbl;
  QLineEdit *m_pPortLEdit;

  QLabel *m_pUsernameLbl;
  QLineEdit *m_pUserNameLEdit;

  QLabel *m_pPasswordLbl;
  QLineEdit *m_pPasswordLEdit;

  QPushButton *m_pOkBtn;
  QPushButton *m_pCancelBtn;
};

#endif // PROXYSETTING_H
