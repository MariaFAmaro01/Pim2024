//main.c: Controla o fluxo principal do programa

#include <stdio.h>
#include "login.h"  // Incluímos o cabeçalho do login
#include "menu.h"   // Incluímos o cabeçalho do menu

int main() {
    // Matriz para armazenar usuários e senhas
    char usuarios[MAX_USUARIOS][20] = {"admin", "funcionario"};
    char senhas[MAX_USUARIOS][20] = {"1234", "senha123"};
    
    // Tentativa de login
    if (realizar_login(usuarios, senhas)) {
        printf("Acesso concedido.\n");
        
        int opcao;
        do {
            printf("\n\n----MENU----\n\n");
            printf("1. Gerenciar usuários \n");
            printf("2. Gerenciar estoque \n");
            printf("3. Gerenciar produtos\n");
            printf("4. Gerenciar vendas \n");
            printf("5. Sair \n");
            printf("Escolha uma opção: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    gerenciar_usuarios();
                    break;
                case 2:
                    gerenciar_estoque();
                    break;
                case 3:
                    gerenciar_produtos();
                    break;
                case 4:
                    gerenciar_vendas();
                    break;
                case 5:
                    printf("Saindo...\n");
                    break;
                default:
                    printf("Opção inválida! Tente novamente.\n");
            }
        } while (opcao != 5);  // Continua até que a opção 5 (sair) seja escolh
    } else {
        printf("Acesso negado.\n");
    }

    return 0;
}
