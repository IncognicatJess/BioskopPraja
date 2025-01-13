// Deklarasi fungsi
void HidePW(char password[], int maxSize);

// Implementasi fungsi
void HidePW(char password[], int maxSize)
{
    int i = 0;
    char ch;
    while ((ch = getch()) != '\r') // Mask password input
    {
        if (ch == '\b' && i > 0)
        {
            printf("\b \b");
            i--;
        }
        else if (ch != '\b' && i < maxSize - 1) // Gunakan maxSize
        {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");
}