#ifndef QTMARKUP_H
#define QTMARKUP_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextEdit>
#include <QTextStream>
#include <QString>
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
    explicit qtmarkup(QWidget *parent = 0);
    ~qtmarkup();
    void keyPressEvent(QKeyEvent* e);

private slots:
    void on_markupEdit_textChanged();
    QString qtmarkup::markupToHTML(QString str);


private:
    Ui::qtmarkup *ui;
};

#endif // QTMARKUP_H
