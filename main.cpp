#include "ui/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOrganizationName("Qomodoro");
    QApplication::setApplicationName("Qomodoro");
    MainWindow w;
    w.resize(400, 600);
    w.setWindowTitle("Qomodoro");
    w.show();
    w.exit();
    return a.exec();
}
