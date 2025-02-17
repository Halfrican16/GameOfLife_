#include "DrawingPanel.h"
#include "MainWindow.h"



wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint)
wxEND_EVENT_TABLE()

DrawingPanel::DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& board)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize), gameBoard(board) {
    
}

void DrawingPanel::setGridSize(int newSize) {
    gridSize = newSize;
    Refresh();
}

void DrawingPanel::OnMouseClick(wxMouseEvent& event) {
    int cellWidth, cellHeight;
    calculateCellSize(cellWidth, cellHeight);

    int x = event.GetX();
    int y = event.GetY();

    int col = x / cellWidth;
    int row = y / cellHeight;

    if (row >= 0 && row < gridSize && col >= 0 && col < gridSize) {
        gameBoard[row][col] = !gameBoard[row][col];
    }

    wxFrame* parentFrame = dynamic_cast<wxFrame*>(GetParent());
    if (parentFrame) {
        MainWindow* mainWin = dynamic_cast<MainWindow*>(parentFrame);
        if (mainWin) {
            mainWin->UpdateStatusBar();
        }
    }


    Refresh();
}

void DrawingPanel::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);

    int cellWidth, cellHeight;
    calculateCellSize(cellWidth, cellHeight);

    
    for (size_t row = 0; row < gameBoard.size(); row++) {
        for (size_t col = 0; col < gameBoard[row].size(); col++) {
            int x = col * cellWidth;
            int y = row * cellHeight;

            
            if (gameBoard[row][col]) {
                dc.SetBrush(*wxLIGHT_GREY_BRUSH);
            }
            else {
                dc.SetBrush(*wxWHITE_BRUSH);
            }
            dc.SetPen(*wxBLACK_PEN);

            
            dc.DrawRectangle(x, y, cellWidth, cellHeight);
        }
    }
}

void DrawingPanel::calculateCellSize(int& cellWidth, int& cellHeight) const {
    wxSize size = GetClientSize();
    cellWidth = size.GetWidth() / gridSize;
    cellHeight = size.GetHeight() / gridSize;
}