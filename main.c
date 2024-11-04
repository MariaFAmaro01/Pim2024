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

    User currentUser; 
    if (authenticate(users, &userCount, &currentUser)) { 
        displayMenu(currentUser, users, &userCount, products, &productCount);
    }

    saveUsers(users, userCount);
    saveProducts(products, productCount);

    return 0;
}
