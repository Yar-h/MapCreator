#include "mapview.h"
#include "QGraphicsEllipseItem"
#include <QInputDialog>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <math.h>

MapView::MapView(QObject *parent)
{
    lastItem=NULL;
    currentDraggedItem=NULL;
    setScene(new QGraphicsScene);
    ruler=NULL;
    //scene()->addItem(new Ruler());

    scale_factor=1;

    set_1_dot=false;
    set_2_dot=false;
    pos_1 = new QPoint();
    pos_2 = new QPoint();

    firstPoint=false;
    secondPoint=false;

    show_geo=true;
    show_square=false;

    distance=0;
    distance_pixel=1;
    mode = MapReview;
}

bool MapView::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Wheel) {
        QWheelEvent *wEvent = static_cast<QWheelEvent *>(event);
        if(wEvent->delta()>0){
            this->scale(1.1,1.1);
            scale_factor*=1.1;
        }else {
            this->scale(1.00/1.1,1.00/1.1);
            scale_factor*=1/1.1;
        }// коэффициенты масштабирования
        return true;
    } else
    {
        return QObject::eventFilter(obj, event);
    }
}

void MapView::enterEvent(QEvent *)
{
    QApplication::setOverrideCursor(QCursor(QPixmap("images/CrossCursor.png")));
}

void MapView::leaveEvent(QEvent *)
{
    QApplication::restoreOverrideCursor();
}

void MapView::mouseMoveEvent(QMouseEvent *e)
{
    if (currentDraggedItem!=NULL){
        //currentDraggedItem->setScale(currentDraggedItem->scale()+0.01);
        //currentDraggedItem->setPos(e->pos().x()+MouseAndItemDiff.x(),e->pos().y()+MouseAndItemDiff.y());
    }
    if (ruler!=NULL)ruler->SetCurrentPoint(mapToScene(e->pos()));
    QGraphicsView::mouseMoveEvent(e);

    QString strB="";
    QString strL="";
    QString squareX="";
    QString squareY="";
    if (secondPoint & firstPoint){
        DMCSystem b_;
        DMCSystem l_;
        SquareSystem square_my;
        QPointF mousePos = mapToScene(e->pos());
        square_my.X = (int)(mapLeftTopPos_square.X-(distance/distance_pixel)*mousePos.x());
        square_my.Y = (int)(mapLeftTopPos_square.Y+(distance/distance_pixel)*mousePos.y());
        squareX = "X = "+QString::number(square_my.X);
        squareY = "Y = "+QString::number(square_my.Y);
        GEOPos geo_my = GEOSystemConverter::SQUARE_TO_SK42(square_my);

        b_ = GEOSystemConverter::Decimal_TO_DMC(geo_my.latitude);
        l_ = GEOSystemConverter::Decimal_TO_DMC(geo_my.longitude);
        strB = "B="+ QString::number((int)b_.degrees)+"° "+QString::number((int)b_.minutes)+"' "+QString::number((b_.seconds));
        strL = "L="+ QString::number((int)l_.degrees)+"° "+QString::number((int)l_.minutes)+"' "+QString::number((l_.seconds));
    }
    Coordinates(strB,strL, squareX, squareY);



}

