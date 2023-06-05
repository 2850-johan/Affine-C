#include <stdio.h>
#include <ctype.h>

int euclid_etendu(int a, int b, int *x, int *y) {
    int q, r, x1, x2, y1, y2;

    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    x2 = 1;
    x1 = 0;
    y2 = 0;
    y1 = 1;

    while (b > 0) {
        q = a / b;
        r = a - q * b;
        *x = x2 - q * x1;
        *y = y2 - q * y1;
        a = b;
        b = r;
        x2 = x1;
        x1 = *x;
        y2 = y1;
        y1 = *y;
    }

    *x = x2;
    *y = y2;

    return a;
}

int inverse_modulaire(int a, int m) {
    int x, y;
    euclid_etendu(a, m, &x, &y);
    if (x < 0) {
        x += m;
    }
    return x;
}


int main() {
    // Définition du tableau de correspondance pour les 52 caractères (26 majuscules + 26 minuscules)
    char tableauCorrespondance[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    char texteClaire[100]; 
    char texteChiffre[100] = "";
    char texteDechiffre[100] = "";
    int a, b; // Variables pour les clés a et b

    printf("***************CHIFFREMENT AFFINE *******************\n");
    printf("Entrez le mot à crypter : ");
    fgets(texteClaire, 100, stdin);

    // Conversion des caractères minuscules en majuscules
    for (int i = 0; texteClaire[i] != '\0'; i++) 
    {
        if (islower(texteClaire[i])) {
            texteClaire[i] = toupper(texteClaire[i]);
        }
    }

    // Saisie des clés a et b
    printf("Entrez la clé a : ");
    scanf("%d", &a);
    printf("Entrez la clé b : ");
    scanf("%d", &b);

    // Chiffrement du texte clair
    for (int i = 0; texteClaire[i] != '\0'; i++) {
        if (texteClaire[i] == ' ') {
            texteChiffre[i] = ' ';
        } else {
            int index = texteClaire[i] - 'A';
            texteChiffre[i] = tableauCorrespondance[(a * index + b) % 52];
        }
    }

    // Déchiffrement du texte chiffré
    int a_inv = inverse_modulaire(a, 52);
    for (int i = 0; texteChiffre[i] != '\0'; i++) {
        if (texteChiffre[i] == ' ') 
        {
            texteDechiffre[i] = ' ';
        } 
        else {
            int index = 0;
            for (int j = 0; j < 52; j++) {
                if (tableauCorrespondance[j] == texteChiffre[i]) {
                    index = j;
                    break;
                }
            }
            texteDechiffre[i] = tableauCorrespondance[(a_inv * (index - b + 52)) % 52];
        }
    }

    printf("Texte clair : %s\n", texteClaire);
    printf("Texte chiffré : %s\n", texteChiffre);
    printf("Texte déchiffré : %s\n", texteDechiffre);
    printf("MERCI POUR LE TRAVAIL MONSIEUR\n");

    return 0;
}
