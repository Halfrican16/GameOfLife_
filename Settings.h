#ifndef SETTINGS_H
#define SETTINGS_H

#include <wx/wx.h>
#include <fstream>

struct Settings {
    
    int gridSize = 15;

    
    int interval = 50;

    bool showNeighborCount = false;

    
    unsigned int livingRed = 128;
    unsigned int livingGreen = 128;
    unsigned int livingBlue = 128;
    unsigned int livingAlpha = 255;

    
    unsigned int deadRed = 255;
    unsigned int deadGreen = 255;
    unsigned int deadBlue = 255;
    unsigned int deadAlpha = 255;

    
    wxColor GetLivingColor() const {
        return wxColor(livingRed, livingGreen, livingBlue, livingAlpha);
    }

    
    wxColor GetDeadColor() const {
        return wxColor(deadRed, deadGreen, deadBlue, deadAlpha);
    }

    
    void SetLivingColor(const wxColor& color) {
        livingRed = color.Red();
        livingGreen = color.Green();
        livingBlue = color.Blue();
        livingAlpha = color.Alpha();
    }

    
    void SetDeadColor(const wxColor& color) {
        deadRed = color.Red();
        deadGreen = color.Green();
        deadBlue = color.Blue();
        deadAlpha = color.Alpha();
    }

    void SaveSettings(const std::string& filename = "settings.dat") {
        std::ofstream file(filename, std::ios::binary);
        if (file.is_open()) {
            file.write(reinterpret_cast<char*>(this), sizeof(Settings));
            file.close();
        }
    }

    void LoadSettings(const std::string& filename = "settings.dat") {
        std::ifstream file(filename, std::ios::binary);
        if (file.is_open()) {
            file.read(reinterpret_cast<char*>(this), sizeof(Settings));
            file.close();
        }
    }
};

#endif
