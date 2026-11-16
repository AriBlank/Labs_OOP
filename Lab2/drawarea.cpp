#include "drawarea.h"
#include <Qt>
#include <QPainter>
#include <QPen>

DrawingShapes::DrawingShapes(QWidget *parent) : QWidget(parent){
    setAttribute(Qt::WA_StaticContents);
}
DrawingShapes::~DrawingShapes(){
    for (int i {0}; i < objects.size(); i++){
        delete objects[i];
    }
}
Shapes::~Shapes(){}
Shapes::Shapes(QPoint sp, QPoint ep){
    startPoint = sp;
    lastPoint = ep;
}


PointShape::PointShape(QPoint sp) : Shapes(sp, sp){}
void PointShape::draw(QPainter *painter){
    painter->setPen(QPen(shapeColor, shapeWidth, Qt::SolidLine));
    painter->drawPoint(startPoint);
}


LineShape::LineShape(QPoint sp, QPoint ep) : Shapes(sp, ep){}
void LineShape::draw(QPainter *painter){
    painter->setPen(QPen(shapeColor, shapeWidth, Qt::SolidLine));
    painter->drawLine(startPoint, lastPoint);
}


QPoint RectShape::rightBottomPoint(QPoint sp, QPoint ep){
    QPoint newSp((sp.rx() - (ep.rx() - sp.rx())), (sp.ry() - (ep.ry() - sp.ry())));
    return newSp;
}
RectShape::RectShape(QPoint sp, QPoint ep):Shapes(rightBottomPoint(sp, ep), ep){}
void RectShape::draw(QPainter *painter){
    painter->setBrush(QColor(157, 199, 129));
    painter->setPen(QPen(shapeColor, shapeWidth, Qt::SolidLine));
    painter->drawRect((QRectF(lastPoint, startPoint)).normalized());
}


EllipseShape::EllipseShape(QPoint sp, QPoint ep) : Shapes(sp,ep){}
void EllipseShape::draw(QPainter *painter){
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(shapeColor, shapeWidth, Qt::SolidLine));
    painter->drawEllipse((QRectF(startPoint, lastPoint)).normalized());
}

void DrawingShapes::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        dragging = true;
        startPoint = event->position().toPoint();
        lastPoint = startPoint;
        switch(currentTool){
        case Tool::PointTool:
            if(objects.size()<107){
                PointShape *obj = new PointShape(startPoint);
                objects.append(obj);
                dragging = false;
                update();
            }
            break;

        case Tool::LineTool:
            update();
            break;

        case Tool::RectangleTool:
            update();
            break;

        case Tool::EllipseTool:
            update();
            break;
        }   
    }
}

void DrawingShapes::mouseMoveEvent(QMouseEvent *event){
    if ((event->buttons() & Qt::LeftButton) && dragging){
        lastPoint = event->position().toPoint();
        update();
    }
}

void DrawingShapes::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && dragging) {
        lastPoint = event->position().toPoint();
        dragging = false;
        switch(currentTool){
            case Tool::LineTool:
                if(objects.size()<107){
                    LineShape *obj = new LineShape(startPoint, lastPoint);
                    objects.append(obj);
                }
                break;

            case Tool::RectangleTool:
                if(objects.size()<107){
                    RectShape *obj = new RectShape(startPoint, lastPoint);
                    objects.append(obj);
                }
                break;

            case Tool::EllipseTool:
                if(objects.size()<107){
                    EllipseShape *obj = new EllipseShape(startPoint, lastPoint);
                    objects.append(obj);
                }
                break;
        }
        update();
    }
}

void DrawingShapes::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    for(int i {0}; i < objects.size(); i++){
        objects[i]->draw(&painter);
    }
    if (dragging){
        switch(currentTool){
        case Tool::LineTool:
            painter.setPen(QPen(Qt::black, 2, Qt::DashLine));
            painter.drawLine(startPoint, lastPoint);
            break;

        case Tool::RectangleTool:
            painter.setPen(QPen(Qt::black, 2, Qt::DashLine));
            painter.setBrush(Qt::NoBrush);
            painter.drawRect(QRectF(RectShape::rightBottomPoint(startPoint, lastPoint), lastPoint).normalized());
            break;

        case Tool::EllipseTool:
            painter.setPen(QPen(Qt::black, 2, Qt::DashLine));
            painter.setBrush(Qt::NoBrush);
            painter.drawEllipse(QRectF(startPoint, lastPoint).normalized());
            break;
        }
    }
}
Tool DrawingShapes::getTool(Tool newTool){ 
    Tool oldTool = currentTool;
    currentTool = newTool;
    return  oldTool;
}

