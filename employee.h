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
unsigned int calculateGross(unsigned int basic, unsigned int hra, unsigned int deductions);
int addEmployee(Employee emp[], int count);
int loadFromFile(Employee emp[]);
void displaySavedFile();
int deleteEmployee(Employee emp[], int count);
int updateEmployee(Employee emp[], int count);
void saveAllToFile(Employee emp[], int count);

#endif
