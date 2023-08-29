#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

void readPerroq(char *perroquet) {
    FILE *file = fopen("peroq.def", "r");
    if (file == NULL) {
        printf("Erreur au niveau de la lecture du perroq");
        exit(1);
    }
    fscanf(file, "%s", perroquet);
    fclose(file);
}

void savePerroq(const char *perroquet) {
    FILE *file = fopen("peroq.def", "w");
    if (file == NULL) {
        printf("Erreur au niveau de la sauvegarde du perroq");
        exit(1);
    }
    fprintf(file, "%s", perroquet);
    fclose(file);
}

void chiffrePerroq(const char *source, const char *perroquet, char *chiffree) {
    int sourceLen = strlen(source);
    int perroquetLen = strlen(perroquet);
    int i = 0;

    for (i = 0; i < sourceLen; i++) {
        chiffree[i] = source[i] + perroquet[i % perroquetLen];
    }
    chiffree[sourceLen] = '\0';
}

void dechiffrePerroq(const char *chiffree, const char *perroquet, char *dechiffree) {
    int chiffreeLen = strlen(chiffree);
    int perroquetLen = strlen(perroquet);
    int i = 0;

    for (i = 0; i < chiffreeLen; i++) {
        dechiffree[i] = chiffree[i] - perroquet[i % perroquetLen];
    }
    dechiffree[chiffreeLen] = '\0';
}

int main() {
    char perroquet[MAX_LEN];
    char source[MAX_LEN];
    char chiffree[MAX_LEN];
    char dechiffree[MAX_LEN];
    char chiffreeDecrypt[MAX_LEN];

    printf("Programme de chiffrement 'Perroquet'!\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Choisir le perroquet\n");
        printf("2. Chiffrer un texte\n");
        printf("3. Dechiffrer un texte\n");
        printf("4. Quitter\n");

        int choix;
        printf("Entrez votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Entrez le perroquet : ");
                scanf("%s", perroquet);
                savePerroq(perroquet);
                printf("Perroquet enregistre.\n");
                break;
            case 2:
                printf("Entrez le texte à chiffrer : ");
                scanf(" %[^\n]s", source);

                readPerroq(perroquet);
                chiffrePerroq(source, perroquet, chiffree);

                printf("Texte chiffre : %s\n", chiffree);

                FILE *chiffreeFile = fopen("dest.crt", "w");
                if (chiffreeFile == NULL) {
                    printf("Erreur lors de l'ouverture du fichier dest.crt\n");
                    return 1;
                }
                fprintf(chiffreeFile, "%s", chiffree);
                fclose(chiffreeFile);

                remove("source.txt");

                break;
            case 3:
                printf("Entrez le texte chiffre : ");
                scanf(" %[^\n]s", chiffreeDecrypt);

                readPerroq(perroquet);
                dechiffrePerroq(chiffreeDecrypt, perroquet, dechiffree);

                printf("Texte déchiffre : %s\n", dechiffree);
                break;
            case 4:
                printf("Au revoir !\n");
                return 0;
            default:
                printf("Choix invalide. Veuillez entrer un choix valide.\n");
        }
    }

    return 0;
}

