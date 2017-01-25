/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <mapview.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionClose;
    QAction *actionOpen;
    QAction *actionCreate;
    QAction *actionSave;
    QAction *actionExit;
    QAction *actionZoom_in;
    QAction *actionZoom_out;
    QAction *actionLeft;
    QAction *actionRight;
    QAction *actionDegrees;
    QAction *actionMetres;
    QAction *actionHelp;
    QAction *actionAbout;
    QAction *actionHorizontal;
    QAction *actionVertical;
    QAction *actionPoint1;
    QAction *actionPoint2;
    QAction *actionCloseAll;
    QAction *actionSaveProj;
    QAction *actionAddImg;
    QAction *actionZTop;
    QAction *actionZBottom;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelAngle;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *labelZoom;
    QDoubleSpinBox *doubleSpinBox_2;
    QSpacerItem *horizontalSpacer;
    MapView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_6;
    QMenu *menu_4;
    QMenu *menu_5;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(608, 427);
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionCreate = new QAction(MainWindow);
        actionCreate->setObjectName(QStringLiteral("actionCreate"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionZoom_in = new QAction(MainWindow);
        actionZoom_in->setObjectName(QStringLiteral("actionZoom_in"));
        actionZoom_out = new QAction(MainWindow);
        actionZoom_out->setObjectName(QStringLiteral("actionZoom_out"));
        actionLeft = new QAction(MainWindow);
        actionLeft->setObjectName(QStringLiteral("actionLeft"));
        actionRight = new QAction(MainWindow);
        actionRight->setObjectName(QStringLiteral("actionRight"));
        actionDegrees = new QAction(MainWindow);
        actionDegrees->setObjectName(QStringLiteral("actionDegrees"));
        actionDegrees->setCheckable(true);
        actionMetres = new QAction(MainWindow);
        actionMetres->setObjectName(QStringLiteral("actionMetres"));
        actionMetres->setCheckable(true);
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionHorizontal = new QAction(MainWindow);
        actionHorizontal->setObjectName(QStringLiteral("actionHorizontal"));
        actionVertical = new QAction(MainWindow);
        actionVertical->setObjectName(QStringLiteral("actionVertical"));
        actionPoint1 = new QAction(MainWindow);
        actionPoint1->setObjectName(QStringLiteral("actionPoint1"));
        actionPoint2 = new QAction(MainWindow);
        actionPoint2->setObjectName(QStringLiteral("actionPoint2"));
        actionCloseAll = new QAction(MainWindow);
        actionCloseAll->setObjectName(QStringLiteral("actionCloseAll"));
        actionSaveProj = new QAction(MainWindow);
        actionSaveProj->setObjectName(QStringLiteral("actionSaveProj"));
        actionAddImg = new QAction(MainWindow);
        actionAddImg->setObjectName(QStringLiteral("actionAddImg"));
        actionZTop = new QAction(MainWindow);
        actionZTop->setObjectName(QStringLiteral("actionZTop"));
        actionZBottom = new QAction(MainWindow);
        actionZBottom->setObjectName(QStringLiteral("actionZBottom"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(5, 5, 5, 5);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(3);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelAngle = new QLabel(centralWidget);
        labelAngle->setObjectName(QStringLiteral("labelAngle"));

        horizontalLayout->addWidget(labelAngle);

        doubleSpinBox = new QDoubleSpinBox(centralWidget);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setDecimals(1);
        doubleSpinBox->setMinimum(0);
        doubleSpinBox->setMaximum(180);
        doubleSpinBox->setValue(1);

        horizontalLayout->addWidget(doubleSpinBox);

        labelZoom = new QLabel(centralWidget);
        labelZoom->setObjectName(QStringLiteral("labelZoom"));

        horizontalLayout->addWidget(labelZoom);

        doubleSpinBox_2 = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_2->setObjectName(QStringLiteral("doubleSpinBox_2"));
        doubleSpinBox_2->setMinimum(100);
        doubleSpinBox_2->setMaximum(200);
        doubleSpinBox_2->setValue(101);

        horizontalLayout->addWidget(doubleSpinBox_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 1, 0, 1, 1);

        graphicsView = new MapView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
        graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        graphicsView->setResizeAnchor(QGraphicsView::AnchorUnderMouse);

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 608, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_3 = new QMenu(menu_2);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        menu_6 = new QMenu(menu_2);
        menu_6->setObjectName(QStringLiteral("menu_6"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QStringLiteral("menu_4"));
        menu_5 = new QMenu(menuBar);
        menu_5->setObjectName(QStringLiteral("menu_5"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setSizeGripEnabled(true);
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menuBar->addAction(menu_5->menuAction());
        menu->addAction(actionOpen);
        menu->addAction(actionCreate);
        menu->addAction(actionAddImg);
        menu->addAction(actionSaveProj);
        menu->addAction(actionSave);
        menu->addSeparator();
        menu->addAction(actionCloseAll);
        menu->addSeparator();
        menu->addAction(actionExit);
        menu_2->addAction(actionZoom_in);
        menu_2->addAction(actionZoom_out);
        menu_2->addSeparator();
        menu_2->addAction(menu_3->menuAction());
        menu_2->addAction(menu_6->menuAction());
        menu_3->addAction(actionLeft);
        menu_3->addAction(actionRight);
        menu_6->addAction(actionHorizontal);
        menu_6->addAction(actionVertical);
        menu_4->addAction(actionClose);
        menu_4->addSeparator();
        menu_4->addAction(actionDegrees);
        menu_4->addAction(actionMetres);
        menu_4->addSeparator();
        menu_4->addAction(actionPoint1);
        menu_4->addAction(actionPoint2);
        menu_4->addSeparator();
        menu_4->addAction(actionZTop);
        menu_4->addAction(actionZBottom);
        menu_5->addAction(actionHelp);
        menu_5->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\320\265\320\273\321\214 \320\272\320\260\321\200\321\202 v0.1", 0));
        actionClose->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\262\321\213\320\264\320\265\320\273\320\265\320\275\320\275\321\213\320\271 \321\215\320\273\320\265\320\274\320\265\320\275\321\202", 0));
#ifndef QT_NO_TOOLTIP
        actionClose->setToolTip(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\262\321\213\320\264\320\265\320\273\320\265\320\275\320\275\321\213\320\271 \321\215\320\273\320\265\320\274\320\265\320\275\321\202", 0));
#endif // QT_NO_TOOLTIP
        actionClose->setShortcut(QApplication::translate("MainWindow", "Del", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \320\277\321\200\320\276\320\265\320\272\321\202", 0));
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Shift+O", 0));
        actionCreate->setText(QApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", 0));
        actionSave->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\320\272 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", 0));
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", 0));
        actionExit->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", 0));
        actionExit->setShortcut(QApplication::translate("MainWindow", "Alt+C", 0));
        actionZoom_in->setText(QApplication::translate("MainWindow", "\320\243\320\262\320\265\320\273\320\270\321\207\320\270\321\202\321\214 \321\215\320\273\320\265\320\274\320\265\320\275\321\202", 0));
#ifndef QT_NO_TOOLTIP
        actionZoom_in->setToolTip(QApplication::translate("MainWindow", "\320\243\320\262\320\265\320\273\320\270\321\207\320\270\321\202\321\214 \321\215\320\273\320\265\320\274\320\265\320\275\321\202", 0));
#endif // QT_NO_TOOLTIP
        actionZoom_in->setShortcut(QApplication::translate("MainWindow", "+", 0));
        actionZoom_out->setText(QApplication::translate("MainWindow", "\320\243\320\274\320\265\320\275\321\214\321\210\320\270\321\202\321\214 \321\215\320\273\320\265\320\274\320\265\320\275\321\202", 0));
#ifndef QT_NO_TOOLTIP
        actionZoom_out->setToolTip(QApplication::translate("MainWindow", "\320\243\320\274\320\265\320\275\321\214\321\210\320\270\321\202\321\214 \321\215\320\273\320\265\320\274\320\265\320\275\321\202", 0));
#endif // QT_NO_TOOLTIP
        actionZoom_out->setShortcut(QApplication::translate("MainWindow", "-", 0));
        actionLeft->setText(QApplication::translate("MainWindow", "\320\222\320\273\320\265\320\262\320\276", 0));
        actionLeft->setShortcut(QApplication::translate("MainWindow", "Shift+E", 0));
        actionRight->setText(QApplication::translate("MainWindow", "\320\222\320\277\321\200\320\260\320\262\320\276", 0));
        actionRight->setShortcut(QApplication::translate("MainWindow", "Shift+R", 0));
        actionDegrees->setText(QApplication::translate("MainWindow", "\320\223\321\200\320\260\320\264\321\203\321\201\321\213", 0));
        actionMetres->setText(QApplication::translate("MainWindow", "\320\234\320\265\321\202\321\200\321\213", 0));
        actionHelp->setText(QApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", 0));
        actionHelp->setShortcut(QApplication::translate("MainWindow", "F1", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", 0));
        actionAbout->setShortcut(QApplication::translate("MainWindow", "F2", 0));
        actionHorizontal->setText(QApplication::translate("MainWindow", "\320\250\320\270\321\200\320\270\320\275\320\265", 0));
        actionVertical->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\201\320\276\321\202\320\265", 0));
        actionPoint1->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\321\202\321\214 \321\202\320\276\321\207\320\272\321\203 1", 0));
        actionPoint2->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\321\202\321\214 \321\202\320\276\321\207\320\272\321\203 2", 0));
        actionCloseAll->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214 \320\262\321\201\320\265", 0));
        actionSaveProj->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\277\321\200\320\276\320\265\320\272\321\202", 0));
        actionSaveProj->setShortcut(QApplication::translate("MainWindow", "Shift+S", 0));
        actionAddImg->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", 0));
        actionAddImg->setShortcut(QApplication::translate("MainWindow", "O", 0));
        actionZTop->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\264\320\275\321\217\321\202\321\214 \320\275\320\260 \320\277\320\265\321\200\320\265\320\264\320\275\320\270\320\271 \320\277\320\273\320\260\320\275", 0));
        actionZTop->setShortcut(QApplication::translate("MainWindow", "W", 0));
        actionZBottom->setText(QApplication::translate("MainWindow", "\320\236\320\277\321\203\321\201\321\202\320\270\321\202\321\214 \320\275\320\260 \320\267\320\260\320\264\320\275\320\270\320\271 \320\277\320\273\320\260\320\275", 0));
        actionZBottom->setShortcut(QApplication::translate("MainWindow", "Q", 0));
        labelAngle->setText(QApplication::translate("MainWindow", "\320\243\320\263\320\276\320\273 \320\277\320\276\320\262\320\276\321\200\320\276\321\202\320\260:", 0));
        doubleSpinBox->setPrefix(QString());
        labelZoom->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\265\321\204\320\270\321\206\320\270\320\265\320\275\321\202 \320\274\320\260\321\201\321\210\321\202\320\260\320\261\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217, %:", 0));
        menu->setTitle(QApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", 0));
        menu_2->setTitle(QApplication::translate("MainWindow", "\320\222\320\270\320\264", 0));
        menu_3->setTitle(QApplication::translate("MainWindow", "\320\237\320\276\320\262\320\276\321\200\320\276\321\202...", 0));
        menu_6->setTitle(QApplication::translate("MainWindow", "\320\222\321\213\321\200\320\276\320\262\320\275\321\217\321\202\321\214 \320\277\320\276...", 0));
        menu_4->setTitle(QApplication::translate("MainWindow", "\320\244\320\276\321\200\320\274\320\260\321\202", 0));
        menu_5->setTitle(QApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "\320\237\320\260\320\275\320\265\320\273\321\214 \320\270\320\275\321\201\321\202\321\200\321\203\320\274\320\265\320\275\321\202\320\276\320\262", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
