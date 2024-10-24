#ifndef MENU_H
#define MENU_H

#include "login.h"
#include "hortifruti.h"

void displayMenu(User currentUser, User users[], int *userCount, Product products[], int *productCount);
void manageUsers(User users[], int *userCount);
void manageStock(Product products[], int *productCount);
void manageSales(Product products[], int productCount);
void manageUsers(User users[], int *userCount);

#endif // MENU_H
