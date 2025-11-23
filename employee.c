#include "employee.h"
#include <ctype.h>
#include <stdlib.h>

float calculateGross(float basic, float hra, float deductions) {
    return basic + hra - deductions;
}

static int readInt(int *value) {
    char buf[100];
    if (!fgets(buf, sizeof(buf), stdin)) return 0;

    for (int i = 0; buf[i] && buf[i] != '\n'; i++)
        if (!isdigit(buf[i])) return 0;

    *value = atoi(buf);
    return 1;
}

static int readFloat(float *value) {
    char buf[100];
    int dots = 0;

    if (!fgets(buf, sizeof(buf), stdin)) return 0;

    for (int i = 0; buf[i] && buf[i] != '\n'; i++) {
        if (buf[i] == '.') { dots++; continue; }
        if (!isdigit(buf[i])) return 0;
    }
    if (dots > 1) return 0;

    *value = atof(buf);
    return 1;
}

int addEmployee(Employee emp[], int count) {

    if (count >= MAX) {
        printf("Error: Maximum limit reached!\n");
        return count;
    }

    printf("\nEnter Employee ID: ");
    while (!readInt(&emp[count].id))
        printf("Invalid ID! Enter numbers only: ");

    while (1) {
        printf("Enter Name : ");
        fgets(emp[count].name, sizeof(emp[count].name), stdin);
        emp[count].name[strcspn(emp[count].name, "\n")] = 0;

        int valid = 1;
        for (int i = 0; emp[count].name[i] != '\0'; i++)
            if (!isalpha(emp[count].name[i]) && emp[count].name[i] != ' ')
                valid = 0;

        if (valid && strlen(emp[count].name) > 0) break;

        printf("Invalid! Alphabets only.\n");
    }

    printf("Enter Basic Salary: ");
    while (!readFloat(&emp[count].basicSalary))
        printf("Invalid input! Enter number: ");

    printf("Enter HRA: ");
    while (!readFloat(&emp[count].hra))
        printf("Invalid input! Enter number: ");

    printf("Enter Deductions: ");
    while (!readFloat(&emp[count].deductions))
        printf("Invalid input! Enter number: ");

    emp[count].grossSalary =
        calculateGross(emp[count].basicSalary,
                       emp[count].hra,
                       emp[count].deductions);

    /* ------------------------------------
       Write to file immediately (auto-save)
       ------------------------------------ */
    FILE *fp = fopen("employees.txt", "a");
    if (!fp) {
        printf("Error opening file!\n");
    } else {
        fprintf(fp, "%d %s %.2f %.2f %.2f %.2f\n",
                emp[count].id,
                emp[count].name,
                emp[count].basicSalary,
                emp[count].hra,
                emp[count].deductions,
                emp[count].grossSalary);

        fclose(fp);
    }

    printf("Employee Details added");

    return count + 1;
}

void displaySavedFile() {
    FILE *fp = fopen("employees.txt", "r");

    if (!fp) {
        printf("\nNo saved records found!\n");
        return;
    }

    printf("\n===== Employee Records (From File) =====\n");

    char line[200];
    while (fgets(line, sizeof(line), fp))
        printf("%s", line);

    fclose(fp);
}

