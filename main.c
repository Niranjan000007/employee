// main.c
#include "employee.h"

int main() {
    Employee emp[MAX];
    int count = 0;
    int choice;

    while (1) {
        choice = menu();

        if (choice == 1) {
            count = addEmployee(emp, count);
        }
        else if (choice == 2) {
            displayEmployees(emp, count);
        }
        else if (choice == 3) {
            printf("\nExit\n");
            break;
        }
        else {
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

