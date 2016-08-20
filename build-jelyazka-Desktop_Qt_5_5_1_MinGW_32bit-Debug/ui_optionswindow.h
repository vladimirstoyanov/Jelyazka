/********************************************************************************
** Form generated from reading UI file 'optionswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONSWINDOW_H
#define UI_OPTIONSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OptionsWindow
{
public:
    QTreeWidget *treeWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *OK_Button;
    QPushButton *Cancel_Button;

    void setupUi(QWidget *OptionsWindow)
    {
        if (OptionsWindow->objectName().isEmpty())
            OptionsWindow->setObjectName(QStringLiteral("OptionsWindow"));
        OptionsWindow->resize(500, 300);
        OptionsWindow->setMinimumSize(QSize(500, 200));
        treeWidget = new QTreeWidget(OptionsWindow);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setGeometry(QRect(10, 20, 121, 261));
        pushButton = new QPushButton(OptionsWindow);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(170, 20, 75, 23));
        pushButton_2 = new QPushButton(OptionsWindow);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(170, 60, 75, 23));
        pushButton_3 = new QPushButton(OptionsWindow);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(170, 90, 75, 23));
        OK_Button = new QPushButton(OptionsWindow);
        OK_Button->setObjectName(QStringLiteral("OK_Button"));
        OK_Button->setGeometry(QRect(300, 20, 75, 23));
        Cancel_Button = new QPushButton(OptionsWindow);
        Cancel_Button->setObjectName(QStringLiteral("Cancel_Button"));
        Cancel_Button->setGeometry(QRect(300, 50, 75, 23));

        retranslateUi(OptionsWindow);

        QMetaObject::connectSlotsByName(OptionsWindow);
    } // setupUi

    void retranslateUi(QWidget *OptionsWindow)
    {
        OptionsWindow->setWindowTitle(QApplication::translate("OptionsWindow", "Jelyazka Options", 0));
        pushButton->setText(QApplication::translate("OptionsWindow", "PushButton", 0));
        pushButton_2->setText(QApplication::translate("OptionsWindow", "PushButton", 0));
        pushButton_3->setText(QApplication::translate("OptionsWindow", "PushButton", 0));
        OK_Button->setText(QApplication::translate("OptionsWindow", "OK", 0));
        Cancel_Button->setText(QApplication::translate("OptionsWindow", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class OptionsWindow: public Ui_OptionsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONSWINDOW_H
