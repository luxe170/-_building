#define _CRT_SECURE_NO_WARNINGS
#include "medical_record.h"
#include "util.h"
#include "ward.h"
#include "patient.h"
#include "doctor.h"
#include "medicine.h"
#include "bed.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int medicalRecordIdCounter = -1; // 挂号记录ID计数器，初始值为-1 

MedicalRecord* medicalRecordListHead = NULL;

void initMedicalRecordList() {
	medicalRecordListHead = NULL;
}//初始化记录头指针为NULL

void addMedicalRecord(MedicalRecord* p) {					//尾插法添加记录
	if (p == NULL) return;
	p->next = NULL;
	if (medicalRecordListHead == NULL)
	{
		medicalRecordListHead = p;
	}
	else
	{
		MedicalRecord* current = medicalRecordListHead;
		while (current->next != NULL) current = current->next;
		current->next = p;
	}
}

int deleteMedicalRecordById(int medicalRecordId) {        //双指针法删除记录
	if (medicalRecordListHead == NULL) return -1;//记录列表为空，无法删除
	MedicalRecord* current = medicalRecordListHead;
	MedicalRecord* previous = NULL;
	while (current != NULL) {
		if (current->medicalRecordId == medicalRecordId) {
			if (previous == NULL) {     //特判删除首位置记录
				medicalRecordListHead = current->next;
			}
			else {
				previous->next = current->next;
			}
			free(current);
			return 1;	//成功删除记录
		}
		previous = current;
		current = current->next;
	}
	return 0;//未找到记录
}

MedicalRecord* searchMedicalRecordById(int medicalRecordId) {		//线性搜索记录
	if (medicalRecordListHead == NULL) return NULL;//记录列表为空，无法搜索
	MedicalRecord* current = medicalRecordListHead;
	while (current != NULL) {
		if (current->medicalRecordId == medicalRecordId) return current;//成功找到记录

		current = current->next;
	}
	return NULL;//未找到记录
}

void modifyMedicalRecord(MedicalRecord* medicalRecord) {			//修改记录信息
	if (medicalRecordListHead == NULL) return;//记录列表为空，无法修改
	MedicalRecord* target = searchMedicalRecordById(medicalRecord->medicalRecordId);
	if (target == NULL) return;//未找到记录，无法修改
	target->medicalRecordId = medicalRecord->medicalRecordId;
    strcpy(target->typeOfMedicalRecord, medicalRecord->typeOfMedicalRecord);
	target->patientId = medicalRecord->patientId;
	target->relatedDoctorId = medicalRecord->relatedDoctorId;
	strcpy(target->time, medicalRecord->time);
	strcpy(target->detail, medicalRecord->detail);
	target->status = medicalRecord->status;
}

void printAllMedicalRecords() {		//
  if (medicalRecordListHead == NULL) return; //记录为空，无效访问
	MedicalRecord* current = medicalRecordListHead;
	while (current != NULL) {
		// 打印医疗记录的主要字段
		printf("%d\n%d\n%d\n%s\n%s\n%s\n%d\n",
			current->medicalRecordId,
			current->patientId,
			current->relatedDoctorId,
			current->typeOfMedicalRecord,
			current->time,
			current->detail,
			current->status);
		current = current->next;
	}
}

static void updateNextIdFromList() {  //更新记录ID (封装
    // 将计数器设置为当前链表中最大的ID值（若无记录则为-1）
	medicalRecordIdCounter = -1;
	MedicalRecord* current = medicalRecordListHead;
	while (current != NULL) {
		if (current->medicalRecordId > medicalRecordIdCounter) {
			medicalRecordIdCounter = current->medicalRecordId;
		}
		current = current->next;
	}
}

static int generateMedicalRecordId() { //生成新的记录ID (封装
    return ++medicalRecordIdCounter;
}

