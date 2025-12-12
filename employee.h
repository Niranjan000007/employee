#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <stdio.h>
#include <string.h>

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
<<<<<<< HEAD
unsigned int calculateGross(unsigned int basic, unsigned int hra, unsigned int deductions);
int addEmployee(Employee emp[], int count);
int loadFromFile(Employee emp[]);
=======
float calculateGross(float basic, float hra, float deductions);
int addEmployee(Employee emp[], int count);
>>>>>>> 7014e7b104ecdcd7290138e799f5a54e7d12761d
void displaySavedFile();
int deleteEmployee(Employee emp[], int count);
int updateEmployee(Employee emp[], int count);
void saveAllToFile(Employee emp[], int count);

#endif
