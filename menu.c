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


// OPÇÃO 2. GERENCIAR ESTOQUE
void addProduct(Product products[], int *productCount) {
    if (*productCount >= MAX_PRODUCTS) {
        printf("Capacidade máxima de produtos atingida.\n");
        return;
    }

    Product newProduct;
    printf("\n\nNome do produto: ");
    scanf("%s", newProduct.name);

    // Selecionar o tipo de precificação
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
    printf("\nProdutos disponíveis:\n");
    for (int i = 0; i < productCount; i++) {
        printf("ID: %d, Nome: %s, Preço: R$ %.2f (%s)\n", products[i].id, products[i].name, products[i].price, products[i].pricingType);
    }

    while (1) {
        printf("\nDigite o ID do produto para consultar/editar (ou -1 para sair): \n");
        scanf("%d", &id);

        if (id == -1) return;

        int found = 0; 
        for (int i = 0; i < productCount; i++) {
            if (products[i].id == id) {
                found = 1; 
                printf("Produto encontrado:\n");
                printf("ID: %d, Nome: %s, Preço: R$ %.2f (%s)\n", products[i].id, products[i].name, products[i].price, products[i].pricingType);

                printf("Deseja editar este produto? (s/n): ");
                scanf(" %c", &choice);

                if (choice == 's' || choice == 'S') {
                    printf("Novo nome: ");
                    scanf("%s", products[i].name);

                    char novoTipo;
                    do {
                        printf("Novo tipo de precificação (k para quilo, u para unidade): ");
                        scanf(" %c", &novoTipo);
                        if (novoTipo == 'k' || novoTipo == 'K') {
                            strcpy(products[i].pricingType, "Kg");
                        } else if (novoTipo == 'u' || novoTipo == 'U') {
                            strcpy(products[i].pricingType, "Unit");
                        } else {
                            printf("Opção inválida. Tente novamente.\n");
                        }
                    } while (novoTipo != 'k' && novoTipo != 'K' && novoTipo != 'u' && novoTipo != 'U');

                    printf("Novo preço (%s): ", products[i].pricingType);
                    scanf("%f", &products[i].price);

                    printf("Produto atualizado com sucesso!\n");
                }
                break;
            }
        }
        if (!found) {
            printf("Produto não encontrado. Tente novamente.\n");
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
 

