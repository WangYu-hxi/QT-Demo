#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QTcpServer>
#include "qtclient.h"
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void initLayout();
public slots:
    void On_SendButton();
    void On_connectButton();
public:
    QLabel* label;
    QPushButton* SendButton;
    QPushButton* ConnectButton;
    QLineEdit* lineEdit;
    QTextEdit* TextEdit;
    QTextEdit* textEdit;
    QLineEdit* LineEdit;

    QtClient* client;

    QTcpServer* m_server;
    QTcpSocket* m_socket;
};
#endif // WIDGET_H
