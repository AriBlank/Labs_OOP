#pragma once

#include <QMainWindow>
#include <QApplication>
#include "drawarea.h"

class ObjectMenu : public QMainWindow { 
    public:
    ObjectMenu(QWidget *parent = nullptr);
    
    private:
    
    DrawingShapes *drawingShapes; 

    void createMenus();
    void createActions();

    QMenu *file;

    QAction *quit;
    QAction *point;
    QAction *line;
    QAction *rect;
    QAction *ellipse;
};



