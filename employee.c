// employee.c
#include "employee.h"

float calculateGross(float basic, float hra, float deductions) {
    return basic + hra - deductions;
}

int addEmployee(int ids[], char names[][50], float basicSalary[],
                float hra[], float deductions[], float grossSalary[], int count) {

    if (count >= MAX) {
        printf("Error: Maximum employee limit reached!\n");
        return count;
    }

    printf("\nEnter Employee ID: ");
    scanf("%d", &ids[count]);
    getchar(); // clear leftover newline

    printf("Enter Name : ");
    fgets(names[count], sizeof(names[count]), stdin);
    names[count][strcspn(names[count], "\n")] = 0;

    printf("Enter Basic Salary: ");
    scanf("%f", &basicSalary[count]);

    printf("Enter HRA: ");
    scanf("%f", &hra[count]);

    printf("Enter Deductions: ");
    scanf("%f", &deductions[count]);

    grossSalary[count] = calculateGross(basicSalary[count], hra[count], deductions[count]);

    printf("\n✅ Employee added successfully!\n");

    return count + 1;
}

void displayEmployees(int ids[], char names[][50], float basicSalary[],
                      float hra[], float deductions[], float grossSalary[], int count) {

    if (count == 0) {
        printf("\nNo employee records found!\n");
        return;
    }

    printf("\n%-5s %-20s %-10s %-10s %-10s %-10s\n",
           "ID", "Name", "Basic", "HRA", "Deduct", "Gross");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %-10.2f %-10.2f %-10.2f %-10.2f\n",
               ids[i], names[i], basicSalary[i],
               hra[i], deductions[i], grossSalary[i]);
    }
}

