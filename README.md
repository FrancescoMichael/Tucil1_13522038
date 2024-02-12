# Tucil1_13522038
Tugas Kecil 1 IF2211 Strategi Algoritma Semester II tahun 2023/2024 
Penyelesaian Cyberpunk 2077 Breach Protocol dengan Algoritma Brute Force

## Problem Description
Cyberpunk 2077 Breach Protocol adalah minigame meretas pada permainan video Cyberpunk 2077.
Minigame ini merupakan simulasi peretasan jaringan local dari ICE (Intrusion Countermeasures
Electronics) pada permainan Cyberpunk 2077. Komponen pada permainan ini antara lain adalah:
1. Token – terdiri dari dua karakter alfanumerik seperti E9, BD, dan 55.
2. Matriks – terdiri atas token-token yang akan dipilih untuk menyusun urutan kode.
3. Sekuens – sebuah rangkaian token (dua atau lebih) yang harus dicocokkan.
4. Buffer – jumlah maksimal token yang dapat disusun secara sekuensial.

Aturan permainan Breach Protocol antara lain:
1. Pemain bergerak dengan pola horizontal, vertikal, horizontal, vertikal (bergantian) hingga
semua sekuens berhasil dicocokkan atau buffer penuh.
2. Pemain memulai dengan memilih satu token pada posisi baris paling atas dari matriks.
3. Sekuens dicocokkan pada token-token yang berada di buffer.
4. Satu token pada buffer dapat digunakan pada lebih dari satu sekuens.
5. Setiap sekuens memiliki bobot hadiah atau reward yang variatif.
6. Sekuens memiliki panjang minimal berupa dua token.

Program ini bertugas untuk menemukan solusi dari permainan Breach Protocol yang paling optimal untuk
setiap kombinasi matriks, sekuens, dan ukuran buffer dengan menggunakan algoritma brute force.


## Technologies Used
C++ versi 13.2.0

## Usage
Jalankan perintah berikut
```
git clone https://github.com/FrancescoMichael/Tucil1_13522038.git
cd Tucil1_13522038
g++ ./src/main.cpp -o ./bin/main.exe
./bin/main.exe
```
## Identity
Francesco Michael Kusuma - 13522038