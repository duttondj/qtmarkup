/*
File: main.cpp
Name: Danny Dutton
Class: ECE3574
Project: 1
Description: This is the main function for qtmarkup. It creates the object 
             and displays it.
*/

#include <QApplication>
#include <QtWebKit/QWebView>
#include "qtmarkup.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qtmarkup w;
    w.show();

    return a.exec();
}
