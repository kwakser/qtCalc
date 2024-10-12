#include "calculator.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    calculator calc;
    Login login;
    login.resize(600,400);
    login.setWindowTitle("Calculator");
    QObject::connect(&login, &Login::login_successful, [&] {calc.show();});
    login.show();

    return app.exec();
}
