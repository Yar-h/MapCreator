#ifndef RULER_H
#define RULER_H
#include "QGraphicsItem"
#include "QPainter"
//#include "mapview.h"
#include "QPointF"
class MapView;
class Ruler : public QGraphicsItem
{
public:
    Ruler(MapView *m, QPointF p, QGraphicsItem *parent=0);
    void SetCurrentPoint(QPointF p);
    ~Ruler();
    QRectF boundingRect() const;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    MapView *map;
    QPointF startPoint;
    QPointF currentPoint;





    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // RULER_H
