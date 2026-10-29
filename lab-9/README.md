# MODUL 9 — File dan Direktori; Permission, Link, Stream, dan Pipe

## Daftar Isi

**[Bagian I — File dan Direktori](#bagian-1)**
- [I.1 Pengantar Praktikum](#i-1)
- [I.2 Materi Inti](#i-2)
  - [I.2.1 Konsep File](#i-2-1)
  - [I.2.2 Struktur Direktori dan Path](#i-2-2)
  - [I.2.3 Identifikasi dan Navigasi: `file`, `pwd`, `cd`](#i-2-3)
  - [I.2.4 Menampilkan Isi Direktori: `ls`](#i-2-4)
  - [I.2.5 Membuat dan Memperbarui: `touch`, `mkdir`](#i-2-5)
  - [I.2.6 Menyalin, Memindahkan, dan Menghapus: `cp`, `mv`, `rm`, `rmdir`](#i-2-6)
  - [I.2.7 Menampilkan Struktur Direktori: `tree`](#i-2-7)
  - [I.2.8 Dotfile dan Simbol Direktori Khusus](#i-2-8)
- [I.3 Lembar Kerja Praktikum (LKP) — Bagian I](#i-3)

**[Bagian II — Permission, Link, Stream, dan Pipe](#bagian-2)**
- [II.1 Pengantar Praktikum](#ii-1)
- [II.2 Materi Inti](#ii-2)
  - [II.2.1 Kepemilikan dan Notasi Hak Akses Berkas](#ii-2-1)
  - [II.2.2 Perintah `chown` dan `chmod`](#ii-2-2)
  - [II.2.3 Contoh Penerapan `chmod`](#ii-2-3)
  - [II.2.4 Pengayaan: Bit Setuid dan Sticky Bit](#ii-2-4)
  - [II.2.5 Hard Link dan Symbolic Link](#ii-2-5)
  - [II.2.6 Inode: Struktur Data di Balik Sebuah Berkas](#ii-2-6)
  - [II.2.7 Stream Standar Proses](#ii-2-7)
  - [II.2.8 Pipe: Komunikasi Antarproses](#ii-2-8)
  - [II.2.9 Redirection I/O](#ii-2-9)
- [II.3 Praktik: Permission, Link, dan Pipe pada Terminal](#ii-3)
- [II.4 Latihan](#ii-4)
- [II.5 Lembar Kerja Praktikum (LKP) — Bagian II](#ii-5)

**[Referensi](#referensi)**

---

<a id="bagian-1"></a>

# BAGIAN I — FILE DAN DIREKTORI

*Pertemuan ke-9: File dan Direktori*

> **Tujuan Praktikum**
>
> 1. Memahami konsep *file* dan direktori, atribut dasarnya, serta struktur direktori bertingkat (*tree-structured directory*) pada sistem operasi berbasis Unix/Linux.
> 2. Membedakan *path absolute* dan *relative*, serta memahami makna simbol direktori khusus `~`, `.`, `..`, dan `/`.
> 3. Menerapkan perintah dasar *shell* untuk mengelola *file* dan direktori: `pwd`, `cd`, `ls`, `touch`, `mkdir`, `cp`, `mv`, `rm`, `rmdir`, dan `tree`.

<a id="i-1"></a>

## I.1 Pengantar Praktikum

Modul ini melanjutkan Modul 8 (Pengenalan *Command Line Interface*) dengan berfokus pada bagaimana pengguna berinteraksi dengan *file* dan direktori melalui *shell*. Hampir seluruh aktivitas pada sistem operasi—menjalankan program, menyimpan data, mengonfigurasi aplikasi—pada akhirnya melibatkan operasi terhadap *file* dan direktori. Oleh karena itu, penguasaan perintah dasar manajemen *file* menjadi keterampilan fundamental sebelum mempelajari topik lanjutan seperti hak akses (*permission*), *pipe*, dan pemrosesan teks pada modul-modul berikutnya.

Pada praktikum ini, mahasiswa akan mempelajari konsep *file* dan direktori secara teoretis, kemudian mempraktikkan sepuluh perintah dasar *shell* untuk membuat, menampilkan, menyalin, memindahkan, dan menghapus *file* maupun direktori, serta memahami *dotfile* dan simbol direktori khusus. Hasil praktik ditulis pada Lembar Kerja Praktikum (LKP) di Bagian I.3.

> **Catatan Penting**
>
> Buku acuan utama praktikum ini adalah Silberschatz, Galvin, dan Gagne, *Operating System Concepts*, edisi ke-10 (2018), khususnya Bab 11 (*File-System Interface*). Slide kuliah pada topik ini hanya memuat sintaks perintah secara ringkas tanpa nomor halaman kutipan tertentu; penjelasan konsep *file*, direktori, dan *path* pada modul ini dilengkapi dari buku tersebut agar dapat dipelajari secara mandiri.

<a id="i-2"></a>

## I.2 Materi Inti

<a id="i-2-1"></a>

### I.2.1 Konsep File

*File* adalah kumpulan informasi berkait (*related information*) yang diberi nama dan disimpan secara persisten pada media penyimpanan sekunder.¹ Bagi pengguna, *file* adalah unit penyimpanan logis terkecil yang dapat berisi program, data teks, gambar, maupun data biner lainnya; sistem operasi menyembunyikan detail bagaimana data tersebut sesungguhnya disusun pada *disk* (dalam bentuk *block* atau *sector*) dan menyediakan pandangan logis berupa *file* yang dapat diberi nama serta diakses melalui sejumlah operasi standar.

Setiap *file* memiliki sejumlah atribut yang dikelola oleh sistem operasi, di antaranya:

- **Nama** (*name*): identitas *file* yang dipahami manusia, misalnya `catatan.txt`.
- **Identifier**: nomor unik (biasanya *inode number* pada sistem berkas Unix/Linux) yang mengidentifikasi *file* di dalam sistem berkas.
- **Tipe**: jenis *file*, misalnya *file* biasa (*regular file*), direktori, atau *symbolic link*.
- **Lokasi**: penunjuk ke lokasi *file* pada perangkat penyimpanan.
- **Ukuran**: ukuran *file* saat ini dalam satuan *byte*.
- **Proteksi**: informasi kontrol akses yang menentukan siapa saja yang boleh membaca, menulis, atau mengeksekusi *file*.
- **Waktu, tanggal, dan identitas pengguna**: informasi kapan *file* dibuat, terakhir diubah (*modify*), dan terakhir diakses (*access*), beserta identitas pemiliknya.

Sistem operasi menyediakan sejumlah operasi dasar terhadap *file*, yaitu *create* (membuat), *open* (membuka), *read* (membaca), *write* (menulis), *reposition* (memindahkan penunjuk baca/tulis), *delete* (menghapus), dan *truncate* (mengosongkan isi tanpa menghapus *file*). Pada praktikum ini, operasi-operasi tersebut tidak diakses melalui pustaka bahasa C secara langsung, melainkan melalui perintah *shell* yang pada akhirnya juga memanggil *system call* yang sama di balik layar (misalnya `touch` yang pada dasarnya memanggil operasi *create*/*update timestamp*).

¹ Silberschatz *et al.* (2018), *Operating System Concepts*, Bab 11 (*File-System Interface*).

<a id="i-2-2"></a>

### I.2.2 Struktur Direktori dan Path

Direktori (*directory*) adalah *file* khusus yang berfungsi sebagai wadah untuk mengelompokkan dan mengatur *file-file* lain, serta memetakan nama *file* ke informasi lokasinya. Hampir seluruh sistem operasi modern, termasuk Linux, menggunakan struktur direktori bertingkat (*tree-structured directory*): terdapat satu direktori *root* sebagai akar pohon, dan setiap direktori dapat memiliki sejumlah subdirektori serta *file* di dalamnya, membentuk hierarki menyerupai pohon terbalik. Struktur ini memungkinkan pengguna mengelompokkan *file* yang berkaitan ke dalam direktori yang sama, serta memisahkan *file* milik pengguna yang berbeda ke dalam direktori *home* masing-masing.

Untuk merujuk ke sebuah *file* atau direktori di dalam hierarki tersebut, digunakan *path name* yang terdiri atas dua jenis:

- **Absolute path**: dituliskan lengkap mulai dari direktori *root* (`/`), sehingga selalu merujuk ke lokasi yang sama tidak peduli di direktori mana pengguna sedang berada. Contoh: `/etc`.
- **Relative path**: dituliskan relatif terhadap direktori kerja saat ini (*current working directory*), sehingga hasilnya bergantung pada posisi pengguna saat perintah dijalankan. Contoh: `../etc`.

Setiap proses pada sistem operasi memiliki satu direktori kerja saat ini yang menjadi acuan bagi *relative path*; direktori ini dapat dilihat dengan perintah `pwd` dan diubah dengan perintah `cd`, sebagaimana akan dibahas pada Subbagian I.2.3.

<a id="i-2-3"></a>

### I.2.3 Identifikasi dan Navigasi: `file`, `pwd`, `cd`

Sebelum mengelola isi sebuah *file*, pengguna sering perlu mengetahui jenis *file* tersebut serta memastikan posisinya di dalam struktur direktori. Tiga perintah berikut digunakan untuk keperluan tersebut.

Perintah `file` menentukan jenis suatu *file* berdasarkan isinya (bukan hanya dari ekstensi nama *file*), misalnya apakah *file* tersebut berupa teks ASCII, *binary executable*, gambar, atau direktori.

```bash
file FILE...
```

Perintah `pwd` (*print working directory*) mencetak *absolute path* dari direktori kerja saat ini.

```bash
pwd
```

Perintah `cd` (*change directory*) mengganti direktori kerja saat ini. Jika dijalankan tanpa argumen, `cd` akan berpindah ke direktori *home* pengguna.

```bash
cd [DIR]
```

<a id="i-2-4"></a>

### I.2.4 Menampilkan Isi Direktori: `ls`

Perintah `ls` menampilkan daftar isi suatu direktori (atau informasi suatu *file*). Tanpa argumen, `ls` menampilkan isi direktori kerja saat ini.

```bash
ls [OPTION] [FILE]
```

Beberapa opsi `ls` yang sering dipakai dirangkum pada Tabel I.1.

**Tabel I.1:** Opsi umum perintah `ls`

| Opsi | Kepanjangan | Keterangan |
|------|-------------|------------|
| `-a` | *all* | Menampilkan seluruh *file*, termasuk *dotfile* yang tersembunyi. |
| `-l` | *long* | Menampilkan *file* dalam format panjang (*permission*, pemilik, ukuran, waktu modifikasi). |
| `-h` | *human-readable* | Menampilkan ukuran *file* dalam format yang mudah dibaca manusia (KB, MB, GB). |
| `-i` | *inode* | Mencetak nomor *inode* tiap *file*. |

Opsi-opsi ini dapat digabungkan, misalnya `ls -lah` untuk menampilkan seluruh *file* (termasuk *dotfile*) dalam format panjang dengan ukuran *human-readable*.

<a id="i-2-5"></a>

### I.2.5 Membuat dan Memperbarui: `touch`, `mkdir`

Perintah `touch` meng-*update* waktu akses dan modifikasi suatu *file*. Jika *file* yang dirujuk belum ada, `touch` akan membuat *file* kosong dengan nama tersebut—inilah sebabnya `touch` sering dipakai sekadar untuk membuat *file* kosong.

```bash
touch FILE
```

Perintah `mkdir` (*make directory*) membuat direktori baru.

```bash
mkdir [OPTION] DIR
```

Opsi `-p` (*parent*) membuat seluruh direktori *parent* yang diperlukan sekaligus jika belum ada, sehingga `mkdir -p a/b/c` akan membuat direktori `a`, `a/b`, dan `a/b/c` dalam satu perintah meskipun `a` dan `a/b` sebelumnya belum ada.

<a id="i-2-6"></a>

### I.2.6 Menyalin, Memindahkan, dan Menghapus: `cp`, `mv`, `rm`, `rmdir`

Perintah `cp` menyalin *file* dan direktori ke lokasi tujuan.

```bash
cp [OPTION] SOURCE DEST
cp [OPTION] SOURCES... DIR
```

Opsi yang sering dipakai: `-r` (*recursive*, menyalin direktori beserta seluruh isinya), `-f` (*force*, menimpa *file* tujuan tanpa konfirmasi jika sudah ada), dan `-i` (*interactive*, meminta konfirmasi sebelum menimpa *file* tujuan).

Perintah `mv` memindahkan sekaligus dapat berfungsi mengganti nama *file*, karena secara logis mengganti nama juga berarti memindahkan *file* ke lokasi baru dengan nama berbeda pada direktori yang sama.

```bash
mv [OPTION] SOURCE DEST
mv [OPTION] SOURCES... DIR
```

Sama seperti `cp`, opsi `-f` akan menimpa *file* tujuan tanpa konfirmasi, sedangkan `-i` meminta konfirmasi terlebih dahulu.

Perintah `rm` menghapus *file* atau direktori.

```bash
rm [OPTION] FILE...
```

Opsi `-r` diperlukan untuk menghapus direktori beserta seluruh isinya secara *recursive*; `-f` memaksa penghapusan tanpa memunculkan galat/konfirmasi (misalnya untuk *file* yang tidak ada); dan `-i` meminta konfirmasi sebelum menghapus setiap *file*.

Perintah `rmdir` khusus menghapus direktori yang **kosong** saja; jika direktori berisi *file* atau subdirektori, `rmdir` akan menampilkan galat dan menolak menghapusnya (berbeda dengan `rm -r` yang menghapus tanpa syarat kekosongan).

```bash
rmdir [OPTION] DIR...
```

Opsi `-p` menghapus direktori beserta direktori *parent*-nya secara berurutan, selama direktori *parent* tersebut juga menjadi kosong setelah penghapusan.

#### Perbandingan `rm -r` dan `rmdir`

Perbedaan mendasar antara `rm -r` dan `rmdir` terletak pada syarat isi direktori: `rmdir` dirancang sebagai pengaman agar direktori yang masih berisi data tidak terhapus secara tidak sengaja, sedangkan `rm -r` akan menghapus direktori beserta seluruh isinya tanpa mempedulikan apakah direktori tersebut kosong atau tidak. Karena sifatnya yang destruktif dan sulit dibatalkan, `rm -r` (apalagi jika dikombinasikan dengan `-f`) harus digunakan dengan sangat hati-hati.

<a id="i-2-7"></a>

### I.2.7 Menampilkan Struktur Direktori: `tree`

Perintah `tree` menampilkan isi direktori dalam format pohon (*tree*) yang secara visual merepresentasikan hierarki direktori sebagaimana dijelaskan pada Subbagian I.2.2.

```bash
tree [OPTION] [DIR...]
```

Opsi `-L N` membatasi kedalaman level direktori yang ditampilkan hingga level ke-`N`, sedangkan `-h` menampilkan ukuran *file* dalam format *human-readable*, serupa dengan opsi `-h` pada `ls`.

<a id="i-2-8"></a>

### I.2.8 Dotfile dan Simbol Direktori Khusus

*File* yang namanya diawali dengan tanda titik (`.`), misalnya `.bashrc` atau `.gitignore`, disebut *dotfile*. Secara *default*, *dotfile* tidak ditampilkan oleh `ls` (bersifat *hidden*) kecuali opsi `-a` disertakan. *Dotfile* umumnya dipakai untuk menyimpan *file* konfigurasi suatu program atau *shell*, sehingga tidak mengganggu tampilan isi direktori sehari-hari.

Selain itu, terdapat beberapa simbol khusus yang merujuk ke lokasi direktori tertentu tanpa perlu menuliskan *path* lengkapnya, dirangkum pada Tabel I.2.

**Tabel I.2:** Simbol direktori khusus pada Unix/Linux

| Simbol | Makna | Keterangan |
|--------|-------|------------|
| `~` | Direktori *home* pengguna | Merujuk ke `/home/$USER/`; mis. `cd ~` berpindah ke direktori *home*. |
| `.` | Direktori saat ini | Merujuk ke direktori kerja saat ini (*current working directory*). |
| `..` | Direktori *parent* | Merujuk ke direktori satu tingkat di atas direktori saat ini. |
| `/` | Direktori *root* | Direktori paling atas (akar) dari seluruh hierarki sistem berkas. |

Sebagai ilustrasi, dari direktori `/home/user/dokumen`, perintah `cd ..` akan berpindah ke `/home/user`, sedangkan `cd ../..` akan berpindah dua tingkat ke atas menuju `/home`. Pemahaman simbol-simbol ini penting agar navigasi direktori menggunakan *relative path* dapat dilakukan secara efisien tanpa harus selalu menuliskan *absolute path* yang panjang.

Tabel I.3 merangkum seluruh perintah dasar yang dibahas pada Bagian I ini beserta fungsinya secara singkat.

**Tabel I.3:** Ringkasan perintah dasar manajemen *file* dan direktori

| Perintah | Sintaks | Fungsi |
|----------|---------|--------|
| `file` | `file FILE...` | Menentukan jenis suatu *file*. |
| `pwd` | `pwd` | Mencetak nama direktori kerja saat ini. |
| `cd` | `cd [DIR]` | Mengganti direktori kerja (*default* ke direktori *home*). |
| `ls` | `ls [OPTION] [FILE]` | Menampilkan daftar isi direktori. |
| `touch` | `touch FILE` | Membuat *file* kosong atau meng-*update* waktunya. |
| `mkdir` | `mkdir [OPTION] DIR` | Membuat direktori baru. |
| `cp` | `cp [OPTION] SOURCE DEST` | Menyalin *file* dan direktori. |
| `mv` | `mv [OPTION] SOURCE DEST` | Memindahkan atau mengganti nama *file*. |
| `rm` | `rm [OPTION] FILE...` | Menghapus *file* atau direktori. |
| `rmdir` | `rmdir [OPTION] DIR...` | Menghapus direktori kosong. |
| `tree` | `tree [OPTION] [DIR...]` | Menampilkan isi direktori dalam format pohon. |

<a id="i-3"></a>

## I.3 Lembar Kerja Praktikum (LKP) — Bagian I

> **Instruksi Tugas**
>
> - [ ] Kerjakan setiap bagian dengan benar secara individu.
> - [ ] Jawaban Bagian B dituliskan dengan penjelasan sendiri.
> - [ ] Kumpulkan seluruh berkas dalam satu file terkompresi dengan format nama `NIM_NamaLengkap_LKP9.zip`.

### Bagian A — Publikasi Halaman Web

1. Login ke server praktikum `172.18.14.15`.
2. Buat direktori `public_html` pada direktori *home* anda di server tersebut, lalu buat *file* baru `index.html` di dalam direktori tersebut.
3. Edit *file* `index.html` sehingga memuat NIM dan nama anda, kemudian pastikan halaman tersebut dapat diakses melalui:
   - `http://172.18.14.15/~$USER`
   - `http://s1.apps.cs.ipb.ac.id/~$USER`

### Bagian B — Analisis

1. Jelaskan mengapa opsi `-i` pada `cp`, `mv`, dan `rm` dianggap praktik yang lebih aman dibandingkan `-f` pada sistem yang dipakai bersama banyak pengguna (*multi-user*), dan pada situasi apa `-f` tetap masuk akal digunakan.
2. Diberikan struktur direktori `/home/user/proyek/src` dan `/home/user/arsip`. Jika direktori kerja saat ini adalah `/home/user/proyek/src`, tuliskan perintah `cd` menuju `/home/user/arsip` menggunakan *relative path* maupun *absolute path*, lalu jelaskan situasi di mana masing-masing pendekatan lebih efisien digunakan.
3. Perintah `rmdir` menolak menghapus direktori yang masih berisi *file*, sedangkan `rm -r` tidak. Jelaskan mengapa perbedaan perilaku ini penting dari sudut pandang keandalan sistem (*system reliability*) dan pencegahan kehilangan data yang tidak disengaja.
4. *Dotfile* tidak ditampilkan secara *default* oleh `ls`. Jelaskan risiko yang dapat timbul jika informasi konfigurasi sensitif (misalnya kredensial) disimpan sebagai *dotfile* di dalam direktori `public_html` yang dapat diakses publik melalui *web server*, serta bagaimana seharusnya konfigurasi semacam itu ditangani.

---
---

<a id="bagian-2"></a>

# BAGIAN II — PERMISSION, LINK, STREAM, DAN PIPE

*Pertemuan ke-9: Permission & Pipe*

> **Tujuan Praktikum**
>
> 1. Memahami konsep kepemilikan (*ownership*) dan hak akses (*permission*) berkas pada sistem UNIX/Linux, serta cara membaca dan mengubahnya menggunakan `chmod` dan `chown`.
> 2. Memahami perbedaan *hard link* dan *symbolic link*, serta peran *inode* sebagai struktur data yang menyimpan metadata suatu berkas.
> 3. Menerapkan konsep *stream* standar (`stdin`, `stdout`, `stderr`), *pipe*, dan *redirection* I/O untuk menyusun *pipeline* perintah pada *shell*.

<a id="ii-1"></a>

## II.1 Pengantar Praktikum

Bagian ini membahas tiga topik yang saling berkaitan pada sistem berkas UNIX/Linux: *permission* (hak akses berkas), *link* (penamaan berkas melalui *hard link* dan *symbolic link*), serta *stream* dan *pipe* sebagai mekanisme aliran data antar-perintah maupun antar-proses. Ketiganya adalah bekal penting bagi seorang pengguna maupun administrator sistem UNIX/Linux, karena hampir seluruh interaksi dengan berkas dan antarproses pada *shell* bergantung pada konsep-konsep ini.

Materi dibagi menjadi tiga bagian besar. Bagian pertama membahas kepemilikan dan hak akses berkas beserta perintah `chmod` dan `chown`. Bagian kedua membahas *hard link* dan *symbolic link* beserta konsep *inode* yang mendasarinya. Bagian ketiga membahas *stream* standar suatu proses (`stdin`, `stdout`, `stderr`), mekanisme *pipe* untuk menyalurkan keluaran satu perintah menjadi masukan perintah lain, serta *redirection* I/O. Hasil praktik ditulis pada Lembar Kerja Praktikum (LKP) di Bagian II.5.

> **Catatan Penting**
>
> Buku acuan utama praktikum ini adalah Silberschatz, Galvin, dan Gagne, *Operating System Concepts*, edisi ke-10 (2018) — khususnya bab yang membahas antarmuka sistem berkas (*file-system interface*), proteksi berkas, implementasi sistem berkas, dan komunikasi antarproses (*interprocess communication*).

<a id="ii-2"></a>

## II.2 Materi Inti

<a id="ii-2-1"></a>

### II.2.1 Kepemilikan dan Notasi Hak Akses Berkas

Setiap berkas pada sistem UNIX/Linux memiliki seorang *owner* (pemilik). Sebagai aturan keamanan dasar, hanya *superuser* (`root`) yang berwenang mengubah kepemilikan suatu berkas ke pengguna lain; pengguna biasa tidak dapat memberikan berkas miliknya kepada pengguna lain begitu saja. Selain *owner*, sistem berkas UNIX/Linux mengenal tiga **kelas pengguna** yang dapat dikenai aturan akses berbeda-beda terhadap sebuah berkas, sebagaimana dirangkum pada Tabel II.1.

**Tabel II.1:** Tiga kelas pengguna pada *permission* UNIX/Linux

| Notasi | Nama | Keterangan |
|--------|------|------------|
| `u` | *user owner* | Pemilik berkas, biasanya pengguna yang membuat berkas tersebut. |
| `g` | *group owner* | Kelompok pengguna yang diberi akses bersama terhadap berkas. |
| `o` | *others* | Seluruh pengguna lain di luar *owner* dan anggota *group*. |

Terhadap masing-masing kelas pengguna tersebut, sistem UNIX/Linux mendefinisikan tiga **jenis permission** dasar yang maknanya berbeda antara berkas biasa dan direktori, sebagaimana dirangkum pada Tabel II.2.

**Tabel II.2:** Tiga jenis *permission* dan artinya pada berkas vs direktori

| Notasi | Nama | Arti pada Berkas | Arti pada Direktori |
|--------|------|------------------|---------------------|
| `r` | *read* | Membaca isi berkas. | Melihat daftar berkas (*list files*) di dalam direktori. |
| `w` | *write* | Mengubah isi berkas. | Menambah atau menghapus berkas di dalam direktori (*add or remove files*). |
| `x` | *execute* | Menjalankan berkas sebagai program/skrip. | Masuk ke dalam direktori (*enter the directory*), misalnya dengan `cd`. |

Kombinasi tiga kelas pengguna dan tiga jenis *permission* inilah yang membentuk sembilan bit hak akses yang tampil pada kolom *permission* keluaran `ls -l`, misalnya `rwxr-xr-x`: tiga karakter pertama untuk *owner*, tiga berikutnya untuk *group*, dan tiga terakhir untuk *others*.

<a id="ii-2-2"></a>

### II.2.2 Perintah `chown` dan `chmod`

Perintah `chown` digunakan untuk mengubah kepemilikan (*owner* dan/atau *group*) suatu berkas:

```bash
chown [OPTION] OWNER[:GROUP] FILE
```

Opsi `-R` (*recursive*) membuat perubahan kepemilikan berlaku untuk seluruh isi direktori secara rekursif. Karena perubahan kepemilikan berdampak pada kendali akses, perintah ini umumnya hanya dapat dijalankan oleh `root` (atau melalui `sudo`).

Perintah `chmod` (*change mode*) digunakan untuk mengubah *permission* suatu berkas:

```bash
chmod [OPTION] MODE FILE...
```

Sama seperti `chown`, opsi `-R` membuat perubahan berlaku rekursif ke seluruh isi direktori. Argumen `MODE` dapat dituliskan dalam dua format, yaitu format simbolis dan format oktal.

#### Format Simbolis

Format simbolis `chmod` berbentuk `[ugoa][+-=][rwx]`, yaitu kombinasi dari:

- **Sasaran kelas**: `u` (*user*), `g` (*group*), `o` (*others*), atau `a` (*all*, ketiganya sekaligus).
- **Operator**: `+` (menambah *permission*), `-` (mencabut *permission*), atau `=` (menetapkan *permission* persis seperti yang dituliskan, menghapus yang lain).
- **Jenis permission**: kombinasi `r`, `w`, dan/atau `x`.

#### Format Oktal

Format oktal merepresentasikan *permission* tiap kelas pengguna sebagai satu digit oktal (0–7), dengan bobot: `r` = 4, `w` = 2, `x` = 1. Nilai digit diperoleh dari **penjumlahan** bobot *permission* yang aktif, dan *permission* suatu kelas ditulis sebagai satu digit untuk masing-masing `u`, `g`, dan `o` secara berurutan (misalnya `755`). Tabel II.3 merangkum seluruh delapan kemungkinan kombinasi digit oktal.

**Tabel II.3:** Nilai oktal *permission* (r=4, w=2, x=1)

| Oktal | Simbolis | Keterangan |
|-------|----------|------------|
| 0 | `---` | Tidak ada akses sama sekali. |
| 1 | `--x` | Hanya *execute*. |
| 2 | `-w-` | Hanya *write*. |
| 3 | `-wx` | *Write* dan *execute*. |
| 4 | `r--` | Hanya *read*. |
| 5 | `r-x` | *Read* dan *execute*. |
| 6 | `rw-` | *Read* dan *write*. |
| 7 | `rwx` | *Read*, *write*, dan *execute* (akses penuh). |

Sebagai contoh, *permission* `rwxr-xr-x` dapat ditulis sebagai digit oktal `7` (owner: 4+2+1), `5` (group: 4+0+1), dan `5` (others: 4+0+1), sehingga menjadi `755`.

<a id="ii-2-3"></a>

### II.2.3 Contoh Penerapan `chmod`

Tabel II.4 menunjukkan beberapa contoh *permission* yang umum dijumpai beserta cara menyetelnya menggunakan format oktal maupun format simbolis.

**Tabel II.4:** Contoh *permission* dan perintah `chmod` yang setara

| Permission | Format Oktal | Format Simbolis |
|------------|--------------|-----------------|
| `r--r--r--` | `chmod 444 FILE` | `chmod a=r FILE` |
| `rw-rw----` | `chmod 660 FILE` | `chmod ug=rw,o= FILE` |
| `rwxr-xr-x` | `chmod 755 FILE` | `chmod u=rwx,go=rx FILE` |

<a id="ii-2-4"></a>

### II.2.4 Pengayaan: Bit Setuid dan Sticky Bit

Selain sembilan bit dasar (`rwx` untuk `u`, `g`, `o`), sistem UNIX/Linux juga mengenal beberapa bit *permission* khusus yang tidak muncul secara eksplisit pada slide utama, namun penting untuk dipahami:

- **Setuid** (*set user ID*): jika bit ini aktif pada berkas program yang dapat dieksekusi (tampak sebagai huruf `s` pada posisi *execute* milik *owner*, misalnya `rwsr-xr-x`), maka program tersebut akan dijalankan dengan hak akses *owner* berkas, bukan hak akses pengguna yang menjalankannya. Contoh klasik adalah perintah `ping`, yang berkasnya dimiliki `root` dan berbit *setuid* agar pengguna biasa tetap dapat membuat *raw socket* yang normalnya memerlukan hak akses `root`.
- **Setgid** (*set group ID*): serupa dengan *setuid*, tetapi berlaku untuk *group*. Pada direktori, bit ini membuat berkas baru yang dibuat di dalamnya otomatis mewarisi *group* direktori tersebut, bukan *group* pengguna yang membuatnya.
- **Sticky bit**: jika aktif pada sebuah direktori (misalnya direktori `/tmp`), pengguna hanya dapat menghapus atau mengubah nama berkas miliknya sendiri di dalam direktori tersebut, walaupun pengguna lain memiliki *permission write* pada direktori itu.

Ketiga bit ini turut disetel melalui `chmod`, baik dengan digit oktal keempat (*setuid*=4, *setgid*=2, *sticky*=1, dituliskan di depan tiga digit biasa) maupun format simbolis (`u+s`, `g+s`, `+t`).

<a id="ii-2-5"></a>

### II.2.5 Hard Link dan Symbolic Link

Pada sistem berkas UNIX/Linux, sebuah berkas dapat memiliki lebih dari satu nama melalui mekanisme *link*. Terdapat dua jenis *link*:

1. ***Hard link***: mengacu langsung ke *id* berkas, yaitu nomor *inode*-nya. Karena hanya menunjuk ke *inode* yang sama, perubahan nama salah satu *hard link* tidak memengaruhi *hard link* lainnya — keduanya benar-benar setara sebagai nama untuk data yang sama. *Hard link* hanya dapat dibuat di dalam satu partisi (sistem berkas) yang sama, karena nomor *inode* hanya unik dalam lingkup satu sistem berkas.
2. ***Symbolic link*** (*symlink*): berupa berkas khusus yang isinya adalah *path* (nama/alamat) menuju berkas lain, bukan mengacu langsung ke *inode* data. Karena mengacu ke nama, jika berkas target diganti namanya atau dihapus, *symlink* akan menjadi *broken link* (menunjuk ke berkas yang tidak lagi ada). Kelebihan *symlink* adalah dapat dibuat lintas partisi, dan dapat pula menunjuk ke sebuah direktori.

*Link* dibuat menggunakan perintah `ln`:

```bash
ln [OPTION] TARGET LINK-NAME
```

Tanpa opsi, `ln` membuat *hard link*. Opsi `-s` membuat *symbolic link*.

<a id="ii-2-6"></a>

### II.2.6 Inode: Struktur Data di Balik Sebuah Berkas

Setiap berkas pada sistem berkas bergaya UNIX (misalnya `ext2`, `ext3`, `ext4`) direpresentasikan oleh sebuah struktur data yang disebut *inode* (*index node*). *Inode* menyimpan seluruh **metadata** berkas — seperti pemilik, *group*, *permission*, ukuran, waktu modifikasi terakhir, dan lokasi blok data pada *disk* — namun **tidak menyimpan nama berkas itu sendiri**. Nama berkas justru disimpan sebagai pasangan (nama, nomor *inode*) di dalam *entry* direktori tempat berkas tersebut berada.

Seluruh *inode* pada suatu sistem berkas disimpan dalam sebuah tabel/*array inode* berukuran tetap yang dialokasikan saat sistem berkas dibuat (*format*). Karena jumlah slot *inode* ini dibatasi sejak awal, sebuah *disk* yang secara kapasitas byte masih memiliki ruang kosong dapat tetap kehabisan *inode* apabila berisi sangat banyak berkas berukuran kecil — kondisi ini dapat dicek dengan perintah `df -i`. Inilah alasan mengapa penghapusan nama (*unlink*) sebuah *hard link* tidak langsung menghapus data: data dan *inode*-nya baru benar-benar dibebaskan ketika **jumlah *hard link* yang menunjuk ke *inode* tersebut mencapai nol**.

<a id="ii-2-7"></a>

### II.2.7 Stream Standar Proses

Setiap proses pada UNIX/Linux, sejak awal dijalankan, secara otomatis memiliki tiga *stream* (aliran data) I/O standar yang masing-masing diidentifikasi dengan nomor *file descriptor*:

1. ***standard input*** (`stdin`, *file descriptor* 0): sumber masukan proses, secara *default* berasal dari papan ketik.
2. ***standard output*** (`stdout`, *file descriptor* 1): keluaran normal proses, secara *default* ditampilkan ke layar terminal.
3. ***standard error*** (`stderr`, *file descriptor* 2): keluaran pesan galat proses, juga tampil ke layar secara *default*, namun dipisahkan dari `stdout` agar dapat ditangani secara berbeda.

```text
              +------------+
              |            |
stdin --->|    PROSES    |---> stdout
              |            |
              +-----+------+
                    |
                    \---> stderr
```

Pemisahan `stdout` dan `stderr` menjadi dua *stream* yang berbeda inilah yang memungkinkan pengguna mengarahkan keduanya secara terpisah — misalnya menyimpan keluaran normal ke satu berkas dan pesan galat ke berkas lain — sebagaimana dibahas pada Subbagian II.2.9.

<a id="ii-2-8"></a>

### II.2.8 Pipe: Komunikasi Antarproses

*Pipe* adalah mekanisme yang menyalurkan `stdout` suatu proses menjadi `stdin` proses lain, sehingga dua atau lebih perintah dapat dirangkai menjadi satu *pipeline*. Secara konsep, *pipe* adalah salah satu bentuk paling sederhana dari *interprocess communication* (IPC), yaitu mekanisme yang memungkinkan proses-proses yang berbeda saling bertukar data.²

```text
                          pipe
 +-------------+            +            +-------------+
 |             |            |            |             |
 | PROCESS1    +----------- | --------->| PROCESS2    |
 |             |  stdout    |   stdin   |             |
 +-------------+            +            +-------------+
```

*Pipe* yang dibuat pada *shell* dengan karakter `|` disebut **pipe anonim** (*anonymous pipe*) karena hanya dapat dipakai oleh proses-proses yang memiliki hubungan *parent–child* (satu *shell* yang sama), bersifat satu arah (*unidirectional*), dan tidak memiliki nama pada sistem berkas. Contoh penggunaannya pada *shell*:

```bash
echo "halo" | rev
echo "2 + 5" | bc
who | wc -l
```

Pada baris pertama, keluaran `echo "halo"` (yaitu teks `halo`) menjadi masukan bagi `rev`, yang membalikkan urutan karakternya. Pada baris kedua, ekspresi `2 + 5` dikirim sebagai masukan ke kalkulator `bc`. Pada baris ketiga, daftar pengguna yang sedang *login* dari `who` dihitung jumlah barisnya oleh `wc -l`.

² Silberschatz, Galvin, & Gagne (2018), *Operating System Concepts*, Bab 3 (*Processes*), Subbab *Interprocess Communication*.

#### Pengayaan: Pipa Anonim pada Bahasa C

Di balik layar, ketika *shell* membuat *pipeline* seperti `cmd1 | cmd2`, *shell* sesungguhnya memanggil fungsi pustaka `pipe()` sebelum melakukan `fork()` dan `exec()` untuk kedua perintah tersebut. Fungsi `pipe()` membuat sepasang *file descriptor* yang saling terhubung: salah satu ujung untuk menulis, ujung lainnya untuk membaca.

```c
int pipe(int fd[2]);
// fd[0] : ujung untuk membaca (read end)
// fd[1] : ujung untuk menulis (write end)
```

Karena kedua ujung *pipe* berupa *file descriptor* biasa, proses *child* hasil `fork()` akan mewarisi keduanya; proses *child* yang berperan sebagai `cmd1` kemudian menutup ujung baca dan mengarahkan `stdout`-nya ke ujung tulis *pipe* (dengan `dup2()`), sedangkan proses *child* yang berperan sebagai `cmd2` menutup ujung tulis dan mengarahkan `stdin`-nya ke ujung baca *pipe*. Dengan cara inilah data dapat mengalir dari `cmd1` ke `cmd2` tanpa keduanya perlu saling mengetahui detail implementasi satu sama lain.

Karena kapasitas *buffer pipe* pada *kernel* terbatas, proses penulis yang mengisi *buffer* hingga penuh akan diblokir (menunggu) sampai proses pembaca mengosongkan sebagian isinya. Sebaliknya, jika proses pembaca (`cmd2`) berhenti sebelum proses penulis (`cmd1`) selesai menulis, sistem operasi akan mengirim sinyal `SIGPIPE` ke proses penulis, yang secara *default* akan menghentikan proses tersebut.

<a id="ii-2-9"></a>

### II.2.9 Redirection I/O

*Redirection* mengarahkan salah satu *stream* standar suatu proses ke sebuah berkas yang ditentukan pengguna, alih-alih ke papan ketik/layar secara *default*. Tabel II.5 merangkum karakter *redirect* yang umum dipakai pada *shell* `bash`.

**Tabel II.5:** Karakter *redirect* I/O pada *shell*

| Karakter | Redirect | Keterangan |
|----------|----------|------------|
| `<` | `stdin` | Membaca masukan proses dari isi sebuah berkas, bukan dari papan ketik. |
| `>` | `stdout` | Menuliskan keluaran proses ke sebuah berkas; isi berkas lama **ditimpa**. |
| `>>` | `stdout` (*append*) | Menuliskan keluaran proses ke sebuah berkas dengan **menambahkan** di akhir isi lama, tanpa menghapusnya. |
| `2>` | `stderr` | Mengarahkan pesan galat proses ke sebuah berkas, terpisah dari `stdout`. |

Contoh penggunaan *redirect*:

```bash
date > now.txt 2> err.txt
rev < now.txt
rev < now.txt > rev.txt
```

Baris pertama menuliskan keluaran normal `date` ke `now.txt` dan pesan galatnya (jika ada) ke `err.txt`. Baris kedua membaca isi `now.txt` sebagai masukan `rev` dan menampilkan hasilnya ke layar. Baris ketiga menggabungkan *redirect* masukan dan keluaran sekaligus: isi `now.txt` dibalik oleh `rev`, lalu hasilnya disimpan ke `rev.txt`.

*Redirect* dan *pipe* sama-sama memanipulasi *stream* standar suatu proses, namun berbeda tujuan: *redirect* menghubungkan *stream* proses dengan sebuah **berkas**, sedangkan *pipe* menghubungkan *stream* satu proses langsung dengan *stream* **proses lain** tanpa melalui berkas perantara di *disk*.

<a id="ii-3"></a>

## II.3 Praktik: Permission, Link, dan Pipe pada Terminal

> ### Langkah 1: Menyiapkan Berkas Percobaan
>
> Buat sebuah direktori kerja untuk modul ini, misalnya `modul9-permission-pipe/`. Di dalamnya, buat sebuah berkas teks percobaan:
>
> ```bash
> mkdir modul9-permission-pipe && cd modul9-permission-pipe
> echo "Praktikum Sistem Operasi" > coba.txt
> ls -l coba.txt
> ```
>
> Amati kolom *permission*, *owner*, dan *group* pada keluaran `ls -l`.

> ### Langkah 2: Mengubah Permission dengan `chmod`
>
> Ubah *permission* `coba.txt` menggunakan format oktal maupun simbolis, lalu amati perubahannya dengan `ls -l` setiap kali:
>
> ```bash
> chmod 644 coba.txt
> ls -l coba.txt
>
> chmod u+x coba.txt
> ls -l coba.txt
>
> chmod a=r coba.txt
> ls -l coba.txt
> ```
>
> Cocokkan hasil setiap perintah dengan Tabel II.3 dan Tabel II.4.

> ### Langkah 3: Mencoba `chown` (Opsional, Memerlukan `sudo`)
>
> Jika tersedia akses `sudo` pada mesin latihan (mis. *virtual machine* sendiri), coba ubah *group owner* berkas:
>
> ```bash
> sudo chown $(whoami):users coba.txt
> ls -l coba.txt
> ```
>
> Jika tidak memiliki akses `sudo`, cukup jelaskan pada LKP mengapa perintah `chown` umumnya dibatasi hanya untuk `root`.

> ### Langkah 4: Membuat Hard Link dan Symbolic Link
>
> Buat kedua jenis *link* dari `coba.txt`, lalu bandingkan nomor *inode*-nya dengan `ls -li`:
>
> ```bash
> ln coba.txt coba_hard.txt
> ln -s coba.txt coba_sym.txt
> ls -li coba.txt coba_hard.txt coba_sym.txt
> ```
>
> Amati bahwa `coba.txt` dan `coba_hard.txt` memiliki nomor *inode* yang **sama**, sedangkan `coba_sym.txt` memiliki *inode* sendiri yang isinya berupa *path* menuju `coba.txt`. Selanjutnya, ganti nama berkas asli dan amati akibatnya pada kedua *link*:
>
> ```bash
> mv coba.txt coba_asli.txt
> cat coba_hard.txt
> cat coba_sym.txt
> ```

> ### Langkah 5: Menggabungkan Pipe dan Redirect
>
> Jalankan rangkaian perintah berikut, lalu jelaskan pada LKP apa yang terjadi pada setiap baris:
>
> ```bash
> echo "halo" | rev
> echo "2 + 5" | bc
> who | wc -l
>
> date > now.txt 2> err.txt
> rev < now.txt
> rev < now.txt > rev_now.txt
> cat rev_now.txt
> ```
>
> Simpan tangkapan layar hasil eksekusi seluruh perintah pada langkah ini.

<a id="ii-4"></a>

## II.4 Latihan

Kerjakan latihan *permission* pada tautan berikut sebagaimana dirujuk pada slide kuliah, lalu lampirkan tangkapan layar dan jawabannya: Launch School — *Intro Command Line*, <https://launchschool.com/books/command_line/read/permissions#exercises>.

<a id="ii-5"></a>

## II.5 Lembar Kerja Praktikum (LKP) — Bagian II

> **Instruksi Tugas**
>
> - [ ] Kerjakan tugas secara individu.
> - [ ] Kumpulkan seluruh berkas dalam satu file terkompresi dengan format nama `NIM_NamaLengkap_LKP9.zip`.

### Bagian A — Permission

1. Buat sebuah berkas `skrip_a.sh` berisi satu baris perintah apa saja (mis. `echo "halo"`), lalu jadikan berkas tersebut dapat dieksekusi **khusus oleh *owner* saja** (*owner*: `rwx`; *group* dan *others*: tidak ada akses sama sekali) menggunakan `chmod` format oktal. Jalankan skrip tersebut dengan `./skrip_a.sh` untuk membuktikan *permission* sudah benar.

### Bagian B — Link, Stream, dan Pipe

1. Buat sebuah berkas `data_b.txt` berisi beberapa baris teks bebas. Buat satu *hard link* dan satu *symbolic link* untuk berkas tersebut, lalu **hapus** (bukan ganti nama) berkas aslinya dengan `rm`. Amati dan jelaskan apa yang terjadi pada isi *hard link* dan pada *symbolic link*.
2. Buat satu *pipeline* tiga perintah (`cmd1 | cmd2 | cmd3`) bebas menggunakan perintah-perintah UNIX/Linux yang tersedia (contoh: `cat data_b.txt | sort | uniq`), lalu arahkan hasil akhirnya ke sebuah berkas menggunakan *redirect* `>`. Tunjukkan bahwa isi berkas hasil sesuai dengan yang diharapkan.

---

<a id="referensi"></a>

## Referensi

- Silberschatz, A., Galvin, P. B., & Gagne, G. (2018). *Operating System Concepts* (10th ed.). Wiley.
- Evans, J. *Unix Permissions* dan *Pipes* (komik edukasi). <https://drawings.jvns.ca>.
- Launch School. *Introduction to Command Line*. <https://launchschool.com/>.
- Launch School. *Introduction to Command Line — Permissions*. <https://launchschool.com/books/command_line/read/permissions>.
