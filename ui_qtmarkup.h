/********************************************************************************
** Form generated from reading UI file 'qtmarkup.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTMARKUP_H
#define UI_QTMARKUP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qtmarkup
{
public:
    QWidget *centralWidget;
    QPlainTextEdit *plainTextEdit;
    QTextEdit *textEdit;

    void setupUi(QMainWindow *qtmarkup)
    {
        if (qtmarkup->objectName().isEmpty())
            qtmarkup->setObjectName(QString::fromUtf8("qtmarkup"));
        qtmarkup->resize(800, 600);
        qtmarkup->setMinimumSize(QSize(800, 600));
        centralWidget = new QWidget(qtmarkup);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(10, 10, 311, 581));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(330, 10, 461, 581));
        qtmarkup->setCentralWidget(centralWidget);

        retranslateUi(qtmarkup);

        QMetaObject::connectSlotsByName(qtmarkup);
    } // setupUi

    void retranslateUi(QMainWindow *qtmarkup)
    {
        qtmarkup->setWindowTitle(QApplication::translate("qtmarkup", "qtmarkup", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class qtmarkup: public Ui_qtmarkup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTMARKUP_H
