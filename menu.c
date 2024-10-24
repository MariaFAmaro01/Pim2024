#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "common.h"

// MENU 
void displayMenu(User currentUser, User users[], int *userCount, Product products[], int *productCount) {
    int option;

    while (1) { // Loop infinito até que o usuário escolha sair
        if (currentUser.isAdmin) {
            printf("\n--- MENU ---\n");
            printf("1. Gerenciar Usuarios\n");
            printf("2. Gerenciar Estoque\n");
            printf("3. Gerenciar Vendas\n");
            printf("0. Sair\n");
        } else {
            printf("\n--- MENU ---\n");
            printf("1. Gerenciar Estoque\n");
            printf("2. Gerenciar Vendas\n");
            printf("0. Sair\n");
        }

        printf("Escolha uma opaco: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                if (currentUser.isAdmin) {
                    // Chamar a função de gerenciar usuários
                    manageUsers(users, userCount);
                } else {
                    // Gerenciar estoque ou outra funcionalidade
                    manageStock(products, productCount);
                }
                break;
            case 2:
                if (currentUser.isAdmin) {
                    // Gerenciar estoque
                    manageStock(products, productCount);
                } else {
                    // Gerenciar vendas
                    manageSales(products, productCount);
                }
                break;
            case 3:
                if (currentUser.isAdmin) {
                    // Gerenciar vendas
                    manageSales(products, productCount);
                }
                break;
            case 0:
                printf("Saindo do sistema...\n");
                return; // Sai do loop e do programa
            default:
                printf("Opção invalida. Tente novamente.\n");
                break;
        }
    }
}



// OPÇÃO 1. ADICIONAR USUARIO
void addUser(User users[], int *userCount) {
    if (*userCount >= MAX_USERS) {
        printf("Não e possível adicionar mais usuarios.\n");
        return;
    }

    User newUser;
    printf("\nDigite o nome de usuario: ");
    scanf("%s", newUser.username);
    printf("Digite a senha: ");
    scanf("%s", newUser.password);
    printf("Digite 1 para admin ou 0 para funcionario: ");
    scanf("%d", &newUser.isAdmin);

    users[*userCount] = newUser;
    (*userCount)++;
    printf("\nUsuario adicionado com sucesso!");
}

// Função para remover usuário
void removeUser(User users[], int *userCount) {
    char username[50];
    printf("\nDigite o nome de usuario a ser removido: ");
    scanf("%s", username);

    for (int i = 0; i < *userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            for (int j = i; j < *userCount - 1; j++) {
                users[j] = users[j + 1];
            }
            (*userCount)--;
            printf("Usuario removido com sucesso!\n");
            return;
        }
    }

    printf("Usuario nao encontrado.\n");
}

// Função para consultar/editar usuário
void consultEditUser(User users[], int userCount) {
    char username[50];
    printf("\nDigite o nome de usuario a ser consultado: ");
    scanf("%s", username);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Usuario encontrado:\n");
            printf("Nome: %s\n", users[i].username);
            printf("Tipo: %s\n", users[i].isAdmin ? "Admin" : "Funcionario");
            printf("Digite a nova senha (ou pressione Enter para manter a atual): ");
            char newPassword[50];
            scanf("%s", newPassword);
            if (strlen(newPassword) > 0) {
                strcpy(users[i].password, newPassword);
            }
            printf("Informacoes atualizadas com sucesso!\n");
            return;
        }
    }

    printf("Usuario nao encontrado.\n");
}

//menu de gerenciar usuários
void manageUsers(User users[], int *userCount) {
    int option;
    do {
        printf("\n\n--- GERENCIAR USUARIOS ---\n");
        printf("1. Adicionar Usuario\n");
        printf("2. Remover Usuario\n");
        printf("3. Consultar/Editar Usuario\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                addUser(users, userCount);
                break;
            case 2:
                removeUser(users, userCount);
                break;
            case 3:
                consultEditUser(users, *userCount);
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção invalida, tente novamente.\n");
                break;
        }
    } while (option != 0);
}


// OPÇÃO 2. GERENCIAR ESTOQUE
void addProduct(Product products[], int *productCount) {
    if (*productCount >= MAX_PRODUCTS) {
        printf("Capacidade máxima de produtos atingida.\n");
        return;
    }

    Product newProduct;
        printf("\n\nNome do produto: ");
        scanf("%s", newProduct.name);
        
        printf("Preço do produto: ");
        scanf("%f", &newProduct.price);
        
        printf("Quantidade do produto: ");
        scanf("%d", &newProduct.quantity);

        products[*productCount] = newProduct;
        (*productCount)++; 
        printf("Produto adicionado com sucesso!\n");
        
        char addMore;
        printf("\nDeseja adicionar mais produtos? (s/n): ");
        scanf(" %c", &addMore); 
        if (addMore == 's' || addMore == 'S') {
            addProduct(products, productCount); 
        }
}

// Função para remover produto
void removeProduct(Product products[], int *productCount) {
    while (1) {
        int productId;
        printf("ID do produto a remover: ");
        scanf("%d", &productId);

        if (productId >= 0 && productId < *productCount) {
            for (int i = productId; i < *productCount - 1; i++) {
                products[i] = products[i + 1];
            }
            (*productCount)--;
            printf("Produto removido com sucesso!\n");
        } else {
            printf("Produto nao encontrado!\n");
        }

        char continueRemoving;
        printf("Deseja remover outro produto? (s/n): ");
        scanf(" %c", &continueRemoving);
        
        if (continueRemoving == 'n' || continueRemoving == 'N') {
            break;
        }
    }
}

