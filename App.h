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

