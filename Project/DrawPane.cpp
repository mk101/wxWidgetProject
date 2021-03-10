#include "DrawPane.h"

RenderTimer::RenderTimer(DrawPane* pane) : wxTimer() {
	this->pane = pane;
}

void RenderTimer::Notify() {
	pane->Refresh();
}

void RenderTimer::start() {
	wxTimer::Start(120);
}

DrawPane::DrawPane(wxFrame* parent, json& data) : wxPanel(parent), data(data) {}

void DrawPane::paintEvent(wxPaintEvent& evt) {
    wxBufferedPaintDC dc(this);
	render(dc);
}

void DrawPane::paintNow() {
	wxClientDC dc(this);
	render(dc);
}

// size = 800 * 600
void DrawPane::render(wxDC& dc) {
    static int x = 0;
    static int k = 0;
    static int x_speed = 1;
    const int size = data.size();

    dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();
    dc.SetPen(*wxRED_PEN);

    for (int i = 0; i <= x; i++) {
        dc.DrawLine(wxPoint(i, 260 - data[k + i] / 4), wxPoint((i + 1), 260 - data[k + i + 1] / 4));
    }

    dc.DrawText(wxString::Format("%d/%d", k, size), wxPoint(20, 20));
    if (x < 790) {
        x += x_speed;
    } else {
        x = 790;
    }

    if (k < size - 792) {
        k += x_speed;
    } else {
        k = 0;
        x = 0;
    }

}

void DrawPane::eraseBackground(wxEraseEvent& evt) {}
