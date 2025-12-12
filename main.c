#include <stdio.h>
#include "employee.h"

#include "employee.c"
#include "menu.c"

int main() {
    Employee emp[MAX];
    int count = loadFromFile(emp);

    printf("Loaded %d employee record(s).\n", count);

    while (1) {
        int choice = menu();

        switch (choice) {
            case 1: count = addEmployee(emp, count); break;
            case 2: displaySavedFile(); break;
            case 3: count = deleteEmployee(emp, count); break;
            case 4: count = updateEmployee(emp, count); break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}
