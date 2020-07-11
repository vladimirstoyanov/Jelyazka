/********************************************************************************
** Form generated from reading UI file 'rsssearchgui.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
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
    QPushButton *searchButton;
    QTableView *tableView;
    QPushButton *addRssFeeds;
    QLabel *label;
    QPushButton *removeButton;

    void setupUi(QWidget *RSSSearchGUI)
    {
        if (RSSSearchGUI->objectName().isEmpty())
            RSSSearchGUI->setObjectName(QString::fromUtf8("RSSSearchGUI"));
        RSSSearchGUI->resize(400, 300);
        lineEdit = new QLineEdit(RSSSearchGUI);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(20, 30, 291, 21));
        searchButton = new QPushButton(RSSSearchGUI);
        searchButton->setObjectName(QString::fromUtf8("searchButton"));
        searchButton->setGeometry(QRect(320, 30, 75, 23));
        tableView = new QTableView(RSSSearchGUI);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(30, 70, 256, 192));
        addRssFeeds = new QPushButton(RSSSearchGUI);
        addRssFeeds->setObjectName(QString::fromUtf8("addRssFeeds"));
        addRssFeeds->setGeometry(QRect(320, 80, 75, 23));
        label = new QLabel(RSSSearchGUI);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 280, 46, 13));
        removeButton = new QPushButton(RSSSearchGUI);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        removeButton->setGeometry(QRect(320, 120, 75, 23));

        retranslateUi(RSSSearchGUI);

        QMetaObject::connectSlotsByName(RSSSearchGUI);
    } // setupUi

    void retranslateUi(QWidget *RSSSearchGUI)
    {
        RSSSearchGUI->setWindowTitle(QCoreApplication::translate("RSSSearchGUI", "Search RSS feed(s)", nullptr));
        searchButton->setText(QCoreApplication::translate("RSSSearchGUI", "Search", nullptr));
        addRssFeeds->setText(QCoreApplication::translate("RSSSearchGUI", "Add RSS Feed(s)", nullptr));
        label->setText(QCoreApplication::translate("RSSSearchGUI", "TextLabel", nullptr));
        removeButton->setText(QCoreApplication::translate("RSSSearchGUI", "Remove", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RSSSearchGUI: public Ui_RSSSearchGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RSSSEARCHGUI_H
