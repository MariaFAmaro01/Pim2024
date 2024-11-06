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
        printf("Não e possivel adicionar mais usuarios.\n");
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
    listarUsuarios(users, *userCount); // Listar usuários antes de remover
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
            listarUsuarios(users, *userCount); // Lista os usuários após remover
            return;
        }
    }

    printf("Usuario nao encontrado.\n");
}

// Função para consultar/editar usuário
void consultEditUser(User users[], int *userCount) {
    listarUsuarios(users, *userCount); 
    char username[50];
    printf("\nDigite o nome de usuario a ser consultado: ");
    scanf("%s", username);

    for (int i = 0; i < *userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Usuario encontrado:\n");
            printf("Nome: %s\n", users[i].username);
            printf("Tipo: %s\n", users[i].isAdmin ? "Admin" : "Funcionario");

             char escolhaSenha;
            printf("Deseja alterar a senha? (s/n): ");
            getchar();  // Limpa o buffer do Enter anterior
            scanf("%c", &escolhaSenha);

            if (escolhaSenha == 's' || escolhaSenha == 'S') {
                char senhaAtual[50];
                while (1) {
                    printf("Digite a senha atual: ");
                    scanf("%s", senhaAtual);

                    if (strcmp(senhaAtual, users[i].password) == 0) {
                        char novaSenha[50];
                        printf("Senha correta! Digite a nova senha: ");
                        scanf("%s", novaSenha);
                        strcpy(users[i].password, novaSenha);
                        printf("Senha atualizada com sucesso!\n");
                        break;
                    } else {
                        printf("Senha incorreta. Tente novamente.\n");
                    }
                }
            } else {
                printf("Nenhuma alteracao na senha foi feita.\n");
            }

            
            char escolhaTipo;
            printf("Deseja alterar o tipo do usuario? (s/n): ");
            getchar();  // Limpa o buffer do Enter anterior
            scanf("%c", &escolhaTipo);

            if (escolhaTipo == 's' || escolhaTipo == 'S') {
                char novoTipo;
                printf("Digite 'a' para Admin ou 'f' para Funcionario: ");
                getchar();  // Limpa o buffer do Enter anterior
                scanf("%c", &novoTipo);

                if (novoTipo == 'a' || novoTipo == 'A') {
                    users[i].isAdmin = 1;
                    printf("Tipo do usuario atualizado para Admin.\n");
                } else if (novoTipo == 'f' || novoTipo == 'F') {
                    users[i].isAdmin = 0;
                    printf("Tipo do usuario atualizado para Funcionario.\n");
                } else {
                    printf("Opcao invalida. Nenhuma alteracao no tipo de usuario foi feita.\n");
                }
            } else {
                printf("Nenhuma alteracao no tipo do usuario foi feita.\n");
            }

            listarUsuarios(users, *userCount); // Lista os usuários após a possível edição
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
        printf("3. Vizualizar ou Editar Usuarios\n");
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
                consultEditUser(users, userCount);  
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

int nextId = 1; // Variavel global 
// OPÇÃO 2. GERENCIAR ESTOQUE
void addProduct(Product products[], int *productCount) {
    if (*productCount >= MAX_PRODUCTS) {
        printf("Capacidade maxima de produtos atingida.\n");
        return;
    }

    Product newProduct;
    newProduct.id = nextId++;

    printf("\n\nNome do produto: ");
    scanf("%s", newProduct.name);

    char tipoPreco;
    do {
        printf("Tipo de precificacao (k para quilo, u para unidade): ");
        scanf(" %c", &tipoPreco);
        if (tipoPreco == 'k' || tipoPreco == 'K') {
            strcpy(newProduct.pricingType, "Kg");
        } else if (tipoPreco == 'u' || tipoPreco == 'U') {
            strcpy(newProduct.pricingType, "Unit");
        } else {
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (tipoPreco != 'k' && tipoPreco != 'K' && tipoPreco != 'u' && tipoPreco != 'U');

    printf("Preco do produto (%s): ", newProduct.pricingType);
    scanf("%f", &newProduct.price);

    printf("Quantidade do produto: ");
    scanf("%d", &newProduct.quantity);

    products[*productCount] = newProduct;
    (*productCount)++; 
    printf("Produto adicionado com sucesso! ID: %d\n", newProduct.id);

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
        char productName[50];
        printf("Nome do produto a remover: ");
        scanf("%s", productName);

        int found = 0;
        for (int i = 0; i < *productCount; i++) {
            if (strcmp(products[i].name, productName) == 0) {
                
                for (int j = i; j < *productCount - 1; j++) {
                    products[j] = products[j + 1];
                }
                (*productCount)--;
                found = 1;
                printf("Produto removido com sucesso!\n");
                break;
            }
        }

        if (!found) {
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

// Função para editar produto pelo nome
void consultEditProduct(Product products[], int productCount) {
    char productName[50];
    char choice;

    printf("\nProdutos disponiveis:\n");
    for (int i = 0; i < productCount; i++) {
        printf("ID: %d, Nome: %s, Preco: R$ %.2f (%s)\n", products[i].id, products[i].name, products[i].price, products[i].pricingType);
    }

    while (1) {
        printf("\nDigite o nome do produto para consultar ou editar (ou 'sair' para sair): ");
        scanf("%s", productName);

        if (strcmp(productName, "sair") == 0) return;

        int found = 0;
        for (int i = 0; i < productCount; i++) {
            if (strcmp(products[i].name, productName) == 0) {
                found = 1;
                printf("Produto encontrado:\n");
                printf("ID: %d, Nome: %s, Preco: R$ %.2f (%s)\n", products[i].id, products[i].name, products[i].price, products[i].pricingType);

                printf("Deseja editar este produto? (s/n): ");
                scanf(" %c", &choice);

                if (choice == 's' || choice == 'S') {
                    printf("Novo nome: ");
                    scanf("%s", products[i].name);

                    char novoTipo;
                    do {
                        printf("Novo tipo de precificacao (k para quilo, u para unidade): ");
                        scanf(" %c", &novoTipo);
                        if (novoTipo == 'k' || novoTipo == 'K') {
                            strcpy(products[i].pricingType, "Kg");
                        } else if (novoTipo == 'u' || novoTipo == 'U') {
                            strcpy(products[i].pricingType, "Unit");
                        } else {
                            printf("Opcao invalida. Tente novamente.\n");
                        }
                    } while (novoTipo != 'k' && novoTipo != 'K' && novoTipo != 'u' && novoTipo != 'U');

                    printf("Novo preco (%s): ", products[i].pricingType);
                    scanf("%f", &products[i].price);

                    printf("Produto atualizado com sucesso!\n");
                }
                break;
            }
        }

        if (!found) {
            printf("Produto nao encontrado. Tente novamente.\n");
        }
    }
}

void updateStock(Product products[], int productCount) {
    char productName[50];
    int found = 0;

    printf("Digite o nome do produto para atualizar o estoque: ");
    scanf("%s", productName);

    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].name, productName) == 0) {
            found = 1;
            int newQuantity;
            printf("Quantidade atual de %s: %d\n", products[i].name, products[i].quantity);
            printf("Digite a nova quantidade: ");
            scanf("%d", &newQuantity);

            products[i].quantity = newQuantity;
            printf("Estoque atualizado com sucesso!\n");
            break;
        }
    }

    if (!found) {
        printf("Produto nao encontrado.\n");
    }
}


// Função para gerenciar estoque
void manageStock(Product products[], int *productCount) {
    int choice;
    do {
        printf("\n--- Gerenciar Estoque ---\n");
        printf("1. Adicionar Produto\n");
        printf("2. Remover Produto\n");
        printf("3. Editar e Vizualizar Produtos\n");
        printf("4. Atualizar Estoque\n");
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
            case 4:
                updateStock(products, *productCount);
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (choice != 0);
}


// 3. GERENCIAR VENDAS
void manageSales(Product products[], int *productCount) {
    int choice;
    do {
        printf("\n--- Gerenciar Vendas ---\n");
        printf("1. Realizar Venda\n");
        printf("2. Relatorio de Vendas\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                makeSale(products, productCount);  
                break;
            case 2:
                salesReport(); 
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (choice != 0);
}


int clientCounter = 1;  

// Função para realizar a venda
void makeSale(Product products[], int *productCount) {
    char productName[50];
    int quantity;
    float totalPrice = 0.0;
    Receipt receipt;
    ReceiptItem receiptItems[100];
    int itemCount = 0;
    char cpfOption;

    
    snprintf(receipt.customerName, sizeof(receipt.customerName), "cliente%02d", clientCounter++);
    
    printf("\n\n-----REALIZAR VENDA-----\n");

    printf("CPF na nota? (s/n): ");
    scanf(" %c", &cpfOption);
    if (cpfOption == 's' || cpfOption == 'S') {
        printf("Digite o CPF do cliente: ");
        scanf(" %11s", receipt.cpf);
    } else {
        strcpy(receipt.cpf, "N/A");
    }

    while (1) {
        printf("Digite o nome do produto: ");
        scanf(" %49[^\n]", productName);

        int found = 0;
        Product selectedProduct;

        for (int i = 0; i < *productCount; i++) {
            if (strcmp(products[i].name, productName) == 0) {
                selectedProduct = products[i];
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Produto nao encontrado!\n");
            continue;
        }

        // Verifica o tipo de preço e solicita a quantidade corretamente
        if (strcmp(selectedProduct.pricingType, "Kg") == 0) {
            printf("Digite a quantidade de %s em gramas (ex: 500 para 500g): ", selectedProduct.name);
            scanf("%d", &quantity);
            float quantityInKg = quantity / 1000.0;
            float itemTotalPrice = selectedProduct.price * quantityInKg;
            totalPrice += itemTotalPrice;
            receiptItems[itemCount].product = selectedProduct;
            receiptItems[itemCount].quantity = quantityInKg;
            receiptItems[itemCount].totalPrice = itemTotalPrice;
            itemCount++;
        } else {
            printf("Quantidade de %s a ser vendida: ", selectedProduct.name);
            scanf("%d", &quantity);
            float itemTotalPrice = selectedProduct.price * quantity;
            totalPrice += itemTotalPrice;
            receiptItems[itemCount].product = selectedProduct;
            receiptItems[itemCount].quantity = quantity;
            receiptItems[itemCount].totalPrice = itemTotalPrice;
            itemCount++;
        }

        char addMore;
        printf("Deseja adicionar mais produtos a venda? (s/n): ");
        scanf(" %c", &addMore);
        if (addMore == 'n' || addMore == 'N') {
            break;
        }
    }

    receipt.totalPrice = totalPrice;

    printf("\n--- Recibo ---\n");
    printf("Cliente: %s\n", receipt.customerName);
    printf("CPF: %s\n", receipt.cpf);
    printf("Itens comprados:\n");

    for (int i = 0; i < itemCount; i++) {
        printf("%s - Quantidade: %.3f %s - Preco unitario: R$ %.2f - Total: R$ %.2f\n",
            receiptItems[i].product.name,
            receiptItems[i].quantity,
            strcmp(receiptItems[i].product.pricingType, "Kg") == 0 ? "Kg" : "Unid",
            receiptItems[i].product.price,
            receiptItems[i].totalPrice);
    }

    printf("Total: R$ %.2f\n", receipt.totalPrice);
    printf("----------------\n");

    FILE *file = fopen("sales_report.txt", "a");
    if (file) {
        fprintf(file, "Venda realizada:\n");
        fprintf(file, "Cliente: %s\n", receipt.customerName);
        fprintf(file, "CPF: %s\n", receipt.cpf);
        for (int i = 0; i < itemCount; i++) {
            fprintf(file, "%s - Quantidade: %.3f %s - Preco unitario: R$ %.2f - Total: R$ %.2f\n",
                receiptItems[i].product.name,
                receiptItems[i].quantity,
                strcmp(receiptItems[i].product.pricingType, "Kg") == 0 ? "Kg" : "Unid",
                receiptItems[i].product.price,
                receiptItems[i].totalPrice);
        }
        fprintf(file, "Total da venda: R$ %.2f\n\n", receipt.totalPrice);
        fclose(file);
    }
    printf("Venda registrada no relatorio!\n");
}


// Função relatório de vendas
void salesReport() {
    FILE *file = fopen("sales_report.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de relatorio de vendas.\n");
        return;
    }

    char line[256];
    printf("\n--- Relatorio de Vendas ---\n");

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}