#include "AracKiralama.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iterator>
#include <sstream>
#include <utility>

namespace {

std::string kucukHarf(std::string s) {
    for (char& c : s) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return s;
}

}  // namespace

AracKiralama::AracKiralama(std::string dosyaYolu) : dosyaYolu_(std::move(dosyaYolu)) {}

int AracKiralama::aracBul(int numara) const {
    for (std::size_t i = 0; i < araclar_.size(); i++) {
        if (araclar_[i].numara == numara) return static_cast<int>(i);
    }
    return -1;
}

Sonuc AracKiralama::aracEkle(int numara, const std::string& marka, const std::string& model,
                             double gunlukUcret) {
    if (numara <= 0) return {false, "Arac numarasi pozitif olmali!"};
    if (marka.empty() || model.empty()) return {false, "Marka ve model bos olamaz!"};
    if (marka.find(';') != std::string::npos || model.find(';') != std::string::npos)
        return {false, "Marka ve model ';' karakteri iceremez!"};
    if (gunlukUcret <= 0) return {false, "Gunluk ucret sifirdan buyuk olmali!"};
    if (aracBul(numara) != -1) return {false, "Bu numarada bir arac zaten var!"};

    Arac yeni;
    yeni.numara = numara;
    yeni.marka = marka;
    yeni.model = model;
    yeni.gunlukUcret = gunlukUcret;
    araclar_.push_back(yeni);
    return {true, "Arac basariyla eklendi."};
}

Sonuc AracKiralama::aracSil(int numara) {
    int i = aracBul(numara);
    if (i == -1) return {false, "Bu numarada arac bulunamadi!"};
    if (araclar_[i].kiralandi) return {false, "Kiradaki bir arac silinemez, once iade edin!"};

    araclar_.erase(araclar_.begin() + i);
    return {true, "Arac silindi."};
}

Sonuc AracKiralama::aracKirala(int numara, int gun, double& toplamUcret) {
    toplamUcret = 0;
    int i = aracBul(numara);
    if (i == -1) return {false, "Bu numarada arac bulunamadi!"};
    if (araclar_[i].kiralandi) return {false, "Bu arac zaten kiralanmis!"};
    if (gun <= 0) return {false, "Gecersiz gun sayisi!"};

    // Toplam ucret = gun sayisi x gunluk ucret
    toplamUcret = gun * araclar_[i].gunlukUcret;
    araclar_[i].kiralandi = true;
    araclar_[i].kiralamaGunu = gun;
    return {true, araclar_[i].marka + " " + araclar_[i].model + " " + std::to_string(gun) +
                      " gunlugune kiralandi."};
}

Sonuc AracKiralama::aracIadeEt(int numara) {
    int i = aracBul(numara);
    if (i == -1) return {false, "Bu numarada arac bulunamadi!"};
    if (!araclar_[i].kiralandi) return {false, "Bu arac zaten musait, iade edilemez!"};

    araclar_[i].kiralandi = false;
    araclar_[i].kiralamaGunu = 0;
    return {true, "Arac iade edildi, tekrar musait."};
}

std::vector<Arac> AracKiralama::musaitAraclar() const {
    std::vector<Arac> sonuc;
    std::copy_if(araclar_.begin(), araclar_.end(), std::back_inserter(sonuc),
                 [](const Arac& a) { return !a.kiralandi; });
    return sonuc;
}

std::vector<Arac> AracKiralama::markayaGoreAra(const std::string& marka) const {
    std::vector<Arac> sonuc;
    const std::string aranan = kucukHarf(marka);
    for (const Arac& a : araclar_) {
        if (kucukHarf(a.marka).find(aranan) != std::string::npos) sonuc.push_back(a);
    }
    return sonuc;
}

double AracKiralama::kiradakiToplamGelir() const {
    double toplam = 0;
    for (const Arac& a : araclar_) {
        if (a.kiralandi) toplam += a.kiralamaGunu * a.gunlukUcret;
    }
    return toplam;
}

// Dosya bicimi: her satirda bir arac, alanlar ';' ile ayrilir
// numara;marka;model;gunlukUcret;kiralandi;kiralamaGunu
bool AracKiralama::kaydet() const {
    std::ofstream dosya(dosyaYolu_);
    if (!dosya) return false;

    for (const Arac& a : araclar_) {
        dosya << a.numara << ';' << a.marka << ';' << a.model << ';' << a.gunlukUcret << ';'
              << (a.kiralandi ? 1 : 0) << ';' << a.kiralamaGunu << '\n';
    }
    return static_cast<bool>(dosya);
}

bool AracKiralama::yukle() {
    std::ifstream dosya(dosyaYolu_);
    if (!dosya) return false;  // dosya yoksa ilk calistirmadir

    std::vector<Arac> okunan;
    std::string satir;
    while (std::getline(dosya, satir)) {
        if (satir.empty()) continue;

        std::stringstream ss(satir);
        std::string numara, marka, model, ucret, kiralandi, gun;
        if (!std::getline(ss, numara, ';') || !std::getline(ss, marka, ';') ||
            !std::getline(ss, model, ';') || !std::getline(ss, ucret, ';') ||
            !std::getline(ss, kiralandi, ';') || !std::getline(ss, gun)) {
            continue;  // bozuk satiri atla
        }

        try {
            Arac a;
            a.numara = std::stoi(numara);
            a.marka = marka;
            a.model = model;
            a.gunlukUcret = std::stod(ucret);
            a.kiralandi = (kiralandi == "1");
            a.kiralamaGunu = std::stoi(gun);
            okunan.push_back(a);
        } catch (...) {
            continue;  // sayiya cevrilemeyen satiri atla
        }
    }

    araclar_ = std::move(okunan);
    return true;
}
