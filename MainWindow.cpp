#include "MainWindow.h"


wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::OnSizeChange)
EVT_MENU(10001, MainWindow::OnPlay)
EVT_MENU(10002, MainWindow::OnPause)
EVT_MENU(10003, MainWindow::OnNext)
EVT_MENU(10004, MainWindow::OnClear)
wxEND_EVENT_TABLE()

MainWindow::MainWindow()
    : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(400, 400)) { 

    initializeGrid();

    drawingPanel = new DrawingPanel(this, gameBoard);

    drawingPanel->setGridSize(gridSize);

    statusBar = CreateStatusBar();
    UpdateStatusBar();

    toolbar = CreateToolBar();

    wxBitmap playIcon(play_xpm);
    wxBitmap pauseIcon(pause_xpm);
    wxBitmap nextIcon(next_xpm);
    wxBitmap trashIcon(trash_xpm);

   
    toolbar->AddTool(10001, "Play", playIcon, "Start Simulation");
    toolbar->AddTool(10002, "Pause", pauseIcon, "Pause Simulation");
    toolbar->AddTool(10003, "Next", nextIcon, "Next Generation");
    toolbar->AddTool(10004, "Reset", trashIcon, "Clear Grid");

    


    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(drawingPanel, 1, wxEXPAND);
    SetSizer(sizer);

    this->Layout();
}

MainWindow::~MainWindow() {
    
}

void MainWindow::OnSizeChange(wxSizeEvent& event) {
    if (drawingPanel) {
        drawingPanel->Refresh();
    }
    event.Skip();
}


void MainWindow::initializeGrid() {

    gameBoard.resize(gridSize, std::vector<bool>(gridSize, false));
}


void MainWindow::UpdateStatusBar() {
    livingCells = 0;
    for (const auto& row : gameBoard) {
        for (bool cell : row) {
            if (cell) livingCells++;
        }
    }
}

void MainWindow::OnPlay(wxCommandEvent& event) {
    wxLogMessage("Play button clicked!");
}

void MainWindow::OnPause(wxCommandEvent& event) {
    wxLogMessage("Pause button clicked!");
}

void MainWindow::OnNext(wxCommandEvent& event) {
    wxLogMessage("Next Generation button clicked!");
}

void MainWindow::OnClear(wxCommandEvent& event) {
    wxLogMessage("Reset button clicked!");
}

int MainWindow::CountLivingNeighbors(int row, int col) {
    int count = 0;

    
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1}, 
        { 0, -1},         { 0, 1},  
        { 1, -1}, { 1, 0}, { 1, 1} 
    };

    for (int i = 0; i < 8; i++) {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];

        
        if (newRow >= 0 && newRow < gridSize && newCol >= 0 && newCol < gridSize) {
            if (gameBoard[newRow][newCol]) {
                count++;
            }
        }
    }

    return count;
}

void MainWindow::GenerateNextGeneration() {
    
    std::vector<std::vector<bool>> sandbox(gridSize, std::vector<bool>(gridSize, false));

    
    int newLivingCells = 0;

    
    for (int row = 0; row < gridSize; row++) {
        for (int col = 0; col < gridSize; col++) {
            int neighbors = CountLivingNeighbors(row, col);

            
            if (gameBoard[row][col]) { 
                if (neighbors < 2 || neighbors > 3) {
                    sandbox[row][col] = false;
                }
                else {
                    sandbox[row][col] = true;
                    newLivingCells++;
                }
            }
            else {
                if (neighbors == 3) {
                    sandbox[row][col] = true;
                    newLivingCells++;
                }
            }
        }
    }

   
    
    gameBoard.swap(sandbox);

    
    generation++;
    livingCells = newLivingCells;

    
    UpdateStatusBar();

    
    drawingPanel->Refresh();
}