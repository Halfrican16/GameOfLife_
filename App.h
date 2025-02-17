#pragma once

#include "wx/wx.h"
#include "MainWindow.h"

#include<wx/wx.h>

class App : public wxApp
{
private:
	MainWindow* mainWindow;

public:
	App();
	~App();
	virtual bool OnInit();
};

bool App::OnInit() {
	ENABLE_LEAK_DETECTION();
	MainWindow* mainWin = new MainWindow();
	mainWin->Show();
	return true;
}

