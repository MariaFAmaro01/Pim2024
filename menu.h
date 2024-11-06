#ifndef MENU_H
#define MENU_H

#include "common.h"

// Prototipagem das funções
void displayMenu(User currentUser, User users[], int *userCount, Product products[], int *productCount);
void manageUsers(User users[], int *userCount);
void manageStock(Product products[], int *productCount);
void manageSales(Product products[], int *productCount);
void listarUsuarios(User users[], int userCount);
void consultEditUser(User users[], int *userCount); 
void manuSales(Product products[], int *productCount);  
void makeSale(Product products[], int *productCount); 
void salesReport();


#endif // MENU_H
