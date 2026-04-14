#pragma once

#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#define DEPARTMENT_NAME_LEN 50
#define DEPARTMENT_CONTACTPHONE_LEN 20
typedef struct Department {
	int departmentId;
	char name[DEPARTMENT_NAME_LEN];
	int headDoctorId; //科室主任医生ID
	char contactPhone[DEPARTMENT_CONTACTPHONE_LEN];
	int numberOfDoctors; //科室医生数量
	struct Department* next;
} Department;

extern Department* departmentListHead; // 科室链表头指针

void initDepartmentList();
void addDepartment(Department* departmentListHead);
int deleteDepartmentById(int departmentId); //返回类型int是为了确认删除状态
Department* searchDepartmentById(int departmentId);
void modifyDepartment(Department* department);
void printAllDepartments();
void saveDepartmentsToFile(const char* filename);
void loadDepartmentsFromFile(const char* filename);

#endif

