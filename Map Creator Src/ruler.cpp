#include "ruler.h"
#include "QDebug"
#include "mapview.h"
Ruler::Ruler(MapView *m, QPointF p,QGraphicsItem *parent): QGraphicsItem(parent)
{
    map=m;
    startPoint=p;
    currentPoint=p;
}

void Ruler::SetCurrentPoint(QPointF p)
{
    //prepareGeometryChange();
    currentPoint=p;
    update();
}

Ruler::~Ruler()
{

}

QRectF Ruler::boundingRect() const
{

    QPointF p(currentPoint.x()-startPoint.x()+2,currentPoint.y()-startPoint.y()+2);

    QRectF rect(startPoint.x(), startPoint.y(), p.x(),p.y());
    rect=rect.normalized();
    return QRectF(rect.x()-100,rect.y()-100,rect.width()+200,rect.height()+200);
}

void Ruler::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF p2(20,20);
    //currentPoint.operator +=(p2);
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Ruler::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
    //painter->scale(1/map->getScaleFactor(),1/map->getScaleFactor());
    painter->drawLine(startPoint.x(),startPoint.y(),currentPoint.x(),currentPoint.y());
    painter->drawEllipse(QRectF(startPoint.x()-2, startPoint.y()-2, 4,4));
    painter->drawEllipse(QRectF(currentPoint.x()-2, currentPoint.y()-2, 4,4));

    painter->setBrush(Qt::white);
    painter->setOpacity(0.75);
    painter->drawRect((currentPoint.x()+5)*map->getScaleFactor(), currentPoint.y()*map->getScaleFactor(),65, 35);


    painter->setBrush(Qt::red);
    painter->setOpacity(1);
    painter->drawText(currentPoint.x()+10,currentPoint.y()+20,"Dt = "+QString::number(currentPoint.y()));
    //painter->drawRect(boundingRect());
        Q_UNUSED(option);
        Q_UNUSED(widget);


}
