/********************************************************************************
** Form generated from reading UI file 'web_search_interface.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEB_SEARCH_INTERFACE_H
#define UI_WEB_SEARCH_INTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WebSearchInterface
{
public:
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QTableView *tableView;
    QPushButton *pushButton_2;
    QLabel *label;
    QPushButton *pushButton_3;

    void setupUi(QWidget *WebSearchInterface)
    {
        if (WebSearchInterface->objectName().isEmpty())
            WebSearchInterface->setObjectName(QStringLiteral("WebSearchInterface"));
        WebSearchInterface->resize(400, 300);
        lineEdit = new QLineEdit(WebSearchInterface);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(20, 30, 291, 21));
        pushButton = new QPushButton(WebSearchInterface);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(320, 30, 75, 23));
        tableView = new QTableView(WebSearchInterface);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(30, 70, 256, 192));
        pushButton_2 = new QPushButton(WebSearchInterface);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(320, 80, 75, 23));
        label = new QLabel(WebSearchInterface);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 280, 46, 13));
        pushButton_3 = new QPushButton(WebSearchInterface);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(320, 120, 75, 23));

        retranslateUi(WebSearchInterface);

        QMetaObject::connectSlotsByName(WebSearchInterface);
    } // setupUi

    void retranslateUi(QWidget *WebSearchInterface)
    {
        WebSearchInterface->setWindowTitle(QApplication::translate("WebSearchInterface", "Search RSS feed(s)", 0));
        pushButton->setText(QApplication::translate("WebSearchInterface", "Search", 0));
        pushButton_2->setText(QApplication::translate("WebSearchInterface", "Add RSS Feed(s)", 0));
        label->setText(QApplication::translate("WebSearchInterface", "TextLabel", 0));
        pushButton_3->setText(QApplication::translate("WebSearchInterface", "Remove", 0));
    } // retranslateUi

};

namespace Ui {
    class WebSearchInterface: public Ui_WebSearchInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEB_SEARCH_INTERFACE_H
