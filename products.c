#include <stdio.h>
#include "common.h"
#include "products.h" 

extern int nextId;

void loadProducts(Product products[], int *productCount) {
    FILE *file = fopen("products.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de produtos.\n");
        return;
    }

    *productCount = 0;
    while (fscanf(file, "%d %s %f %d %s", 
                  &products[*productCount].id, 
                  products[*productCount].name, 
                  &products[*productCount].price, 
                  &products[*productCount].quantity, 
                  products[*productCount].pricingType) == 5) {
        if (products[*productCount].id >= nextId) {
            nextId = products[*productCount].id + 1;
        }
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
        fprintf(file, "%d %s %.2f %d %s\n", 
                products[i].id, 
                products[i].name, 
                products[i].price, 
                products[i].quantity, 
                products[i].pricingType);
    }
    fclose(file);
}