#pragma once
#include <string>

// Arac bilgilerini tutan yapi
struct Arac {
    int numara = 0;
    std::string marka;
    std::string model;
    double gunlukUcret = 0.0;
    bool kiralandi = false;  // false: musait, true: kiralandi
    int kiralamaGunu = 0;    // kiralandiysa kac gunluk kiralandigi
};
