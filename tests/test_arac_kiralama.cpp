// AracKiralama sinifi icin basit testler.
// Calistirma: ctest  veya  ./test_arac_kiralama

#include <cstdio>
#include <iostream>
#include <string>

#include "AracKiralama.hpp"

static int hatalar = 0;

static void kontrol(bool kosul, const std::string& ad) {
    std::cout << (kosul ? "[GECTI] " : "[KALDI] ") << ad << "\n";
    if (!kosul) hatalar++;
}

int main() {
    const std::string testDosyasi = "test_araclar.txt";
    std::remove(testDosyasi.c_str());

    {
        AracKiralama s(testDosyasi);
        kontrol(s.aracEkle(1, "Fiat", "Egea", 1500).basarili, "arac eklenir");
        kontrol(!s.aracEkle(1, "Renault", "Clio", 1200).basarili, "ayni numara ikinci kez eklenemez");
        kontrol(!s.aracEkle(2, "Fiat", "Egea", 0).basarili, "ucret sifir olamaz");
        kontrol(!s.aracEkle(3, "", "Egea", 1000).basarili, "marka bos olamaz");
        kontrol(!s.aracEkle(4, "Fi;at", "Egea", 1000).basarili, "';' iceren marka reddedilir");
        kontrol(s.aracEkle(5, "Land Rover", "Defender", 5000).basarili, "bosluklu marka eklenir");
        kontrol(s.araclar().size() == 2, "iki arac kayitli");

        double toplam = 0;
        kontrol(s.aracKirala(1, 3, toplam).basarili && toplam == 4500, "kiralama ucreti gun x ucret");
        kontrol(!s.aracKirala(1, 2, toplam).basarili, "kiradaki arac tekrar kiralanamaz");
        kontrol(!s.aracKirala(5, 0, toplam).basarili, "0 gunluk kiralama reddedilir");
        kontrol(!s.aracKirala(99, 1, toplam).basarili, "olmayan arac kiralanamaz");
        kontrol(s.musaitAraclar().size() == 1, "musait arac sayisi dogru");
        kontrol(s.kiradakiToplamGelir() == 4500, "kiradaki toplam gelir dogru");
        kontrol(!s.aracSil(1).basarili, "kiradaki arac silinemez");

        kontrol(s.markayaGoreAra("land").size() == 1, "marka aramasi buyuk/kucuk harf duyarsiz");
        kontrol(s.markayaGoreAra("bmw").empty(), "olmayan marka bos sonuc verir");

        kontrol(s.kaydet(), "dosyaya kaydedilir");
    }

    {
        AracKiralama s(testDosyasi);
        kontrol(s.yukle(), "dosyadan yuklenir");
        kontrol(s.araclar().size() == 2, "yuklenen arac sayisi dogru");
        kontrol(s.araclar()[1].marka == "Land Rover", "bosluklu marka korunur");
        kontrol(s.araclar()[0].kiralandi && s.araclar()[0].kiralamaGunu == 3, "kiralama durumu korunur");

        kontrol(s.aracIadeEt(1).basarili, "arac iade edilir");
        kontrol(!s.aracIadeEt(1).basarili, "musait arac iade edilemez");
        kontrol(s.aracSil(1).basarili && s.araclar().size() == 1, "iade edilen arac silinir");
    }

    {
        AracKiralama s("olmayan_dosya_123.txt");
        kontrol(!s.yukle() && s.araclar().empty(), "dosya yoksa bos baslar");
    }

    std::remove(testDosyasi.c_str());
    std::cout << (hatalar == 0 ? "\nTum testler gecti.\n" : "\nBazi testler kaldi!\n");
    return hatalar == 0 ? 0 : 1;
}
