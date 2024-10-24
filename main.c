#include <stdio.h>
#include "common.h"
#include "login.h"
#include "menu.h"

int main() {
    User users[MAX_USERS];
    Product products[MAX_PRODUCTS];
    int userCount = 0;
    int productCount = 0;

    loadUsers(users, &userCount);
    loadProducts(products, &productCount);

    authenticate(users, &userCount);

    // A lógica de autenticação deve definir currentUser
    User currentUser = users[0]; // Para fins de exemplo, assumindo que o primeiro usuário é o atual

    displayMenu(currentUser, users, &userCount, products, &productCount);

    saveUsers(users, userCount);
    saveProducts(products, productCount);

    return 0;
}
