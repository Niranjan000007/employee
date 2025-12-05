#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int id;
    char name[50];
    float basicSalary;
    float hra;
    float deductions;
    float grossSalary;
} Employee;

int menu();
float calculateGross(float basic, float hra, float deductions);
int addEmployee(Employee emp[], int count);
void displaySavedFile();
int deleteEmployee(Employee emp[], int count);
int updateEmployee(Employee emp[], int count);
void saveAllToFile(Employee emp[], int count);

#endif
