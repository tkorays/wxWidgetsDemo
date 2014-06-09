#ifndef _TK_MAIN_WINDOW_H_
#define _TK_MAIN_WINDOW_H_

#include "wxinc.h"

class MainWindow :public wxFrame{
public:
	MainWindow(const wxString& title, const wxPoint& pos, wxSize& size, long style);
	~MainWindow();

private:
	wxMenuBar* menuBar;
	wxToolBar* toolBar;
	wxStatusBar* statusBar;
	

	wxDECLARE_EVENT_TABLE();
};


#endif // _TK_MAIN_WINDOW_H_