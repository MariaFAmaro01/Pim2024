#ifndef PRODUCTS_H
#define PRODUCTS_H

#include "common.h"

void loadProducts(Product products[], int *productCount);
void saveProducts(Product products[], int productCount);

extern int nextId;  

#endif 
