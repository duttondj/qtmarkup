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

// #include <QApplication>
// #include <QLabel>
// #include <QPlainTextEdit>
// #include <QWebView>
// #include <QWidget>

using namespace std;


// I should redo these to actually see if the length of the symbols
// are at least as long as the line above, not a huge priority right now
// is_h1 will detect if a line contains only "=", the symbol for an h1
bool is_h1(const string &str)
{
	if (!str.empty())
	{
		return str.find_first_not_of("=") == string::npos;
	}
	else
	{
		return false;
	}
		
}

// is_h2 will detect if a line contains only "-", the symbol for an h2
bool is_h2(const string &str)
{
	if (!str.empty())
	{
		return str.find_first_not_of("-") == string::npos;
	}
	else
	{
		return false;
	}
}

// Find any italics in a string an return a properly formated HTML line
string italics(const string &str)
{
	//string
	//size_t found = 

	return str;
}

// Find any bolds in a string an return a properly formated HTML line
string bold(const string &str)
{
	string newstr = str;
	size_t first = newstr.find("**");
	size_t second = newstr.find("**",first+1);

	if (first != string::npos && second != string::npos)
	{
		newstr.replace(first, 2, "<b>");
		newstr.replace(second+1, 2, "</b>");

		return bold(newstr);
	}
	else
	{
		return newstr;
	}
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

	string row;					// Row to be read from text file
	string temp;				// Temporary string to be manipulated
	vector<string> markdown;	// Vector containing all lines in the MD file
	vector<string> html;		// Vector containing all lines in HTML file
	int i;						// Iterator for loops

	ifstream inFile;			// Input file stream

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
		// Check for h1
		if(i != markdown.size()-1 && is_h1(markdown[i+1]))
		{
			html.push_back("<h1>" + markdown[i] + "</h1>");
		}

		// Check for h2
		else if(i != markdown.size()-1 && is_h2(markdown[i+1]))
		{
			html.push_back("<h2>" + markdown[i] + "</h2>");
		}
		
		// Not an h1 or h2
		else if (!markdown[i].empty())
		{
			// We dont want to include any ====== or -----
			if(!is_h1(markdown[i]) && !is_h2(markdown[i]))
			{
				temp = bold(markdown[i]);
				html.push_back("<p>" + temp + "</p>");
			}
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
