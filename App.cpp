#include "App.h"
#include "Utilities.h"

#include<wx/wx.h>

App::App() {

}

App::~App() {

}

bool App::OnInit() {
	ENABLE_LEAK_DETECTION();
	mainWindow = new MainWindow(); // Initiate the main window
	mainWindow->Show();            // Display the window
	return true;                   // Return true to start the main event loop

}