#include <stdio.h>
#include "common.h"
#include "products.h" // Assegure-se de ter um cabeçalho para produtos

void loadProducts(Product products[], int *productCount) {
    FILE *file = fopen("products.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de produtos.\n");
        return;
    }

    *productCount = 0;
    while (fscanf(file, "%s %f %d %s", 
                  products[*productCount].name, 
                  &products[*productCount].price, 
                  &products[*productCount].quantity, 
                  products[*productCount].pricingType) == 4) { 
        (*productCount)++;
    }
    fclose(file);
}

void saveProducts(Product products[], int productCount) {
    FILE *file = fopen("products.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar produtos.\n");
        return;
    }

    for (int i = 0; i < productCount; i++) {
        fprintf(file, "%s %.2f %d %s\n", 
                products[i].name, 
                products[i].price, 
                products[i].quantity, 
                products[i].pricingType); 
    }
    fclose(file);
}
