/*
File: qtmarkup.h
Name: Danny Dutton
Class: ECE3574
Project: 1
Description: This is the header file for qtmarkup. It contains the class
             definition for qtmarkup.
*/

#ifndef QTMARKUP_H
#define QTMARKUP_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextEdit>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <cstdlib>
#include <string>
#include <vector>


namespace Ui {
class qtmarkup;
}

class qtmarkup : public QMainWindow
{
    Q_OBJECT

public:
    // Functions, documented in qtmarkup.cpp
    explicit qtmarkup(QWidget *parent = 0);
    virtual ~qtmarkup();
    void keyPressEvent(QKeyEvent* e);

    // These below should be private but not sure how to test them from the outside otherwise
    // Private variable to save the html output in so that htmlEdit doesn't introduce extra tags
    QString htmlstr;

    // Functions, documented in qtmarkup.cpp
    bool is_h1(const std::string &str, unsigned int width = 1);
    bool is_h2(const std::string &str, unsigned int width = 1);
    std::string italics(const std::string &str);
    std::string bold(const std::string &str);
    QString markupToHTML(QString str);

private slots:
    void on_markupEdit_textChanged();

private:
    // Creates UI
    Ui::qtmarkup *ui;
};

#endif // QTMARKUP_H
