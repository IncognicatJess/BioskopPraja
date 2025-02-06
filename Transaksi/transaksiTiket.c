#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

typedef struct{
    int tanggal;
    int bulan;
    int tahun;
} tanggal;

typedef struct
{
    char ID[10];
    char IDSchedule[10];
    char IDFilm[10];
    char IDKursi[10];
    int NoTeater;
    char JudulFilm[50];
    int Tiket;
    char genre[50];
    char studio[50];
    float hargatiket;
    double ttlHarga;
    char MtdPembayaran;
    tanggal Tgl;
    int JamAwal;
} TransFilm;

int ReadSchedule();

int main()
{
    pilihMenu();
    PemesananTiket();

    TampilkanPesan("\nTransaksi selesai. Terima kasih!\n",2);
    return 0;
}

void PemesananTiket(){
ReadSchedule();



}