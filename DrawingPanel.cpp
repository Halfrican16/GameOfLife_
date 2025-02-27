#include "DrawingPanel.h"
#include "MainWindow.h"
#include "Utilities.h"



wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint)
wxEND_EVENT_TABLE()

DrawingPanel::DrawingPanel(wxWindow* parent, std::vector<std::vector<Cell>>& board, Settings* settingsPtr)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize), gameBoard(board), settings(settingsPtr) {
    
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
        gameBoard[row][col] = gameBoard[row][col];
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

            
            if (gameBoard[row][col].alive) {
                dc.SetBrush(wxBrush(settings->GetLivingColor()));
            }
            else {
                dc.SetBrush(wxBrush(settings->GetDeadColor()));
            }
            dc.SetBrush(wxBrush(gameBoard[row][col].alive ? settings->GetLivingColor() : settings->GetDeadColor()));
            dc.SetPen(*wxBLACK_PEN);
            dc.DrawRectangle(x, y, cellWidth, cellHeight);

            if (settings->showNeighborCount) {
                int neighbors = gameBoard[row][col].alive ? 1 : 0;
                dc.SetFont(wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
                dc.SetTextForeground(*wxRED);
                dc.DrawText(std::to_string(neighbors), x + cellWidth / 3, y + cellHeight / 4);
            }
        }
    }
}

void DrawingPanel::calculateCellSize(int& cellWidth, int& cellHeight) const {
    wxSize size = GetClientSize();
    cellWidth = size.GetWidth() / gridSize;
    cellHeight = size.GetHeight() / gridSize;
}