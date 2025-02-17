#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <wx/wx.h>
#include<wx/timer.h>
#include <vector>
#include "DrawingPanel.h"
#include "Utilities.h"

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

private:
    std::vector<std::vector<Cell>> gameBoard;
    int gridSize = 15;

    DrawingPanel* drawingPanel;
    wxStatusBar* statusBar;
    wxToolBar* toolbar;
    wxTimer* timer;
    
    int generation = 0;
    int livingCells = 0;
    int timerInterval = TIMER_INTERVAL;
    

    void initializeGrid();
   
    void OnSizeChange(wxSizeEvent& event);
    void OnNextGeneration(wxCommandEvent& event);

    void OnPlay(wxCommandEvent& event);
    void OnPause(wxCommandEvent& event);
    void OnNext(wxCommandEvent& event);
    void OnClear(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);

    wxDECLARE_EVENT_TABLE();

};

#endif