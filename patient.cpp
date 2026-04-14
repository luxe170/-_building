#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient.h"

Patient *patientListHead = NULL;

void initPatientList() {  //初始化患者头指针为NULL
	patientListHead = NULL;
}

void addPatient(Patient* p) {	//尾插法添加患者
	if (p == NULL) return;		//添加目标为空，操作无效
	p->next = NULL;
	if (patientListHead == NULL)
	{
		patientListHead = p;
	}
	else
	{
		Patient* current = patientListHead;
		while (current->next != NULL) current = current->next;
		current->next = p;
	}
}

int deletePatientById(int patientId) {        //双指针法删除患者
	if (patientListHead == NULL) return -1;//患者列表为空，无法删除，返回值为-1
	Patient* current = patientListHead;
	Patient* previous = NULL;
	while (current != NULL) {
		if (current->patientId == patientId) {
			if (previous == NULL) {     //特判删除首位置患者
				patientListHead = current->next;
			}
			else {
				previous->next = current->next;
			}
			free(current);
			return 1;	//成功删除患者 返回值为1
		}
		previous = current;
		current = current->next;
	}
	return 0;//未找到患者 返回值为0
}

Patient* searchPatientById(int patientId) {		//线性搜索患者
	if (patientListHead == NULL) return NULL;//患者列表为空，无法搜索
	Patient* current = patientListHead;
	while (current != NULL) {
		if (current->patientId == patientId) return current;//成功找到患者列表

		current = current->next;
	}
	return NULL;//未找到患者
}

Patient* searchPatientByName(char* patientName) {		//准确线性搜索患者
	if (patientListHead == NULL) return NULL;//患者列表为空，无法搜索
	Patient* current = patientListHead;
	while (current != NULL) {
		if (strcmp(current->name,patientName)==0) return current;//成功找到患者
		current = current->next;
	}
	return NULL;//未找到患者
}

void modifyPatient(Patient* patient) {			//修改患者信息
	if (patientListHead == NULL) return;//患者列表为空，无法修改
	Patient* target = searchPatientById(patient->patientId);
	if (target == NULL) return;//未找到患者，无法修改
	target->patientId = patient->patientId;  
	strcpy(target->name, patient->name);
	strcpy(target->gender, patient->gender);
	target->age = patient->age;
	strcpy(target->diagnosis, patient->diagnosis);
	strcpy(target->typeOfPatient, patient->typeOfPatient);
	target->relatedWardId = patient->relatedWardId;
	target->relatedBedId = patient->relatedBedId;
	strcpy(target->phone, patient->phone);
}

void printAllPatients() {		//
	if (patientListHead == NULL) return; //患者列表为空，无效访问
	Patient* current = patientListHead;
	while (current != NULL) {
		printf("%d\n%s\n%s\n%d\n%s\n%s\n%d\n%d\n%s\n",
			current->patientId, current->name, current->gender, current->age, current->diagnosis, current->typeOfPatient, current->relatedWardId, current->relatedBedId, current->phone);
		current = current->next;
	}
}

void savePatientsToFile(const char* filename) {
	FILE* file = fopen(filename, "w");
	if (!file) return;
	Patient* current = patientListHead;
	while (current) {
		fprintf(file, "%d %s %s %d %s %s %d %d %s\n",
			current->patientId, current->name, current->gender, current->age,
			current->diagnosis, current->typeOfPatient, current->relatedWardId,
			current->relatedBedId, current->phone);
		current = current->next;
	}
	fclose(file);
}

void loadPatientsFromFile(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (!file) return;
	initPatientList();
	Patient* p;
	while ((p = (Patient*)malloc(sizeof(Patient)))) {
		if (fscanf(file, "%d %s %s %d %s %s %d %d %s",
			&p->patientId, p->name, p->gender, &p->age,
			p->diagnosis, p->typeOfPatient, &p->relatedWardId,
			&p->relatedBedId, p->phone) != 9) {
			free(p);
			break;
		}
		p->next = NULL;
		addPatient(p);
	}
	fclose(file);
}