#include "mainwindow.h"
#include "drawarea.h"
#include <QWidget>
#include <QMainWindow>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ObjectMenu window;
    window.resize(650,400);
    window.setWindowTitle("Lab2");
    window.show();
    return app.exec();
}