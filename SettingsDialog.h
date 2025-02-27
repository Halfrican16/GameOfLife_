#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <wx/wx.h>
#include <wx/spinctrl.h>  
#include <wx/clrpicker.h> 
#include "Settings.h"

class SettingsDialog : public wxDialog {
public:
    SettingsDialog(wxWindow* parent, Settings* settings);

private:
    Settings* settings;

    
    wxSpinCtrl* gridSizeCtrl;
    wxSpinCtrl* intervalCtrl;
    wxColourPickerCtrl* livingCellColorCtrl;
    wxColourPickerCtrl* deadCellColorCtrl;

    
    void OnOK(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

#endif
