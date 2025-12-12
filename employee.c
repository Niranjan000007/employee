#include "employee.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

<<<<<<< HEAD
/* safe integer reader (only positive integers) */
=======
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
>>>>>>> 7014e7b104ecdcd7290138e799f5a54e7d12761d
static int readInt(int *value) {
    char buf[100];
    if (!fgets(buf, sizeof(buf), stdin)) return 0;

    int len = strcspn(buf, "\n");
    if (len == 0) return 0;

    for (int i = 0; i < len; i++)
<<<<<<< HEAD
        if (!isdigit((unsigned char)buf[i])) return 0;
=======
        if (!isdigit(buf[i])) return 0;
>>>>>>> 7014e7b104ecdcd7290138e799f5a54e7d12761d

    *value = atoi(buf);
    return 1;
}

<<<<<<< HEAD
/* Check if ID exists */
static int idExists(Employee emp[], int count, int id) {
    for (int i = 0; i < count; i++)
        if (emp[i].id == id)
            return 1;
    return 0;
}

/* calculate gross safely (avoid unsigned underflow) */
unsigned int calculateGross(unsigned int basic, unsigned int hra, unsigned int deductions) {
    unsigned int total = basic + hra;
    if (deductions >= total) return 0;
    return total - deductions;
}
=======
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
>>>>>>> 7014e7b104ecdcd7290138e799f5a54e7d12761d

/* ------------------ LOAD FROM FILE ------------------ */
/* Expected line format:
   id "Name with spaces" basic hra deductions gross
   Example:
   12 "Niranjan Kumar" 30000 4000 1000 33000
*/
int loadFromFile(Employee emp[]) {
    FILE *fp = fopen("employees.txt", "r");
    if (!fp) return 0;

    char line[512];
    int count = 0;
    while (fgets(line, sizeof(line), fp)) {
        char *p = line;
        int id;
        if (sscanf(p, "%d", &id) != 1) continue;

        /* find first quote */
        char *q = strchr(p, '\"');
        if (!q) continue;
        char *r = strchr(q + 1, '\"');
        if (!r) continue;

        char namebuf[50];
        int nlen = (int)(r - (q + 1));
        if (nlen <= 0) continue;
        if (nlen >= (int)sizeof(namebuf))
            nlen = sizeof(namebuf) - 1;
        strncpy(namebuf, q + 1, nlen);
        namebuf[nlen] = '\0';

        unsigned int basic, hra, ded, gross;
        if (sscanf(r + 1, "%u %u %u %u", &basic, &hra, &ded, &gross) != 4)
            continue;

        emp[count].id = id;
        strncpy(emp[count].name, namebuf, sizeof(emp[count].name));
        emp[count].name[sizeof(emp[count].name)-1] = '\0';
        emp[count].basicSalary = basic;
        emp[count].hra = hra;
        emp[count].deductions = ded;
        emp[count].grossSalary = gross;

        count++;
        if (count >= MAX) break;
    }

    fclose(fp);
    return count;
}

/* ------------------ SAVE ENTIRE DATA ------------------ */
void saveAllToFile(Employee emp[], int count) {
    FILE *fp = fopen("employees.txt", "w");
    if (!fp) {
        perror("File error");
        return;
    }

    for (int i = 0; i < count; i++) {
        /* write name in quotes so spaces are preserved */
        fprintf(fp, "%d \"%s\" %u %u %u %u\n",
                emp[i].id,
                emp[i].name,
                emp[i].basicSalary,
                emp[i].hra,
                emp[i].deductions,
                emp[i].grossSalary);
    }

    fclose(fp);
}

/* ------------------ ADD EMPLOYEE ------------------ */
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

<<<<<<< HEAD
        /* enforce ID range 1–100 */
=======
        // NEW: enforce ID range 1–100
>>>>>>> 7014e7b104ecdcd7290138e799f5a54e7d12761d
        if (tempID < 1 || tempID > 100) {
            printf("ID must be between 1 and 100. Enter again: ");
            continue;
        }

<<<<<<< HEAD
        /* Duplicate ID check */
=======
        // Duplicate ID check
>>>>>>> 7014e7b104ecdcd7290138e799f5a54e7d12761d
        if (idExists(emp, count, tempID)) {
            printf("ID already exists! Enter a new ID: ");
            continue;
        }

        break;
    }

    emp[count].id = tempID;

