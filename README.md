# Araç Kiralama Sistemi

![build](https://github.com/ysufkaratepe/arac-kiralama/actions/workflows/build.yml/badge.svg)

C++ ile yazılmış, konsolda çalışan bir araç kiralama yönetim sistemi. Araç ekleme, kiralama, iade ve arama işlemlerini yapar; veriler program kapandığında dosyaya kaydedilir.

```
===== ARAC KIRALAMA SISTEMI =====
1. Arac Ekle
2. Tum Araclari Listele
3. Musait Araclari Listele
4. Markaya Gore Ara
5. Arac Kirala
6. Arac Iade Et
7. Arac Sil
8. Kiradaki Araclarin Toplam Geliri
0. Kaydet ve Cik
Seciminiz: 2
No    Marka         Model         Gunluk (TL)   Durum
--------------------------------------------------------
1     Land Rover    Defender      2500.00       Kiralandi (3 gun)
2     Fiat          Egea          1500.00       Musait
```

## Özellikler

- Araç ekleme, silme, kiralama ve iade
- Tüm araçları veya sadece müsait olanları tablo halinde listeleme
- Markaya göre arama (büyük/küçük harf duyarsız)
- Kiradaki araçlardan beklenen toplam geliri hesaplama
- Verilerin `araclar.txt` dosyasına kaydedilmesi ve açılışta geri yüklenmesi
- Hatalı girişe karşı kontrol: sayı yerine harf girilirse program çökmez, tekrar sorar
- Boşluk içeren marka/model desteği (ör. "Land Rover")
- Birim testleri ve GitHub Actions ile Windows, Linux ve macOS'ta otomatik derleme

## Derleme ve çalıştırma

**g++ ile:**

```bash
g++ -std=c++17 -Iinclude src/*.cpp -o arac_kiralama
./arac_kiralama
```

**CMake ile:**

```bash
cmake -B build
cmake --build build
ctest --test-dir build --output-on-failure   # testleri çalıştırır
```

## Proje yapısı

```
include/
  Arac.hpp            Araç bilgilerini tutan yapı
  AracKiralama.hpp    Araçları yöneten sınıf
src/
  AracKiralama.cpp    İş kuralları ve dosya işlemleri
  main.cpp            Menü ve kullanıcı etkileşimi
tests/
  test_arac_kiralama.cpp
```

İş kuralları (`AracKiralama` sınıfı) ekrana yazmaz ve klavyeden okumaz; sonuçları `Sonuc` yapısıyla döndürür. Menü ve giriş/çıkış `main.cpp` içindedir. Bu ayrım sayesinde kurallar testlerle doğrudan kontrol edilebiliyor.

## Kullanılanlar

C++17 · STL (`vector`, `algorithm`, `fstream`) · CMake · GitHub Actions

## Geliştirici

**Yusuf Karatepe**, Bilgisayar Mühendisliği öğrencisi
[LinkedIn](https://www.linkedin.com/in/yusuf-karatepe-0720923a1/) · [GitHub](https://github.com/ysufkaratepe)
