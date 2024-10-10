// Define a função realizar_login e a constante MAX_USUARIOS. O uso de #ifndef, #define e #endif é uma prática comum para evitar múltiplas inclusões do mesmo cabeçalho.

#ifndef LOGIN_H  // Previne a inclusão múltipla
#define LOGIN_H

// Definimos o número máximo de usuários
#define MAX_USUARIOS 2

// Declaração da função de login
int realizar_login(char usuarios[][20], char senhas[][20]);

#endif