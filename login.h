#ifndef LOGIN_H
#define LOGIN_H

#include "common.h"

void maskPassword(char *password, int maxLength); 
int authenticate(User users[], int *userCount, User *currentUser); 

#endif // LOGIN_H
