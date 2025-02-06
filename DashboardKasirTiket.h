// Prototipe fungsi tambahan
void clearScreen();
void tampilkanProfilKasirTiket();
void tampilkanPemesananTiket();
void tampilkanJadwalTayangTiket();
void tampilkanLaporanTiket();
void tampilkanFilmKasir();
int tampilkanMenuTiketNavigasi();
void cariFilmByIDOrJudul(const char *keyword);
int ReadSchedule();

#include "Transaksi/transaksiTiket.h"


// Fungsi untuk menampilkan menu dengan navigasi arrow key
int tampilkanMenuTiketNavigasi()
{
    int pilihan = 1;       // Indeks menu yang sedang dipilih
    int jumlahPilihan = 6; // Total menu
    char key;

    while (1)
    {
        clearScreen();
        printf("=== SIDE NAVBAR ===\n");
        printf("%s PROFIL\n", pilihan == 1 ? ">" : " ");
        printf("%s PEMESANAN\n", pilihan == 2 ? ">" : " ");
        printf("%s JADWAL TAYANG\n", pilihan == 3 ? ">" : " ");
        printf("%s DAFTAR FILM\n", pilihan == 4 ? ">" : " ");
        printf("%s LAPORAN\n", pilihan == 5 ? ">" : " ");
        printf("%s LOGOUT\n", pilihan == 6 ? ">" : " ");

        key = getch();

        if (key == 72)
        { // Arrow Up
            pilihan--;
            if (pilihan < 1)
                pilihan = jumlahPilihan;
        }
        else if (key == 80)
        { // Arrow Down
            pilihan++;
            if (pilihan > jumlahPilihan)
                pilihan = 1;
        }
        else if (key == '\r')
        { // Enter
            return pilihan;
        }
    }
}

// Fungsi untuk menampilkan profil admin
void tampilkanProfilKasirTiket(AkunData *akun, ProfilData *profil)
{

    while (1)
    {
        clearScreen();

         const char *menuProfil[] = {"GANTI SANDI", "EDIT", "KEMBALI"};

        int pilihan = PilihOpsi("Profil", menuProfil, akun, profil, 3);

        ReadProfile(akun, profil);

       switch (pilihan)
        {
        case 0:
            system("cls");
            ReadProfile(akun, profil);
            GantiSandi(akun, "Profil");

            break;
        case 1:
            system("cls");
            ReadProfile(akun, profil);
            EditProfil(akun, profil);
            break;
        case 2:
            break;
        }
        if (pilihan == 2)
        {
            break;
        }
    }
}


// Fungsi untuk menampilkan daftar akun
void tampilkanPemesananTiket()
{
      while (1)
    {
        clearScreen();

         const char *menuPemesanan[] = {"KEMBALI", "PEMESANAN"};

        int pilihan = PilihOpsi("ScheduleShowing", menuPemesanan, NULL, NULL, 2);


       switch (pilihan)
        {
        case 0:
            break;
        case 1:
           system("cls");
           PemesananTiket();
            break;
        }
        if (pilihan == 0)
        {
            break;
        }
    }
}

void tampilkanJadwalTayangTiket()
{
    while (1)
    {
        system("cls");

        const char *menuJadwalTayang[] = {"KEMBALI"};

        const char *Master = "Schedule";
        int pilihan = PilihOpsi(Master, menuJadwalTayang, NULL, NULL, 1);
        

        switch (pilihan)
        {
        case 0:
           // system("cls");
            //Pencarian("Schedule");
            break;
        }
        if (pilihan == 0)
        {
            break;
        }
    }
}

void tampilkanFilmKasir()
{
    while (1)
    {
        system("cls");

        const char *menuJadwalTayang[] = {"KEMBALI"};

        const char *Master = "Film";
        int pilihan = PilihOpsi(Master, menuJadwalTayang, NULL, NULL, 1);
        
       //ReadFilm();

        switch (pilihan)
        {
        case 0:
           // system("cls");
            //Pencarian("Schedule");
            break;
        }
        if (pilihan == 0)
        {
            break;
        }
    }
}

// Fungsi untuk menampilkan laporan transaksi
void tampilkanLaporanTiket()
{
    TampilkanPesan("Maaf fitur belum tersedia!",2);
}

// Fungsi untuk menampilkan menu utama
void tampilkanMenuTiket(AkunData *akun, ProfilData *profil)
{
    int pilihan;

    do
    {
        pilihan = tampilkanMenuTiketNavigasi();

        switch (pilihan)
        {
        case 1:
            tampilkanProfilKasirTiket(akun, profil);
            break;
        case 2:
            tampilkanPemesananTiket();
            break;
        case 3:
            tampilkanJadwalTayangTiket();
            break;
        case 4:
            tampilkanFilmKasir();
            break;
        case 5:
            tampilkanLaporanTiket();
            break;
        case 6:
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
int DashboardUserTiket(AkunData *akun)
{

    ProfilData profil = {0};
    tampilkanMenuTiket(akun, &profil);
    return 0;
}
