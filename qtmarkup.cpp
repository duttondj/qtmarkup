/*
File: qtmarkup.cpp
Name: Danny Dutton
Class: ECE3574
Project: 1
Description: This is the cpp file for qtmarkup. It contains the function for
             the class.
*/

#include "qtmarkup.h"
#include "ui_qtmarkup.h"

// Constructor function, creates UI
qtmarkup::qtmarkup(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::qtmarkup)
{
    ui->setupUi(this);
}

// Destructor function
qtmarkup::~qtmarkup()
{
    delete ui;
}

// This function listens for keys being pressed, listens for C-o (open) and C-s (save)
// Input: QKeyEvent* e
// Output: Sends opened file to textEdit, saves converted HTML to file
void qtmarkup::keyPressEvent(QKeyEvent* e)
{
    // This is for any error messages to be displayed
    QMessageBox* box = new QMessageBox();

    // Check if CTRL was pressed
    if (e->modifiers().testFlag(Qt::ControlModifier))
    {
        // Check if O was pressed as well
        if(e->key() == Qt::Key_O)
        {
            // Show a file dialog box
            QString filename = QFileDialog::getOpenFileName(this, tr("Open Simple Markdown File"), "", "All files (*.*);;Simple Mardown (*.sm)");
            QFile file(filename);

            QString line;

            // Open the file as read only and as text
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                // Clear out the markupEdit box since we are loading a file
                ui->markupEdit->clear();

                // Write every line to the markupEdit box
                QTextStream stream(&file);
                while (!stream.atEnd())
                {
                    line = stream.readLine();
                    ui->markupEdit->setText(ui->markupEdit->toPlainText()+line+"\n");
                }
            }
            // There was an issue so show an error
            else
            {
                box->setText(QString("Error: No file selected to open, try again"));
                box->show();
            }
            file.close();
        }
        // Check if S was pressed as well
        else if(e->key() == Qt::Key_S)
        {
            // Show a file dialog box
            QString filenamehtml = QFileDialog::getSaveFileName(this, tr("Save HTML File"), "", "HTML File (*.html)");
            QFile filehtml(filenamehtml);

            // Open the file only as writeable and as text
            if(filehtml.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                // Write the contents of htmlEdit to the file
                QTextStream stream(&filehtml);
                stream << htmlstr;
                filehtml.flush();
            }
            // There was an issue so show an error
            else
            {
                box->setText(QString("Error: No valid save file selected, try again"));
                box->show();
            }
            filehtml.close();
        }
    }
}

// is_h1 will detect if a string contains only "=", the symbol for an h1 only if it is longer than width
// Input: string &str of simple markdown and unsigned int width = 0
// Output: bool stating if the string containing only "=" is longer than width (default value of zero)
bool qtmarkup::is_h1(const std::string &str, unsigned int width) // width = 1
{
    // Only check nonempty strings with a width at least the size of the line above
    if (!str.empty() && str.size() >= width && width != 0)
    {
        return str.find_first_not_of("=") == std::string::npos;
    }
    else
    {
        return false;
    }

}

// is_h2 will detect if a string contains only "-", the symbol for an h2 only if it is longer than width
// Input: string &str of simple markdown and unsigned int width = 0
// Output: bool stating if the string containing only "-" is longer than width (default value of zero)
bool qtmarkup::is_h2(const std::string &str, unsigned int width) // width = 1
{
    // Only check nonempty strings with a width at least the size of the line above
    if (!str.empty() && str.size() >= width && width != 0)
    {
        return str.find_first_not_of("-") == std::string::npos;
    }
    else
    {
        return false;
    }
}

// Find any italics in a string an return a properly formated HTML line
// Input: string &str of simple markdown
// Output: string that has replaced paired "*" with italics tags
std::string qtmarkup::italics(const std::string &str)
{
    // Create new string from the passed one
    std::string newstr = str;

    // Find first and second instance of *
    std::size_t first = newstr.find("*");
    std::size_t second = newstr.find("*",first+1);

    // Make sure the first and second instances exist.
    // Also make sure there is actual text between the *
    // We want to ignore things like **
    if (first != std::string::npos && second != std::string::npos && first != second-1)
    {
        // Replace first and second instances
        newstr.replace(first, 1, "<i>");
        newstr.replace(second+2, 1, "</i>");

        // Use recursion to detect any other instances
        return italics(newstr);
    }
    // There are no non-consecutive pairs of *
    else
    {
        return newstr;
    }
}

