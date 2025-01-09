#include <stdio.h>
#include <conio.h>
#include <windows.h>

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
