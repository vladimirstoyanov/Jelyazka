/********************************************************************************
** Form generated from reading UI file 'notificationwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTIFICATIONWINDOW_H
#define UI_NOTIFICATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NotificationWindow
{
public:
    QTextBrowser *textBrowser;

    void setupUi(QWidget *NotificationWindow)
    {
        if (NotificationWindow->objectName().isEmpty())
            NotificationWindow->setObjectName(QString::fromUtf8("NotificationWindow"));
        NotificationWindow->resize(400, 300);
        textBrowser = new QTextBrowser(NotificationWindow);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(60, 60, 256, 192));

        retranslateUi(NotificationWindow);

        QMetaObject::connectSlotsByName(NotificationWindow);
    } // setupUi

    void retranslateUi(QWidget *NotificationWindow)
    {
        NotificationWindow->setWindowTitle(QApplication::translate("NotificationWindow", "Jelyazka", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NotificationWindow: public Ui_NotificationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTIFICATIONWINDOW_H
