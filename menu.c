#include "employee.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

int menu() {
    int choice;
    char buf[50];

    printf("\n====== Employee Payroll System ======\n");
    printf("1. Add Employee\n");
    printf("2. Display Employees\n");
    printf("3. Delete Employee\n");
    printf("4. Update Employee\n");
    printf("5. Exit\n");

    while (1) {
        printf("Enter your choice: ");

        if (!fgets(buf, sizeof(buf), stdin)) continue;

        int valid = 1;
        for (int i = 0; buf[i] && buf[i] != '\n'; i++)
            if (!isdigit((unsigned char)buf[i])) valid = 0;

        if (valid) return atoi(buf);

        printf("Invalid choice!\n");
    }
}
