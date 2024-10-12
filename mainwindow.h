#pragma once
#include <QObject>
#include <QWidget>
#include <QLineEdit>
class Login : public QWidget{
    Q_OBJECT
public:
    Login(QWidget *parent = 0);

public slots:
    void check_login_and_password();
signals:
    void login_successful();
private:
    QLineEdit *enter_username;
    QLineEdit *enter_password;

};
