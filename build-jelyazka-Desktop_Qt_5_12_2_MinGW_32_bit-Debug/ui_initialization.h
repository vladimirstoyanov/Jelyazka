/********************************************************************************
** Form generated from reading UI file 'initialization.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INITIALIZATION_H
#define UI_INITIALIZATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Initialization
{
public:
    QWidget *centralWidget;

    void setupUi(QMainWindow *Initialization)
    {
        if (Initialization->objectName().isEmpty())
            Initialization->setObjectName(QString::fromUtf8("Initialization"));
        Initialization->resize(300, 300);
        centralWidget = new QWidget(Initialization);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Initialization->setCentralWidget(centralWidget);

        retranslateUi(Initialization);

        QMetaObject::connectSlotsByName(Initialization);
    } // setupUi

    void retranslateUi(QMainWindow *Initialization)
    {
        Initialization->setWindowTitle(QApplication::translate("Initialization", "Initialization", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Initialization: public Ui_Initialization {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INITIALIZATION_H
