#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "medicine.h"

Medicine *medicineListHead = NULL;

void initMedicineList() {
    medicineListHead = NULL;
}

void addMedicine(Medicine* p) {
    if (p == NULL) return;   
    p->next = NULL;
    if (medicineListHead == NULL) {
        medicineListHead = p;
    } else {
        Medicine* current = medicineListHead;
        while (current->next != NULL) current = current->next;
        current->next = p;
    }
}

int deleteMedicineById(int medicineId) {
    if (medicineListHead == NULL) return -1;
    Medicine* current = medicineListHead;
    Medicine* previous = NULL;
    while (current != NULL) {
        if (current->medicineId == medicineId) {
            if (previous == NULL) {
                medicineListHead = current->next;
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

Medicine* searchMedicineById(int medicineId) {
    if (medicineListHead == NULL) return NULL;
    Medicine* current = medicineListHead;
    while (current != NULL) {
        if (current->medicineId == medicineId) return current;
        current = current->next;
    }
    return NULL;
}

Medicine* searchMedicineByName(char* medicineName) {
    if (medicineListHead == NULL) return NULL;
    Medicine* current = medicineListHead;
    while (current != NULL) {
        if (strcmp(current->name, medicineName) == 0) return current;
        current = current->next;
    }
    return NULL;
}

void modifyMedicine(Medicine* medicine) {
    if (medicineListHead == NULL) return;
    Medicine* target = searchMedicineById(medicine->medicineId);
    if (target == NULL) return;
    target->medicineId = medicine->medicineId;
    strcpy(target->name, medicine->name);
    target->inventory = medicine->inventory;
    target->sellingPrice = medicine->sellingPrice;
    target->purchasePrice = medicine->purchasePrice;
    target->relatedDepartmentId = medicine->relatedDepartmentId;
}

void printAllMedicines() {
    if (medicineListHead == NULL) return;
    Medicine* current = medicineListHead;
    while (current != NULL) {
        printf("%d\n%s\n%d\n%d\n%d\n%d\n",
            current->medicineId, current->name, current->inventory, current->sellingPrice, current->purchasePrice, current->relatedDepartmentId);
        current = current->next;
    }
}

void saveMedicinesToFile(const char* filename) {
	FILE* file = fopen(filename, "w");
	if (!file) return;
	Medicine* current = medicineListHead;
	while (current) {
		fprintf(file, "%d %s %s %d %lf %lf %d\n",
			current->medicineId, current->name, current->manufacturer,  current->inventory, current->purchasePrice,current->sellingPrice, current->relatedDepartmentId);
		current = current->next;
	}
	fclose(file);
}

void loadMedicinesFromFile(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (!file) return;
	initMedicineList();
	Medicine* m;
	while (1) {
		m = (Medicine*)malloc(sizeof(Medicine));
		if (fscanf(file, "%d %s %s %d %lf %lf %d",
			&m->medicineId, m->name, m->manufacturer,  &m->inventory, &m->purchasePrice,&m->sellingPrice, &m->relatedDepartmentId) != 7) {
			free(m);
			break;
		}
		m->next = NULL;
		addMedicine(m);
	}
	fclose(file);
}