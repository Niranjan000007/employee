#include "employee.h"

float calculateGross(float basic, float hra, float deductions) {
    return basic + hra - deductions;
}

int addEmployee(Employee emp[], int count) {

    if (count >= MAX) {
        printf("Error: Maximum employee limit reached!\n");
        return count;
    }

    printf("\nEnter Employee ID: ");
    scanf("%d", &emp[count].id);
    getchar();

    printf("Enter Name : ");
    fgets(emp[count].name, sizeof(emp[count].name), stdin);
    emp[count].name[strcspn(emp[count].name, "\n")] = 0;

    printf("Enter Basic Salary: ");
    scanf("%f", &emp[count].basicSalary);

    printf("Enter HRA: ");
    scanf("%f", &emp[count].hra);

    printf("Enter Deductions: ");
    scanf("%f", &emp[count].deductions);

    emp[count].grossSalary = calculateGross(emp[count].basicSalary, emp[count].hra, emp[count].deductions);

    printf("\n✅ Employee added successfully!\n");

    return count + 1;
}

void displayEmployees(Employee emp[], int count) {

    if (count == 0) {
        printf("\nNo employee records found!\n");
        return;
    }

    printf("\n%-5s %-20s %-10s %-10s %-10s %-10s\n",
           "ID", "Name", "Basic", "HRA", "Deduct", "Gross");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %-10.2f %-10.2f %-10.2f %-10.2f\n",
               emp[i].id, emp[i].name, emp[i].basicSalary,
               emp[i].hra, emp[i].deductions, emp[i].grossSalary);
    }
}

