#include "widget.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    initLayout();
    connect(SendButton,&QPushButton::clicked,this,&Widget::On_SendButton);
    connect(ConnectButton,&QPushButton::clicked,this,&Widget::On_connectButton);

    m_server = new QTcpServer(this);
    connect(m_server,&QTcpServer::newConnection,this,[=]()
    {
        m_socket = m_server->nextPendingConnection();
        TextEdit->append(QStringLiteral("成功和客户端建立了新的连接..."));
        connect(m_socket,&QTcpSocket::readyRead,this,[=]()
        {
            //接收数据
            QString recvMsg = m_socket->readAll();
            TextEdit->append(QStringLiteral("客户端say:")+recvMsg);
        });
        //客户端断开连接
        connect(m_socket,&QTcpSocket::disconnected,this,[=]()
        {
            TextEdit->append(QStringLiteral("客户端已经断开了连接..."));
            m_socket->deleteLater();
        });
    });

}

Widget::~Widget()
{
}

void Widget::initLayout()
{
    this->setWindowTitle(QStringLiteral("服务器端_网络通信"));
//设计布局
    QHBoxLayout* HBoxLayout = new QHBoxLayout();
    QHBoxLayout* hboxLayout = new QHBoxLayout();
    QVBoxLayout* VBoxLayout = new QVBoxLayout();
    QHBoxLayout* CBoxLayout = new QHBoxLayout();
//QLabel和LineEdit
    QWidget *Widget = new QWidget(this);
    label = new QLabel(QStringLiteral("端口号:"),Widget);
    lineEdit = new QLineEdit(Widget);
    ConnectButton = new QPushButton(QStringLiteral("连接客户端"),Widget);
    QLabel* label1 = new QLabel(Widget);
    label1->setText(QStringLiteral("ip地址:"));
    LineEdit = new QLineEdit(Widget);
    CBoxLayout->addWidget(label1);
    CBoxLayout->addWidget(LineEdit);
    CBoxLayout->addSpacing(100);
    HBoxLayout->addWidget(label);
    HBoxLayout->addWidget(lineEdit);
    HBoxLayout->addWidget(ConnectButton);
//    Widget->setLayout(HBoxLayout);
//    Widget->show();
    //QGroupBox通信记录
    QVBoxLayout* BoxLayout = new QVBoxLayout();
    QGroupBox* GroupBox = new QGroupBox(this);
    TextEdit = new QTextEdit(this);
    QString Text =TextEdit->toPlainText();
    BoxLayout->addWidget(TextEdit);
    GroupBox->setLayout(BoxLayout);
    GroupBox->setTitle(QStringLiteral("历史记录"));
//QGroupBox发送信息
    QVBoxLayout* boxLayout = new QVBoxLayout();
    QGroupBox* Group_Box = new QGroupBox(this);
    Group_Box->setTitle(QStringLiteral("发送消息"));
    textEdit = new QTextEdit(this);
    QString text = textEdit->toPlainText();
    boxLayout->addWidget(textEdit);
    Group_Box->setLayout(boxLayout);
    SendButton = new QPushButton();
    SendButton->setText(QStringLiteral("发送消息"));

    hboxLayout->addSpacing(300);
    hboxLayout->addWidget(SendButton);
    hboxLayout->addSpacing(30);


    VBoxLayout->addLayout(HBoxLayout);
    VBoxLayout->addLayout(CBoxLayout);
    VBoxLayout->addWidget(GroupBox);
    VBoxLayout->addWidget(Group_Box);
    VBoxLayout->addLayout(hboxLayout);

    this->setLayout(VBoxLayout);
    this->resize(450,600);
}

void Widget::On_SendButton()
{
    QString sendMsg = textEdit->toPlainText();
    m_socket->write(sendMsg.toUtf8());
    TextEdit->append(QStringLiteral("服务器Say:")+ sendMsg);
    textEdit->clear();
}

void Widget::On_connectButton()
{
    QString ip = LineEdit->text();
    unsigned short port = lineEdit->text().toInt();
    qDebug()<<"ip:"<<ip<<"port:"<<port<<endl;
    m_server->listen(QHostAddress(ip),port);
}

