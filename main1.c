#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void sulpar(int dl) {
    printf("Паролі ");
    if (dl < 10)
        printf("слабкі\n");
    else if (dl < 20)
        printf("середні\n");
    else if (dl < 30)
        printf("сильні\n");
    else
        printf("дуже сильні\n");
}

void genp(char* parol, int dl, const char* bazsymb) {
    int charsetSize = strlen(bazsymb);
    for (int i = 0; i < dl; i++) {
        parol[i] = bazsymb[rand() % charsetSize];
    }
    parol[dl] = '\0';
}

int zap(const char* zapyt, int min, int max) {
    int znach;
    int c;
    while (1) {
        printf("%s", zapyt);
        if (scanf("%d", &znach) != 1) {
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Помилка: введіть ціле число.\n");
            continue;
        }
        while ((c = getchar()) != '\n' && c != EOF);
        if (znach < min || znach > max) {
            printf("Помилка: введіть число від %d до %d.\n", min, max);
            continue;
        }
        return znach;
    }
}

char symyn(const char* zapyt) {
    char lit;
    int c;
    while (1) {
        printf("%s", zapyt);
        lit = getchar();
        while ((c = getchar()) != '\n' && c != EOF);
        if (lit == 'y' || lit == 'Y' || lit == 'n' || lit == 'N')
            return lit;
        printf("Помилка: введіть 'y' або 'n'.\n");
    }
}

int main() {
    printf("===================================\n");
    printf("       ГЕНЕРАТОР ПАРОЛІВ\n");
    printf("===================================\n\n");

    int dl, kilk;
    char bazsymb[256] = "";
    char parol[100];

    struct {
        const char* description;
        const char* characters;
    } options[] = {
        {"малі літери", "abcdefghijklmnopqrstuvwxyz"},
        {"великі літери", "ABCDEFGHIJKLMNOPQRSTUVWXYZ"},
        {"цифри",        "0123456789"},
        {"спеціальні символи", "!@#$%^&*()-_=+[]{};:,.<>?"}
    };

    dl = zap("Введіть довжину пароля (від 4 до 99): ", 4, 99);
    kilk = zap("Введіть кількість паролів (до 10): ", 1, 10);

    for (int i = 0; i < 4; i++) {
        char zapyt[100];
        snprintf(zapyt, sizeof(zapyt), "Включати %s? (y/n): ", options[i].description);
        char vidp = symyn(zapyt);
        if (vidp == 'y' || vidp == 'Y') {
            strcat(bazsymb, options[i].characters);
        }
    }

    srand((unsigned int)time(NULL));

    printf("\n--- Згенеровані паролі ---\n");
    for (int i = 0; i < kilk; i++) {
        genp(parol, dl, bazsymb);
        printf("%d: %s\n", i + 1, parol);
    }

    printf("\n--- Складність паролів ---\n");
    sulpar(dl);

    return 0;
}

