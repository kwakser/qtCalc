#pragma once

#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

class calculator : public QWidget{
    Q_OBJECT
public:
    calculator(QWidget *parent = 0);

private slots:
    void plus();
    void minus();
    void multiply();
    void divide();
    void equal();
    void clear();
    void remove();

    void add_digit(int digit);

private:
    QLineEdit *written_number;
};
