#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Function Declarations
int menu();
float calculateGross(float basic, float hra, float deductions);
int addEmployee(int ids[], char names[][50], float basicSalary[],
                float hra[], float deductions[], float grossSalary[], int count);
void displayEmployees(int ids[], char names[][50], float basicSalary[],
                      float hra[], float deductions[], float grossSalary[], int count);

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

//================ MENU FUNCTION =================
int menu() {
    int choice;
    printf("\n====== Employee Payroll System ======\n");
    printf("1. Add Employee\n");
    printf("2. Display All Employees\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

//================ SALARY CALCULATION FUNCTION =================
float calculateGross(float basic, float hra, float deductions) {
    return basic + hra - deductions;
}

//================ ADD EMPLOYEE FUNCTION =================
int addEmployee(int ids[], char names[][50], float basicSalary[],
                float hra[], float deductions[], float grossSalary[], int count) {

    if (count >= MAX) {
        printf("Error: Maximum employee limit reached!\n");
        return count;
    }

    printf("\nEnter Employee ID: ");
    scanf("%d", &ids[count]);

    printf("Enter Name : ");
    fgets(names[count], sizeof(names[count]), stdin);
    names[count][strcspn(names[count], "\n")] = 0; // remove newline

    printf("Enter Basic Salary: ");
    scanf("%f", &basicSalary[count]);

    printf("Enter HRA: ");
    scanf("%f", &hra[count]);

    printf("Enter Deductions: ");
    scanf("%f", &deductions[count]);

    grossSalary[count] = calculateGross(basicSalary[count], hra[count], deductions[count]);

    printf("\n✅ Employee added successfully!\n");

    return count + 1; // increase count
}

//================ DISPLAY EMPLOYEE FUNCTION =================
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

