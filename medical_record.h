#pragma once
#ifndef MEDICAL_RECORD_H
#define MEDICAL_RECORD_H

#define MEDICAL_RECORD_TIME 20
#define DOCTOR_NAME_LEN 50 
#define TYPE_OF_MEDICAL_RECORD 30
#define MEDICAL_RECORD_DETAIL_LEN 100

typedef struct MedicalRecord {
	int medicalRecordId;
	int patientId;
	int relatedDoctorId;//关联医生
	//建议修改
	char typeOfMedicalRecord[TYPE_OF_MEDICAL_RECORD]; //挂号状态：已挂号待诊/已就诊/已住院/已退号    /处方？
	char time[MEDICAL_RECORD_TIME];//挂号时间 收集时间戳转换为本地时间成字符串 
	char detail[MEDICAL_RECORD_DETAIL_LEN];
	int status; //挂号状态：0-已挂号待诊，1-已就诊，2-已住院，3-已退号
	struct MedicalRecord* next;
} MedicalRecord;

extern MedicalRecord* medicalRecordListHead; // 挂号记录链表头指针

void initMedicalRecordList();
void addMedicalRecord(MedicalRecord* medicalRecordListHead);
int deleteMedicalRecordById(int medicalRecordId); //返回类型int是为了确认删除状态
MedicalRecord* searchMedicalRecordById(int medicalRecordId);
void modifyMedicalRecord(MedicalRecord* medicalRecord);
void printAllMedicalRecords();		//链表操作

int registerPatient(int patientId, int doctorId);//挂号
int consultPatient(int registrationId, const char* diagnosis);//看诊
int addExamination(int patientId, int doctorId, const char* examItem);//检查
int admitPatient(int patientId, int wardId);//住院

void saveMedicalRecordsToFile(const char* filename);
void loadMedicalRecordsFromFile(const char* filename);

#endif