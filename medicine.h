#pragma once

#ifndef MEDICINE_H
#define MEDICINE_H

#define MEDICINE_NAME_LEN 50
#define	MANUFACTURER_NAME_LEN 50
typedef struct Medicine {  //生产日期?
	int medicineId;
	char name[MEDICINE_NAME_LEN];
	char manufacturer[MANUFACTURER_NAME_LEN]; //生产厂家
	int inventory; //库存量
	double purchasePrice; //进价
	double sellingPrice; //售价
	int relatedDepartmentId; //药品关联科室ID
	struct Medicine* next;
} Medicine;

extern Medicine* medicineListHead; // 药品链表头指针

void initMedicineList();
void addMedicine(Medicine* medicineListHead);
int deleteMedicineById(int medicineId); //返回类型int是为了确认删除状态
Medicine* searchMedicineById(int medicineId);
Medicine* searchMedicineByName(char* medicineName);
void modifyMedicine(Medicine* medicine);
void printAllMedicines();
void saveMedicinesToFile(const char* filename);
void loadMedicinesFromFile(const char* filename);


#endif