void consultEditProduct(Product products[], int productCount) {
    int id;
    char choice;

    // Exibe todos os produtos disponíveis
    printf("\nProdutos disponiveis:\n");
    for (int i = 0; i < productCount; i++) {
        printf("ID: %d, Nome: %s, Preco: R$ %.2f\n", products[i].id, products[i].name, products[i].price);
    }

    while (1) {
        printf("\nDigite o ID do produto para consultar/editar (ou -1 para sair): \n");
        scanf("%d", &id);

        // Permite sair do loop
        if (id == -1) {
            return; // Volta para o menu anterior
        }

        // Verifica se o ID é válido
        int found = 0; // Flag para verificar se o produto foi encontrado
        for (int i = 0; i < productCount; i++) {
            if (products[i].id == id) {
                found = 1; // Produto encontrado
                printf("Produto encontrado:\n");
                printf("ID: %d, Nome: %s, Preco: R$ %.2f\n", products[i].id, products[i].name, products[i].price);
                
                // Pergunta se deseja editar
                printf("Deseja editar este produto? (s/n): ");
                scanf(" %c", &choice); // O espaço antes de %c consome qualquer nova linha pendente

                if (choice == 's' || choice == 'S') {
                    printf("Novo nome: ");
                    scanf("%s", products[i].name);
                    printf("Novo preco: ");
                    scanf("%f", &products[i].price);
                    printf("Produto atualizado com sucesso!\n");
                }
                break; // Sai do loop após encontrar o produto
            }
        }

        // Se o produto não foi encontrado
        if (!found) {
            printf("Produto nao encontrado. Tente novamente.\n");
        }
    }
}

// Função para gerenciar estoque
void manageStock(Product products[], int *productCount) {
    int choice;
    do {
        printf("\n--- Gerenciar Estoque ---\n");
        printf("1. Adicionar Produto\n");
        printf("2. Remover Produto\n");
        printf("3. Consultar/Editar Produto\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct(products, productCount);
                break;
            case 2:
                removeProduct(products, productCount);
                break;
            case 3:
                consultEditProduct(products, *productCount);
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opção invalida. Tente novamente.\n");
        }
    } while (choice != 0);
}


// 3. GERENCIAR VENDAS
void manageSales(Product products[], int *productCount) {
    char includeCPF;
    char cpf[12];
    int productId;
    int quantity;
    int customerCounter = 0; // Contador para nomes de clientes
    float totalPrice = 0.0; // Armazena o total acumulado
    Receipt receipt; // Recebe o recibo acumulado
    ReceiptItem receiptItems[100]; // Array para armazenar os produtos vendidos
    int itemCount = 0; // Contador de itens no recibo

    // Inicializa os campos do recibo
    strcpy(receipt.customerName, "Cliente não identificado");
    strcpy(receipt.cpf, "N/A");

    // Pergunta se deseja incluir CPF
    printf("\n\n-----REALIZAR VENDA-----\n");
    printf("CPF na nota? (s/n): ");
    scanf(" %c", &includeCPF);

    // Gerar nome do cliente automaticamente
    snprintf(receipt.customerName, sizeof(receipt.customerName), "cliente%d", customerCounter++);
    
    if (includeCPF == 's' || includeCPF == 'S') {
        printf("CPF do cliente: ");
        scanf("%s", cpf); // Considere validar o CPF aqui
        strcpy(receipt.cpf, cpf);
    } else {
        strcpy(receipt.cpf, "N/A");
    }

    while (1) {

        // Solicita o ID do produto
        printf("Digite o ID do produto: ");
        scanf("%d", &productId);

        // Verifica se o ID do produto é válido
        if (productId < 0 || productId >= *productCount) {
            printf("Produto nao encontrado!\n");
            continue; // Retorna ao início do loop se o produto não for válido
        }

        Product selectedProduct = products[productId]; // Seleciona o produto

        // Solicita a quantidade
        printf("Quantidade de %s a ser vendida: ", selectedProduct.name);
        scanf("%d", &quantity);

        // Verifica se a quantidade é válida
        if (quantity <= 0) {
            printf("Quantidade invalida!\n");
            continue; // Retorna ao início do loop se a quantidade não for válida
        }

        // Calcula o total
         float itemTotalPrice = selectedProduct.price * quantity;
        totalPrice += itemTotalPrice; // Acumula o preço total

        // Armazena o item no recibo
        receiptItems[itemCount].product = selectedProduct;
        receiptItems[itemCount].quantity = quantity;
        receiptItems[itemCount].totalPrice = itemTotalPrice;
        itemCount++; // Incrementa o contador de itens

        // Exibe a confirmação da venda
        printf("Produto %s adiconado com sucesso! Total parcial: R$ %.2f\n", selectedProduct.name, itemTotalPrice);

        // Pergunta se deseja adicionar mais produtos
        char addMore;
        printf("Deseja adicionar mais produtos a venda? (s/n): \n");
        scanf(" %c", &addMore);
        if (addMore == 'n' || addMore == 'N') {
            break; // Sai do loop se não quiser adicionar mais produtos
        }
    }

    // Gera o recibo final
    receipt.totalPrice = totalPrice; // Total final do recibo
    printf("\n--- Recibo ---\n");
    printf("Cliente: %s\n", receipt.customerName);
    printf("CPF: %s\n", receipt.cpf);
    printf("Itens comprados:\n");

    for (int i = 0; i < itemCount; i++) {
        printf("%s - Quantidade: %d - Preco unitario: R$ %.2f - Total: R$ %.2f\n",
               receiptItems[i].product.name,
               receiptItems[i].quantity,
               receiptItems[i].product.price,
               receiptItems[i].totalPrice);
    }

    printf("Total: R$ %.2f\n", receipt.totalPrice);
    printf("----------------\n");
}
 

