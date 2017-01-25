#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QFileDialog"
#include "QGraphicsPixmapItem"
#include "QDesktopServices"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->toolBar->addAction(QPixmap("images/view.png"), "Режим просмотра", this, SLOT(on_review_pressed()));
    ui->toolBar->addAction(QPixmap("images/edit.png"), "Режим редактирования", this, SLOT(on_editing_pressed()));
    //ui->toolBar->addAction(QPixmap("images/line.png"), "Линейка", this, SLOT(on_ruler_pressed()));
    ui->toolBar->actions().at(0)->setCheckable(true);
    ui->toolBar->actions().at(1)->setCheckable(true);
    //ui->toolBar->actions().at(2)->setCheckable(true);
    ui->toolBar->actions().at(0)->setChecked(true);
    Lat = new QLabel(this);
    Lon = new QLabel(this);
    posX = new QLabel(this);
    posY = new QLabel(this);
    statusBar()->addWidget(Lat);
    statusBar()->addWidget(Lon);
    statusBar()->addWidget(posX);
    statusBar()->addWidget(posY);

    ui->actionDegrees->setChecked(true);
    ui->graphicsView->show_geo=true;
    ui->actionMetres->setChecked(false);
    ui->graphicsView->show_square=false;
    connect(ui->graphicsView, SIGNAL(Coordinates(QString,QString,QString,QString)), this, SLOT(updateStatusBar(QString,QString,QString,QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateStatusBar(QString lat, QString lon, QString squareX, QString squareY)
{
    Lat->setText(lat);
    Lon->setText(lon);
    posX->setText(squareX);
    posY->setText(squareY);
}

void MainWindow::on_editing_pressed()
{
    ui->graphicsView->setMode(MapView::MapEdit);
    ui->toolBar->actions().at(1)->setChecked(true);
    ui->toolBar->actions().at(0)->setChecked(false);
    //ui->toolBar->actions().at(2)->setChecked(false);
}

void MainWindow::on_ruler_pressed()
{
    ui->graphicsView->setMode(MapView::MapRuler);
    ui->toolBar->actions().at(2)->setChecked(true);
    ui->toolBar->actions().at(1)->setChecked(false);
    //ui->toolBar->actions().at(0)->setChecked(false);
}

void MainWindow::on_review_pressed()
{
    ui->graphicsView->setMode(MapView::MapReview);
    ui->toolBar->actions().at(0)->setChecked(true);
    ui->toolBar->actions().at(1)->setChecked(false);
    //ui->toolBar->actions().at(2)->setChecked(false);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Система автоматического создания карт v0.1 (opensource)\nОснован на Qt 3.3.1\nСобран June 07 2016 в 11:00:00\n\n© 2016 Права не защищены.\nГрущак Я.Ю.");
    msgBox.exec();
}

void MainWindow::on_actionOpen_triggered()
{
    ui->graphicsView->loadMap();
}

void MainWindow::on_actionLeft_triggered()
{
    ui->graphicsView->rotateItem(0-ui->doubleSpinBox->value());
}

void MainWindow::on_actionRight_triggered()
{
    ui->graphicsView->rotateItem(ui->doubleSpinBox->value());
}

void MainWindow::on_actionZoom_in_triggered()
{
    ui->graphicsView->zoomItem(ui->doubleSpinBox_2->value()/100);
}


void MainWindow::on_actionVertical_triggered()
{
QRectF rect = ui->graphicsView->scene()->itemsBoundingRect();
ui->graphicsView->fitInView(rect, Qt::KeepAspectRatio);
}

void MainWindow::on_actionHorizontal_triggered()
{
QRectF rect = ui->graphicsView->scene()->itemsBoundingRect();
ui->graphicsView->fitInView(0,0,rect.width(), (ui->graphicsView->height()*rect.width())/ui->graphicsView->width(), Qt::KeepAspectRatio);
}

void MainWindow::on_actionZoom_out_triggered()
{
    ui->graphicsView->zoomItem(1.00/(ui->doubleSpinBox_2->value()/100));
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("*.png *.jpg"));
    if (fileName!="") ui->graphicsView->save_Image(fileName, 0);
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionMetres_triggered()
{
    ui->actionMetres->setChecked(true);
    ui->actionDegrees->setChecked(false);
    ui->graphicsView->show_geo=false;
    ui->graphicsView->show_square=true;
}

void MainWindow::on_actionDegrees_triggered()
{
    ui->actionDegrees->setChecked(true);
    ui->actionMetres->setChecked(false);
    ui->graphicsView->show_geo=true;
    ui->graphicsView->show_square=false;
}

void MainWindow::on_actionCreate_triggered()
{
    int rows=0;int st_row=INT_MAX, fn_row=0;
    int cols=0;int st_col=INT_MAX, fn_col=0;
QSize loaded_size;
QFileDialog dialog(this);
dialog.setFileMode(QFileDialog::ExistingFiles);
dialog.setNameFilter(tr("Images (*.png *.bmp *.jpg)"));
QStringList fileNames;

if (dialog.exec())  fileNames = dialog.selectedFiles(); else return;
   // map_reset(); //Сброс изменений карты(поворот, масштаб, графика)

QString image_name;
QGraphicsPixmapItem *map_temp;

//analysing images count and start point
    foreach (image_name, fileNames){
        map_temp = new QGraphicsPixmapItem(QPixmap(image_name));
            QRegExp re("(\\d+)_(\\d+).");
            if (re.indexIn(image_name) != -1) {
                if (re.cap(2).toInt()>fn_col) fn_col=re.cap(2).toInt();if (re.cap(2).toInt()<st_col) st_col=re.cap(2).toInt();
                if (re.cap(1).toInt()>fn_row) fn_row=re.cap(1).toInt();if (re.cap(1).toInt()<st_row) st_row=re.cap(1).toInt();
            } else {

            }
     }
    if ((st_row!=INT_MAX)&&(st_row!=INT_MAX)){
        rows = fn_row-st_row+1;
        cols = fn_col-st_col+1;
    }
//*analysing images

//Добавление частей изображения в зависимости от столбца и строки в имени row_col.jpg изображения д.б. одинаковые по размерам
foreach (image_name, fileNames){ //loading images on Map_scene
    map_temp = new QGraphicsPixmapItem(QPixmap(image_name));
        QRegExp re("(\\d+)_(\\d+).");   // D:\\Images\[(re.cap(1)]_[(re.cap(2)].jpg
        if (re.indexIn(image_name) != -1) {
            map_temp->setX((re.cap(2).toInt()-st_col)*map_temp->boundingRect().width());
            map_temp->setY((re.cap(1).toInt()-st_row)*map_temp->boundingRect().height());
            ui->graphicsView->scene()->addItem(map_temp);
        } else {
           // qDebug() << "String not matched.";
        }
 }
//*Добавление частей изображения в зависимости от столбца и строки в имени row_col.jpg

 map_temp = new QGraphicsPixmapItem(QPixmap(fileNames.at(0)));  //get size of a single map's part
 loaded_size.setWidth(cols*map_temp->boundingRect().width());   loaded_size.setHeight(rows*map_temp->boundingRect().height()); //set size of loaded map
 //ui->graphicsView->scene()->setSceneRect(QRectF(0,0,loaded_size.width(),loaded_size.height())); //set map scene size as loaded image

}

void MainWindow::on_actionPoint1_triggered()
{
    if (!ui->graphicsView->set_1_dot){
        ui->graphicsView->set_1_dot=true;
        ui->graphicsView->set_2_dot=false;
        ui->actionPoint1->setText("Задать точку 1 <--");
        ui->actionPoint2->setText("Задать точку 2 ("+QString::number(ui->graphicsView->for_distance_2.X)+","+QString::number(ui->graphicsView->for_distance_2.Y)+")");
    } else {
        ui->graphicsView->set_1_dot=false;
        ui->actionPoint1->setText("Задать точку 1");
        ui->actionPoint2->setText("Задать точку 2");
    }
}

void MainWindow::on_actionPoint2_triggered()
{
    if (!ui->graphicsView->set_2_dot){
        ui->graphicsView->set_2_dot=true;
        ui->graphicsView->set_1_dot=false;
        //ui->actionPoint1->setText("Задать точку 1 ("+QString::number(ui->graphicsView->for_distance_1.X)+","+QString::number(ui->graphicsView->for_distance_1.Y)+")");
        //ui->actionPoint2->setText("Задать точку 2 <--");
    } else {
        ui->graphicsView->set_2_dot=false;
        //ui->actionPoint1->setText("Задать точку 1");
        //ui->actionPoint2->setText("Задать точку 2");
    }
}

void MainWindow::on_actionClose_triggered()
{
    ui->graphicsView->deleteCurrentItem();
}

void MainWindow::on_actionCloseAll_triggered()
{
    ui->graphicsView->scene()->clear();
    ui->graphicsView->firstPoint=false;
    ui->graphicsView->secondPoint=false;
}

void MainWindow::on_actionSaveProj_triggered()
{
        ui->graphicsView->saveMap();
}

void MainWindow::on_actionAddImg_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if (fileName=="") return;
    QGraphicsPixmapItem *map_temp;
    map_temp = new QGraphicsPixmapItem(QPixmap(fileName));
    map_temp->setX(0);
    map_temp->setY(0);
    if (ui->graphicsView->getCurrentMode()==MapView::MapEdit){
        map_temp->setFlag(QGraphicsItem::ItemIsSelectable);
        map_temp->setFlag(QGraphicsItem::ItemIsMovable);
    }
    ui->graphicsView->scene()->addItem(map_temp);
}

void MainWindow::on_actionZTop_triggered()
{
    ui->graphicsView->setZCurrentItem(1);
}

void MainWindow::on_actionZBottom_triggered()
{
    ui->graphicsView->setZCurrentItem(-1);
}

void MainWindow::on_actionHelp_triggered()
{
    QDesktopServices desk;

    desk.openUrl(QUrl("help.chm"));
}
