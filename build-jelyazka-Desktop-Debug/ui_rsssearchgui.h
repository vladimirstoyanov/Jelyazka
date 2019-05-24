/********************************************************************************
** Form generated from reading UI file 'rsssearchgui.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RSSSEARCHGUI_H
#define UI_RSSSEARCHGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RSSSearchGUI
{
public:
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QTableView *tableView;
    QPushButton *pushButton_2;
    QLabel *label;
    QPushButton *pushButton_3;

    void setupUi(QWidget *RSSSearchGUI)
    {
        if (RSSSearchGUI->objectName().isEmpty())
            RSSSearchGUI->setObjectName(QString::fromUtf8("RSSSearchGUI"));
        RSSSearchGUI->resize(400, 300);
        lineEdit = new QLineEdit(RSSSearchGUI);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(20, 30, 291, 21));
        pushButton = new QPushButton(RSSSearchGUI);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(320, 30, 75, 23));
        tableView = new QTableView(RSSSearchGUI);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(30, 70, 256, 192));
        pushButton_2 = new QPushButton(RSSSearchGUI);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(320, 80, 75, 23));
        label = new QLabel(RSSSearchGUI);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 280, 46, 13));
        pushButton_3 = new QPushButton(RSSSearchGUI);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(320, 120, 75, 23));

        retranslateUi(RSSSearchGUI);

        QMetaObject::connectSlotsByName(RSSSearchGUI);
    } // setupUi

    void retranslateUi(QWidget *RSSSearchGUI)
    {
        RSSSearchGUI->setWindowTitle(QApplication::translate("RSSSearchGUI", "Search RSS feed(s)", nullptr));
        pushButton->setText(QApplication::translate("RSSSearchGUI", "Search", nullptr));
        pushButton_2->setText(QApplication::translate("RSSSearchGUI", "Add RSS Feed(s)", nullptr));
        label->setText(QApplication::translate("RSSSearchGUI", "TextLabel", nullptr));
        pushButton_3->setText(QApplication::translate("RSSSearchGUI", "Remove", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RSSSearchGUI: public Ui_RSSSearchGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RSSSEARCHGUI_H
