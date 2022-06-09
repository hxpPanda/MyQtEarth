/********************************************************************************
** Form generated from reading UI file 'digitalearth.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIGITALEARTH_H
#define UI_DIGITALEARTH_H

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

class Ui_DigitalEarthClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DigitalEarthClass)
    {
        if (DigitalEarthClass->objectName().isEmpty())
            DigitalEarthClass->setObjectName(QStringLiteral("DigitalEarthClass"));
        DigitalEarthClass->resize(600, 400);
        menuBar = new QMenuBar(DigitalEarthClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        DigitalEarthClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DigitalEarthClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        DigitalEarthClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(DigitalEarthClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        DigitalEarthClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(DigitalEarthClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DigitalEarthClass->setStatusBar(statusBar);

        retranslateUi(DigitalEarthClass);

        QMetaObject::connectSlotsByName(DigitalEarthClass);
    } // setupUi

    void retranslateUi(QMainWindow *DigitalEarthClass)
    {
        DigitalEarthClass->setWindowTitle(QApplication::translate("DigitalEarthClass", "DigitalEarth", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DigitalEarthClass: public Ui_DigitalEarthClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIGITALEARTH_H
