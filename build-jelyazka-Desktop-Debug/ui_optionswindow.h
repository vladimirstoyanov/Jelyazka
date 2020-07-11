/********************************************************************************
** Form generated from reading UI file 'optionswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONSWINDOW_H
#define UI_OPTIONSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OptionsWindow
{
public:
    QTreeWidget *treeWidget;
    QPushButton *removeFromFavoriteFeedsButton;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QWidget *OptionsWindow)
    {
        if (OptionsWindow->objectName().isEmpty())
            OptionsWindow->setObjectName(QString::fromUtf8("OptionsWindow"));
        OptionsWindow->resize(500, 300);
        OptionsWindow->setMinimumSize(QSize(500, 200));
        treeWidget = new QTreeWidget(OptionsWindow);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setGeometry(QRect(10, 20, 121, 261));
        removeFromFavoriteFeedsButton = new QPushButton(OptionsWindow);
        removeFromFavoriteFeedsButton->setObjectName(QString::fromUtf8("removeFromFavoriteFeedsButton"));
        removeFromFavoriteFeedsButton->setGeometry(QRect(170, 60, 75, 23));
        okButton = new QPushButton(OptionsWindow);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(300, 20, 75, 23));
        cancelButton = new QPushButton(OptionsWindow);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(300, 50, 75, 23));

        retranslateUi(OptionsWindow);

        QMetaObject::connectSlotsByName(OptionsWindow);
    } // setupUi

    void retranslateUi(QWidget *OptionsWindow)
    {
        OptionsWindow->setWindowTitle(QCoreApplication::translate("OptionsWindow", "Jelyazka Options", nullptr));
        removeFromFavoriteFeedsButton->setText(QCoreApplication::translate("OptionsWindow", "Remove", nullptr));
        okButton->setText(QCoreApplication::translate("OptionsWindow", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("OptionsWindow", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OptionsWindow: public Ui_OptionsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONSWINDOW_H
