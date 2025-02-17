#include "MainWindow.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::OnSizeChange)
wxEND_EVENT_TABLE()
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