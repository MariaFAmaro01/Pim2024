#include <stdio.h>
#include "common.h"
#include "login.h"
#include "menu.h"

void loadUsers(User users[], int *userCount) {
    FILE *file = fopen("users.txt", "r");
    if (file) {
        while (fscanf(file, "%s %s %d", users[*userCount].username, users[*userCount].password, &users[*userCount].isAdmin) != EOF) {
            (*userCount)++;
        }
        fclose(file);
    }
}

void saveUsers(User users[], int userCount) {
    FILE *file = fopen("users.txt", "w");
    if (file) {
        for (int i = 0; i < userCount; i++) {
            fprintf(file, "%s %s %d\n", users[i].username, users[i].password, users[i].isAdmin);
        }
        fclose(file);
    }
}

void loadProducts(Product products[], int *productCount) {
    FILE *file = fopen("products.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de produtos.\n");
        return;
    }
    
    while (fscanf(file, "%s %f", products[*productCount].name, &products[*productCount].price) != EOF) {
        products[*productCount].id = *productCount; 
        (*productCount)++;
    }

    fclose(file);
    printf("Produtos carregados com sucesso!\n");
}

void saveProducts(Product products[], int productCount) {
    FILE *file = fopen("products.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar produtos.\n");
        return;
    }

    for (int i = 0; i < productCount; i++) {
        fprintf(file, "%s %.2f\n", products[i].name, products[i].price);
    }

    fclose(file);
    printf("Produtos salvos com sucesso!\n");
}