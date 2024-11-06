#ifndef COMMON_H
#define COMMON_H

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
    char name[50];
    float price;
    int quantity;  
    char pricingType[4];  
} Product;

// Estrutura para Recibo
typedef struct {
    char customerName[50]; 
    char cpf[12];  
    float totalPrice;   
} Receipt;

typedef struct {
    Product product;   
    float quantity;   
    float totalPrice; 
} ReceiptItem;

// Funções para carregar e salvar usuários, produtos e recibo 
void listarUsuarios(User users[], int userCount);
void addUser(User users[], int *userCount);
void removeUser(User users[], int *userCount);
void consultEditUser(User users[], int *userCount);
void loadUsers(User users[], int *userCount);
void saveUsers(User users[], int userCount);
void loadProducts(Product products[], int *productCount);
void saveProducts(Product products[], int productCount);
void manageSales(Product products[], int *productCount);
void makeSale(Product products[], int *productCount);
void salesReport();
void manuSales(Product products[], int *productCount);

// Variável global para controle do contador de clientes
extern int clientCounter;

#endif // COMMON_H
