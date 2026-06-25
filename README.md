# Smart Tongkat Tunanetra Berbasis Web (Project Akhir) 👨‍🦯🤖

Repositori ini berisi kode sumber untuk proyek **Smart Tongkat Tunanetra Berbasis Web**. Pengembangan proyek ini dibagi menjadi dua komponen utama yang dikelola melalui percabangan (*branching*) Git secara terpisah untuk menjaga kerapian struktur kode.

---

## 📌 Struktur Percabangan (Branching)

Repositori ini memiliki dua branch utama dengan peran sebagai berikut:

### 1. 🌐 Branch: `master` (Web Dashboard)
Branch ini dikelola oleh **Nandana Febry Pradana** selaku Master/Owner, berisi kodingan aplikasi web berbasis **Node.js** untuk menampilkan dashboard monitoring data dari tongkat secara realtime.

**Struktur File (`Project_tongkat-web`):**
* `server.js` — File utama aplikasi backend Node.js / Express server.
* `views/index.html` — Tampilan antarmuka (frontend) dashboard web.
* `package.json` & `package-lock.json` — Konfigurasi dependensi dan modul proyek.
* `node_modules/` — Direktori library pihak ketiga yang diinstal.

### 2. 🔌 Branch: `main` (Hardware & Arduino)
Branch ini digunakan untuk kolaborasi pengembangan komponen perangkat keras (hardware) IoT menggunakan mikrokontroler Arduino, yang dikerjakan oleh **Mukhammad Khoirul Aminin** dan **Nanda Firstyanto Putra**.

**Fitur Hardware yang Diimplementasikan:**
* Integrasi lampu indikator LED & layar LCD.
* Pemrosesan data Sensor Ultrasonic untuk mendeteksi halangan di sisi samping kiri dan kanan tongkat.


## 📥 Cara Mengambil Kodingan dari Repositori Ini (Clone & Switch Branch)

Jika Anda ingin mengambil kodingan dari repositori ini, ikuti panduan berikut melalui terminal Git Bash:

------------------------------------------------------------------------
A. PROSES CLONE DAN SINKRONISASI REPOSITORI (GIT BASH)
------------------------------------------------------------------------
1. Unduh repositori utama dari GitHub ke direktori lokal laptop Anda:
   $ git clone https://github.com/febrypradana/Smart-tongkat-tunanetra_Berbasis-web.git
   $ cd Smart-tongkat-tunanetra_Berbasis-web

2. Ambil data indeks seluruh cabang agar Git lokal mengenali semua jalur:
   $ git fetch origin

3. Beralih ke komponen WEB DASHBOARD (Dikelola oleh Nandana Febry P.):
   $ git checkout master

4. Beralih ke komponen HARDWARE / ARDUINO (Dikelola oleh Tim IoT):
   $ git checkout main

------------------------------------------------------------------------
B. TAHAPAN MENJALANKAN APLIKASI WEB DASHBOARD (PADA BRANCH 'MASTER')
------------------------------------------------------------------------
*Pastikan Anda telah kembali ke branch master sebelum mengeksekusi ini*
$ git checkout master

1. Lakukan instalasi seluruh library/dependensi yang terdaftar di package.json:
   $ npm install

2. Eksekusi dan jalankan local server Node.js:
   $ node server.js

3. Buka peramban (Web Browser), lalu akses sistem melalui URL berikut:
   http://localhost:5000
