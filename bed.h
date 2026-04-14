#pragma once
#ifndef BED_H
#define BED_H

typedef struct Bed {
	int bedId;
	int relatedWardId; //床位关联病房ID
	int status; //床位状态：0-空闲，1-占用
	int relatedPatientId; //床位关联患者ID，空闲床位为-1
	struct Bed* next;
} Bed;

extern Bed* bedListHead; // 床位链表头指针

void initBedList();
void addBed(Bed* bedListHead);
int deleteBedById(int bedId); //返回类型int是为了确认删除状态
Bed* searchBedById(int bedId);
void modifyBed(Bed* bed);
void printAllBeds();
Bed* searchFreeBedByWardId(int wardId);
int allocateBed(int bedId, int patientId);//L:给患者分配床位
int releaseBed(int bedId);

void saveBedsToFile(const char* filename);
void loadBedsFromFile(const char* filename);


#endif
