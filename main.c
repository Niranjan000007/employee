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
            displaySavedFile();
        }
        else if (choice == 3) {
            printf("\nExiting program...\n");
            break;
        }
        else {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
