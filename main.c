#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Employee {
    int id;
    char name[50];
    float basicSalary;
    float hra;       // House Rent Allowance
    float da;        // Dearness Allowance
    float ta;        // Travel Allowance
    float deductions;
    float grossSalary;
};

struct Employee emp[MAX];
int count = 0;

// Function Prototypes
void addEmployee();
void calculateSalary(struct Employee *e);
void displayEmployees();
void saveToFile();
void loadFromFile();

int main() {
    int choice;
    loadFromFile(); // load data at start

    while (1) {
        printf("\n====== Employee Payroll System ======\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Save Records to File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                displayEmployees();
                break;
            case 3:
                saveToFile();
                break;
            case 4:
                printf("\nExiting... Goodbye!\n");
                saveToFile();
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

// Function to add new employee
void addEmployee() {
    if (count >= MAX) {
        printf("Error: Maximum employee limit reached!\n");
        return;
    }

    struct Employee *e = &emp[count];
    printf("\nEnter Employee ID: ");
    scanf("%d", &e->id);
    getchar(); // consume newline

    printf("Enter Name: ");
    fgets(e->name, sizeof(e->name), stdin);
    e->name[strcspn(e->name, "\n")] = 0; // remove newline

    printf("Enter Basic Salary: ");
    scanf("%f", &e->basicSalary);

    printf("Enter HRA: ");
    scanf("%f", &e->hra);

    printf("Enter DA: ");
    scanf("%f", &e->da);

    printf("Enter TA: ");
    scanf("%f", &e->ta);

    printf("Enter Deductions: ");
    scanf("%f", &e->deductions);

    calculateSalary(e);
    count++;

    printf("\n✅ Employee added successfully!\n");
}

// Function to calculate gross salary
void calculateSalary(struct Employee *e) {
    e->grossSalary = e->basicSalary + e->hra + e->da + e->ta - e->deductions;
}

// Function to display employee records
void displayEmployees() {
    if (count == 0) {
        printf("\nNo employee records found!\n");
        return;
    }

    printf("\n%-5s %-20s %-10s %-10s %-10s %-10s %-10s %-10s\n",
           "ID", "Name", "Basic", "HRA", "DA", "TA", "Deduct", "Gross");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %-10.2f %-10.2f %-10.2f %-10.2f %-10.2f %-10.2f\n",
               emp[i].id, emp[i].name, emp[i].basicSalary, emp[i].hra, emp[i].da,
               emp[i].ta, emp[i].deductions, emp[i].grossSalary);
    }
}

// Save data to file
void saveToFile() {
    FILE *fp = fopen("payroll.txt", "w");
    if (fp == NULL) {
        printf("Error: Unable to save file!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %s %.2f %.2f %.2f %.2f %.2f %.2f\n",
                emp[i].id, emp[i].name, emp[i].basicSalary, emp[i].hra, emp[i].da,
                emp[i].ta, emp[i].deductions, emp[i].grossSalary);
    }

    fclose(fp);
    printf("\n💾 Records saved to 'payroll.txt'\n");
}

// Load data from file
void loadFromFile() {
    FILE *fp = fopen("payroll.txt", "r");
    if (fp == NULL) {
        return; // no existing file
    }

    while (fscanf(fp, "%d %s %f %f %f %f %f %f",
                  &emp[count].id, emp[count].name,
                  &emp[count].basicSalary, &emp[count].hra,
                  &emp[count].da, &emp[count].ta,
                  &emp[count].deductions, &emp[count].grossSalary) != EOF) {
        count++;
    }

    fclose(fp);
    printf("📂 Loaded %d employee records from file.\n", count);
}

