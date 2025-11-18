// menu.c
#include "employee.h"

int menu() {
    int choice;
    printf("\n====== Employee Payroll System ======\n");
    printf("1. Add Employee\n");
    printf("2. Display All Employees\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // clear newline left by scanf
    return choice;
}

