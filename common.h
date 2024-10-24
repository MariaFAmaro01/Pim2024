#ifndef COMMON_H
#define COMMON_H

// MENU
#define MAX_USERS 100
#define MAX_PRODUCTS 100

// Estrutura para adicionar usuario
typedef struct {
    char username[50];
    char password[50];
    int isAdmin; // 1 para admin, 0 para funcionário
} User;

// Estrutura para adicionar produto 
typedef struct {
    int id;           
    char name[100]; 
    float price; 
    int quantity;  
} Product;

// Estrutura para Recibo
typedef struct {
    char customerName[100];
    char cpf[12]; // CPF pode ter 11 dígitos + 1 para o terminador de string
    Product product;
    int quantity;
    float totalPrice;
} Receipt;

typedef struct {
    Product product; // Produto vendido
    int quantity; // Quantidade vendida
    float totalPrice; // Total do item
} ReceiptItem;

// Funções para carregar e salvar usuários, produtos e recibo 
void loadUsers(User users[], int *userCount);
void saveUsers(User users[], int userCount);
void loadProducts(Product products[], int *productCount);
void saveProducts(Product products[], int productCount);
void manageSales(Product products[], int *productCount);




#endif // COMMON_H
