#ifndef _TK_APPCONFIG_H_
#define _TK_APPCONFIG_H_

#include "wxinc.h"
#include <stdint.h>

typedef struct app_config_{
	wxString title = _T("ARDrone¿ØÖÆ³ÌÐò");
	wxString author = _T("tkorays");
	wxPoint pos = wxPoint(20, 20);
	wxSize size = wxSize(800, 600);
	long winstyle = wxDEFAULT_FRAME_STYLE & ~wxMAXIMIZE_BOX & ~wxRESIZE_BORDER;
} app_config;


#endif // _TK_APPCONFIG_H_