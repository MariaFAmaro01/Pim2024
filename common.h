#ifndef COMMON_H
#define COMMON_H

#define MAX_USERS 100
#define MAX_PRODUCTS 100

// Definição da estrutura User
typedef struct {
    char username[50];
    char password[50];
    int isAdmin; // 1 se admin, 0 se funcionário
} User;

// Definição da estrutura Product
typedef struct {
    char name[50];
    int quantity;
} Product;

#endif // COMMON_H
