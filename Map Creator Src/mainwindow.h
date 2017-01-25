#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void updateStatusBar(QString lat, QString lon, QString squareX, QString squareY);
    void on_editing_pressed();
    void on_ruler_pressed();
    void on_review_pressed();

    void on_actionAbout_triggered();

    void on_actionOpen_triggered();

    void on_actionHorizontal_triggered();

    void on_actionLeft_triggered();

    void on_actionRight_triggered();

    void on_actionZoom_in_triggered();

    void on_actionZoom_out_triggered();

    void on_actionSave_triggered();

    void on_actionExit_triggered();

    void on_actionMetres_triggered();

    void on_actionDegrees_triggered();

    void on_actionCreate_triggered();

    void on_actionPoint1_triggered();

    void on_actionPoint2_triggered();

    void on_actionClose_triggered();

    void on_actionCloseAll_triggered();

    void on_actionSaveProj_triggered();

    void on_actionAddImg_triggered();

    void on_actionZTop_triggered();

    void on_actionZBottom_triggered();

    void on_actionHelp_triggered();

    void on_actionVertical_triggered();

private:
    Ui::MainWindow *ui;
    QLabel* Lat;
    QLabel* Lon;
    QLabel* posX;
    QLabel* posY;
};

#endif // MAINWINDOW_H
