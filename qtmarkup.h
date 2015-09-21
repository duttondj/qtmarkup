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
    explicit qtmarkup(QWidget *parent = 0);
    virtual ~qtmarkup();
    void keyPressEvent(QKeyEvent* e);

private:
    bool is_h1(const std::string &str, unsigned int width = 0);
    bool is_h2(const std::string &str, unsigned int width = 0);
    std::string italics(const std::string &str);
    std::string bold(const std::string &str);
    QString markupToHTML(QString str);

private slots:
    void on_markupEdit_textChanged();

private:
    Ui::qtmarkup *ui;
};

#endif // QTMARKUP_H
