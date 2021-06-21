#include "cApp.h"


wxIMPLEMENT_APP(cApp);

cApp::cApp() {

}

cApp::~cApp() {

}

bool cApp::OnInit() {
	m_frame1 = new cMain();
	m_frame1->Show();

#if defined(_WIN32) || defined(WIN32)
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif

	return true;
}