// employee.h
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int menu();
float calculateGross(float basic, float hra, float deductions);
int addEmployee(int ids[], char names[][50], float basicSalary[],
                float hra[], float deductions[], float grossSalary[], int count);
void displayEmployees(int ids[], char names[][50], float basicSalary[],
                      float hra[], float deductions[], float grossSalary[], int count);

#endif

