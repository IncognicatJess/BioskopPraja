#define FILENAME "./Database/Akun/DataFilm.dat"
#define MAX_ID 1000


typedef struct
{
    char ID[10];
    char title[50];
    char genre[20];
    int tahunRelease;
    double durasi;
    char studioFilm[20];
    char bentuk[10];
    double price;
} MovieData;

//ID, Judul, Genre, Tahun Rilis, Durasi, Studio Film, Bentuk, Harga
void BuatFilm();
bool ValidasititleCreate(const char *title);
bool ValidasiSandiCreate(const char *sandi);
bool titleUnik(const char *title, FILE *file);

int CreateFilm()
{
   
    BuatFilm();
    return 0;
}



void BuatFilm()
{
    FILE *file = fopen(FILENAME, "a+b");
    if (!file)
    {
        printf("Belum ada data!\n");
        return;
    }

    rewind(file);

    MovieData movieBaru;

    const char *pilihanGenre[] = {"Action", "Horror", "Comedy", "Drama", "Romance", "Thriller", "Sci-Fi", "Fantasy", "Animation", "Documentary"};
    const char *pilihanBentuk[] = {"2D", "3D"};
    //const double harga[] = {50000, 60000};

    int pilihanGenreIndex = 0, pilihanBentukIndex = 0; //studioIndex = 0, harga = 0;
    char title[50] = "";
    int step = 0; 

    while (1)
    {
        
        system("cls");
       // ReadFilm();
        printf("==== Tambah Film ====\n");

        printf("Judul    :");
        scanf("%[^\n]", movieBaru.title);

        printf("Tahun Rilis    :");
        scanf("%d", movieBaru.tahunRelease);

        printf("Durasi    :");
        scanf("%lf", movieBaru.durasi);
        
        printf("Studio Film    :");
        scanf("%[^\n]", movieBaru.studioFilm);

        printf("Harga    :Rp. ");
        scanf("%lf", movieBaru.price);
        

        printf("Genre Film    :");
        for (int i = 0; i < 10; i++)
        {
            if (i == pilihanGenreIndex && step == 0)
            {
                printf(" >[%s]", pilihanGenre[i]);
            }
            else
            {
                printf("  [%s]", pilihanGenre[i]);
            }
        }
        printf("\n");

        printf("Bentuk :");
        const char **bentukOptions = strcmp(pilihanBentuk[pilihanBentukIndex], "Action") == 0 ? bentuk2D : bentuk3D;
        int bentukOptionsCount = 2;
        for (int i = 0; i < bentukOptionsCount; i++)
        {
            if (i == pilihanBentukIndex && step == 1)
            {
                printf(" >[%s]", bentukOptions[i]);
            }
            else
            {
                printf("  [%s]", bentukOptions[i]);
            }
        }
        printf("\n\n");

        printf("Film: %s%s\n", step == 2 ? ">" : "", title);

        const char *pilihanKonfirmasi[] = {"BATAL", "KONFIRMASI"};
        printf("Konfirmasi: ");
        for (int i = 0; i < 2; i++)
        {
            if (i == step - 4)
            {
                printf(" >[%s]", pilihanKonfirmasi[i]);
            }
            else
            {
                printf("  [%s]", pilihanKonfirmasi[i]);
            }
        }
        printf("\n");

        char key = getch();
        if (step == 0)
        {
            if (key == 75)
                pilihanGenreIndex = (pilihanGenreIndex - 1 + 2) % 2;
            if (key == 77)
                pilihanGenreIndex = (pilihanGenreIndex + 1) % 2;
            if (key == '\r')
                step++;
        }
        else if (step == 1)
        {
            if (key == 75)
                pilihanBentukIndex = (pilihanBentukIndex - 1 + bentukOptionsCount) %  bentukOptionsCount;
            if (key == 77)
                pilihanBentukIndex = (pilihanBentukIndex + 1) % bentukOptionsCount;
            if (key == '\r')
                step++;
        }
        else if (step == 2)
        {
            if (isalnum(key) || key == '@' || key == '#')
            {
                size_t len = strlen(title);
                if (len < sizeof(title) - 1)
                {
                    title[len] = key;
                    title[len + 1] = '\0';
                }
            }
            else if (key == 8 && strlen(title) > 0)
            {
                title[strlen(title) - 1] = '\0';
            }
            else if (key == '\r' && ValidasititleCreate(title))
            {
                step++;
            }
        }
        else if (step >= 4)
        {
            int konfirmasiIndex = step - 4;
            if (key == 75 || key == 77)
            {
                konfirmasiIndex = 1 - konfirmasiIndex;
                step = 4 + konfirmasiIndex;
            }
            else if (key == '\r')
            {
                if (konfirmasiIndex == 0)
                {
                    printf("Pembuatan film dibatalkan.\n");
                    break;
                }
                else
                {
                    strncpy(movieBaru.genre, pilihanGenre[pilihanGenreIndex], sizeof(movieBaru.genre) - 1);
                    strncpy(movieBaru.studio, studioOptions[studioIndex], sizeof(movieBaru.studio) - 1);
                    strncpy(movieBaru.price, harga, sizeof(movieBaru.price) - 1);
                    
                    rewind(file);
                    bool idTerpakai[MAX_ID] = {false};
                    MovieData temp;
                    while (fread(&temp, sizeof(MovieData), 1, file))
                    {
                        if (strncmp(temp.ID, "MVE", 3) == 0)
                        {
                            int idNum = atoi(&temp.ID[3]);
                            if (idNum > 0 && idNum < MAX_ID)
                            {
                                idTerpakai[idNum] = true;
                            }
                        }
                    }
                    int idBaru = 2;
                    while (idBaru < MAX_ID && idTerpakai[idBaru])
                    {
                        idBaru++;
                    }
                    snprintf(movieBaru.ID, sizeof(movieBaru.ID), "MVE%03d", idBaru);

                    if (titleUnik(title, file))
                    {
                        fwrite(&movieBaru, sizeof(MovieData), 1, file);
                        TampilkanPesan("Data berhasil disimpan.\n",2);
                    }
                    else
                    {
                        TampilkanPesan("Judul telah digunakan, coba yang lain.\n",2);
                    }
                    break;
                }
            }
        }
    }

    fclose(file);
}

bool ValidasititleCreate(const char *title)
{
    if (strlen(title) == 0)
        return false;

    for (int i = 0; title[i] != '\0'; i++)
    {
        if (!isalnum(title[i]) && title[i] != '@' && title[i] != '_')
        {
            return false;
        }
    }
    return true;
}

bool ValidasiSandiCreate(const char *sandi)
{
    if (strlen(sandi) < 8)
    {
        TampilkanPesan("Sandi minimal 8 karakter.\n",2);
        return false;
    }
}

bool titleUnik(const char *title, FILE *file)
{
    rewind(file);
    MovieData temp;
    while (fread(&temp, sizeof(MovieData), 1, file))
    {
        if (strcmp(temp.title, title) == 0)
        {
            return false;
        }
    }
    return true;
}
