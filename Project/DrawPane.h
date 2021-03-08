#pragma once
#include <wx/wxprec.h>
#include <wx/dcbuffer.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class DrawPane;

class RenderTimer : public wxTimer {
	DrawPane* pane;
public:
	RenderTimer(DrawPane* pane);
	void Notify();
	void start();
};

class DrawPane : public wxPanel {
	json& data;
public:
	DrawPane(wxFrame* parent, json& data);
	
	void paintEvent(wxPaintEvent& evt);
	void paintNow();
	void render(wxDC& dc);
	void eraseBackground(wxEraseEvent& evt);

	DECLARE_EVENT_TABLE()
};

