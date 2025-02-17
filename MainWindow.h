#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <wx/wx.h>
#include <vector>
#include "DrawingPanel.h"

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

private:
    std::vector<std::vector<bool>> gameBoard;
    int gridSize = 15;

    DrawingPanel* drawingPanel;
    wxStatusBar* statusBar;
    wxToolBar* toolbar;
    
    int generation = 0;
    int livingCells = 0;

    
    
    

    void initializeGrid();
   
    void OnSizeChange(wxSizeEvent& event);

    void OnPlay(wxCommandEvent& event);
    void OnPause(wxCommandEvent& event);
    void OnNext(wxCommandEvent& event);
    void OnClear(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();

};

#endif