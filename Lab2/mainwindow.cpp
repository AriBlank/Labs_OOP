#include "mainwindow.h"
#include "drawarea.h"
#include <QMenu>
#include <QMenuBar>

ObjectMenu::ObjectMenu(QWidget *parent) : QMainWindow(parent), 
drawingShapes(new DrawingShapes(this)){ 
    setCentralWidget(drawingShapes);
    drawingShapes->setStyleSheet("background-color:white;");
    createActions();
    createMenus();
};

void ObjectMenu::createActions(){
    //quit = new QAction ("Quit", this);
    point = new QAction ("Point", this);
    line = new QAction ("Line", this);
    rect = new QAction ("Rectangle", this);
    ellipse = new QAction ("Ellipses", this);

    //connect(quit, &QAction::triggered, QApplication::quit);
    connect(point, &QAction::triggered, [this](){drawingShapes->getTool(Tool::PointTool); this->setWindowTitle("Lab2 - Point");});
    connect(line, &QAction::triggered, [this](){drawingShapes->getTool(Tool::LineTool); this->setWindowTitle("Lab2 - Line");});
    connect(rect, &QAction::triggered, [this](){drawingShapes->getTool(Tool::RectangleTool); this->setWindowTitle("Lab2 - Rectangle");});
    connect(ellipse, &QAction::triggered, [this](){drawingShapes->getTool(Tool::EllipseTool); this->setWindowTitle("Lab2 - Ellipse");});
}

void ObjectMenu::createMenus(){
    menuBar()->addMenu("File");
    file = menuBar()->addMenu("Objects");
    menuBar()->addMenu("Help");
    //file->addAction(quit);
    file->addAction(point);
    file->addAction(line);
    file->addAction(rect);
    file->addAction(ellipse);
}