// Find any bolds in a string an return a properly formated HTML line
// Input: string &str of simple markdown
// Output: string that has replaced paired "**" with bold tags
std::string qtmarkup::bold(const std::string &str)
{
    // Create new string from the passed one
    std::string newstr = str;

    // Find first and second instance of **
    std::size_t first = newstr.find("**");
    std::size_t second = newstr.find("**",first+1);

    // Make sure the first and second instances exist.
    // Also make sure there is actual text between the **
    // We want to ignore things like ****
    if (first != std::string::npos && second != std::string::npos && first != second-2)
    {
        newstr.replace(first, 2, "<b>");
        newstr.replace(second+1, 2, "</b>");

        // Use recursion to detect any other instances
        return bold(newstr);
    }
    // There are no non-consecutive pairs of **
    else
    {
        return newstr;
    }
}

// Convert a qstring containing simple markdown to a qstring containing html
// Input: QString str of simple markdown
// Ouput: QString str of HTML
QString qtmarkup::markupToHTML(QString str)
{
    std::vector<std::string> markdown;  // Vector containing all lines in the MD file
    std::vector<std::string> html;      // Vector containing all lines in HTML file
    unsigned int i;                     // Iterator for loops
    QString outputstr;                  // Output QString to be returned

    // Split up the QString so we can read each line
    QStringList list = str.split("\n");
    // Read all the lines in the file and add them to the markdown vector
    foreach(QString row, list)
    {
        markdown.push_back(row.toStdString());
    }

    // Setup html file
    html.push_back("<html>");
    html.push_back("<body>");

    // Look for formating symbols
    for (i = 0; i < markdown.size(); i++)
    {
        // Check for h1
        if(i != markdown.size()-1 && is_h1(markdown[i+1], markdown[i].size()))
        {
            html.push_back("<h1>" + markdown[i] + "</h1>");
        }

        // Check for h2
        else if(i != markdown.size()-1 && is_h2(markdown[i+1], markdown[i].size()))
        {
            html.push_back("<h2>" + markdown[i] + "</h2>");
        }

        // Not an h1 or h2
        else if (!markdown[i].empty())
        {
            // We dont want to include any ====== or -----
            if((!is_h1(markdown[i]) && !is_h2(markdown[i])) || i == 0)
            {
                // Pass the line through bold first to find any ** pairs
                // and then pass it through italics to find any * pairs.
                // Order does matter as italics can be tricked with nesting
                html.push_back("<p>" + italics(bold(markdown[i])) + "</p>");
            }

        }
    }

    // End html file
    html.push_back("</body>");
    html.push_back("</html>");

    // Write the html to the output list after modifying
    for (i = 0; i < html.size(); i++)
    {
        outputstr.append(QString::fromStdString(html[i]));
        outputstr.append(QString::fromStdString("\n"));
    }

    // Return the output as a QString
    return outputstr;
}

// When ever the markupEdit box changes, we want to update the htmlEdit box
// Input: this is a slot listening for a signal
// Output: Moves text in textEdit to markdownToHTML to htmlEdit
void qtmarkup::on_markupEdit_textChanged()
{
    // Dump the markupEdit contents to a single qstring
    QString markupstr = ui->markupEdit->toPlainText();

    // Save the output of markupToHTML as a string, input is the markupEdit contents
    htmlstr = markupToHTML(markupstr);

    // Clear the htmlEdit box since a lot of extra garbage will be created
    ui->htmlEdit->clear();

    // Set the htmlEdit contents to the new html text but display it as HTML rather than plain text
    ui->htmlEdit->setText(ui->htmlEdit->toHtml()+htmlstr);

    // Set htmlEdit to be readonly
    ui->htmlEdit->setReadOnly(true);
}
