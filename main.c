#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#define MAX 100

typedef struct {
    unsigned int id;
    char name[50];
    unsigned int basicSalary;
    unsigned int hra;
    unsigned int deductions;
    unsigned int grossSalary;
} Employee;

int menu();
int loadFromFile(Employee emp[]);
void saveAllToFile(Employee emp[], int count);

int addEmployee(Employee emp[], int count);
int deleteEmployee(Employee emp[], int count);
int updateEmployee(Employee emp[], int count);

void displaySavedFile();

unsigned int calculateGross(unsigned int basic,
                            unsigned int hra,
                            unsigned int deductions);

#endif
