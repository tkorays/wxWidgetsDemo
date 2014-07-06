#ifndef _TK_XFRAME_H_
#define _TK_XFRAME_H_

#include <wx/frame.h>

#define ID_CLOSE_BTN  1

class wxBoxSizer;
class wxPanel;
class XSettingFrame;

class XFrame :public wxFrame {
private:
	XFrame();
	void OnCloseBtn(wxMouseEvent& event);
	void OnHeaderLeftDown(wxMouseEvent& event);
	void OnHeaderLeftDrag(wxMouseEvent& event); 
	void OnHeaderLeftUp(wxMouseEvent& event);
	void OnSetting(wxMouseEvent& event);
public:
	wxPoint offset;
	wxString title;
	wxString icon_png;
	wxBoxSizer* main_sizer;
	wxPanel* main_panel;
	XSettingFrame* setting_frame;
	XFrame(wxSize size, wxString icon_png, wxString title);

	

	DECLARE_EVENT_TABLE();
};


#endif // _TK_XFRAME_H_