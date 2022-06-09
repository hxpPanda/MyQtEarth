/********************************************************************************
** Form generated from reading UI file 'qearthwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QEARTHWIDGET_H
#define UI_QEARTHWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QEarthWidgetClass
{
public:

    void setupUi(QWidget *QEarthWidgetClass)
    {
        if (QEarthWidgetClass->objectName().isEmpty())
            QEarthWidgetClass->setObjectName(QStringLiteral("QEarthWidgetClass"));
        QEarthWidgetClass->resize(600, 400);

        retranslateUi(QEarthWidgetClass);

        QMetaObject::connectSlotsByName(QEarthWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *QEarthWidgetClass)
    {
        QEarthWidgetClass->setWindowTitle(QApplication::translate("QEarthWidgetClass", "QEarthWidget", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QEarthWidgetClass: public Ui_QEarthWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QEARTHWIDGET_H
