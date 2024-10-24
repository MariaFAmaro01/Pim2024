#include <string.h>
#include <stdio.h>
#include "common.h"
#include "login.h"
#include "menu.h"

void authenticate(User users[], int *userCount) {
    char username[50], password[50];
    printf("Usuário: ");
    scanf("%s", username);
    printf("Senha: ");
    scanf("%s", password);

    for (int i = 0; i < *userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login bem-sucedido! Bem-vindo, %s.\n", username);
            return;
        }
    }
    printf("Usuário ou senha inválidos!\n");
}
