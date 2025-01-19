// Prototipe fungsi tambahan
void clearScreen();
void tampilkanProfilKasirTiket();
void tampilkanPemesananTiket();
void tampilkanJadwalTayang();
void tampilkanLaporanTiket();
void tampilkanFilmKasir();
int tampilkanMenuTiketNavigasi();
void cariFilmByIDOrJudul(const char *keyword);




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
void tampilkanPemesananTiket()
{
    while (1)
    {
        clearScreen();
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
void tampilkanFilmKasir()
{
    while (1) {
        system("cls");

        // Input pencarian
        char keyword[50];
        printf("\nMasukkan ID atau Judul Film: ");
        fgets(keyword, sizeof(keyword), stdin);
        keyword[strcspn(keyword, "\n")] = '\0'; // Hapus newline

        // Jika pengguna ingin keluar
        if (strcmp(keyword, "EXIT") == 0) {
            break;
        }

        // Cari film berdasarkan input
        cariFilmByIDOrJudul(keyword);

        printf("\nTekan Enter untuk kembali ke pencarian...");
        getchar();
    }
}

// Fungsi untuk menampilkan laporan transaksi
void tampilkanLaporanTiket()
{
    // while (1)
   
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
            // tampilkanPemesanan();
            break;
        case 3:
            // tampilkanDaftarJadwalTayang();
            break;
        case 4:
            tampilkanFilmKasir();
            break;
        case 5:
            // tampilkanLaporanTiket();
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
int DashboardUser(AkunData *akun)
{

    ProfilData profil = {0};
    tampilkanMenuTiket(akun, &profil);
    return 0;
}
