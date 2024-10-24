#include <string.h>
#include <stdio.h>
#include "common.h"
#include "login.h"
#include "menu.h"

void displayMenu(User currentUser, User users[], int *userCount, Product products[], int *productCount) {
    int choice;
    do {
        printf("\n--- Menu ---\n");
        if (currentUser.isAdmin) {
            printf("1. Gerenciar Usuários\n");
            printf("2. Gerenciar Estoque\n");
        }
        printf("3. Gerenciar Vendas\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (currentUser.isAdmin) {
                    manageUsers(users, userCount);
                } else {
                    printf("Você não tem permissão para gerenciar usuários.\n");
                }
                break;
            case 2:
                if (currentUser.isAdmin) {
                    manageStock(products, productCount);
                } else {
                    printf("Você não tem permissão para gerenciar o estoque.\n");
                }
                break;
            case 3:
                manageSales(products, *productCount);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (choice != 0);
}

void manageStock(Product products[], int *productCount) {
    printf("\n--- Consultar Produtos ---\n");
    if (*productCount == 0) {
        printf("Nenhum produto cadastrado no estoque.\n");
    } else {
        for (int i = 0; i < *productCount; i++) {
            printf("Produto: %s, Quantidade: %d\n", products[i].name, products[i].quantity);
        }
    }
}

void manageSales(Product products[], int productCount) {
    char productName[50];
    int quantity;
    printf("Nome do produto: ");
    scanf("%s", productName);
    printf("Quantidade: ");
    scanf("%d", &quantity);

    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].name, productName) == 0) {
            if (products[i].quantity >= quantity) {
                products[i].quantity -= quantity;
                printf("Venda realizada! Produto: %s, Quantidade: %d\n", productName, quantity);
                printf("Recibo:\n");
                printf("Produto: %s\n", productName);
                printf("Quantidade: %d\n", quantity);
                // Aqui você pode adicionar mais informações do cliente, se necessário
                return;
            } else {
                printf("Estoque insuficiente!\n");
                return;
            }
        }
    }
    printf("Produto não encontrado!\n");
}


void manageUsers(User users[], int *userCount) {
    // Implementação da função aqui
}