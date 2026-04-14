#pragma once
#ifndef DOCTOR_H
#define DOCTOR_H

#define DOCTOR_NAME_LEN 50
#define DOCTOR_DEPARTMENT_LEN 50
#define DOCTOR_PHONE_LEN 20
#define DOCTOR_TITLE_LEN 30
#define DOCTOR_ID_CARD_LEN 20
#define DOCTOR_SPECIALTY_LEN 50

typedef struct Doctor {
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
	struct Doctor* next;
} Doctor;

extern Doctor* doctorListHead; // 医生链表头指针

void initDoctorList();
void addDoctor(Doctor* doctorListHead);
int deleteDoctorById(int doctorId); //返回类型int是为了确认删除状态
Doctor* searchDoctorById(int doctorId);
Doctor* searchDoctorByName(char* doctorName);
void modifyDoctor(Doctor* doctor);
void printAllDoctors();

void saveDoctorsToFile(const char* filename);//L
void loadDoctorsFromFile(const char* filename);
	
#endif