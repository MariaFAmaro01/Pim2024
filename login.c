#include <string.h>
#include <stdio.h>
#include "common.h"
#include "login.h"
#include "menu.h"

int authenticate(User users[], int *userCount, User *currentUser) { // Agora é correto
    char username[50], password[50];
    printf("\n\n----- LOGIN -----\n\n");
    printf("Usuario (admin ou funcionario): ");
    scanf("%s", username);
    printf("Senha: ");
    scanf("%s", password);

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
