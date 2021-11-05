#ifndef QTCLIENT_H
#define QTCLIENT_H

#include <QWidget>
#include <QtWidgets>
#include <QTcpServer>
#include <QTcpSocket>
class QtClient : public QWidget
{
    Q_OBJECT
public:
    explicit QtClient(QWidget *parent = nullptr);
    ~QtClient();

    void initLayout();
public slots:
    void On_connectServer_clicked();

    void On_SendMsg_clicked();

    void On_disConnect_clcked();
private:
    QLabel* label;
    QLabel* label1;
    QTextEdit* textEdit;
    QTextEdit* TextEdit;

    QPushButton* connectServer;
    QPushButton* SendMsg;
    QPushButton* disConnect;

    QLineEdit* lineEdit;
    QLineEdit* LineEdit;

    QTcpSocket* m_socket;

};

#endif // QTCLIENT_H
