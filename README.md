========================================================================
       PANDUAN KHUSUS: CARA MENGAMBIL & UPLOAD KODE ARDUINO (BRANCH MAIN)
========================================================================

Jika Anda adalah tim penguji atau divisi hardware yang hanya ingin fokus 
mengambil dan menjalankan kodingan komponen IoT/Mikrokontroler:

------------------------------------------------------------------------
LANGKAH 1: DOWNLOAD & SHIFT KE JALUR ARDUINO (GIT BASH)
------------------------------------------------------------------------
1. Buka terminal Git Bash di komputer Anda, lalu unduh repositori:
   $ git clone https://github.com/febrypradana/Smart-tongkat-tunanetra_Berbasis-web.git
   $ cd Smart-tongkat-tunanetra_Berbasis-web

2. Perbarui indeks data agar laptop mengenali seluruh branch dari server:
   $ git fetch origin

3. Berpindah jalur secara khusus ke komponen HARDWARE & ARDUINO:
   $ git checkout main

   *Catatan: Setelah perintah ini dieksekusi, seluruh isi file di folder 
   lokal komputer Anda otomatis berubah total menjadi berkas kodingan 
   Arduino (.ino) yang dikerjakan oleh M. Khoirul Aminin & Nanda Firstyanto.

   ------------------------------------------------------------------------
LANGKAH 2: KONFIGURASI DAN UPLOAD ALAT (ARDUINO IDE)
------------------------------------------------------------------------
1. Hubungkan mikrokontroler Smart Tongkat ke Port USB laptop Anda menggunakan 
   kabel data bawaan.

2. Jalankan aplikasi ARDUINO IDE, lalu buka file kodingan utama (.ino) 
   yang berada di dalam folder proyek tadi.

3. Atur spesifikasi perangkat pada menu bar atas Arduino IDE:
   - Pilih Board  : Tools -> Board -> Arduino Uno / Nano (Sesuaikan alat)
   - Pilih Port   : Tools -> Port -> COM3 (Pilih Port 3)

4. Proses Pengiriman Kode:
   - Klik tombol "Verify" (Simbol Centang) untuk memastikan kompilasi aman.
   - Klik tombol "Upload" (Simbol Panah Kanan) untuk meng-inject kodingan 
     langsung ke sirkuit tongkat tunanetra.

------------------------------------------------------------------------
LANGKAH 3: VERIFIKASI FUNGSIONAL HARDWARE TONGKAT
------------------------------------------------------------------------
Setelah proses upload sukses, sistem hardware pada samakan dengan port yang                                                ada di laptop kalian akan langsung aktif dan siap merespons rintangan (Sensor
Kiri, Depan, Kanan) melalui bunyi Buzzer, kedipan LED, serta menampilkan status
pada LCD I2C.
========================================================================
