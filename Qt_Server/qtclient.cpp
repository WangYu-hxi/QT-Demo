#include "qtclient.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

QtClient::QtClient(QWidget *parent) : QWidget(parent)
{
    initLayout();
    connect(connectServer,&QPushButton::clicked,this,&QtClient::On_connectServer_clicked);
    connect(disConnect,&QPushButton::clicked,this,&QtClient::On_disConnect_clcked);
    connect(SendMsg,&QPushButton::clicked,this,&QtClient::On_SendMsg_clicked);

    this->setWindowTitle(QStringLiteral("客户端_网络通信"));
    m_socket = new QTcpSocket(this);

    connect(m_socket,&QTcpSocket::readyRead,[&]()
    {
        QByteArray recvMsg = m_socket->readAll();
        TextEdit->append(QStringLiteral("服务器Say:") + recvMsg);
    });

    connect(m_socket,&QTcpSocket::connected,this,[&]()
    {
        TextEdit->append(QStringLiteral("恭喜，服务器连接成功"));
    });

    connect(m_socket,&QTcpSocket::disconnected,this,[&]()
    {
        TextEdit->append(QStringLiteral("服务器已经断开连接..."));
        connectServer->setEnabled(true);
        disConnect->setEnabled(false);
    });


}

QtClient::~QtClient()
{

}

void QtClient::initLayout()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QVBoxLayout* VBoxLayout = new QVBoxLayout(this);
    QVBoxLayout* vBoxLayout = new QVBoxLayout(this);
    QVBoxLayout* BoxLayout = new QVBoxLayout(this);
    QHBoxLayout* boxLayout = new QHBoxLayout(this);
    QHBoxLayout* HBoxLayout = new QHBoxLayout(this);
    QHBoxLayout* hBoxLayout = new QHBoxLayout(this);

    QWidget* widget = new QWidget(this);
    label = new QLabel(QStringLiteral("端口号:"),widget);
    lineEdit = new QLineEdit(widget);
    connectServer = new QPushButton(QStringLiteral("连接服务器"),widget);

    label1 = new QLabel(QStringLiteral("IP地址:"),widget);
    LineEdit = new QLineEdit(widget);
    disConnect = new QPushButton(QStringLiteral("断开连接"),widget);

    HBoxLayout->addWidget(label);
    HBoxLayout->addWidget(lineEdit);
    HBoxLayout->addWidget(connectServer);

    hBoxLayout->addWidget(label1);
    hBoxLayout->addWidget(LineEdit);
    hBoxLayout->addWidget(disConnect);

    VBoxLayout->addLayout(HBoxLayout);
    VBoxLayout->addLayout(hBoxLayout);
   // widget->setLayout(VBoxLayout);


//QGroupBox--1
    QGroupBox* GroupBox = new QGroupBox();
    GroupBox->setTitle(QStringLiteral("通信记录"));
    TextEdit = new QTextEdit(this);
    vBoxLayout->addWidget(TextEdit);
    GroupBox->setLayout(vBoxLayout);
//QGroupBox--2
    QGroupBox* Group_Box = new QGroupBox();
    Group_Box->setTitle(QStringLiteral("发送信息"));
    textEdit = new QTextEdit(this);
    BoxLayout->addWidget(textEdit);
    Group_Box->setLayout(BoxLayout);

    SendMsg = new QPushButton(QStringLiteral("发送"),this);
    boxLayout->addSpacing(300);
    boxLayout->addWidget(SendMsg);
    boxLayout->addSpacing(30);

    mainLayout->addLayout(VBoxLayout);
    mainLayout->addWidget(GroupBox);
    mainLayout->addWidget(Group_Box);
    mainLayout->addLayout(boxLayout);

    this->setLayout(mainLayout);
    this->resize(450,600);

}

void QtClient::On_connectServer_clicked()
{
    QString ip = LineEdit->text();
    unsigned short port = lineEdit->text().toInt();
    m_socket->connectToHost(QHostAddress(ip),port);
    connectServer->setEnabled(false);
    disConnect->setEnabled(true);
}

void QtClient::On_SendMsg_clicked()
{
    QString sendMsg = textEdit->toPlainText();
    m_socket->write(sendMsg.toUtf8());
    TextEdit->append(QStringLiteral("客户端Say:") + sendMsg);
    textEdit->clear();
}

void QtClient::On_disConnect_clcked()
{
    m_socket->close();
    connectServer->setEnabled(true);
    disConnect->setEnabled(false);
}
