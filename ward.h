#pragma once
#ifndef WARD_H
#define WARD_H

#define WARD_TYPE_LEN 20
#define WARD_NOTE_LEN 128

typedef struct Ward {
	int wardId;
	char typeOfWard[WARD_TYPE_LEN];
	int relatedDepartmentId; //病房关联科室ID
	int totalBedOfWard;
	int availableBedOfWard;
	char wardNote[128];		 //温馨提示
	struct Ward* next;
} Ward;

extern Ward* wardListHead; // 病房链表头指针

void initWardList();
void addWard(Ward* wardListHead);
int deleteWardById(int wardId); //返回类型int是为了确认删除状态
Ward* searchWardById(int wardId);
void modifyWard(Ward* ward);
void printAllWards();
void saveWardsToFile(const char* filename);
void loadWardsFromFile(const char* filename);

#endif