static MedicalRecord* createEmptyMedicalRecord() {
	MedicalRecord* newRecord = (MedicalRecord*)malloc(sizeof(MedicalRecord));
	if (newRecord == NULL) return NULL; //内存分配失败，返回NULL
	memset(newRecord, 0, sizeof(MedicalRecord)); //初始化新记录的内存为0 将刚通过 malloc 分配的内存区域全部填充为 0,避免垃圾值
	newRecord ->medicalRecordId = generateMedicalRecordId(); //为新记录生成唯一ID
	return newRecord;
}

void medicalRecordPostLoad() { //加载记录后更新ID计数器 公共接口
	updateNextIdFromList();
}
	
static int hasPendingRegistration(int patientId) {
    MedicalRecord* current = medicalRecordListHead;
	while (current != NULL) {
		if (current->patientId == patientId && current->status == 0)
			return 1; //病人有挂号待诊记录
		current = current->next;
	}
	return 0;//无挂号待诊记录
}

int registerPatient(int patientId, int doctorId) {//挂号
	//1.检查病人ID是否存在
	//2.检查病人是否已挂号待诊，若是则返回-2表示病人已挂号待诊，无法重复挂号
	//3.检查医生ID是否存在
	//4.创建新的挂号记录,初始化status=0-已挂号待诊 和 typeOfMedicalRecord="已挂号待诊"
	//5.获取时间戳转换进time
	//6,detail先不写?或者挂号成功
	//7.添加至链表
	//8.返回挂号记录ID
	if (searchPatientById(patientId) == NULL) return -1;//病人ID不存在
	if (hasPendingRegistration(patientId)) return -2;//病人已挂号待诊，无法重复挂号  //hasPendingRegistration函数没写呢
	if (searchDoctorById(doctorId) == NULL) return -3;	//医生ID不存在
	MedicalRecord* record = createEmptyMedicalRecord();
	if (record == NULL) return -4; //内存分配失败
	record->patientId = patientId;
	record->relatedDoctorId = doctorId;
	strcpy(record->typeOfMedicalRecord, "已挂号待诊");
	record->status = 0;
	getCurrentTime(record->time, MEDICAL_RECORD_TIME); //获取当前时间戳并转换为字符串存储在record->time中
	addMedicalRecord(record); //将新记录添加到链表中
	return record->medicalRecordId; //返回挂号记录ID
}

int consultPatient(int registrationId, const char* diagnosis) {  //看诊
	//1.检查挂号记录ID是否存在  ERR:-1
	//2.检查记录status?=0是否为已挂号待诊  ERR:-2
	//3.新建医疗记录 status=1 detail=diagnosis typeOfMedicalRecord="已就诊" 内存不足 ERR:-3
	//4.添加至链表
	MedicalRecord* registerRec = searchMedicalRecordById(registrationId);
	if (registerRec == NULL) return -1;// Err:-1 挂号记录ID不存在
	if (registerRec->status != 0) return -2;// Err:-2 记录status不为已挂号待诊
	registerRec->status = 1; //更新挂号记录状态为已就诊
	MedicalRecord* consultRec = createEmptyMedicalRecord();
	if (consultRec == NULL) return -3;// Err:-3 内存不足,无法创建新的医疗记录
	consultRec->patientId = registerRec->patientId;
	consultRec->relatedDoctorId = registerRec->relatedDoctorId;
	strcpy(consultRec->typeOfMedicalRecord, "看诊");
	getCurrentTime(consultRec->time, MEDICAL_RECORD_TIME);
	strncpy(consultRec->detail,diagnosis,sizeof(consultRec->detail) - 1);
	consultRec->detail[sizeof(consultRec->detail) - 1] = '\0';
	consultRec->status = 0; //看诊记录无所谓
	addMedicalRecord(consultRec);
	return consultRec->medicalRecordId;
}

