#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int ids[100];
    char names[100][50];
    float basicSalary[100];
    float hra[100];
    float deductions[100];
    float grossSalary[100];
    int count = 0;
    int choice;

    while (1) {
        printf("\n====== Employee Payroll System ======\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        if (choice == 1) {
            if (count >= 100) {
                printf("Error: Maximum employee limit reached!\n");
                continue;
            }

            printf("\nEnter Employee ID: ");
            scanf("%d", &ids[count]);
            getchar(); // consume newline

            printf("Enter Name: ");
            fgets(names[count], sizeof(names[count]), stdin);
            names[count][strcspn(names[count], "\n")] = 0; // remove newline

            printf("Enter Basic Salary: ");
            scanf("%f", &basicSalary[count]);

            printf("Enter HRA: ");
            scanf("%f", &hra[count]);

            printf("Enter Deductions: ");
            scanf("%f", &deductions[count]);

            grossSalary[count] = basicSalary[count] + hra[count] - deductions[count];
            count++;

            printf("\n✅ Employee added successfully!\n");
        }
        else if (choice == 2) {
            if (count == 0) {
                printf("\nNo employee records found!\n");
            } else {
                printf("\n%-5s %-20s %-10s %-10s %-10s %-10s\n",
                       "ID", "Name", "Basic", "HRA", "Deduct", "Gross");
                printf("--------------------------------------------------------------\n");

                for (int i = 0; i < count; i++) {
                    printf("%-5d %-20s %-10.2f %-10.2f %-10.2f %-10.2f\n",
                           ids[i], names[i], basicSalary[i],
                           hra[i], deductions[i], grossSalary[i]);
                }
            }
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

