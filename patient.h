#pragma once
#ifndef PATIENT_H
#define PATIENT_H

#define PATIENT_NAME_LEN 50
#define PATIENT_GENDER_LEN 10 
#define PATIENT_DIAGNOSIS_LEN 100
#define PATIENT_PHONE_LEN 20
#define PATIENT_TYPE_LEN 20
#define PATIENT_ID_CARD_LEN 20

typedef struct Patient {
	char idCard[PATIENT_ID_CARD_LEN];		//身份证号区分重名
	int patientId;
	char name[PATIENT_NAME_LEN];
	char gender[PATIENT_GENDER_LEN];
	int age;
	char diagnosis[PATIENT_DIAGNOSIS_LEN];//诊断结果
	char typeOfPatient[PATIENT_TYPE_LEN]; //门诊/住院
	int relatedWardId; //住院患者关联病房ID，门诊患者为-1  
	int relatedBedId; //住院患者关联病床ID，门诊患者为-1   
	char phone[PATIENT_PHONE_LEN];
	
	struct Patient* next;
	//医疗记录还没写
	//还有科室 大夫
} Patient;
extern Patient* patientListHead; // 病人链表头指针

void initPatientList();
void addPatient(Patient* patientListHead);
int deletePatientById(int patientId); //返回类型int是为了确认删除状态
Patient* searchPatientById(int patientId);
Patient* searchPatientByName(char* patientName);
void modifyPatient(Patient* patient);
void printAllPatients();
void savePatientsToFile(const char* filename);
void loadPatientsFromFile(const char* filename);

#endif