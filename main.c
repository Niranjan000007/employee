// main.c
#include "employee.h"

int main() {
    int ids[MAX];
    char names[MAX][50];
    float basicSalary[MAX];
    float hra[MAX];
    float deductions[MAX];
    float grossSalary[MAX];
    int count = 0;
    int choice;

    while (1) {
        choice = menu();

        if (choice == 1) {
            count = addEmployee(ids, names, basicSalary, hra, deductions, grossSalary, count);
        }
        else if (choice == 2) {
            displayEmployees(ids, names, basicSalary, hra, deductions, grossSalary, count);
        }
        else if (choice == 3) {
            printf("\nExiting... Goodbye!\n");
            break;
        }
        else {
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

