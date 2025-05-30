# Kelompok 9

# Judul Program

Aplikasi Romberg Integration dalam Analisis Kecepatan Freefall Skydiving Dengan Bahasa C

# Nama Anggota dan NPM:
- Bonifasius Raditya Pandu Hendrianto (2306242350)
- Bryan Herdianto (2306210885)
- Deandro Najwan Ahmad Syahbanna (2306213174)
- Falah Andhesryo (2306161990)
- Wesley Frederick Oh (2306202763)

## Penjelasan Program

Program ini menyelesaikan kasus perhitungan jarak tempuh objek yang jatuh dengan hambatan udara menggunakan metode Romberg Integration. Program menerima input berupa massa objek (kg), koefisien drag (kg/s), dan waktu (s), kemudian menghitung total jarak yang ditempuh oleh objek tersebut. Kasus ini merupakan aplikasi fisika real-world dimana objek yang jatuh tidak hanya dipengaruhi oleh gravitasi, tetapi juga mengalami hambatan udara yang mempengaruhi kecepatan dan jarak tempuhnya.

Metode Romberg Integration digunakan untuk menyelesaikan integrasi numerik dari fungsi kecepatan v(t) = (gm/c) * (1 - e^(-(c/m)*t)) untuk mendapatkan jarak tempuh. Metode ini menggabungkan aturan trapesium dengan Richardson extrapolation untuk meningkatkan akurasi perhitungan. Program menampilkan tabel iterasi Romberg yang menunjukkan proses konvergensi menuju hasil yang akurat, dengan output akhir berupa jarak tempuh dalam meter.
