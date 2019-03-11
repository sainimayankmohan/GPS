#include "proxySetting.h"

ProxySetting::ProxySetting()
{
  m_pProxyServerLbl = new QLabel("Proxy Server");
  m_pProxyPortLbl = new QLabel("Proxy Port");
  m_pUsernameLbl = new QLabel("Username");
  m_pPasswordLbl = new QLabel("Password");

  m_pProxyServerLEdit = new QLineEdit;
  m_pProxyServerLEdit->setText("proxy.gtm.visteon.com");
  m_pPortLEdit = new QLineEdit;
  m_pPortLEdit->setText("83");
  m_pUserNameLEdit = new QLineEdit;
  m_pUserNameLEdit->setText("msaini1@visteon.com");
  m_pPasswordLEdit = new QLineEdit;
  m_pPasswordLEdit->setEchoMode(QLineEdit::Password);

  m_pOkBtn = new QPushButton("Ok");
  m_pCancelBtn = new QPushButton("Cancel");

  m_pProxyLayout = new QGridLayout;

  m_pProxyLayout->addWidget(m_pProxyServerLbl,0,0);
  m_pProxyLayout->addWidget(m_pProxyServerLEdit,0,1);
  m_pProxyLayout->addWidget(m_pProxyPortLbl,1,0);
  m_pProxyLayout->addWidget(m_pPortLEdit,1,1);
  m_pProxyLayout->addWidget(m_pUsernameLbl,2,0);
  m_pProxyLayout->addWidget(m_pUserNameLEdit,2,1);
  m_pProxyLayout->addWidget(m_pPasswordLbl,3,0);
  m_pProxyLayout->addWidget(m_pPasswordLEdit,3,1);
  m_pProxyLayout->addWidget(m_pOkBtn,4,0);
  m_pProxyLayout->addWidget(m_pCancelBtn,4,1);

  setLayout(m_pProxyLayout);
  setFixedSize(300,300);
  setWindowFlags(Qt::FramelessWindowHint);

  connect(m_pOkBtn,SIGNAL(pressed()),this,SLOT(accept()));
  connect(m_pCancelBtn,SIGNAL(pressed()),this,SLOT(reject()));
}

ProxySetting::~ProxySetting()
{
  disconnect(m_pOkBtn,SIGNAL(pressed()),this,SLOT(accept()));
  disconnect(m_pCancelBtn,SIGNAL(pressed()),this,SLOT(reject()));

  delete m_pProxyServerLbl;
  delete m_pProxyServerLEdit;
  delete m_pProxyPortLbl;
  delete m_pPortLEdit;
  delete m_pUsernameLbl;
  delete m_pUserNameLEdit;
  delete m_pPasswordLbl;
  delete m_pPasswordLEdit;
  delete m_pOkBtn;
  delete m_pCancelBtn;
  delete m_pProxyLayout;
}

QString ProxySetting::getProxyServer()
{
  return m_pProxyServerLEdit->text();
}

QString ProxySetting::getProxyPort()
{
  return m_pPortLEdit->text();
}

QString ProxySetting::getUserName()
{
  return m_pUserNameLEdit->text();
}

QString ProxySetting::getUserPassword()
{
  return m_pPasswordLEdit->text();
}
