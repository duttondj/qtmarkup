/*
File: testqtmarkup.cpp
Name: Danny Dutton
Class: ECE3574
Project: 1
Description: This is the test module for qtmarkup. It contains
             test functions that test the output of qtmarkup function
             based on specified inputs.
*/

#include <QApplication>
#include <QMainWindow>
#include <QKeyEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QtTest>
#include <QTextEdit>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <cstdlib>
#include <string>
#include <vector>
#include "qtmarkup.h"

class TestQtMarkup : public QObject
{
    Q_OBJECT
public:
    QApplication b();
    qtmarkup a;

private Q_SLOTS:
    void test_is_h1();
    void test_is_h2();
    void test_italicsbold();
    void test_markupToHTML();
};

// Test h1 headers
void TestQtMarkup::test_is_h1()
{
    // String Inputs
    std::vector<std::string> teststrs = {"",
                                             "hello",
                                             "=",
                                             "===",
                                             "===="};

    // Width Inputs
    std::vector<int> testints = {0, 0, 2, 3, 3};

    // Check for each case
    QVERIFY(a.is_h1(teststrs[0], testints[0]) == false);
    QVERIFY(a.is_h1(teststrs[1], testints[1]) == false);
    QVERIFY(a.is_h1(teststrs[2], testints[2]) == false);
    QVERIFY(a.is_h1(teststrs[3], testints[3]) == true);
    QVERIFY(a.is_h1(teststrs[4], testints[4]) == true);
}

// Test h2 headers
void TestQtMarkup::test_is_h2()
{
    // String Inputs
        std::vector<std::string> teststrs = {"",
                                             "hello",
                                             "-",
                                             "---",
                                             "----"};
    // Width Inputs
    std::vector<int> testints = {0, 0, 2, 3, 3};

    // Check for each case
    QVERIFY(a.is_h2(teststrs[0], testints[0]) == false);
    QVERIFY(a.is_h2(teststrs[1], testints[1]) == false);
    QVERIFY(a.is_h2(teststrs[2], testints[2]) == false);
    QVERIFY(a.is_h2(teststrs[3], testints[3]) == true);
    QVERIFY(a.is_h2(teststrs[4], testints[4]) == true);
}

// Test together because of the recursion used
void TestQtMarkup::test_italicsbold()
{
    // Inputs
    std::vector<std::string> teststrs = {"*italics*",
                                             "normal",
                                             "normal *italics*",
                                             "*normal",
                                             "normal*",
                                             "*italics* normal",
                                             "**bold**",
                                             "**bold** *italics* normal",
                                             "**bold *bolditalics* bold**",
                                             "normal *italics **bold** italics*",
                                             "**normal",
                                             "normal**",
                                             "**bold *bold**",
                                             "**bold *bold** italics*"};

    // Expected outputs
    std::vector<std::string> results = {"<i>italics</i>",
                                            "normal",
                                            "normal <i>italics</i>",
                                            "*normal",
                                            "normal*",
                                            "<i>italics</i> normal",
                                            "<b>bold</b>",
                                            "<b>bold</b> <i>italics</i> normal",
                                            "<b>bold <i>bolditalics</i> bold</b>",
                                            "normal <i>italics <b>bold</b> italics</i>",
                                            "**normal",
                                            "normal**",
                                            "<b>bold *bold</b>",
                                            "<b>bold <i>bold</b> italics</i>"}; // Chrome displays this correctly but not Qt

    // Run through each test and check results
//    for(unsigned int i = 0; i < results.size(); i++)
//    {
//        QVERIFY(a.italics(a.bold(teststrs[i])) == results[i]);
//    }

    QVERIFY(a.italics(a.bold(teststrs[0])) == results[0]);
    QVERIFY(a.italics(a.bold(teststrs[1])) == results[1]);
    QVERIFY(a.italics(a.bold(teststrs[2])) == results[2]);
    QVERIFY(a.italics(a.bold(teststrs[3])) == results[3]);
    QVERIFY(a.italics(a.bold(teststrs[4])) == results[4]);
    QVERIFY(a.italics(a.bold(teststrs[5])) == results[5]);
    QVERIFY(a.italics(a.bold(teststrs[6])) == results[6]);
    QVERIFY(a.italics(a.bold(teststrs[7])) == results[7]);
    QVERIFY(a.italics(a.bold(teststrs[8])) == results[8]);
    QVERIFY(a.italics(a.bold(teststrs[9])) == results[9]);
    QVERIFY(a.italics(a.bold(teststrs[10])) == results[10]);
    QVERIFY(a.italics(a.bold(teststrs[11])) == results[11]);
    QVERIFY(a.italics(a.bold(teststrs[12])) == results[12]);
    QVERIFY(a.italics(a.bold(teststrs[13])) == results[13]);
}

// Test a sample of input for correct html conversion
void TestQtMarkup::test_markupToHTML()
{
    // Giant input string to pipe into function
    QString teststr = "Big Header\n===========\n\nBig\n===\n\nNot Big\n======\n\n=\nThis is some *fancy* text.\nThis is also *some* fancy *text* but we want to ignore ** and *.\n\nA small header\n---------------\n\nAnother small header\n--------------------\n\nNot small header\n---------\n\nThis is some **very** important **text.\n\nThis raw html <code> is left as is.</code>\n<marquee>This text will scroll from right to left</marquee>\n\n**this is in bold *this is in both* bold once more**\n*this is italics **this is in both** italics once more*\n\n*italics*\nnormal\nnormal *italics*\n*normal\nnormal*\n*italics* normal\n**bold**\n**bold** *italics* normal\n**bold *bolditalics* bold**\nnormal *italics **bold** italics*\n**normal\nnormal**\n**bold *bold**\n**bold *bold** normal*";

    // Expected output
    QString results = "<html>\n<body>\n<h1>Big Header</h1>\n<h1>Big</h1>\n<p>Not Big</p>\n<p>This is some <i>fancy</i> text.</p>\n<p>This is also <i>some</i> fancy <i>text</i> but we want to ignore ** and *.</p>\n<h2>A small header</h2>\n<h2>Another small header</h2>\n<p>Not small header</p>\n<p>This is some <b>very</b> important **text.</p>\n<p>This raw html <code> is left as is.</code></p>\n<p><marquee>This text will scroll from right to left</marquee></p>\n<p><b>this is in bold <i>this is in both</i> bold once more</b></p>\n<p><i>this is italics <b>this is in both</b> italics once more</i></p>\n<p><i>italics</i></p>\n<p>normal</p>\n<p>normal <i>italics</i></p>\n<p>*normal</p>\n<p>normal*</p>\n<p><i>italics</i> normal</p>\n<p><b>bold</b></p>\n<p><b>bold</b> <i>italics</i> normal</p>\n<p><b>bold <i>bolditalics</i> bold</b></p>\n<p>normal <i>italics <b>bold</b> italics</i></p>\n<p>**normal</p>\n<p>normal**</p>\n<p><b>bold *bold</b></p>\n<p><b>bold <i>bold</b> normal</i></p>\n</body>\n</html>\n";

    // Check if input matches expected output
    QVERIFY(QString::compare(a.markupToHTML(teststr), results, Qt::CaseSensitive) == 0);
}

QTEST_MAIN(TestQtMarkup)
#include "testqtmarkup.moc"