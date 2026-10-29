#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "AracKiralama.hpp"

using namespace std;

// Kullanici sayi yerine harf girerse programin cokmemesi icin tekrar sorar.
int tamSayiOku(const string& soru) {
    int deger;
    while (true) {
        cout << soru;
        if (cin >> deger) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return deger;
        }
        if (cin.eof()) exit(0);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Lutfen gecerli bir sayi girin." << endl;
    }
}

double ondalikOku(const string& soru) {
    double deger;
    while (true) {
        cout << soru;
        if (cin >> deger) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return deger;
        }
        if (cin.eof()) exit(0);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Lutfen gecerli bir sayi girin." << endl;
    }
}

// Bosluklu metinleri de okur (or. "Land Rover")
string satirOku(const string& soru) {
    string deger;
    cout << soru;
    getline(cin, deger);
    return deger;
}

void tabloYazdir(const vector<Arac>& liste) {
    if (liste.empty()) {
        cout << "Gosterilecek arac yok." << endl;
        return;
    }
    cout << left << setw(6) << "No" << setw(14) << "Marka" << setw(14) << "Model" << setw(14)
         << "Gunluk (TL)" << "Durum" << endl;
    cout << string(56, '-') << endl;
    for (const Arac& a : liste) {
        cout << left << setw(6) << a.numara << setw(14) << a.marka << setw(14) << a.model
             << setw(14) << fixed << setprecision(2) << a.gunlukUcret
             << (a.kiralandi ? "Kiralandi (" + to_string(a.kiralamaGunu) + " gun)" : "Musait")
             << endl;
    }
}

void sonucYazdir(const Sonuc& s) {
    cout << (s.basarili ? "" : "Hata: ") << s.mesaj << endl;
}

int main() {
    AracKiralama sistem;
    if (sistem.yukle()) {
        cout << sistem.araclar().size() << " arac dosyadan yuklendi." << endl;
    }

    int secim;
    do {
        cout << "\n===== ARAC KIRALAMA SISTEMI =====" << endl;
        cout << "1. Arac Ekle" << endl;
        cout << "2. Tum Araclari Listele" << endl;
        cout << "3. Musait Araclari Listele" << endl;
        cout << "4. Markaya Gore Ara" << endl;
        cout << "5. Arac Kirala" << endl;
        cout << "6. Arac Iade Et" << endl;
        cout << "7. Arac Sil" << endl;
        cout << "8. Kiradaki Araclarin Toplam Geliri" << endl;
        cout << "0. Kaydet ve Cik" << endl;
        secim = tamSayiOku("Seciminiz: ");

        switch (secim) {
            case 1: {
                int numara = tamSayiOku("Arac numarasi: ");
                string marka = satirOku("Marka: ");
                string model = satirOku("Model: ");
                double ucret = ondalikOku("Gunluk kiralama ucreti: ");
                sonucYazdir(sistem.aracEkle(numara, marka, model, ucret));
                break;
            }
            case 2:
                tabloYazdir(sistem.araclar());
                break;
            case 3:
                tabloYazdir(sistem.musaitAraclar());
                break;
            case 4:
                tabloYazdir(sistem.markayaGoreAra(satirOku("Aranacak marka: ")));
                break;
            case 5: {
                int numara = tamSayiOku("Kiralanacak arac numarasi: ");
                int gun = tamSayiOku("Kiralama suresi (gun): ");
                double toplam = 0;
                Sonuc s = sistem.aracKirala(numara, gun, toplam);
                sonucYazdir(s);
                if (s.basarili) cout << "Toplam ucret: " << fixed << setprecision(2) << toplam << " TL" << endl;
                break;
            }
            case 6:
                sonucYazdir(sistem.aracIadeEt(tamSayiOku("Iade edilecek arac numarasi: ")));
                break;
            case 7:
                sonucYazdir(sistem.aracSil(tamSayiOku("Silinecek arac numarasi: ")));
                break;
            case 8:
                cout << "Kiradaki araclardan beklenen gelir: " << fixed << setprecision(2)
                     << sistem.kiradakiToplamGelir() << " TL" << endl;
                break;
            case 0:
                if (sistem.kaydet())
                    cout << "Veriler kaydedildi. Programdan cikiliyor..." << endl;
                else
                    cout << "Uyari: Veriler kaydedilemedi!" << endl;
                break;
            default:
                cout << "Gecersiz secim!" << endl;
        }
    } while (secim != 0);

    return 0;
}
