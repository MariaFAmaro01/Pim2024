#include <stdio.h>
#include "common.h"
#include "login.h"
#include "menu.h"

int main() {
    User users[MAX_USERS];
    Product products[MAX_PRODUCTS];
    int userCount = 0;
    int productCount = 0;
    
    // Carregar usuários e produtos
    loadUsers(users, &userCount);
    loadProducts(products, &productCount);

    User currentUser; // Declarar o usuário atual
    if (authenticate(users, &userCount, &currentUser)) { // Verifica se o login foi bem-sucedido
        displayMenu(currentUser, users, &userCount, products, &productCount);
    }

    saveUsers(users, userCount);
    saveProducts(products, productCount);

    return 0;
}
