#include "employee.h"
#include <ctype.h>
#include <stdlib.h>

static int readInt(int *value);
static int readFloat(float *value);

// Check if ID exists
static int idExists(Employee emp[], int count, int id) {
    for (int i = 0; i < count; i++)
        if (emp[i].id == id)
            return 1;
    return 0;
}

float calculateGross(float basic, float hra, float deductions) {
    return basic + hra - deductions;
}

// ------------------ SAFE INPUT ------------------
static int readInt(int *value) {
    char buf[100];
    if (!fgets(buf, sizeof(buf), stdin)) return 0;

    int len = strcspn(buf, "\n");
    if (len == 0) return 0;

    for (int i = 0; i < len; i++)
        if (!isdigit(buf[i])) return 0;

    *value = atoi(buf);
    return 1;
}

static int readFloat(float *value) {
    char buf[100];
    int dots = 0;

    if (!fgets(buf, sizeof(buf), stdin)) return 0;
    int len = strcspn(buf, "\n");
    if (len == 0) return 0;

    for (int i = 0; i < len; i++) {
        if (buf[i] == '.') { dots++; continue; }
        if (!isdigit(buf[i])) return 0;
    }
    if (dots > 1) return 0;

    *value = atof(buf);
    return 1;
}

// ------------------ ADD EMPLOYEE ------------------
int addEmployee(Employee emp[], int count) {

    if (count >= MAX) {
        printf("Error: Maximum limit reached!\n");
        return count;
    }

    int tempID;
    printf("\nEnter Employee ID: ");

    while (1) {
        while (!readInt(&tempID))
            printf("Invalid ID. Enter again: ");

        if (idExists(emp, count, tempID))
            printf("ID exists! Enter a new ID: ");
        else
            break;
    }

    emp[count].id = tempID;

    // Name validation
    while (1) {
        printf("Enter Name (min 8 chars): ");
        fgets(emp[count].name, sizeof(emp[count].name), stdin);
        emp[count].name[strcspn(emp[count].name, "\n")] = 0;

        int len = strlen(emp[count].name);
        int valid = 1;

        if (len < 8) valid = 0;
        if (len == 0) valid = 0;

        for (int i = 0; emp[count].name[i]; i++)
            if (!isalpha(emp[count].name[i]) && emp[count].name[i] != ' ')
                valid = 0;

        if (valid) break;
        printf("Invalid name!\n");
    }

    printf("Enter Basic Salary: ");
    while (!readFloat(&emp[count].basicSalary))
        printf("Invalid! Enter again: ");

    printf("Enter HRA: ");
    while (!readFloat(&emp[count].hra))
        printf("Invalid! Enter again: ");

    printf("Enter Deductions: ");
    while (!readFloat(&emp[count].deductions))
        printf("Invalid! Enter again: ");

    emp[count].grossSalary =
        calculateGross(emp[count].basicSalary,
                       emp[count].hra,
                       emp[count].deductions);

    saveAllToFile(emp, count + 1);

    printf("Employee Added.\n");
    return count + 1;
}

// ------------------ SAVE ENTIRE DATA ------------------
void saveAllToFile(Employee emp[], int count) {
    FILE *fp = fopen("employees.txt", "w");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %s %.2f %.2f %.2f %.2f\n",
                emp[i].id,
                emp[i].name,
                emp[i].basicSalary,
                emp[i].hra,
                emp[i].deductions,
                emp[i].grossSalary);
    }

    fclose(fp);
}

// ------------------ DELETE EMPLOYEE ------------------
int deleteEmployee(Employee emp[], int count) {
    if (count == 0) {
        printf("No employees to delete.\n");
        return count;
    }

    int id;
    printf("Enter ID to delete: ");
    while (!readInt(&id))
        printf("Invalid! Enter again: ");

    int index = -1;
    for (int i = 0; i < count; i++)
        if (emp[i].id == id)
            index = i;

    if (index == -1) {
        printf("ID not found.\n");
        return count;
    }

    for (int i = index; i < count - 1; i++)
        emp[i] = emp[i + 1];

    saveAllToFile(emp, count - 1);

    printf("Employee deleted successfully.\n");
    return count - 1;
}

// ------------------ UPDATE EMPLOYEE ------------------
int updateEmployee(Employee emp[], int count) {
    if (count == 0) {
        printf("No employees to update.\n");
        return count;
    }

    int id;
    printf("Enter ID to update: ");
    while (!readInt(&id))
        printf("Invalid! Enter again: ");

    int index = -1;
    for (int i = 0; i < count; i++)
        if (emp[i].id == id)
            index = i;

    if (index == -1) {
        printf("ID not found.\n");
        return count;
    }

    int choice;
    printf("\nUpdate Options:\n");
    printf("1. Update ALL fields\n");
    printf("2. Update NAME only\n");
    printf("3. Update SALARY fields only\n");
    printf("Enter choice: ");

    while (!readInt(&choice))
        printf("Invalid! Enter again: ");

    // --------- UPDATE NAME ---------
    if (choice == 1 || choice == 2) {
        while (1) {
            printf("Enter new Name (min 8 chars): ");
            fgets(emp[index].name, sizeof(emp[index].name), stdin);
            emp[index].name[strcspn(emp[index].name, "\n")] = 0;

            int len = strlen(emp[index].name);
            int valid = 1;

            if (len < 8) valid = 0;

            for (int i = 0; emp[index].name[i]; i++)
                if (!isalpha(emp[index].name[i]) && emp[index].name[i] != ' ')
                    valid = 0;

            if (valid) break;
            printf("Invalid name!\n");
        }
    }

    // --------- UPDATE SALARY FIELDS ---------
    if (choice == 1 || choice == 3) {
        printf("Enter Basic Salary: ");
        while (!readFloat(&emp[index].basicSalary))
            printf("Invalid! Enter again: ");

        printf("Enter HRA: ");
        while (!readFloat(&emp[index].hra))
            printf("Invalid! Enter again: ");

        printf("Enter Deductions: ");
        while (!readFloat(&emp[index].deductions))
            printf("Invalid! Enter again: ");
    }

    emp[index].grossSalary =
        calculateGross(emp[index].basicSalary,
                       emp[index].hra,
                       emp[index].deductions);

    saveAllToFile(emp, count);

    printf("Employee updated successfully.\n");

    return count;
}

// ------------------ DISPLAY FILE ------------------
void displaySavedFile() {
    FILE *fp = fopen("employees.txt", "r");

    if (!fp) {
        printf("No saved records found.\n");
        return;
    }

    printf("\n===== Employee Records =====\n");

    char line[200];
    while (fgets(line, sizeof(line), fp))
        printf("%s", line);

    fclose(fp);
}
