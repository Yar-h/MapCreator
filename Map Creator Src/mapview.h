#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QApplication>
#include <QGraphicsView>
#include <QEvent>
#include <QWheelEvent>
#include "ruler.h"
#include "geosystemconverter.h"


class MapView : public QGraphicsView
{
    Q_OBJECT
public:
    bool set_1_dot;     //вкл выкл установку точки на карте
    bool set_2_dot;
    bool secondPoint;
    bool firstPoint;
    QPoint *pos_1;      //х,у в метрах по изображению
    QPoint *pos_2;
    QPointF pos_1_m;    //х,у в пикселях по изображению
    QPointF pos_2_m;
    SquareSystem for_distance_1,for_distance_2; //kvadr poloj pos_1, pos_2

    QGraphicsEllipseItem *pos_1_pic;    //Кружки обозначаемые отчки привязки
    QGraphicsEllipseItem *pos_2_pic;
    QPen *pen;
    QBrush *brush;

    bool show_geo;  //отображение в градусах минутах секундах
    bool show_square;   //отображение в метрах
    //char *temp; //широтa

    int distance;   //расстояние между точками привязки в метрах
    double distance_pixel;  //расстояние между точками привязки в пикселях

    GEOPos mapLeftTopPos;
    SquareSystem mapLeftTopPos_square;






    enum MapMode { MapReview, MapRuler, MapEdit };
    MapView(QObject *parent);
    bool eventFilter(QObject *obj, QEvent *event);
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    void mouseMoveEvent( QMouseEvent * event );
    void mousePressEvent( QMouseEvent * event );
    void mouseReleaseEvent( QMouseEvent * event );
    void rotateItem (float Angle);
    void zoomItem(float zoom);
    bool save_Image(const QString &fileName, const char *fileFormat);
    void setMode(MapMode mapmode);
    void setTopLeftPosWithPos1AndPos2();
    void deleteCurrentItem();
    void saveMap();
    void loadMap();
    void setZCurrentItem(int z);
    MapMode getCurrentMode();
    qreal getScaleFactor();
private:
    qreal scale_factor;
    MapMode mode;
    Ruler *ruler;
    QGraphicsItem *currentDraggedItem;
    QGraphicsItem *lastItem;
    QPointF MouseAndItemDiff;
signals:
    void Coordinates(QString strB, QString strL, QString squareX, QString squareY);

};

#endif // MAPVIEW_H
