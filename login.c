#include <string.h>
#include <stdio.h>
#include <conio.h> // Para usar _getch
#include "common.h"
#include "login.h"
#include "menu.h"

void maskPassword(char *password, int maxLength) {
    int i = 0;
    char ch;

    while (i < maxLength - 1 && (ch = _getch()) != '\r') { 
        if (ch == '\b') { 
            if (i > 0) {
                i--;
                printf("\b \b"); 
            }
        } else {
            password[i++] = ch;
            printf("*"); 
        }
    }
    password[i] = '\0'; 
    printf("\n"); 
}

int authenticate(User users[], int *userCount, User *currentUser) {
    char username[50], password[50];
    printf("\n\n----- LOGIN -----\n\n");
    printf("Usuario (admin ou funcionario): ");
    scanf("%49s", username);
    
    printf("Senha: ");
    maskPassword(password, 50); // Usa a função para mascarar a entrada da senha

    for (int i = 0; i < *userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("\n----- LOGIN BEM-SUCEDIDO! Bem-vindo, %s. ----- \n", username);
            *currentUser = users[i]; // Configura o usuário atual
            return 1; // Retorna 1 para indicar sucesso
        }
    }

    printf("\n----- USUARIO OU SENHA INVALIDOS ): -----\n");
    return 0; // Retorna 0 para indicar falha
}
