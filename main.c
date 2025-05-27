#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Struktur untuk menyimpan detail kredit
typedef struct {
    double hargaMotor;        // Harga motor
    double uangMuka;          // Uang muka (DP)
    int lamaAngsuran;         // Lama angsuran dalam bulan
    double angsuranPerBulan;  // Jumlah angsuran per bulan
} DetailKredit;

// Fungsi untuk menghitung nilai present value dari anuitas
// Parameters:
// - rate: suku bunga yang ditebak (dalam desimal)
// - kredit: pointer ke struktur DetailKredit
// Return: nilai present value dikurangi pokok pinjaman
double hitungPresentValue(double rate, DetailKredit *kredit) {
    double pokokPinjaman = kredit->hargaMotor - kredit->uangMuka;
    double pv = 0;
    
    // Menghitung present value dari seluruh angsuran
    for (int i = 1; i <= kredit->lamaAngsuran; i++) {
        pv += kredit->angsuranPerBulan / pow(1 + rate, i);
    }
    
    // Mengembalikan selisih present value dengan pokok pinjaman
    return pv - pokokPinjaman;
}

// Fungsi untuk menghitung turunan dari fungsi present value
// Parameters:
// - rate: suku bunga yang ditebak (dalam desimal)
// - kredit: pointer ke struktur DetailKredit
// Return: nilai turunan fungsi present value
double hitungTurunanPV(double rate, DetailKredit *kredit) {
    double derivative = 0;
    
    // Menghitung turunan present value terhadap rate
    for (int i = 1; i <= kredit->lamaAngsuran; i++) {
        derivative += (-i * kredit->angsuranPerBulan) / pow(1 + rate, i + 1);
    }
    
    return derivative;
}

// Fungsi implementasi Metode Newton-Raphson
// Parameters:
// - tebakan_awal: nilai awal suku bunga yang ditebak
// - toleransi: batas toleransi error
// - max_iterasi: maksimum iterasi yang diizinkan
// - kredit: pointer ke struktur DetailKredit
// Return: suku bunga hasil perhitungan
double newtonRaphson(double tebakan_awal, double toleransi, int max_iterasi, DetailKredit *kredit) {
    double x0 = tebakan_awal;
    double x1;
    int iterasi = 0;
    
    printf("\nIterasi\t\tSuku Bunga\t\tError\n");
    printf("------------------------------------------------\n");
    
    do {
        // Menghitung f(x) dan f'(x)
        double fx = hitungPresentValue(x0, kredit);
        double dfx = hitungTurunanPV(x0, kredit);
        
        // Mencegah pembagian dengan nol
        if (fabs(dfx) < 1e-10) {
            printf("Error: Turunan terlalu kecil, metode tidak konvergen.\n");
            return -1;
        }
        
        // Menghitung nilai x yang baru
        x1 = x0 - fx/dfx;
        
        // Menghitung error
        double error = fabs(x1 - x0);
        
        printf("%d\t\t%.8f\t\t%.8f\n", iterasi + 1, x1, error);
        
        // Update nilai x
        x0 = x1;
        iterasi++;
        
        // Cek konvergensi
        if (error < toleransi) {
            printf("\nMetode konvergen setelah %d iterasi\n", iterasi);
            return x1;
        }
        
        // Cek maksimum iterasi
        if (iterasi >= max_iterasi) {
            printf("Error: Mencapai maksimum iterasi tanpa konvergen\n");
            return -1;
        }
        
    } while (1);
}

int main() {
    DetailKredit kredit;
    
    // Input data kredit
    printf("=== Program Perhitungan Suku Bunga Efektif Kredit Motor ===\n\n");
    
    printf("Masukkan harga motor: ");
    scanf("%lf", &kredit.hargaMotor);
    
    printf("Masukkan uang muka (DP): ");
    scanf("%lf", &kredit.uangMuka);
    
    printf("Masukkan lama angsuran (bulan): ");
    scanf("%d", &kredit.lamaAngsuran);
    
    printf("Masukkan angsuran per bulan: ");
    scanf("%lf", &kredit.angsuranPerBulan);
    
    // Parameter untuk metode Newton-Raphson
    double tebakan_awal = 0.01;  // Tebakan awal 1%
    double toleransi = 1e-8;     // Toleransi error
    int max_iterasi = 100;       // Maksimum iterasi
    
    // Menghitung suku bunga efektif
    double suku_bunga = newtonRaphson(tebakan_awal, toleransi, max_iterasi, &kredit);
    
    if (suku_bunga > 0) {
        printf("\nHasil Perhitungan:\n");
        printf("Suku bunga per bulan: %.4f%%\n", suku_bunga * 100);
        printf("Suku bunga per tahun: %.4f%%\n", suku_bunga * 12 * 100);
        
        // Menampilkan rincian kredit
        double pokokPinjaman = kredit.hargaMotor - kredit.uangMuka;
        printf("\nRincian Kredit:\n");
        printf("Harga Motor: Rp %.2f\n", kredit.hargaMotor);
        printf("Uang Muka: Rp %.2f\n", kredit.uangMuka);
        printf("Pokok Pinjaman: Rp %.2f\n", pokokPinjaman);
        printf("Angsuran per bulan: Rp %.2f\n", kredit.angsuranPerBulan);
        printf("Total Pembayaran: Rp %.2f\n", kredit.angsuranPerBulan * kredit.lamaAngsuran);
        printf("Total Bunga: Rp %.2f\n", (kredit.angsuranPerBulan * kredit.lamaAngsuran) - pokokPinjaman);
    }
    
    return 0;
}
