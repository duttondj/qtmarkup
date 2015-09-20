#include "qtmarkup.h"
#include "ui_qtmarkup.h"


qtmarkup::qtmarkup(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::qtmarkup)
{
    ui->setupUi(this);
}

qtmarkup::~qtmarkup()
{
    delete ui;
}

void qtmarkup::keyPressEvent(QKeyEvent* e)
{
    //QMenu *file = new QMenu(this)

    QMessageBox* box = new QMessageBox();

    if (e->modifiers().testFlag(Qt::ControlModifier))
    {
        if(e->key() == Qt::Key_O)
        {
            //box->setText(QString("Open File detected"));
            //box->show();

            QString filename = QFileDialog::getOpenFileName(
                        this,
                        tr("Open Simple Markdown File"),
                        "",
                        "All files (*.*);;Simple Mardown (*.sm)");
            QFile file(filename);

            QString line;
            ui->markupEdit->clear();
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QTextStream stream(&file);
                while (!stream.atEnd())
                {
                    line = stream.readLine();
                    ui->markupEdit->setText(ui->markupEdit->toPlainText()+line+"\n");
                }
            }
            file.close();
        }
        else if(e->key() == Qt::Key_S)
        {
            box->setText(QString("Save File detected"));
            box->show();
        }
    }
}

void qtmarkup::on_markupEdit_textChanged()
{
    QString markupstr = ui->markupEdit->toPlainText().toStdString();
    //QStringList list = str.split("\n");

    QString htmlstr = markupToHTML(str);

    ui->htmlEdit->setText(ui->htmlEdit->toHtml()+line+"\n");
}

QString qtmarkup::markupToHTML(QString str)
{
    return 0;
}
