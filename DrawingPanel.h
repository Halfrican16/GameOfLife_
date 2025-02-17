#ifndef DRAWINGPANEL_H
#define DRAWINGPANEL_H

#include <wx/wx.h>
#include <vector>

class DrawingPanel : public wxPanel {
public:
    DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& board);

    void setGridSize(int newSize); 
    void OnMouseClick(wxMouseEvent& event); 
    void OnPaint(wxPaintEvent& event);

private:
    int gridSize = 15; 
    std::vector<std::vector<bool>>& gameBoard;

    void calculateCellSize(int& cellWidth, int& cellHeight) const;
    

    wxDECLARE_EVENT_TABLE();
};

#endif

