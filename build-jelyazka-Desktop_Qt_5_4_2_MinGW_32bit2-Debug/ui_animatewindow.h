/********************************************************************************
** Form generated from reading UI file 'animatewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANIMATEWINDOW_H
#define UI_ANIMATEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CAnimateWindow
{
public:
    QTextBrowser *textBrowser;

    void setupUi(QWidget *CAnimateWindow)
    {
        if (CAnimateWindow->objectName().isEmpty())
            CAnimateWindow->setObjectName(QStringLiteral("CAnimateWindow"));
        CAnimateWindow->resize(400, 300);
        textBrowser = new QTextBrowser(CAnimateWindow);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(60, 60, 256, 192));

        retranslateUi(CAnimateWindow);

        QMetaObject::connectSlotsByName(CAnimateWindow);
    } // setupUi

    void retranslateUi(QWidget *CAnimateWindow)
    {
        CAnimateWindow->setWindowTitle(QApplication::translate("CAnimateWindow", "Jelyazka", 0));
    } // retranslateUi

};

namespace Ui {
    class CAnimateWindow: public Ui_CAnimateWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANIMATEWINDOW_H
