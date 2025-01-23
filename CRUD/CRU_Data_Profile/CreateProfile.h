#ifndef CREATE_PROFIL_H
#define CREATE_PROFIL_H
#define MAX_PROFILES 1000

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// Deklarasi fungsi
void EditProfil(AkunData *akun, ProfilData *profil);
bool ValidasiNama(const char *nama);
bool ValidasiTempat(const char *tempat);
bool ValidasiTL(int tanggal, int bulan, int tahun);
bool ValidasiNoHP(const char *noHP);

void EditProfil(AkunData *akun, ProfilData *profil)
{
    char nama[50] = "";
    char tempat[50] = "";
    int tanggal = 1, bulan = 1, tahun = 1900;
    char noHP[13] = "";
    int step = 0;

    FILE *file = fopen(PROFILDAT, "rb+");
    if (!file)
    {
        file = fopen(PROFILDAT, "wb+");
        if (!file)
        {
            perror("Gagal membuka file");
            return;
        }
    }

    // Menentukan ID Profil berdasarkan ID Akun
    snprintf(profil->ID, sizeof(profil->ID), "PRF%03d", atoi(&akun->ID[3]));

    // Mencari apakah profil dengan ID yang sesuai sudah ada
    ProfilData temp;
    bool profilDitemukan = false;
    long posisi = -1;

    rewind(file);
    while (fread(&temp, sizeof(ProfilData), 1, file))
    {
        if (strcmp(temp.ID, profil->ID) == 0)
        {
            profilDitemukan = true;
            posisi = ftell(file) - sizeof(ProfilData);
            break;
        }
    }

    // Jika profil ditemukan, salin data lama sebagai default
    if (profilDitemukan)
    {
        strncpy(nama, temp.nama, sizeof(nama) - 1);
        strncpy(tempat, temp.TTL.tempat, sizeof(tempat) - 1);
        tanggal = temp.TTL.tanggal;
        bulan = temp.TTL.bulan;
        tahun = temp.TTL.tahun;
        strncpy(noHP, temp.noHP, sizeof(noHP) - 1);
    }

    // Proses pengeditan profil
    while (1)
    {
        system("cls");
        printf("==== Edit Profil ====\n");
        printf("Nama    : %s%s\n", step == 0 ? ">" : "", nama);
        printf("TTL     : %s%s, %02d/%02d/%4d\n", step == 1 ? ">" : "", tempat, tanggal, bulan, tahun);
        printf("NO HP   : %s%s\n\n", step == 3 ? ">" : "", noHP);

        switch (step)
        {
        case 0:
            printf("\nMasukkan Nama: ");
            scanf(" %49[^\n]", nama);
            if (ValidasiNama(nama))
                step++;
            else
                TampilkanPesan("Nama tidak valid. Harus hanya berupa huruf atau spasi.\n", 2);
            break;

        case 1:
            printf("\nMasukkan Tempat Lahir: ");
            scanf(" %49[^\n]", tempat);
            if (ValidasiTempat(tempat))
                step++;
            else
                TampilkanPesan("Tempat lahir tidak valid. Harus berupa huruf, angka, '.' atau '-'.\n", 2);
            break;

        case 2:
            printf("\nMasukkan Tanggal Lahir (DD/MM/YYYY): ");
            scanf("%d/%d/%d", &tanggal, &bulan, &tahun);
            if (ValidasiTL(tanggal, bulan, tahun))
                step++;
            else
                TampilkanPesan("Tanggal lahir tidak valid.\n", 2);
            break;

        case 3:
            printf("\nMasukkan Nomor HP (hanya angka, maks. 12 digit): ");
            scanf(" %12s", noHP);
            if (ValidasiNoHP(noHP))
                step++;
            else
                TampilkanPesan("Nomor HP tidak valid. Harus berupa angka maksimal 12 digit.\n", 2);
            break;

        default:
            strncpy(profil->nama, nama, sizeof(profil->nama) - 1);
            strncpy(profil->TTL.tempat, tempat, sizeof(profil->TTL.tempat) - 1);
            profil->TTL.tanggal = tanggal;
            profil->TTL.bulan = bulan;
            profil->TTL.tahun = tahun;
            strncpy(profil->noHP, noHP, sizeof(profil->noHP) - 1);

            int konfirmasiIndex = TombolKonfirmasi("Profil", "Edit", profil, "ProfilData");

            if (konfirmasiIndex == 1)
            {
                if (profilDitemukan && posisi >= 0)
                {
                    // Update profil di posisi yang ditemukan
                    fseek(file, posisi, SEEK_SET);
                }
                else
                {
                    // Tambahkan profil baru
                    fseek(file, 0, SEEK_END);
                }

                fwrite(profil, sizeof(ProfilData), 1, file);
                TampilkanPesan("\nData berhasil diperbarui!\n", 2);
            }
            else
            {
                TampilkanPesan("Perubahan dibatalkan.\n", 2);
            }
            fclose(file);
            return;
        }
    }
}

bool ValidasiNama(const char *nama)
{
    for (int i = 0; nama[i] != '\0'; i++)
    {
        if (!isalpha(nama[i]) && nama[i] != ' ')
        {
            return false;
        }
    }
    return true;
}

bool ValidasiTempat(const char *tempat)
{
    for (int i = 0; tempat[i] != '\0'; i++)
    {
        if (!isalnum(tempat[i]) && tempat[i] != '.' && tempat[i] != '-')
        {
            return false;
        }
    }
    return true;
}

bool ValidasiTL(int tanggal, int bulan, int tahun)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int tahunSekarang = tm.tm_year + 1900;

    if (tahun < 1900 || tahun > tahunSekarang || bulan < 1 || bulan > 12)
    {
        return false;
    }

    int hariPerBulan[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((tahun % 4 == 0 && tahun % 100 != 0) || tahun % 400 == 0)
    {
        hariPerBulan[1] = 29; // Tahun kabisat
    }

    return tanggal > 0 && tanggal <= hariPerBulan[bulan - 1];
}

bool ValidasiNoHP(const char *noHP)
{
    int len = strlen(noHP);
    if (len == 0 || len > 12)
        return false;
    for (int i = 0; i < len; i++)
    {
        if (!isdigit(noHP[i]))
            return false;
    }
    return true;
}

#endif // CREATE_PROFIL_H
