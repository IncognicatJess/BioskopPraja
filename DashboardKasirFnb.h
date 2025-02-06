// Prototipe fungsi tambahan
void clearScreen();
void tampilkanProfilKasirFnb();
void tampilkanPemesananFnb();
void tampilkanLaporanFnb();
void tampilkanFnbKasir();
int tampilkanMenuTiketNavigasi();
void cariMenuByID(const char *keyword);

#include "Transaksi/transaksifnb.h"

// Fungsi untuk menampilkan menu dengan navigasi arrow key
int tampilkanMenuFnbNavigasi()
{
    int pilihan = 1;       // Variabel untuk menyimpan pilihan menu (mulai dari 1)
    int jumlahPilihan = 5; // Jumlah total pilihan menu
    char key;              // Variabel untuk menyimpan input tombol

    // Daftar menu
    const char *menu[] = {
        "PROFIL",
        "PEMESANAN",
        "DAFTAR FNB",
        "LAPORAN",
        "LOGOUT"};

    while (1)
    {
        clearScreen();
        printf("=== DASHBOARD MENU F&B ===\n");

        // Tampilkan menu dengan warna yang sesuai
        for (int i = 0; i < jumlahPilihan; i++)
        {
            if (i + 1 == pilihan)
            { // Perhatikan: i + 1 untuk menyesuaikan pilihan yang dimulai dari 1
                // Highlight opsi yang dipilih dengan warna background cyan
                printf(" > \033[48;2;62;254;255m %s \033[0m \n", menu[i]);
            }
            else
            {
                // Tampilkan opsi biasa
                printf("   %s\n", menu[i]);
            }
        }

        // Input tombol dari pengguna
        key = getch();

        if (key == 72)
        { // Tombol Arrow Up
            pilihan--;
            if (pilihan < 1)
                pilihan = jumlahPilihan; // Reset ke pilihan terakhir
        }
        else if (key == 80)
        { // Tombol Arrow Down
            pilihan++;
            if (pilihan > jumlahPilihan)
                pilihan = 1; // Reset ke pilihan pertama
        }
        else if (key == '\r')
        {                   // Tombol Enter
            return pilihan; // Kembalikan nilai pilihan (mulai dari 1)
        }
    }
}

// Fungsi untuk menampilkan profil admin
void tampilkanProfilKasirFnb(AkunData *akun, ProfilData *profil)
{

    while (1)
    {
        clearScreen();

        const char *menuProfil[] = {"KEMBALI"};

        int pilihan = PilihOpsi("Profil", menuProfil, akun, profil, 1);

        ReadProfile(akun, profil);

        switch (pilihan)
        {
        case 0:
            system("cls");
            ReadProfile(akun, profil);
        }
        if (pilihan == 0)
        {
            break;
        }
    }
}

// Fungsi untuk menampilkan daftar akun
void tampilkanPemesananFnb()
{
    while (1)
    {
        system("cls");
        TransaksiMakanan();
    }
}
/*
void tampilkanJadwalTayang()
{
    while (1)
    {

    }
}
*/
void tampilkanFnbKasir()
{
    while (1)
    {
        system("cls");
        ReadFnb();

        // Input pencarian
        char keyword[50];
        printf("\nMasukkan ID Menu: ");
        fgets(keyword, sizeof(keyword), stdin);
        keyword[strcspn(keyword, "\n")] = '\0'; // Hapus newline

        // Jika pengguna ingin keluar
        if (strcmp(keyword, "-1") == 0)
        {
            break;
        }

        // Cari film berdasarkan input
        cariMenuByID(keyword);

        printf("\nTekan Enter untuk kembali ke pencarian...");
        getchar();
    }
}

// Fungsi untuk menampilkan laporan transaksi
void tampilkanLaporanFnb()
{
    // while (1)
}

// Fungsi untuk menampilkan menu utama
void tampilkanMenuFnb(AkunData *akun, ProfilData *profil)
{
    int pilihan;

    do
    {
        pilihan = tampilkanMenuFnbNavigasi();

        switch (pilihan)
        {
        case 1:
            tampilkanProfilKasirFnb(akun, profil);
            break;
        case 2:
            tampilkanPemesananFnb();
            break;
        case 3:
            tampilkanFnbKasir();
            break;
        case 4:
            // tampilkanLaporanFnb();
            break;
        case 5:
            TampilkanPesan("Logging out...\n", 1);
            return loginPage(); // Kembali ke halaman login
        default:
            TampilkanPesan("Fitur belum tersedia!\n", 1);
            break;
        }
    } while (1);
    //  if(pilihan == 8){return main();}
}

// MAIN
int DashboardUserFnb(AkunData *akun)
{

    ProfilData profil = {0};
    tampilkanMenuFnb(akun, &profil);
    return 0;
}
