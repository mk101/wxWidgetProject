/*
 https://wiki.wxwidgets.org/Making_a_render_loop
 https://github.com/nlohmann/json
 https://wiki.wxwidgets.org/Flicker-Free_Drawing
 */
#pragma once
#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <nlohmann/json.hpp>
#include <fstream>

#include "DrawPane.h"

using json = nlohmann::json;

class MainFrame;

class App : public wxApp {
	json data;
	MainFrame* frame;
public:
	virtual bool OnInit() wxOVERRIDE;
};

class MainFrame : public wxFrame {
	RenderTimer* timer;
	DrawPane* pane;
public:
	MainFrame(const wxString& title, const wxSize& size, json& data);
	~MainFrame();
	void onClose(wxCloseEvent& e);

	DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_CLOSE(MainFrame::onClose)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(DrawPane, wxPanel)
EVT_PAINT(DrawPane::paintEvent)
EVT_ERASE_BACKGROUND(DrawPane::eraseBackground)
END_EVENT_TABLE()