/********************************************************************************
** Form generated from reading UI file 'myviewerwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYVIEWERWIDGET_H
#define UI_MYVIEWERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyViewerWidgetClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MyViewerWidgetClass)
    {
        if (MyViewerWidgetClass->objectName().isEmpty())
            MyViewerWidgetClass->setObjectName(QStringLiteral("MyViewerWidgetClass"));
        MyViewerWidgetClass->resize(600, 400);
        menuBar = new QMenuBar(MyViewerWidgetClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        MyViewerWidgetClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MyViewerWidgetClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MyViewerWidgetClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(MyViewerWidgetClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MyViewerWidgetClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MyViewerWidgetClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MyViewerWidgetClass->setStatusBar(statusBar);

        retranslateUi(MyViewerWidgetClass);

        QMetaObject::connectSlotsByName(MyViewerWidgetClass);
    } // setupUi

    void retranslateUi(QMainWindow *MyViewerWidgetClass)
    {
        MyViewerWidgetClass->setWindowTitle(QApplication::translate("MyViewerWidgetClass", "MyViewerWidget", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MyViewerWidgetClass: public Ui_MyViewerWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYVIEWERWIDGET_H
