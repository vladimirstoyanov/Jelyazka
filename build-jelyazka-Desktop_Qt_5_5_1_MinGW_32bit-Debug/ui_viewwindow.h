/********************************************************************************
** Form generated from reading UI file 'viewwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWWINDOW_H
#define UI_VIEWWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ViewWindow
{
public:
    QComboBox *comboBox;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *ViewWindow)
    {
        if (ViewWindow->objectName().isEmpty())
            ViewWindow->setObjectName(QStringLiteral("ViewWindow"));
        ViewWindow->resize(489, 400);
        ViewWindow->setMinimumSize(QSize(480, 400));
        ViewWindow->setMouseTracking(true);
        comboBox = new QComboBox(ViewWindow);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(165, 65, 321, 30));
        pushButton = new QPushButton(ViewWindow);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(5, 65, 75, 30));
        pushButton_2 = new QPushButton(ViewWindow);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(85, 65, 75, 30));
        textBrowser = new QTextBrowser(ViewWindow);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(5, 100, 481, 295));

        retranslateUi(ViewWindow);

        QMetaObject::connectSlotsByName(ViewWindow);
    } // setupUi

    void retranslateUi(QWidget *ViewWindow)
    {
        ViewWindow->setWindowTitle(QApplication::translate("ViewWindow", "Jelyazka", 0));
        pushButton->setText(QApplication::translate("ViewWindow", "<", 0));
        pushButton_2->setText(QApplication::translate("ViewWindow", ">", 0));
    } // retranslateUi

};

namespace Ui {
    class ViewWindow: public Ui_ViewWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWWINDOW_H
