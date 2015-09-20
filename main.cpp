#include "qtmarkup.h"
#include <QApplication>
#include <QtWebKit/QWebView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qtmarkup w;
    w.show();

    return a.exec();
}
