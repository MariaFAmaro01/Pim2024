#ifndef HORTIFRUTI_H
#define HORTIFRUTI_H

#include "common.h"

// Funções para manipulação de usuários e produtos
void loadUsers(User users[], int *userCount);
void loadProducts(Product products[], int *productCount);
void saveUsers(User users[], int userCount);
void saveProducts(Product products[], int productCount);

#endif // HORTIFRUTI_H
