// login.c
#include <stdio.h>
#include <string.h>
#include "login.h"  // Inclui o cabeçalho com a declaração da função

// Função para realizar o login
int realizar_login(char usuarios[][20], char senhas[][20]) {
    char usuario[20], senha[20];
    
    printf("Digite seu nome de usuário: ");
    scanf("%s", usuario);
    printf("Digite sua senha: ");
    scanf("%s", senha);
    
    // Verifica se o nome de usuário e a senha estão corretos
    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (strcmp(usuario, usuarios[i]) == 0 && strcmp(senha, senhas[i]) == 0) {
            printf("Login bem-sucedido! Bem-vindo, %s.\n", usuario);
            return 1;  // Login válido
        }
    }
    
    printf("Nome de usuário ou senha incorretos.\n");
    return 0;  // Login inválido
}