void MapView::mousePressEvent(QMouseEvent *e)
{
    lastItem = currentDraggedItem;
    currentDraggedItem = itemAt(e->pos());
    if (currentDraggedItem!=NULL){
        qDebug()<<currentDraggedItem->type();
    }
    if (ruler==NULL){
        //ruler= new Ruler(this,this->mapToScene(e->pos()));
        //scene()->addItem(ruler);
    }

    QPointF mousePos = mapToScene(e->pos());

    if(e->button()==Qt::LeftButton){
        if (set_1_dot){
            bool ok;
            if (show_square){
                pos_1->setX(QInputDialog::getText(this, tr("Введите x в метрах."), tr("x:"), QLineEdit::Normal, "5720000", &ok).toInt());
                pos_1->setY(QInputDialog::getText(this, tr("Введите y в метрах."), tr("y:"), QLineEdit::Normal, "6370000", &ok).toInt());
            }
            if (show_geo){
                GEOPos temp_geo;
                temp_geo.latitude = QInputDialog::getText(this, tr("Введите b в градусах."), tr("b:"), QLineEdit::Normal, "51.5947", &ok).toDouble();
                temp_geo.longitude = QInputDialog::getText(this, tr("Введите l в градусах."), tr("l:"), QLineEdit::Normal, "31.1239", &ok).toDouble();
                SquareSystem temp_square = GEOSystemConverter::SK42_TO_SQUARE(temp_geo);
                pos_1->setX(temp_square.X);
                pos_1->setY(temp_square.Y);
            }
            pos_1_m = mousePos;
            if (scene()->items().contains(pos_1_pic)) scene()->removeItem(pos_1_pic);
            pos_1_pic = new QGraphicsEllipseItem(pos_1_m.x()-2,pos_1_m.y()-2,4,4);
            pos_1_pic->setBrush(Qt::red);
            pos_1_pic->setPen(QPen(Qt::red));
            scene()->addItem(pos_1_pic);

            for_distance_1.X=pos_1->x();
            for_distance_1.Y=pos_1->y();

            distance = GEOSystemConverter::calculateDistance(for_distance_1,for_distance_2);
            distance_pixel = sqrt(pow(pos_1_m.x()-pos_2_m.x(),2)+pow(pos_1_m.y()-pos_2_m.y(),2));

   //ui->action_1->setText("Задать точку 1 ("+QString::number(for_distance_1.X)+","+QString::number(for_distance_1.Y)+")");

            setTopLeftPosWithPos1AndPos2(); //установить координаты верхней левой точки изоражения(пока не учитывая угол наклона)
            firstPoint=true;
            set_1_dot=false;
        }
        if (set_2_dot){
            bool ok;
            if (show_square){
                pos_2->setX(QInputDialog::getText(this, tr("Введите x в метрах."), tr("x:"), QLineEdit::Normal, "5720000", &ok).toInt());
                pos_2->setY(QInputDialog::getText(this, tr("Введите y в метрах."), tr("y:"), QLineEdit::Normal, "6380000", &ok).toInt());
            }
            if (show_geo){
                GEOPos temp_geo;
                temp_geo.latitude = QInputDialog::getText(this, tr("Введите b в градусах."), tr("b:"), QLineEdit::Normal, "51.5991", &ok).toDouble();
                temp_geo.longitude = QInputDialog::getText(this, tr("Введите l в градусах."), tr("l:"), QLineEdit::Normal, "31.2681", &ok).toDouble();
                SquareSystem temp_square = GEOSystemConverter::SK42_TO_SQUARE(temp_geo);
                pos_2->setX(temp_square.X);
                pos_2->setY(temp_square.Y);
            }
            pos_2_m = mapToScene(e->pos());
            if (scene()->items().contains(pos_2_pic)) scene()->removeItem(pos_2_pic);
            pos_2_pic = new QGraphicsEllipseItem(pos_2_m.x()-2,pos_2_m.y()-2,4,4);
            pos_2_pic->setBrush(Qt::red);
            pos_2_pic->setPen(QPen(Qt::red));
            scene()->addItem(pos_2_pic);
   //qDebug()<<pos_2->x()<<","<<pos_2->y()<<" at "<<pos_2_m.x()<<","<<pos_2_m.y();

            for_distance_2.X=pos_2->x();
            for_distance_2.Y=pos_2->y();

            distance = GEOSystemConverter::calculateDistance(for_distance_1,for_distance_2);
            double angle = GEOSystemConverter::calculateAngle(for_distance_1,for_distance_2);
            qDebug()<<angle;
            distance_pixel = sqrt(pow(pos_1_m.x()-pos_2_m.x(),2)+pow(pos_1_m.y()-pos_2_m.y(),2));

   //ui->action_2->setText("Задать точку 2 ("+QString::number(for_distance_2.X)+","+QString::number(for_distance_2.Y)+")");

            setTopLeftPosWithPos1AndPos2(); //установить координаты верхней левой точки изоражения(пока не учитывая угол наклона)

            if (pos_1->x()==pos_2->x()){//подсчет наклона прямой на карте(например, 2870к.3600к 2870к.3800к)
                double degree = -atan2((pos_2_m.y()-pos_1_m.y()),(pos_2_m.x()-pos_1_m.x()))*180/3.1415926535897932384626433832795;
                qDebug()<<"Degree = "<<degree;
            }
            secondPoint=true;
            set_2_dot=false;
        }
    }
    QGraphicsView::mousePressEvent(e);
}

void MapView::mouseReleaseEvent(QMouseEvent *e)
{
    currentDraggedItem = NULL;
    QGraphicsView::mouseReleaseEvent(e);
}

void MapView::rotateItem(float Angle)
{
    QList<QGraphicsItem*> items = scene()->selectedItems();
    foreach (QGraphicsItem *item, items) item->setRotation(item->rotation()+Angle);
}

void MapView::zoomItem(float zoom)
{
    //scale(zoom,zoom);
    QList<QGraphicsItem*> items = scene()->selectedItems();
    foreach (QGraphicsItem *item, items) item->setScale(item->scale()*zoom);
}

bool MapView::save_Image(const QString &fileName, const char *fileFormat)
{
    QRectF ItemsRect = scene()->itemsBoundingRect();

    QImage newImage(QSize(ItemsRect.width(),ItemsRect.height()),QImage::Format_RGB32);
    QPainter painter(&newImage);
    QRectF Rect;
    scene()->render(&painter,Rect,ItemsRect);
    painter.end();
    if (newImage.save(fileName,fileFormat,80))
    {
       return true;
    }
    else
        return false;
}

void MapView::setMode(MapMode mapmode)
{
    QList<QGraphicsItem*> items;
    switch (mapmode) {
    case MapReview:
        mode = MapReview;
        items = scene()->items();
        foreach (QGraphicsItem *item, items){
            item->setFlag(QGraphicsItem::ItemIsSelectable,false);
            item->setFlag(QGraphicsItem::ItemIsMovable,false);
        }
        break;
    case MapEdit:
        mode = MapEdit;
        items = scene()->items();
        foreach (QGraphicsItem *item, items){
            item->setFlag(QGraphicsItem::ItemIsSelectable);
            item->setFlag(QGraphicsItem::ItemIsMovable);
        }
        break;
    case MapRuler:
        mode = MapRuler;
        break;
    default:
        break;
    }
}


