#include "App.h"

IMPLEMENT_APP(App)

bool App::OnInit() {
	std::ifstream f("signal.json");
	json j;
	f >> j;
	data = j[0];

	frame = new MainFrame(wxT("Project"), wxSize(800, 600), data);
	frame->Show();

	return true;
}

MainFrame::MainFrame(const wxString& title, const wxSize& size, json& data) : wxFrame(nullptr, wxID_ANY, title, wxPoint(40,40), size) {
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	pane = new DrawPane(this, data);
	sizer->Add(pane, 1, wxEXPAND);
	SetSizer(sizer);

	timer = new RenderTimer(pane);
	Show();
	timer->start();
}

MainFrame::~MainFrame() {
	delete timer;
}

void MainFrame::onClose(wxCloseEvent& e) {
	timer->Stop();
	e.Skip();
}
