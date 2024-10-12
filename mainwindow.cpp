#include "mainwindow.h"

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QString>
#include <QMessageBox>

Login::Login(QWidget * parent)
    : QWidget(parent){
    QLabel *hint_lbl = new QLabel("Username:123    password:123");
    QLabel *username_lbl = new QLabel("Login");
    QLabel *password_lbl = new QLabel("Password");

    enter_username = new QLineEdit(this);
    enter_password = new QLineEdit(this);
    enter_password->setEchoMode(QLineEdit::Password);
    QPushButton *enter_btn = new QPushButton("ENTER");

    QGridLayout *grid = new QGridLayout;
    grid->addWidget(hint_lbl, 0, 0,1,4,Qt::AlignCenter);
    grid->addWidget(username_lbl,1,0,1,1);
    grid->addWidget(enter_username,1,1,1,1);
    grid->addWidget(password_lbl,1,2,1,1);
    grid->addWidget(enter_password,1,3,1,1);
    grid->addWidget(enter_btn,2,0,2,4);


    setLayout(grid);
    connect(enter_btn, &QPushButton::clicked, this, &Login::check_login_and_password);



}
void Login::check_login_and_password(){
    QString username = enter_username->text();
    QString password = enter_password->text();
    QString correct_username = QString("123");
    QString correct_password = QString("123");
    if (username==correct_username && password==correct_password){
        emit login_successful();
        close();
    }
    else{
        QMessageBox::warning(this, "LOGIN ERROR!", "Wrong login or password!");
    }

}
