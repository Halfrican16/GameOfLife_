#include "App.h"

wxIMPLEMENT_APP(App);

App::App() {

}

App::~App() {

}

bool App::OnInit() {
	mainWindow = new MainWindow(); // Initiate the main window
	mainWindow->Show();            // Display the window
	return true;                   // Return true to start the main event loop

}