#include "SettingsDialog.h"

wxBEGIN_EVENT_TABLE(SettingsDialog, wxDialog)
EVT_BUTTON(wxID_OK, SettingsDialog::OnOK)
EVT_BUTTON(wxID_CANCEL, SettingsDialog::OnCancel)
wxEND_EVENT_TABLE()

SettingsDialog::SettingsDialog(wxWindow* parent, Settings* settingsPtr)
    : wxDialog(parent, wxID_ANY, "Settings", wxDefaultPosition, wxSize(300, 250)), settings(settingsPtr) {

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    
    wxBoxSizer* gridSizeSizer = new wxBoxSizer(wxHORIZONTAL);
    gridSizeSizer->Add(new wxStaticText(this, wxID_ANY, "Grid Size:"), 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    gridSizeCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(60, -1),
        wxSP_ARROW_KEYS, 5, 100, settings->gridSize);
    gridSizeSizer->Add(gridSizeCtrl, 1, wxALL, 5);
    mainSizer->Add(gridSizeSizer, 0, wxEXPAND | wxALL, 5);

    
    wxBoxSizer* intervalSizer = new wxBoxSizer(wxHORIZONTAL);
    intervalSizer->Add(new wxStaticText(this, wxID_ANY, "Interval (ms):"), 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    intervalCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(60, -1),
        wxSP_ARROW_KEYS, 10, 500, settings->interval);
    intervalSizer->Add(intervalCtrl, 1, wxALL, 5);
    mainSizer->Add(intervalSizer, 0, wxEXPAND | wxALL, 5);

    
    wxBoxSizer* livingColorSizer = new wxBoxSizer(wxHORIZONTAL);
    livingColorSizer->Add(new wxStaticText(this, wxID_ANY, "Living Cell Color:"), 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    livingCellColorCtrl = new wxColourPickerCtrl(this, wxID_ANY, settings->GetLivingColor());
    livingColorSizer->Add(livingCellColorCtrl, 1, wxALL, 5);
    mainSizer->Add(livingColorSizer, 0, wxEXPAND | wxALL, 5);

    
    wxBoxSizer* deadColorSizer = new wxBoxSizer(wxHORIZONTAL);
    deadColorSizer->Add(new wxStaticText(this, wxID_ANY, "Dead Cell Color:"), 1, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    deadCellColorCtrl = new wxColourPickerCtrl(this, wxID_ANY, settings->GetDeadColor());
    deadColorSizer->Add(deadCellColorCtrl, 1, wxALL, 5);
    mainSizer->Add(deadColorSizer, 0, wxEXPAND | wxALL, 5);

    
    mainSizer->Add(CreateButtonSizer(wxOK | wxCANCEL), 0, wxEXPAND | wxALL, 10);

    SetSizerAndFit(mainSizer);
}


void SettingsDialog::OnOK(wxCommandEvent& event) {
    settings->gridSize = gridSizeCtrl->GetValue();
    settings->interval = intervalCtrl->GetValue();
    settings->SetLivingColor(livingCellColorCtrl->GetColour());
    settings->SetDeadColor(deadCellColorCtrl->GetColour());

    EndModal(wxID_OK);
}


void SettingsDialog::OnCancel(wxCommandEvent& event) {
    EndModal(wxID_CANCEL);
}
