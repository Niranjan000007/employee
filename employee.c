#include "employee.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/* ---------- Safe Integer Reader ---------- */
static int readInt(int *value) {
    char buf[50];
    if (!fgets(buf, sizeof(buf), stdin)) return 0;

    int len = strcspn(buf, "\n");
    if (len == 0) return 0;

    for (int i = 0; i < len; i++)
        if (!isdigit((unsigned char)buf[i])) return 0;

    *value = atoi(buf);
    return 1;
}

/* ---------- Check ID Exists ---------- */
static int idExists(Employee emp[], int count, int id) {
    for (int i = 0; i < count; i++)
        if (emp[i].id == id)
            return 1;
    return 0;
}

/* ---------- Gross Salary Calculator ---------- */
unsigned int calculateGross(unsigned int basic,
                            unsigned int hra,
                            unsigned int deductions) {
    unsigned int total = basic + hra;
    if (deductions >= total) return 0;
    return total - deductions;
}

/* ---------- LOAD FROM FILE ---------- */
int loadFromFile(Employee emp[]) {
    FILE *fp = fopen("employees.txt", "r");
    if (!fp) return 0;

    int count = 0;
    while (!feof(fp) && count < MAX) {
        Employee e;
        if (fscanf(fp, "%u \"%49[^\"]\" %u %u %u %u\n",
                   &e.id, e.name,
                   &e.basicSalary, &e.hra,
                   &e.deductions, &e.grossSalary) == 6) {
            emp[count++] = e;
        }
    }

    fclose(fp);
    return count;
}

/* ---------- SAVE ALL ---------- */
void saveAllToFile(Employee emp[], int count) {
    FILE *fp = fopen("employees.txt", "w");
    if (!fp) return;

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%u \"%s\" %u %u %u %u\n",
                emp[i].id, emp[i].name,
                emp[i].basicSalary, emp[i].hra,
                emp[i].deductions, emp[i].grossSalary);
    }

    fclose(fp);
}

/* ---------- NAME VALIDATION (NO MIN LENGTH) ---------- */
static int isValidName(const char *name) {
    if (strlen(name) == 0) return 0;

    for (int i = 0; name[i]; i++)
        if (!isalpha((unsigned char)name[i]) && name[i] != ' ')
            return 0;

    return 1;
}

/* ---------- ADD EMPLOYEE ---------- */
int addEmployee(Employee emp[], int count) {
    if (count >= MAX) {
        printf("Limit reached\n");
        return count;
    }

    int value;

    /* ID Input */
    printf("Enter Employee ID (1-100): ");
    while (!readInt(&value) || value < 1 || value > 100 ||
           idExists(emp, count, value)) {
        printf("Invalid or exists. Enter again: ");
    }
    emp[count].id = value;

    /* Name Input (NO MIN LENGTH) */
    while (1) {
        printf("Enter Name: ");
        fgets(emp[count].name, sizeof(emp[count].name), stdin);
        emp[count].name[strcspn(emp[count].name, "\n")] = 0;

        if (isValidName(emp[count].name)) break;
        printf("Invalid name! Only letters and spaces allowed.\n");
    }

    /* Salary Fields */
    printf("Enter Basic Salary: ");
    while (!readInt(&value)) printf("Invalid. Enter again: ");
    emp[count].basicSalary = value;

    printf("Enter HRA: ");
    while (!readInt(&value)) printf("Invalid. Enter again: ");
    emp[count].hra = value;

    printf("Enter Deductions: ");
    while (!readInt(&value)) printf("Invalid. Enter again: ");
    emp[count].deductions = value;

    emp[count].grossSalary = calculateGross(
        emp[count].basicSalary,
        emp[count].hra,
        emp[count].deductions
    );

    saveAllToFile(emp, count + 1);

    printf("Employee Added.\n");
    return count + 1;
}

/* ---------- DELETE EMPLOYEE ---------- */
int deleteEmployee(Employee emp[], int count) {
    if (count == 0) {
        printf("No employees.\n");
        return count;
    }

    int id;
    printf("Enter ID to delete: ");
    while (!readInt(&id)) printf("Invalid.\n");

    int index = -1;
    for (int i = 0; i < count; i++)
        if (emp[i].id == id)
            index = i;

    if (index == -1) {
        printf("Not found.\n");
        return count;
    }

    for (int i = index; i < count - 1; i++)
        emp[i] = emp[i + 1];

    saveAllToFile(emp, count - 1);

    printf("Deleted.\n");
    return count - 1;
}

/* ---------- UPDATE EMPLOYEE ---------- */
int updateEmployee(Employee emp[], int count) {
    if (count == 0) {
        printf("No employees.\n");
        return count;
    }

    int id;
    printf("Enter ID to update: ");
    while (!readInt(&id)) printf("Invalid.\n");

    int index = -1;
    for (int i = 0; i < count; i++)
        if (emp[i].id == id)
            index = i;

    if (index == -1) {
        printf("Not found.\n");
        return count;
    }

    /* Update Name */
    while (1) {
        printf("Enter new Name: ");
        fgets(emp[index].name, sizeof(emp[index].name), stdin);
        emp[index].name[strcspn(emp[index].name, "\n")] = 0;

        if (isValidName(emp[index].name)) break;
        printf("Invalid name!\n");
    }

    int value;

    /* Salary Fields */
    printf("Enter Basic Salary: ");
    while (!readInt(&value)) printf("Invalid.\n");
    emp[index].basicSalary = value;

    printf("Enter HRA: ");
    while (!readInt(&value)) printf("Invalid.\n");
    emp[index].hra = value;

    printf("Enter Deductions: ");
    while (!readInt(&value)) printf("Invalid.\n");
    emp[index].deductions = value;

    emp[index].grossSalary = calculateGross(
        emp[index].basicSalary,
        emp[index].hra,
        emp[index].deductions
    );

    saveAllToFile(emp, count);
    printf("Updated.\n");

    return count;
}

/* ---------- DISPLAY FILE ---------- */
void displaySavedFile() {
    FILE *fp = fopen("employees.txt", "r");
    if (!fp) {
        printf("No saved data.\n");
        return;
    }

    char line[200];
    printf("\n=== Employee Records ===\n");
    while (fgets(line, sizeof(line), fp))
        printf("%s", line);

    fclose(fp);
}
