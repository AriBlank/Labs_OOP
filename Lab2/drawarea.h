#pragma once

#include <iostream>
#include <string>
#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QColor>
#include <QList>
#include <QPainter>

enum class Tool {
    NoTool,
    PointTool,
    LineTool,
    RectangleTool,
    EllipseTool
};

class Shapes{
    protected:
    QColor shapeColor = Qt::black;
    int shapeWidth = 2;
    QPoint startPoint;
    QPoint lastPoint;
    public:
    virtual void draw(QPainter *painter)=0;
    Shapes(QPoint sp, QPoint ep);
    virtual ~Shapes();
};

class DrawingShapes : public QWidget {
    public:
    DrawingShapes(QWidget *parent = nullptr);
    Tool getTool(Tool newTool);
    ~DrawingShapes();
    
    protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

    private:
    QPoint startPoint;
    QPoint lastPoint;
    Tool currentTool = Tool::NoTool;
    bool dragging = false; 
    QColor penColor;
    QList <Shapes*> objects;
};

class PointShape : public Shapes {
    public:
    void draw(QPainter *painter) override;
    PointShape(QPoint sp);
};

class LineShape : public Shapes {
   public:
    void draw(QPainter *painter) override;
    LineShape(QPoint sp, QPoint ep);
};

class RectShape : public Shapes {
    public:
    void draw(QPainter *painter) override;
    RectShape(QPoint sp, QPoint ep);
    static QPoint rightBottomPoint(QPoint sp, QPoint ep);
};

class EllipseShape : public Shapes {
    public:
    void draw(QPainter *painter) override;
    EllipseShape(QPoint sp, QPoint ep);
};

