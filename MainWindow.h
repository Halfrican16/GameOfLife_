#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <wx/wx.h>
#include <wx/timer.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "DrawingPanel.h"
#include "Utilities.h"
#include "Settings.h"
#include "SettingsDialog.h"

#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"

class MainWindow : public wxFrame
{
public:

	MainWindow(); //Constructor
	~MainWindow(); //Destructor

    void UpdateStatusBar();
    int CountLivingNeighbors(int row, int col);
    void GenerateNextGeneration();
    void OnClearBoard(wxCommandEvent& event);
    void OnOpenSettings(wxCommandEvent& event);
    void OnToggleNeighborCount(wxCommandEvent& event);
    void OnRandomizeWithSeed(wxCommandEvent& event);
    void OnRandomize(wxCommandEvent& event);
   
   

private:
    std::vector<std::vector<Cell>> gameBoard;
    int gridSize = 15;
    std::vector<std::vector<int>> neighborCounts;

    DrawingPanel* drawingPanel;
    wxStatusBar* statusBar;
    wxToolBar* toolbar;
    wxMenuBar* menuBar;
    wxTimer* timer;
    
    int generation = 0;
    int livingCells = 0;
    int timerInterval = TIMER_INTERVAL;

    Settings settings;
    

    void initializeGrid();
   
    void OnSizeChange(wxSizeEvent& event);
    void OnNextGeneration(wxCommandEvent& event);
    void RandomizeGrid(unsigned int seed);

    void OnPlay(wxCommandEvent& event);
    void OnPause(wxCommandEvent& event);
    void OnNext(wxCommandEvent& event);
    void OnClear(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);

    wxDECLARE_EVENT_TABLE();

};

#endif