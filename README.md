# Car Rental Management System

![build](https://github.com/ysufkaratepe/arac-kiralama/actions/workflows/build.yml/badge.svg)

A console-based car rental management system written in C++17. It handles adding, renting, returning and searching cars, and saves all data to a file when the program closes. It started as a course assignment and was extended afterwards.

> The program's menus are in Turkish.

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

## Features

- Add, remove, rent and return cars
- List all cars or only available ones in a table
- Search by brand (case-insensitive)
- Calculate the expected revenue from currently rented cars
- Data is saved to `araclar.txt` and loaded again on startup
- Input validation: entering letters instead of numbers doesn't crash the program, it asks again
- Brand and model names with spaces (e.g. "Land Rover")
- Unit tests and automated builds on Windows, Linux and macOS with GitHub Actions

## Build and run

**With g++:**

```bash
g++ -std=c++17 -Iinclude src/*.cpp -o arac_kiralama
./arac_kiralama
```

**With CMake:**

```bash
cmake -B build
cmake --build build
ctest --test-dir build --output-on-failure   # runs the tests
```

## Project structure

```
include/
  Arac.hpp            Car data structure
  AracKiralama.hpp    Class that manages the cars
src/
  AracKiralama.cpp    Business rules and file handling
  main.cpp            Menu and user interaction
tests/
  test_arac_kiralama.cpp
```

The business rules (`AracKiralama` class) never print to the screen or read from the keyboard; they return results in a `Sonuc` (result) struct. The menu and all input/output live in `main.cpp`. This separation makes it possible to test the rules directly.

## Tech

C++17 · STL (`vector`, `algorithm`, `fstream`) · CMake · GitHub Actions

## Author

**Yusuf Karatepe**, Computer Engineering student
[LinkedIn](https://www.linkedin.com/in/yusuf-karatepe-0720923a1/) · [GitHub](https://github.com/ysufkaratepe)
