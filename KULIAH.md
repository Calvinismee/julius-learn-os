# Ringkasan Materi Sistem Operasi (Minggu 1–7)

## Daftar Isi

- [Minggu 1: Pengenalan & Konsep Dasar Sistem Operasi](#minggu-1-pengenalan--konsep-dasar-sistem-operasi)
  - [1. Definisi dan Peran Sistem Operasi](#1-definisi-dan-peran-sistem-operasi)
  - [2. Struktur Sistem Komputer](#2-struktur-sistem-komputer)
  - [3. Operasi-operasi Sistem Operasi](#3-operasi-operasi-sistem-operasi)
  - [4. Multiprogramming vs. Multitasking](#4-multiprogramming-vs-multitasking)
  - [5. Dual-Mode Operations](#5-dual-mode-operations)
  - [6. Manajemen Sumber Daya](#6-manajemen-sumber-daya)
- [Minggu 2: Struktur Sistem Operasi](#minggu-2-struktur-sistem-operasi)
  - [1. Layanan-layanan Sistem Operasi](#1-layanan-layanan-sistem-operasi)
  - [2. Antarmuka Pengguna](#2-antarmuka-pengguna-user-interface)
  - [3. System Calls & API](#3-system-calls--api)
  - [4. Rancangan dan Implementasi](#4-rancangan-dan-implementasi-sistem-operasi)
  - [5. Struktur Sistem Operasi](#5-struktur-sistem-operasi)
- [Minggu 3: Manajemen Proses - Konsep Proses & IPC](#minggu-3-manajemen-proses---konsep-proses--ipc)
  - [1. Konsep Proses dan Komponennya](#1-konsep-proses-dan-komponennya)
  - [2. Penjadwalan Proses & Context Switch](#2-penjadwalan-proses--context-switch)
  - [3. Operasi Standar Proses](#3-operasi-standar-proses)
  - [4. Interprocess Communication (IPC)](#4-kerjasama-antar-proses-ipc---interprocess-communication)
  - [5. Komunikasi Client-Server](#5-komunikasi-client-server)
- [Minggu 4: Multithreaded Programming](#minggu-4-multithreaded-programming)
  - [1. Definisi Thread & Multithreading](#1-definisi-thread--multithreading)
  - [2. Pemrograman Multicore](#2-pemrograman-multicore)
  - [3. Konsep Multithreading](#3-konsep-multithreading)
  - [4. Model Multithreading](#4-model-multithreading)
  - [5. Thread Libraries & Implicit Threading](#5-thread-libraries--implicit-threading)
- [Minggu 5: Penjadwalan CPU](#minggu-5-penjadwalan-cpu)
  - [1. Konsep Dasar Penjadwalan CPU](#1-konsep-dasar-penjadwalan-cpu)
  - [2. Kriteria Penjadwalan](#2-kriteria-penjadwalan)
  - [3. Algoritme Penjadwalan](#3-algoritme-penjadwalan)
- [Minggu 6: Penjadwalan Tingkat Lanjut & Real-Time](#minggu-6-penjadwalan-tingkat-lanjut--real-time)
  - [1. Multiple-Processor Scheduling](#1-multiple-processor-scheduling)
  - [2. Penjadwalan Thread](#2-penjadwalan-thread)
  - [3. Real-Time Systems Scheduling](#3-real-time-systems-scheduling)
  - [4. Contoh Penjadwal Sistem Operasi Nyata](#4-contoh-penjadwal-sistem-operasi-nyata)
- [Minggu 7: Sinkronisasi Proses & Deadlock](#minggu-7-sinkronisasi-proses--deadlock)
  - [1. Konsep Konkurensi & Critical Section](#1-konsep-konkurensi--critical-section)
  - [2. Syarat Solusi Critical Section](#2-syarat-solusi-critical-section)
  - [3. Mekanisme Konkurensi](#3-mekanisme-konkurensi)
  - [4. Kasus Klasik Sinkronisasi](#4-kasus-klasik-sinkronisasi)
  - [5. Deadlock dan Metode Penanganannya](#5-deadlock-dan-metode-penanganannya)

---

## Minggu 1: Pengenalan & Konsep Dasar Sistem Operasi

### 1. Definisi dan Peran Sistem Operasi

- **Pengelola Sumber Daya (*Resource Manager*):** Mengelola seluruh komponen perangkat keras (CPU, memori, penyimpanan, perangkat I/O) dan mengalokasikannya secara adil dan efisien di antara program pengguna.
- **Program Pengontrol (*Control Program*):** Mengendalikan eksekusi program pengguna untuk mencegah kesalahan (*error*) dan penggunaan komputer yang tidak sah.

### 2. Struktur Sistem Komputer

- **Empat komponen utama:** Perangkat Keras (*Hardware*), Sistem Operasi, Program Aplikasi, dan Pengguna (*User*).
- **Sistem interupsi & bus:** Perangkat keras memicu interupsi dengan mengirim sinyal ke CPU melalui *system bus*. Saat interupsi terjadi, CPU menghentikan pekerjaannya dan melompat ke *Interrupt Service Routine* (ISR) di memori.

### 3. Operasi-operasi Sistem Operasi

- **Interupsi perangkat keras:** dipicu oleh kontroler I/O.
- **Interupsi perangkat lunak:** dipicu oleh kesalahan program atau permintaan layanan melalui *trap* / *exception*.

### 4. Multiprogramming vs. Multitasking

| Konsep | Penjelasan |
|---|---|
| **Multiprogramming** | Beberapa proses disimpan di memori utama secara bersamaan. Saat satu proses menunggu I/O, OS beralih ke proses lain sehingga CPU tidak *idle*. |
| **Multitasking (Time-Sharing)** | Ekstensi multiprogramming: CPU berpindah antarproses sangat cepat (hitungan milidetik) sehingga pengguna merasakan pengalaman interaktif. |

### 5. Dual-Mode Operations

- **Tujuan:** Perlindungan perangkat keras dengan membedakan eksekusi kode OS dan kode pengguna.
- **User Mode (Mode Bit = 1):** Mode eksekusi aplikasi pengguna dengan akses terbatas.
- **Kernel Mode / Supervisor Mode (Mode Bit = 0):** Mode terproteksi tempat kode OS berjalan dengan akses penuh ke perangkat keras.
- **Privileged Instructions:** Instruksi berbahaya (mis. mengubah arah interupsi atau mengontrol I/O) hanya boleh dijalankan di *kernel mode*. Jika dijalankan di *user mode*, perangkat keras memicu *trap*.
- **Transisi mode:** Terjadi melalui *system call*.

### 6. Manajemen Sumber Daya

- **Manajemen proses & memori:** Memuat program, mengalokasikan memori, dan melacak status eksekusi.
- **Manajemen penyimpanan & I/O:** Memetakan sistem berkas logis ke media fisik (*mass storage*) dan menyediakan abstraksi perangkat I/O yang terproteksi.

---

## Minggu 2: Struktur Sistem Operasi

### 1. Layanan-layanan Sistem Operasi

- **Layanan untuk pengguna:** Antarmuka Pengguna (UI), Eksekusi Program, Operasi I/O, Manipulasi Sistem Berkas, Komunikasi antarproses, dan Deteksi Kesalahan.
- **Layanan untuk efisiensi sistem:** Alokasi Sumber Daya (*Resource Allocation*), Akuntansi (*Accounting*), serta Perlindungan dan Keamanan (*Protection & Security*).

### 2. Antarmuka Pengguna (User Interface)

- **CLI (Command-Line Interface / Shell):** Menerima perintah teks langsung dari pengguna.
- **GUI & Touchscreen:** Antarmuka grafis dengan jendela/ikon (*mouse*) atau interaksi sentuhan layar (*finger gestures*).

### 3. System Calls & API

- **System Call:** Antarmuka terprogram yang menyediakan akses langsung ke layanan kernel OS.
- **API (Application Programming Interface):** Pustaka fungsi (mis. POSIX API, Windows API) yang membungkus *system call* agar mudah digunakan pemrogram. *System-call interface* mencocokkan fungsi API dengan nomor indeks *system call* di dalam kernel.
- **6 kategori system call:**
  1. Kendali Proses (*Process Control*)
  2. Manajemen Berkas
  3. Manajemen Perangkat
  4. Pemeliharaan Informasi
  5. Komunikasi
  6. Perlindungan

### 4. Rancangan dan Implementasi Sistem Operasi

- **Mechanism:** Menentukan *bagaimana* melakukan sesuatu (mis. struktur *timer hardware*).
- **Policy:** Menentukan *apa* yang dilakukan (mis. berapa lama kuantum waktu diberikan).
- Pemisahan mekanisme dan kebijakan (*separation of mechanism and policy*) memberi fleksibilitas tinggi.

### 5. Struktur Sistem Operasi

| Struktur | Penjelasan | Kelebihan / Kekurangan |
|---|---|---|
| **Monolithic** | Seluruh fungsi OS dalam satu ruang alamat memori (*single address space*). Contoh: UNIX tradisional, kernel Linux. | Sangat cepat (minim *overhead*), tetapi sulit dimodifikasi. |
| **Layered** | OS dibagi menjadi lapisan dari *Layer 0* (Hardware) hingga *Layer N* (UI). Setiap lapisan hanya memanggil lapisan di bawahnya. | Modular dan mudah di-*debug*. |
| **Microkernel** | Komponen non-esensial dipindah ke *user space*. Komunikasi antarlayanan lewat *message passing* melalui mikrokernel kecil. | Lebih aman dan stabil, tetapi ada *performance overhead*. |
| **Loadable Kernel Modules (LKMs)** | Kernel inti statis; fungsi tambahan (*device driver*, *file system*) dihubungkan secara dinamis saat *runtime*. | Fleksibel tanpa *reboot*. |
| **Hybrid** | Menggabungkan berbagai arsitektur. Contoh: **macOS/Darwin** (mikrokernel Mach + kernel BSD UNIX dalam satu ruang alamat) dan **Windows 10**. | Kompromi antara kinerja dan modularitas. |

---

## Minggu 3: Manajemen Proses - Konsep Proses & IPC

### 1. Konsep Proses dan Komponennya

- **Tata letak memori proses:**
  - *Text section* — kode eksekusi
  - *Data section* — variabel global
  - *Heap* — memori dinamis saat *runtime*
  - *Stack* — variabel lokal dan parameter fungsi
- **Status proses (*process states*):**
  - **New** — sedang dibuat
  - **Ready** — menunggu alokasi CPU
  - **Running** — instruksi sedang dieksekusi
  - **Waiting** — menunggu peristiwa I/O
  - **Terminated** — selesai eksekusi
- **Process Control Block (PCB):** Struktur data kernel yang menyimpan *Process State*, *Program Counter* (PC), Register CPU, Informasi Penjadwalan, Manajemen Memori, dan Status I/O.

### 2. Penjadwalan Proses & Context Switch

- **Scheduling queues:** Proses dikelompokkan dalam *Ready Queue* dan berbagai *Wait Queue*.
- **Context switch:** Saat CPU berpindah proses, OS menyimpan status proses lama ke PCB-nya (*state save*) dan memuat status proses baru dari PCB-nya (*state restore*). Waktu *context switch* murni *overhead*.

### 3. Operasi Standar Proses

- **Pembuatan (*creation*):** Proses induk (*parent*) membuat proses anak (*child*) lewat `fork()`. Induk dapat menunggu anak selesai lewat `wait()`.
- **Penghentian (*termination*):** Proses menghentikan dirinya sendiri lewat `exit()`.

### 4. Kerjasama Antar-Proses (IPC - Interprocess Communication)

- **Shared Memory Model:** Proses berbagi wilayah memori bersama. Akses sangat cepat karena kernel hanya terlibat saat pembuatan memori bersama.
- **Message Passing Model:** Proses bertukar pesan lewat `send()` dan `receive()` tanpa berbagi alamat memori. Cocok untuk sistem terdistribusi.
  - *Direct / Indirect:* Komunikasi langsung menyebut nama proses penerima; tidak langsung menggunakan *mailbox* / *port*.
  - *Synchronous / Asynchronous:* `send/receive` dapat bersifat *blocking* (sinkron) atau *nonblocking* (asinkron).

### 5. Komunikasi Client-Server

- **Sockets:** *Endpoint* komunikasi berupa gabungan Alamat IP dan Nomor Port.
- **RPC (Remote Procedure Calls):** Mengabstraksi pemanggilan prosedur jarak jauh melalui jaringan menggunakan *daemon* dan mekanisme *marshaling* parameter.

---

## Minggu 4: Multithreaded Programming

### 1. Definisi Thread & Multithreading

- **Elemen thread:** Thread adalah unit dasar penggunaan CPU yang memiliki Thread ID, Program Counter (PC), himpunan register, dan *stack* sendiri.
- **Resource sharing:** Thread dalam proses yang sama berbagi kode (*text*), data (*global variables*), dan sumber daya OS (*open files*).

### 2. Pemrograman Multicore

- Menggunakan beberapa *core* pada satu *chip* fisik.
- Pada *single-core*, multithreading berjalan bergantian (*interleaved*); pada *multicore*, thread benar-benar dieksekusi secara simultan.

### 3. Konsep Multithreading

- **Keuntungan:**
  - *Responsiveness* — aplikasi tidak membeku
  - *Resource Sharing* — berbagi memori secara otomatis
  - *Economy* — pembuatan dan *context switch* thread jauh lebih ringan daripada proses
  - *Scalability* — dapat memanfaatkan sistem *multicore*
- **Concurrency vs. Parallelism:** *Concurrency* memungkinkan beberapa tugas membuat kemajuan (*progress*), sedangkan *Parallelism* menjalankan beberapa tugas secara simultan pada *core* fisik yang berbeda.
- **Tipe paralelisme:**
  - **Data Parallelism** — membagi subset data ke beberapa *core*
  - **Task Parallelism** — membagi tugas/fungsi unik ke beberapa *core*
- **Hukum Amdahl:** Menentukan *speedup* maksimum saat menambah *N* pemroses pada program dengan bagian serial \(S\):

  $$Speedup \le \frac{1}{S + \frac{1-S}{N}}$$

  Jika \(N \to \infty\), *speedup* dibatasi oleh \(1/S\).

### 4. Model Multithreading

| Model | Penjelasan |
|---|---|
| **Many-to-One** | Banyak *user thread* dipetakan ke satu *kernel thread*. Efisien, tetapi seluruh proses terblokir jika satu thread melakukan *blocking system call*. |
| **One-to-One** | Satu *user thread* dipetakan ke satu *kernel thread*. Konkurensi lebih tinggi (dipakai Linux dan Windows). |
| **Many-to-Many** | Banyak *user thread* dipetakan ke *kernel thread* dalam jumlah yang sama atau lebih sedikit. |
| **Two-Level** | Variasi Many-to-Many yang mengizinkan *user thread* tertentu diikat (*bound*) ke satu *kernel thread* spesifik. |

### 5. Thread Libraries & Implicit Threading

- **Thread libraries:** POSIX Pthreads, Windows Threads, dan Java Threads.
- **Implicit threading:** Pembuatan dan pengelolaan thread diserahkan kepada kompilator dan pustaka *runtime*:
  - **Thread Pools** — menyiapkan sejumlah thread di awal
  - **Fork-Join Framework**
  - **OpenMP** — arahan kompilator `#pragma omp parallel`
  - **Intel TBB**

---

## Minggu 5: Penjadwalan CPU

### 1. Konsep Dasar Penjadwalan CPU

- **CPU-I/O Burst Cycle:** Eksekusi proses terdiri dari siklus eksekusi CPU (*CPU burst*) dan penantian I/O (*I/O burst*).
- **Preemptive vs. Nonpreemptive:**
  - *Nonpreemptive* — proses berjalan sampai selesai atau meminta I/O.
  - *Preemptive* — CPU dapat diambil paksa dari proses yang berjalan, mis. saat proses baru tiba.
- **Dispatcher:** Komponen yang memberi kendali CPU kepada proses pilihan *scheduler*. Waktu yang dibutuhkan disebut **Dispatch Latency**.

### 2. Kriteria Penjadwalan

- **Dimaksimalkan:** CPU Utilization dan Throughput (jumlah proses selesai per unit waktu).
- **Diminimalkan:** Turnaround Time (total waktu dari masuk hingga selesai), Waiting Time (waktu di *ready queue*), dan Response Time (waktu hingga respons pertama).

### 3. Algoritme Penjadwalan

| Algoritme | Penjelasan |
|---|---|
| **FCFS** (First-Come, First-Served) | *Nonpreemptive*. Mengalami **Convoy Effect** bila proses panjang berjalan lebih dulu dan menghambat proses pendek di belakangnya. |
| **SJF** (Shortest-Job-First) | Menjadwalkan proses dengan *CPU burst* terkecil berikutnya; **optimal** untuk rata-rata waktu tunggu terkecil. Versi *preemptive*: **Shortest-Remaining-Time-First (SRTF)**. |
| **Round-Robin (RR)** | Berbasis *time quantum* (*time slice*). Quantum terlalu besar → menjadi FCFS; terlalu kecil → *context switch overhead* membengkak. |
| **Priority Scheduling** | Berdasarkan angka prioritas. Berpotensi **Starvation**, diatasi dengan **Aging** (menaikkan prioritas secara bertahap). |
| **Multilevel Queue** | *Ready queue* dibagi menjadi beberapa antrean terpisah berdasarkan jenis proses (mis. *interactive* vs *batch*). |
| **Multilevel Feedback Queue (MLFQ)** | Proses dapat berpindah antar-antrean berdasarkan durasi *CPU burst*; paling umum dan paling fleksibel. |

---

## Minggu 6: Penjadwalan Tingkat Lanjut & Real-Time

### 1. Multiple-Processor Scheduling

- **Symmetric Multiprocessing (SMP):** Setiap pemroses menjadwalkan dirinya sendiri, menggunakan antrean bersama (*common queue*) atau antrean per-*core* (*per-core run queues*). Antrean per-*core* membutuhkan **Load Balancing** (*push migration* atau *pull migration*).
- **Multicore & CMT:** *Chip Multithreading* (CMT) atau *Hyper-threading* (SMT) menempatkan beberapa *hardware thread* pada satu *core* untuk menutupi *memory stall*.
- **Heterogeneous Multiprocessing (HMP):** Menggabungkan *core* cepat berdaya tinggi (*big*) dan *core* lambat hemat energi (*LITTLE*), seperti pada ARM big.LITTLE.

### 2. Penjadwalan Thread

- **PCS (Process-Contention Scope):** Menjadwalkan *user-level thread* ke LWP (*Lightweight Process*).
- **SCS (System-Contention Scope):** Menjadwalkan *kernel thread* ke CPU fisik.

### 3. Real-Time Systems Scheduling

- **Soft vs. Hard Real-Time:** *Soft* hanya memberi prioritas utama; *Hard* menjamin tugas selesai sebelum *deadline*.
- **Tugas periodik:** Memiliki waktu pemrosesan \(t\), *deadline* \(d\), dan periode \(p\).
- **Rate-Monotonic Scheduling (RMS):** Prioritas statis berbanding terbalik dengan periode \(p\) (periode lebih pendek = prioritas lebih tinggi). Utilisasi CPU maksimum dibatasi oleh \(N(2^{1/N} - 1)\), sekitar 69% untuk \(N \to \infty\).
- **Earliest-Deadline-First (EDF):** Prioritas **dinamis** berdasarkan *deadline* terdekat. Secara teoritis dapat mencapai utilisasi CPU hingga 100%.

### 4. Contoh Penjadwal Sistem Operasi Nyata

- **Linux CFS (Completely Fair Scheduler):** Menghapus *time slice* tradisional dan mengalokasikan proporsi CPU berdasarkan **nice value** (-20 hingga 19) dan **targeted latency**. Durasi eksekusi dicatat dengan **vruntime** yang disimpan dalam **Red-Black Tree**.
- **Windows Dispatcher:** Skema prioritas *preemptive* 32 tingkat (1–15 untuk *variable class*, 16–31 untuk *real-time class*).

---

## Minggu 7: Sinkronisasi Proses & Deadlock

### 1. Konsep Konkurensi & Critical Section

- **Race Condition:** Beberapa proses memanipulasi data bersama secara bersamaan dan hasil akhirnya bergantung pada urutan eksekusi instruksi.
- **Critical-Section Problem:** Bagian kode dalam proses yang mengakses data bersama (*shared data*).

### 2. Syarat Solusi Critical Section

1. **Mutual Exclusion:** Jika satu proses berada di *critical section*, tidak ada proses lain yang boleh masuk.
2. **Progress:** Keputusan memilih proses yang masuk berikutnya tidak boleh ditunda tanpa batas.
3. **Bounded Waiting:** Ada batas berapa kali proses lain boleh masuk *critical section* setelah suatu proses mengajukan permintaan masuk.

### 3. Mekanisme Konkurensi

- **Dukungan perangkat keras:**
  - *Memory Barriers* — memaksa urutan memori dimuat/disimpan secara konsisten
  - *Compare-and-Swap (CAS)* — instruksi atomik untuk memperbarui nilai variabel secara aman
  - *Atomic Variables* — variabel yang diperbarui secara atomik tanpa penguncian terpisah
- **Mutex Locks:** Penguncian biner sederhana lewat `acquire()` dan `release()` (sering memicu *busy waiting* / *spinlock*).
- **Semaphores:** Variabel integer yang diakses lewat dua fungsi atomik, `wait()` (\(P\)) dan `signal()` (\(V\)). Terdiri dari *Counting Semaphore* dan *Binary Semaphore*; dapat diimplementasikan dengan *blocking queue* untuk menghindari *busy waiting*.
- **Monitors:** Konstruk bahasa tingkat tinggi (ADT) yang menjamin *mutual exclusion* secara otomatis dan menggunakan *condition variables* dengan `wait()` dan `signal()`.

### 4. Kasus Klasik Sinkronisasi

- **Bounded-Buffer Problem (Producer-Consumer):** Menggunakan semaphore `mutex`, `empty`, dan `full`.
- **Readers-Writers Problem:** Mencegah *writer* mengganggu *reader* dan sebaliknya.
- **Dining-Philosophers Problem:** Mengalokasikan beberapa sumber daya terbatas di antara beberapa proses tanpa deadlock atau starvation.

### 5. Deadlock dan Metode Penanganannya

- **Definisi:** Setiap proses dalam suatu himpunan menunggu kejadian yang hanya bisa disebabkan oleh proses lain dalam himpunan yang sama.
- **4 syarat deadlock (harus terjadi bersamaan):**
  1. *Mutual Exclusion* — minimal satu sumber daya *non-sharable*
  2. *Hold and Wait* — proses memegang sumber daya sambil menunggu yang lain
  3. *No Preemption* — sumber daya tidak bisa diambil paksa
  4. *Circular Wait* — rantai melingkar proses yang saling menunggu
- **Metode penanganan:**

| Metode | Penjelasan |
|---|---|
| **Prevention** | Menghilangkan salah satu dari 4 syarat. Yang paling praktis: memutus *circular wait* dengan penomoran urutan sumber daya. |
| **Avoidance** | Menjaga sistem selalu dalam **Safe State**, menggunakan **Banker's Algorithm** untuk memeriksa alokasi maksimum yang aman sebelum mengabulkan permintaan. |
| **Detection & Recovery** | Menjalankan algoritme pendeteksi (*wait-for graph*) secara berkala, lalu memulihkan sistem lewat *process termination* atau *resource preemption*. |