<<<<<<< HEAD
    /* Name input (allow spaces). Remove min length requirement. Keep alpha + space validation. */
    while (1) {
        printf("Enter Name: ");
        if (!fgets(emp[count].name, sizeof(emp[count].name), stdin)) {
            emp[count].name[0] = '\0';
        } else {
            emp[count].name[strcspn(emp[count].name, "\n")] = '\0';
        }
=======
    // Name validation
    while (1) {
        printf("Enter Name (min 8 chars): ");
        fgets(emp[count].name, sizeof(emp[count].name), stdin);
        emp[count].name[strcspn(emp[count].name, "\n")] = 0;
>>>>>>> 7014e7b104ecdcd7290138e799f5a54e7d12761d

        int len = strlen(emp[count].name);
        int valid = 1;
<<<<<<< HEAD
        if (emp[count].name[0] == '\0') valid = 0;

        for (int i = 0; emp[count].name[i]; i++) {
            if (!isalpha((unsigned char)emp[count].name[i]) && emp[count].name[i] != ' ') {
=======

        if (len < 8) valid = 0;
        if (len == 0) valid = 0;

        for (int i = 0; emp[count].name[i]; i++)
            if (!isalpha(emp[count].name[i]) && emp[count].name[i] != ' ')
>>>>>>> 7014e7b104ecdcd7290138e799f5a54e7d12761d
                valid = 0;
                break;
            }
        }

        if (valid) break;
<<<<<<< HEAD
        printf("Invalid name! Use only letters and spaces.\n");
    }

    /* Salary fields (unsigned ints). Use readInt and cast */
    int tmp;
    printf("Enter Basic Salary (integer): ");
    while (!readInt(&tmp))
        printf("Invalid! Enter again: ");
    emp[count].basicSalary = (unsigned int)tmp;

    printf("Enter HRA (integer): ");
    while (!readInt(&tmp))
        printf("Invalid! Enter again: ");
    emp[count].hra = (unsigned int)tmp;

    printf("Enter Deductions (integer): ");
    while (!readInt(&tmp))
        printf("Invalid! Enter again: ");
    emp[count].deductions = (unsigned int)tmp;
=======
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
>>>>>>> 7014e7b104ecdcd7290138e799f5a54e7d12761d

    emp[count].grossSalary = calculateGross(emp[count].basicSalary,
                                           emp[count].hra,
                                           emp[count].deductions);

    saveAllToFile(emp, count + 1);

    printf("Employee Added.\n");
    return count + 1;
}

<<<<<<< HEAD
/* ------------------ DELETE EMPLOYEE ------------------ */
=======
// ------------------ SAVE ENTIRE DATA ------------------
void saveAllToFile(Employee emp[], int count) {
    FILE *fp = fopen("employees.txt", "w");
    if (!fp) {
        perror("File error");
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
>>>>>>> 7014e7b104ecdcd7290138e799f5a54e7d12761d
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

<<<<<<< HEAD
/* ------------------ UPDATE EMPLOYEE ------------------ */
=======
// ------------------ UPDATE EMPLOYEE ------------------
>>>>>>> 7014e7b104ecdcd7290138e799f5a54e7d12761d
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

<<<<<<< HEAD
    /* --------- UPDATE NAME --------- */
    if (choice == 1 || choice == 2) {
        while (1) {
            printf("Enter new Name: ");
            if (!fgets(emp[index].name, sizeof(emp[index].name), stdin)) {
                emp[index].name[0] = '\0';
            } else {
                emp[index].name[strcspn(emp[index].name, "\n")] = '\0';
            }

            int valid = 1;
            if (emp[index].name[0] == '\0') valid = 0;

            for (int i = 0; emp[index].name[i]; i++)
                if (!isalpha((unsigned char)emp[index].name[i]) && emp[index].name[i] != ' ')
                    valid = 0;

            if (valid) break;
            printf("Invalid name! Use only letters and spaces.\n");
        }
    }

    /* --------- UPDATE SALARY FIELDS --------- */
    if (choice == 1 || choice == 3) {
        int tmp;
        printf("Enter Basic Salary (integer): ");
        while (!readInt(&tmp))
            printf("Invalid! Enter again: ");
        emp[index].basicSalary = (unsigned int)tmp;

        printf("Enter HRA (integer): ");
        while (!readInt(&tmp))
            printf("Invalid! Enter again: ");
        emp[index].hra = (unsigned int)tmp;

        printf("Enter Deductions (integer): ");
        while (!readInt(&tmp))
            printf("Invalid! Enter again: ");
        emp[index].deductions = (unsigned int)tmp;
    }

    emp[index].grossSalary = calculateGross(emp[index].basicSalary,
                                           emp[index].hra,
                                           emp[index].deductions);
=======
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
>>>>>>> 7014e7b104ecdcd7290138e799f5a54e7d12761d

    saveAllToFile(emp, count);

    printf("Employee updated successfully.\n");

    return count;
}

<<<<<<< HEAD
/* ------------------ DISPLAY FILE ------------------ */
=======
// ------------------ DISPLAY FILE ------------------
>>>>>>> 7014e7b104ecdcd7290138e799f5a54e7d12761d
void displaySavedFile() {
    FILE *fp = fopen("employees.txt", "r");

    if (!fp) {
        printf("No saved records found.\n");
        return;
    }

    printf("\n===== Employee Records =====\n");

    char line[512];
    while (fgets(line, sizeof(line), fp))
        printf("%s", line);

    fclose(fp);
}
