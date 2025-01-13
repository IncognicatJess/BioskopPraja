#define PROFILDAT "./Database/Akun/DataProfil.dat"

// LIBRARY STANDARD
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>


typedef struct {
    char tempat[50];
    int tanggal;
    int bulan;
    int tahun;
} TempatTanggalLahir;

typedef struct {
    char ID[10];
    char username[50];
    char nama[50];
    TempatTanggalLahir TTL;
    char jabatan[20];
    int noHP[12];
} ProfilData;


int main(){

}



void TambahProfilDefault(FILE *file)
{
    //Menambahkan profil default dengan " - " pada nama dan tempat dan angka tertentu pada beberapa data

    ProfilData profilDefault;
    memset(&profilDefault, 0, sizeof(ProfilData));

    strncpy(profilDefault.nama, " - ", sizeof(profilDefault.nama) - 1);
    strncpy(profilDefault.TTL.tempat, " - ", sizeof(profilDefault.TTL.tempat) - 1);

    //menampilkan dengan tanggal default pada laptop
    profilDefault.TTL.tanggal = 01;
    profilDefault.TTL.bulan = 01;
    profilDefault.TTL.tahun = 2025;

    fwrite(&profilDefault, sizeof(ProfilData), 1, file);
}

void EditProfil(){
    ProfilData profil;
    FILE *file = fopen(PROFILDAT, "a+b");
    if (!file)
    {
        printf("Gagal membuka file database.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0)
    {
        TambahProfilDefault(file);
    }
    rewind(file);

    while(1){
        const char judul = "==== Edit Profil ====\n\n";
        printf(judul);
        printf("ID           : ACT001");
        printf("Username     : Admin");
        printf("Nama         :");
        scanf("%[\^n]", profil.nama);
        printf("TTL          :");
        scanf("%[\^n], %d/%d/%d", profil.TTL.tempat, &profil.TTL.tanggal, &profil.TTL.bulan, &profil.TTL.tahun);
        printf("No HP        :");
        scanf("%d", &profil.noHP);

        TombolKonfirmasi(judul);

        


    }
}


int TombolKonfirmasi(const char *judul)
{
    const char *pilihan[] = {"BATAL", "KONFIRMASI"};
    int indeks = 0;
    char key;

    while (1)
    {
        
        printf("%s\n\n", judul);

        for (int i = 0; i < 2; i++)
        {
            if (i == indeks)
            {
                printf(" >[%s]\n", pilihan[i]);
            }
            else
            {
                printf("  [%s]\n", pilihan[i]);
            }
        }

        key = getch();
        if (key == 75 || key == 72) // Panah kiri atau atas
            indeks = (indeks - 1 + 2) % 2;
        else if (key == 77 || key == 80) // Panah kanan atau bawah
            indeks = (indeks + 1) % 2;
        else if (key == '\r') // Enter
            return indeks;
    }
}
