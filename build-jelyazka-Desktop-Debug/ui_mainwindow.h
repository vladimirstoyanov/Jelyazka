/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QComboBox *titleComboBox;
    QPushButton *previousButton;
    QPushButton *nextButton;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(489, 400);
        MainWindow->setMinimumSize(QSize(480, 400));
        MainWindow->setMouseTracking(true);
        titleComboBox = new QComboBox(MainWindow);
        titleComboBox->setObjectName(QString::fromUtf8("titleComboBox"));
        titleComboBox->setGeometry(QRect(165, 65, 321, 30));
        previousButton = new QPushButton(MainWindow);
        previousButton->setObjectName(QString::fromUtf8("previousButton"));
        previousButton->setGeometry(QRect(5, 65, 75, 30));
        nextButton = new QPushButton(MainWindow);
        nextButton->setObjectName(QString::fromUtf8("nextButton"));
        nextButton->setGeometry(QRect(85, 65, 75, 30));
        textBrowser = new QTextBrowser(MainWindow);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(5, 100, 481, 295));

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Jelyazka", nullptr));
        previousButton->setText(QCoreApplication::translate("MainWindow", "<", nullptr));
        nextButton->setText(QCoreApplication::translate("MainWindow", ">", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
