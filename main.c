#include <stdio.h>
#include <math.h>

// Fungsi untuk menghitung kecepatan pada waktu t
double velocity(double t, double m, double c) {
    const double g = 9.81; // percepatan gravitasi m/s^2
    return (g * m / c) * (1 - exp(-(c/m) * t));
}

// Fungsi untuk Romberg Integration
double romberg(double a, double b, double m, double c, int n) {
    double h = b - a;
    double R[20][20] = {0}; // Array untuk menyimpan hasil integrasi
    int i, j, k;
    
    // Hitung R(0,0) menggunakan aturan trapesium dengan satu interval
    R[0][0] = h * (velocity(a, m, c) + velocity(b, m, c)) / 2.0;
    
    // Iterasi untuk setiap level
    for (i = 1; i < n; i++) {
        h = h / 2.0;
        double sum = 0;
        
        // Hitung sum untuk points baru
        for (k = 1; k <= pow(2, i) - 1; k += 2) {
            sum += velocity(a + k * h, m, c);
        }
        
        // Compute R(i,0)
        R[i][0] = R[i-1][0] / 2.0 + h * sum;
        
        // Compute R(i,j) using Richardson extrapolation
        for (j = 1; j <= i; j++) {
            double pow4j = pow(4, j);
            R[i][j] = (pow4j * R[i][j-1] - R[i-1][j-1]) / (pow4j - 1);
        }
    }
    
    //tes print table romberg dari O(h^2)
    printf("\nRomberg Integration Table\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j <= i; j++) {
            printf("%-15.8f", R[i][j]);
        }
        printf("\n");
    }
    printf("-------------------------------------------\n");
    
    // Return hasil akhir (sudut kanan bawah dari tabel Romberg)
    return R[n-1][n-1];
}

int main() {
    double m, c, t;
    int n = 6; // Jumlah iterasi Romberg (dapat disesuaikan untuk akurasi)
    
    // Input dari pengguna
    printf("Masukkan massa (kg): ");
    scanf("%lf", &m);
    
    printf("Masukkan koefisien drag (kg/s): ");
    scanf("%lf", &c);
    
    printf("Masukkan waktu (s): ");
    scanf("%lf", &t);
    
    // Hitung jarak menggunakan Romberg integration
    double distance = romberg(0, t, m, c, n);
    
    // Tampilkan hasil
    printf("\nHasil Perhitungan:\n");
    printf("Jarak yang ditempuh: %.2f meter\n", distance);
    
    return 0;
}