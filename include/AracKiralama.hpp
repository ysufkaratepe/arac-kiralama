#pragma once
#include <string>
#include <vector>

#include "Arac.hpp"

// Islem sonucunu ve kullaniciya gosterilecek mesaji birlikte tasir.
struct Sonuc {
    bool basarili;
    std::string mesaj;
};

// Araclari yoneten sinif.
// Ekrana yazma veya klavyeden okuma yapmaz; bu sayede test edilebilir.
// Menu ve kullanici etkilesimi main.cpp icindedir.
class AracKiralama {
public:
    explicit AracKiralama(std::string dosyaYolu = "araclar.txt");

    Sonuc aracEkle(int numara, const std::string& marka, const std::string& model, double gunlukUcret);
    Sonuc aracSil(int numara);
    Sonuc aracKirala(int numara, int gun, double& toplamUcret);
    Sonuc aracIadeEt(int numara);

    const std::vector<Arac>& araclar() const { return araclar_; }
    std::vector<Arac> musaitAraclar() const;
    std::vector<Arac> markayaGoreAra(const std::string& marka) const;

    // Su an kirada olan araclardan beklenen toplam gelir
    double kiradakiToplamGelir() const;

    // Dosyaya kaydetme / dosyadan yukleme. Basarisizsa false doner.
    bool kaydet() const;
    bool yukle();

private:
    // Numarasi verilen aracin dizideki yerini bulur, yoksa -1 dondurur
    int aracBul(int numara) const;

    std::vector<Arac> araclar_;
    std::string dosyaYolu_;
};
