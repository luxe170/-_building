#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bed.h"
#include "medical_record.h"

Bed *bedListHead = NULL;

void initBedList() {
    bedListHead = NULL;
}

void addBed(Bed* p) {
    if (p == NULL) return;
    p->next = NULL;
    if (bedListHead == NULL) {
        bedListHead = p;
    } else {
        Bed* current = bedListHead;
        while (current->next != NULL) current = current->next;
        current->next = p;
    }
}

int deleteBedById(int bedId) {
    if (bedListHead == NULL) return -1;
    Bed* current = bedListHead;
    Bed* previous = NULL;
    while (current != NULL) {
        if (current->bedId == bedId) {
            if (previous == NULL) {
                bedListHead = current->next;
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

Bed* searchBedById(int bedId) {
    if (bedListHead == NULL) return NULL;
    Bed* current = bedListHead;
    while (current != NULL) {
        if (current->bedId == bedId) return current;
        current = current->next;
    }
    return NULL;
}

void modifyBed(Bed* bed) {
    if (bedListHead == NULL) return;
    Bed* target = searchBedById(bed->bedId);
    if (target == NULL) return;
    target->bedId = bed->bedId;
    target->relatedWardId = bed->relatedWardId;
    target->status = bed->status;
    target->relatedPatientId = bed->relatedPatientId;
}

void printAllBeds() {
    if (bedListHead == NULL) return;
    Bed* current = bedListHead;
    while (current != NULL) {
        printf("%d\n%d\n%d\n%d\n",
            current->bedId, current->relatedWardId, current->status, current->relatedPatientId);
        current = current->next;
    }
}

Bed* searchFreeBedByWardId(int wardId){
	if (bedListHead == NULL) return NULL;//床位列表为空，无法搜索
    Bed* current = bedListHead;
    while (current != NULL) {
		if (current->relatedWardId == wardId && current->status == 0) 
            return current;
        current = current->next;
    }
	return NULL;//未找到空闲床位
}

int allocateBed(int bedId, int patientId) {
    Bed* bed = searchBedById(bedId);
    if (bed == NULL) return -1;//床位ID不存在
	if (bed->status != 0) return -2;//床位不空闲
	if (patientId < 0) return -3;//患者ID无效
    bed->relatedPatientId = patientId;
	bed->status = 1;
}

int releaseBed(int bedId) {          
	Bed* bed = searchBedById(bedId);
	if (bed == NULL) return -1;//床位ID不存在
	if (bed->status == 0) return -2;//床位未被占用

    bed->relatedPatientId = -1;
    bed->status = 0; 
}

void saveBedsToFile(const char* filename) {
	FILE* file = fopen(filename, "w");
	if (!file) return;
	Bed* current = bedListHead;
	while (current) {
		fprintf(file, "%d %d %d %d\n",
			current->bedId, current->relatedWardId, current->status, current->relatedPatientId);
		current = current->next;
	}
	fclose(file);
}

void loadBedsFromFile(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (!file) return;
	initBedList();
	Bed* b;
	while (1) {
		b = (Bed*)malloc(sizeof(Bed));
		if (fscanf(file, "%d %d %d %d",
			&b->bedId, &b->relatedWardId, &b->status,&b->relatedPatientId) != 4) {
			free(b);
			break;
		}
		b->next = NULL;
		addBed(b);
	}
	fclose(file);
}
