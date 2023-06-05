#include <stdio.h>

// Fonction pour calculer le PGCD
int pgcd(int a, int b) {
    int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Fonction pour trouver l'inverse multiplicatif modulo 26
int findInverse(int a) {
    int inverse = -1;
    for (int i = 0; i < 26; i++) {
        if ((a * i) % 26 == 1) {
            inverse = i;
            break;
        }
    }
    return inverse;
}

// Fonction pour décrypter le message avec toutes les clés possibles
void decryptMessage(char* message) {
    for (int a = 1; a < 26; a++) {
        int inverse = findInverse(a);
        if (inverse == -1 || pgcd(a, 26) != 1) {
            continue;
        }
        
        for (int b = 0; b < 26; b++) {
            for (int i = 0; message[i] != '\0'; i++) {
                if (message[i] >= 'a' && message[i] <= 'z') {
                    int decrypted = (inverse * (message[i] - 'a' - b + 26)) % 26;
                    printf("%c", decrypted + 'a');
                } else {
                    printf("%c", message[i]);
                }
            }
            printf(" (a = %d, b = %d)\n", a, b);
        }
    }
}

int main() {
    char message[100];
    
    printf("Entrez le message chiffré : ");
    scanf("%s", message);
    
    decryptMessage(message);
    
    return 0;
}

