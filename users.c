// users.c
#include <stdio.h>
#include <string.h>
#include "common.h"
#include "users.h" 

void loadUsers(User users[], int *userCount) {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }

    *userCount = 0;
    while (fscanf(file, "%s %s %d", users[*userCount].username, users[*userCount].password, &users[*userCount].isAdmin) == 3) {
        (*userCount)++;
    }
    fclose(file);
}

void saveUsers(User users[], int userCount) {
    FILE *file = fopen("users.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar usuários.\n");
        return;
    }

    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s %s %d\n", users[i].username, users[i].password, users[i].isAdmin);
    }
    fclose(file);
}


void listarUsuarios(User users[], int userCount) {
    printf("\n---- LISTA DE USUARIOS ----\n");
    for (int i = 0; i < userCount; i++) {
        printf("Nome: %s | Tipo: %s\n", users[i].username, users[i].isAdmin ? "Admin" : "Funcionario");
    }
    printf("\n");
}