int addExamination(int patientId, int doctorId, const char* examItem) { //检查
	//1.检查病人ID是否存在  ERR:-1
	//2.检查医生ID是否存在  ERR:-2
	//3.新建医疗记录 status=0 detail=examItem typeOfMedicalRecord="检查" 内存不足 ERR:-3
	//4.添加到链表
	if (searchPatientById(patientId) == NULL) return -1;// Err:-1 病人ID不存在
	if (searchDoctorById(doctorId) == NULL) return -2;	//医生ID不存在
	MedicalRecord* examRec = createEmptyMedicalRecord();
	if (examRec == NULL) return -3;// Err:-3 内存不足,无法创建新的医疗记录
	examRec->status = 0;
	examRec->patientId = patientId;
	examRec->relatedDoctorId = doctorId;
	strcpy(examRec->typeOfMedicalRecord, "检查");
	getCurrentTime(examRec->time, MEDICAL_RECORD_TIME);
	strcpy(examRec->detail, examItem);
	addMedicalRecord(examRec);
	return examRec->medicalRecordId;
}

static int isPatientHospitalized(int patientId) { //检查病人是否已经住院 (封装
	MedicalRecord* current = medicalRecordListHead;
	while (current != NULL) {
		if (current->patientId==patientId && current->status == 2) 
			return 1; //已住院 返回1
		current = current->next;
	}
	return 0; //未住院 返回0
}

int admitPatient(int patientId, int wardId) {  //住院
	Ward* ward = searchWardById(wardId);
	Patient* patient = searchPatientById(patientId);
	if (patient == NULL) return -1;// Err:-1 病人ID不存在
	if (ward == NULL) return -2; // Err:-2 病房ID不存在
	if(isPatientHospitalized(patientId)) return -3; // Err:-3 病人已住院
	if (ward->availableBedOfWard >= ward->totalBedOfWard) return -4; //Err:-4 床位已满
	Bed* bed = searchFreeBedByWardId(wardId);
	if (bed == NULL) return -5; // Err:-5 未找到空闲床位
	if (allocateBed(bed->bedId, patientId) < 0) return -6; //Err:-6 分配床位失败
	ward->availableBedOfWard--; //更新病房可用床位数
	//创建医疗记录
	MedicalRecord* admitRec = createEmptyMedicalRecord();
	if (admitRec == NULL) {
		releaseBed(bed->bedId);
		ward->availableBedOfWard++;
		return -7;//Err:-7 内存不足，无法创建新的医疗记录
	}
	getCurrentTime(admitRec->time, MEDICAL_RECORD_TIME);
	admitRec->patientId = patientId;
	admitRec->status = 2; //已住院
	admitRec->relatedDoctorId = -1; //住院记录不用医生
	strcpy(admitRec->typeOfMedicalRecord, "住院");
	snprintf(admitRec->detail, sizeof(admitRec->detail), "病房ID:%d,床位ID:%d", wardId, bed->bedId);
	addMedicalRecord(admitRec);
	return admitRec->medicalRecordId;
}
void saveMedicalRecordsToFile(const char* filename) {
	FILE* file = fopen(filename, "w");
	if (!file) return;
	MedicalRecord* current = medicalRecordListHead;
	while (current) {
		fprintf(file, "%d %d %d %s %s %s %d\n",
			current->medicalRecordId, current->patientId, current->relatedDoctorId,
			current->typeOfMedicalRecord, current->time, current->detail, current->status);
		current = current->next;
	}
	fclose(file);
}

void loadMedicalRecordsFromFile(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (!file) return;
	initMedicalRecordList();
	MedicalRecord* mr;
	while ((mr = (MedicalRecord*)malloc(sizeof(MedicalRecord)))) {
		if (fscanf(file, "%d %d %d %s %s %s %d",
			&mr->medicalRecordId, &mr->patientId, &mr->relatedDoctorId,
			mr->typeOfMedicalRecord, mr->time, mr->detail, &mr->status) != 7) {
			free(mr);
			break;
		}
		mr->next = NULL;
		addMedicalRecord(mr);
	}
	fclose(file);
}