void MapView::setTopLeftPosWithPos1AndPos2(){
    if ((for_distance_1.X<0)||(for_distance_1.X==INFINITY)||(for_distance_1.Y<0)||(for_distance_1.Y==INFINITY)) return;
    if ((for_distance_2.X<0)||(for_distance_2.X==INFINITY)||(for_distance_2.Y<0)||(for_distance_2.Y==INFINITY)) return;

    qDebug()<<"Distance = "<<distance<<" meters"<<"pixels = "<<distance_pixel;
    qDebug()<<"TopLeft = "<<(int)(for_distance_1.X+(distance/distance_pixel)*pos_1_m.y())<<","<<(int)(for_distance_1.Y-(distance/distance_pixel)*pos_1_m.x());

    SquareSystem topleft_temp_sq;
    topleft_temp_sq.X=(int)(for_distance_1.X+(distance/distance_pixel)*pos_1_m.y());
    topleft_temp_sq.Y=(int)(for_distance_1.Y-(distance/distance_pixel)*pos_1_m.x());

    mapLeftTopPos_square.X=topleft_temp_sq.X;
    mapLeftTopPos_square.Y=topleft_temp_sq.Y;

    mapLeftTopPos = GEOSystemConverter::SQUARE_TO_SK42(topleft_temp_sq);


}

void MapView::deleteCurrentItem()
{
    QList<QGraphicsItem*> items = scene()->selectedItems();
    foreach (QGraphicsItem *item, items){
        scene()->removeItem(item);
    }
}

void MapView::saveMap()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Project"), "", tr("*.map"));
    if (fileName=="")return;
    if (!fileName.endsWith(".map"))fileName+=".map";
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    if(!file.isOpen())
    {
        return;
    }

    QDataStream stream(&file);
    QList<QGraphicsItem*> item=scene()->items();
    foreach(QGraphicsItem *i,item)
    {
        int counter=0;
        if(i->type()==QGraphicsPixmapItem::Type)
        {
            QGraphicsPixmapItem *pixmap=qgraphicsitem_cast<QGraphicsPixmapItem*>(i);
            quint32 x=i->type();
            stream<<counter;
            stream<<x;
            stream<<pixmap->pixmap();
            stream<<pixmap->x();
            stream<<pixmap->y();
            stream<<pixmap->rotation();
            stream<<pixmap->scale();
            stream<<pixmap->transform();
            stream<<pixmap->matrix();
            stream<<pixmap->zValue();
        }
    }
    stream<<999999;
    stream<<mapLeftTopPos_square.X;
    stream<<mapLeftTopPos_square.Y;
    stream<<distance;
    stream<<distance_pixel;
    stream<<firstPoint;
    stream<<secondPoint;
    file.flush();
    file.close();
}

void MapView::loadMap()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Project"), "", tr("Map Project (*.map)"));
    if (fileName=="") return;
    if (!fileName.endsWith(".map"))return;
    scene()->clear();
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);

    QDataStream stream(&file);
    int counter =0;
    quint32 type =0;
    stream>>counter;
    while (counter!=999999){
        stream>>type;
        if (type==QGraphicsPixmapItem::Type){
            QGraphicsPixmapItem *pixmap = new QGraphicsPixmapItem();
            QPixmap qpixmap;
            qreal x;
            qreal y;
            qreal rotation;
            qreal scale;
            QTransform tr;
            QMatrix matrix;
            qreal z;

            stream>>qpixmap;
            stream>>x;
            stream>>y;
            stream>>rotation;
            stream>>scale;
            stream>>tr;
            stream>>matrix;
            stream>>z;
            pixmap->setPixmap(qpixmap);
            pixmap->setX(x);
            pixmap->setY(y);
            pixmap->setRotation(rotation);
            pixmap->setScale(scale);
            pixmap->setTransform(tr);
            pixmap->setMatrix(matrix);
            pixmap->setZValue(z);
            if (mode==MapEdit){
                pixmap->setFlag(QGraphicsItem::ItemIsSelectable);
                pixmap->setFlag(QGraphicsItem::ItemIsMovable);
            }
            scene()->addItem(pixmap);
        }
        stream>>counter;
    }
    stream>>mapLeftTopPos_square.X;
    stream>>mapLeftTopPos_square.Y;
    stream>>distance;
    stream>>distance_pixel;
    stream>>firstPoint;
    stream>>secondPoint;
    file.close();
}

void MapView::setZCurrentItem(int z)
{
    QList<QGraphicsItem*> items = scene()->selectedItems();
    foreach (QGraphicsItem *item, items){
        item->setZValue(item->zValue()+z);
    }
}

MapView::MapMode MapView::getCurrentMode()
{
    return mode;
}

qreal MapView::getScaleFactor()
{
    return scale_factor;
}
