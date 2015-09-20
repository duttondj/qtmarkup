// Danny Dutton
// ECE 3574
// Project 1: Qt Markup
// 
// This is the main file for the Qt application

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <QApplication>
#include <QLabel>
#include <QPlainTextEdit>
#include <QWebView>
#include <QWidget>

using namespace std;

bool is_h1(const string &str)
{
	return str.find_first_not_of("=") == string::npos;
}

bool is_h2(const string &str)
{
	return str.find_first_not_of("-") == string::npos;
}

int main(int argc, char **argv)
{
	// QApplication app(argc, argv);
	// QLabel qtmarkup("hello");
	// qtmarkup.setWindowTitle("Qt Markup");
	// qtmarkup.resize(800, 600);
	// qtmarkup.show();

	// QWebView *view = new QWebView(app);
	// view->load(QUrl("file://index.html"));
	// view->show();


	// return app.exec();

	string row;
	vector<string> markdown;
	vector<string> html;
	int i;

	ifstream inFile;

	// Check if file was opened correctly. If not: display error, free memory and exit main.
	try
	{
		inFile.open(argv[1]);

		if (!inFile.good())
		{
			throw "File failed to open (file not found).";
		}
	}
	catch (const char* msg) {
		cerr << msg << endl;
		return 0;
	}

	// Read all the lines in the file and add them to the markdown vector
	while(getline(inFile, row))
	{
		markdown.push_back(row);
	}

	inFile.close();

	// Setup html file
	html.push_back("<html>");
	html.push_back("<body>");

	// Look for formating
	for (i = 0; i < markdown.size(); i++)
	{
		if(is_h1(markdown[i+1]) && (i < (markdown.size()-1)))
		{
			html.push_back("<h1>" + markdown[i] + "</h1>");
		}

		if(is_h2(markdown[i+1]) && (i < (markdown.size()-1)))
		{
			html.push_back("<h2>" + markdown[i] + "</h2>");
		}
	}

	// End html file
	html.push_back("</body>");
	html.push_back("</html>");

	for (i = 0; i < html.size(); i++)
	{
		cout << html[i] << endl;
	}

	return 0;
}
