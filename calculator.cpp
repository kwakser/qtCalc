#include "calculator.h"
#include <QGridLayout>
#include <QMessageBox>
#include <QLineEdit>

calculator::calculator(QWidget * parent)
    : QWidget(parent){
    QPushButton *plus_btn = new QPushButton("+", this);
    QPushButton *minus_btn = new QPushButton("-", this);
    QPushButton *multiply_btn = new QPushButton("*", this);
    QPushButton *divide_btn = new QPushButton("/", this);
    QPushButton *equal_btn = new QPushButton("=", this);
    QPushButton *clear_btn = new QPushButton("AC", this);
    QPushButton *remove_digit_btn = new QPushButton("C",this);

    const QString buttonLabels[] = { "0","1", "2", "3", "4", "5", "6", "7", "8", "9"};
    QPushButton *add_btn[10];
    for(int i = 0; i < 10;i++){
        add_btn[i] = new QPushButton(buttonLabels[i], this);
    }

    written_number = new QLineEdit("0", this);
    written_number->setReadOnly(true);

    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(plus_btn,1, 3);
    grid->addWidget(minus_btn, 2, 3);
    grid->addWidget(multiply_btn, 3, 3);
    grid->addWidget(divide_btn, 4, 3);
    grid->addWidget(equal_btn, 4, 2);
    grid->addWidget(remove_digit_btn,4,0);

    for(int i = 0; i <= 2; ++i){
        for (int j = 0; j <=2; ++j){
            grid->addWidget(add_btn[i*3 + j+1],i+1,j);
        }
    }
    grid->addWidget(add_btn[0], 4, 1);


    grid->addWidget(written_number, 0, 0,1,4);
    grid->setRowStretch(4,10);
    grid->addWidget(clear_btn, 6,3);
    setLayout(grid);

    connect(plus_btn, &QPushButton::clicked, this, &calculator::plus);
    connect(minus_btn, &QPushButton::clicked, this, &calculator::minus);
    connect(multiply_btn, &QPushButton::clicked, this, &calculator::multiply);
    connect(divide_btn, &QPushButton::clicked, this, &calculator::divide);
    connect(equal_btn, &QPushButton::clicked, this, &calculator::equal);
    connect(clear_btn,&QPushButton::clicked, this, &calculator::clear);
    connect(remove_digit_btn,&QPushButton::clicked, this, &calculator::remove);

    for (int i = 0; i < 10; i++){

        connect(add_btn[i], &QPushButton::clicked, this,[this,i] {add_digit(i);});
    }
}


void calculator::plus(){
    QString val = written_number->text();
    if(val.endsWith(" + ") || val.endsWith(" - ") || val.endsWith(" / ") || val.endsWith(" * ")){
        val.chop(3);
    }
    val += " + ";
    written_number->setText(val);
}
void calculator::minus(){
    QString val = written_number->text();
    if(val.endsWith(" + ") || val.endsWith(" - ") || val.endsWith(" / ") || val.endsWith(" * ")){
        val.chop(3);
    }
    val += " - ";
    written_number->setText(val);
}
void calculator::multiply(){
    QString val = written_number->text();
    if(val.endsWith(" + ") || val.endsWith(" - ") || val.endsWith(" / ") || val.endsWith(" * ")){
        val.chop(3);
    }
    val += " * ";
    written_number->setText(val);
}
void calculator::divide(){
    QString val = written_number->text();
    if(val.endsWith(" + ") || val.endsWith(" - ") || val.endsWith(" / ") || val.endsWith(" * ")){
        val.chop(3);
    }
    val += " / ";
    written_number->setText(val);
}

void calculator::equal(){
    QString number = "";
    std::vector<std::string> numbers;
    std::vector<char> signs;
    QString val = written_number->text().remove(' ');
    for(int i = 0; i < val.length(); i++){
        QChar symbol = val.at(i);
        if (symbol.isDigit()){
            number.append(symbol);
        }
        else{
            signs.push_back(symbol.toLatin1());
            numbers.push_back(number.toStdString());
            number = "";
        }
    }
    if (!number.isEmpty()) {
        numbers.push_back(number.toStdString());
    }

    numbers.push_back("0");
    for(int i  = 0; i < signs.size(); i++){
        float num_1 = std::stof(numbers[0]);
        float num_2 = std::stof(numbers[i+1]);
        if (signs[i] == '+'){
            numbers[0] = std::to_string(num_1 + num_2);
        }
        else if(signs[i] == '-'){
            numbers[0] = std::to_string(num_1 - num_2);
        }
        else if(signs[i] == '*'){
            numbers[0] = std::to_string(num_1 * num_2);
        }
        else if(signs[i] == '/'){
            if (num_2 != 0){
                numbers[0] = std::to_string(num_1 / num_2);
            }
            else{
                QMessageBox::warning(this, "DIVISION ZERO ERROR!","YOU CANT DIVIDE BY ZERO!");
            }
        }
    }
    written_number->setText(QString::fromStdString(numbers[0]));
}

void calculator::clear(){
    written_number->setText(QString("0"));
}
void calculator::remove(){
    QString val = written_number->text();
    if(val != '0'){
        val.chop(1);
        written_number->setText(val);
    }
}


void calculator::add_digit(int digit){
    std::string val = written_number->text().toStdString();
    if (val == "0"){
        written_number->setText(QString::number(digit));
    }
    else
    {
        std::string new_number = val + std::to_string(digit);
        written_number->setText(QString::fromStdString(new_number));
    }
}
