#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doctor.h"

Doctor *doctorListHead = NULL;

void initDoctorList() {
    doctorListHead = NULL;
}

void addDoctor(Doctor* p) {
    if (p == NULL) return;
    p->next = NULL;
    if (doctorListHead == NULL) {
        doctorListHead = p;
    } else {
        Doctor* current = doctorListHead;
        while (current->next != NULL) current = current->next;
        current->next = p;
    }
}

int deleteDoctorById(int doctorId) {
    if (doctorListHead == NULL) return -1;
    Doctor* current = doctorListHead;
    Doctor* previous = NULL;
    while (current != NULL) {
        if (current->doctorId == doctorId) {
            if (previous == NULL) {
                doctorListHead = current->next;
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

Doctor* searchDoctorById(int doctorId) {
    if (doctorListHead == NULL) return NULL;
    Doctor* current = doctorListHead;
    while (current != NULL) {
        if (current->doctorId == doctorId) return current;
        current = current->next;
    }
    return NULL;
}

Doctor* searchDoctorByName(char* doctorName) {
    if (doctorListHead == NULL) return NULL;
    Doctor* current = doctorListHead;
    while (current != NULL) {
        if (strcmp(current->name, doctorName) == 0) return current;
        current = current->next;
    }
    return NULL;
}

void modifyDoctor(Doctor* doctor) {
    if (doctorListHead == NULL) return;
    Doctor* target = searchDoctorById(doctor->doctorId);
    if (target == NULL) return;
    target->doctorId = doctor->doctorId;
    strcpy(target->name, doctor->name);
    target->departmentId = doctor->departmentId;
    strcpy(target->phone, doctor->phone);
}

void printAllDoctors() {
    if (doctorListHead == NULL) return;
    Doctor* current = doctorListHead;
    while (current != NULL) {
        printf("%d\n%s\n%d\n%s\n",
            current->doctorId, current->name, current->departmentId, current->phone);
        current = current->next;
    }
}

void saveDoctorsToFile(const char* filename) {
	FILE* file = fopen(filename, "w");
	if (!file) return;
	Doctor* current = doctorListHead;
	while (current) {
		fprintf(file, "%d %s %d %s %s %s %d %d %d %s %s\n",
			current->doctorId, current->gender, current->age, current->name,  current->title,  current->specialty, current->onDuty, current->departmentId,current->departmentName,current->phone);
		current = current->next;
	}
	fclose(file);
}
/*
    int doctorId;
	char idCard[DOCTOR_ID_CARD_LEN]; //身份证号区分重名
	char gender[10];
	int age;
	char name[DOCTOR_NAME_LEN];
	char title[DOCTOR_TITLE_LEN]; //职称
	char specialty[DOCTOR_SPECIALTY_LEN]; //专业
	int onDuty; //是否值班：0-不值班，1-值班
	int departmentId; //医生所属科室ID
	char departmentName[DOCTOR_DEPARTMENT_LEN]; //医生所属科室名称
	char phone[DOCTOR_PHONE_LEN];
*/

void loadDoctorsFromFile(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (!file) return;
	initDoctorList();
	Doctor* d;
	while (1) {
		d = (Doctor*)malloc(sizeof(Doctor));
		if (fscanf(file, "%d %s %d %s %s %s %d %d %d %s %s",
			&d->doctorId, d->gender, &d->age, d->name,  d->title,  d->specialty, &d->onDuty, &d->departmentId,d->departmentName,d->phone) != 10) {
			free(d);
			break;
		}
		d->next = NULL;
		addDoctor(d);
	}
	fclose(file);
}
