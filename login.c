// login.c: Implementa a função realizar_login, que solicita as credenciais do usuário e as compara com as armazenadas.

#include <stdio.h>
#include <string.h>
#include "login.h"

int realizar_login(char usuarios[MAX_USUARIOS][20], char senhas[MAX_USUARIOS][20]) {
    char usuario[20], senha[20];
    
    printf("Usuário: ");
    scanf("%s", usuario);
    printf("Senha: ");
    scanf("%s", senha);
    
    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (strcmp(usuario, usuarios[i]) == 0 && strcmp(senha, senhas[i]) == 0) {
            return 1; // Login bem-sucedido
        }
    }
    return 0; // Login falhou
}
