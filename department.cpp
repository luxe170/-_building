#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "department.h"

Department *departmentListHead = NULL;

void initDepartmentList() {
    departmentListHead = NULL;
}

void addDepartment(Department* p) {
    if (p == NULL) return;
    p->next = NULL;
    if (departmentListHead == NULL) {
        departmentListHead = p;
    } else {
        Department* current = departmentListHead;
        while (current->next != NULL) current = current->next;
        current->next = p;
    }
}

int deleteDepartmentById(int departmentId) {
    if (departmentListHead == NULL) return -1;
    Department* current = departmentListHead;
    Department* previous = NULL;
    while (current != NULL) {
        if (current->departmentId == departmentId) {
            if (previous == NULL) {
                departmentListHead = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            return 1;
        }
        previous = current;
        current = current->next;
    }
    return 0;
}

Department* searchDepartmentById(int departmentId) {
    if (departmentListHead == NULL) return NULL;
    Department* current = departmentListHead;
    while (current != NULL) {
        if (current->departmentId == departmentId) return current;
        current = current->next;
    }
    return NULL;
}

void modifyDepartment(Department* department) {
    if (departmentListHead == NULL) return;
    Department* target = searchDepartmentById(department->departmentId);
    if (target == NULL) return;
    target->departmentId = department->departmentId;
    strcpy(target->name, department->name);
    target->numberOfDoctors = department->numberOfDoctors;
}

void printAllDepartments() {
    if (departmentListHead == NULL) return;
    Department* current = departmentListHead;
    while (current != NULL) {
        printf("%d\n%s\n%d\n",
            current->departmentId, current->name, current->numberOfDoctors);
        current = current->next;
    }
}

void saveDepartmentsToFile(const char* filename) {
	FILE* file = fopen(filename, "w");
	if (!file) return;
	Department* current = departmentListHead;
	while (current) {
		fprintf(file, "%d %s %d\n",
			current->departmentId, current->name, current->numberOfDoctors);
		current = current->next;
	}
	fclose(file);
}

void loadDepartmentsFromFile(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (!file) return;
	initDepartmentList();
	Department* dep;
	while ((dep = (Department*)malloc(sizeof(Department)))) {
		if (fscanf(file, "%d %s %d",
			&dep->departmentId, dep->name, &dep->numberOfDoctors) != 3) {
			free(dep);
			break;
		}
		dep->next = NULL;
		addDepartment(dep);
	}
	fclose(file);
}
