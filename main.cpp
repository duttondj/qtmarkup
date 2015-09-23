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
