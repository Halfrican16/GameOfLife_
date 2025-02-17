#include "MainWindow.h"


wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::OnSizeChange)
EVT_MENU(10001, MainWindow::OnPlay)
EVT_MENU(10002, MainWindow::OnPause)
EVT_MENU(10003, MainWindow::OnNext)
EVT_MENU(10004, MainWindow::OnClear)
EVT_MENU(10005, MainWindow::OnNextGeneration)
EVT_MENU(10006, MainWindow::OnClearBoard)
EVT_TIMER(1007, MainWindow::OnTimer)
wxEND_EVENT_TABLE()

MainWindow::MainWindow()
    : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(0, 0), wxSize(400, 400)) { 

    initializeGrid();

    drawingPanel = new DrawingPanel(this, gameBoard);

    drawingPanel->setGridSize(gridSize);

    timer = new wxTimer(this, 10010);

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

    toolbar->Realize();

    


    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(drawingPanel, 1, wxEXPAND);
    sizer->Add(toolbar, 0, wxEXPAND);
    SetSizer(sizer);

    this->Layout();
}

MainWindow::~MainWindow() {
    
}

void MainWindow::OnTimer(wxTimerEvent& event) {
    GenerateNextGeneration();
}

void MainWindow::OnSizeChange(wxSizeEvent& event) {
    if (drawingPanel) {
        drawingPanel->Refresh();
    }
    event.Skip();
}


void MainWindow::initializeGrid() {
    gameBoard.resize(DEFAULT_GRID_SIZE, std::vector<Cell>(DEFAULT_GRID_SIZE)); // ✅ Correct type
}

void MainWindow::UpdateStatusBar() {
    livingCells = 0;
    for (const auto& row : gameBoard) {
        for (const auto& cell : row) {
            if (cell.alive) {
                livingCells++;
            }
        }
    }

    
    wxString statusText = wxString::Format("Generation: %d | Living Cells: %d", generation, livingCells);
    statusBar->SetStatusText(statusText);
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
            if (gameBoard[newRow][newCol].alive) {
                count++;
            }
        }
    }

    return count;
}

void MainWindow::GenerateNextGeneration() {
    std::vector<std::vector<Cell>> sandbox(gridSize, std::vector<Cell>(gridSize));

    int newLivingCells = 0;

    for (int row = 0; row < gridSize; row++) {
        for (int col = 0; col < gridSize; col++) {
            int neighbors = CountLivingNeighbors(row, col);

            
            if (gameBoard[row][col].alive) { 
                if (neighbors < 2 || neighbors > 3) {
                    sandbox[row][col].alive = false;
                }
                else {
                    sandbox[row][col].alive = true;
                    newLivingCells++;
                }
            }
            else {
                if (neighbors == 3) {
                    sandbox[row][col].alive = true;
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


    void MainWindow::OnClearBoard(wxCommandEvent& event) {
        
        for (int row = 0; row < gridSize; row++) {
            for (int col = 0; col < gridSize; col++) {
                gameBoard[row][col].alive = false;
            }
        }

       
        generation = 0;
        livingCells = 0;

        
        UpdateStatusBar();

        
        drawingPanel->Refresh();
    }

    

