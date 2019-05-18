/********************************************************************************
** Form generated from reading UI file 'initwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INITWINDOW_H
#define UI_INITWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InitWindow
{
public:
    QLabel *label;

    void setupUi(QWidget *InitWindow)
    {
        if (InitWindow->objectName().isEmpty())
            InitWindow->setObjectName(QString::fromUtf8("InitWindow"));
        InitWindow->resize(400, 300);
        label = new QLabel(InitWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 240, 46, 13));

        retranslateUi(InitWindow);

        QMetaObject::connectSlotsByName(InitWindow);
    } // setupUi

    void retranslateUi(QWidget *InitWindow)
    {
        InitWindow->setWindowTitle(QApplication::translate("InitWindow", "Jelyazka", nullptr));
        label->setText(QApplication::translate("InitWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InitWindow: public Ui_InitWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INITWINDOW_H
