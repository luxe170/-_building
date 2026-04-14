#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient.h"
#include "ward.h"

//log
void testPatient() {
    initPatientList();
    // 手动创建几个患者测试
    Patient* p1 = (Patient*)malloc(sizeof(Patient));
    p1->patientId = 1; strcpy(p1->name, "张三"); strcpy(p1->gender, "男"); p1->age = 30; strcpy(p1->phone, "13800000000");
    addPatient(p1);
    // 继续添加...
    printAllPatients();
    // 测试查找、修改、删除
    Patient* found = searchPatientById(1);
    if (found) printf("找到患者：%s\n", found->name);
    deletePatientById(1);
    printAllPatients();
}

void testWard() {
    initWardList();
    Ward* w1 = (Ward*)malloc(sizeof(Ward));
    w1->wardId = 101; strcpy(w1->typeOfWard, "普通"); w1->totalBedOfWard = 4; w1->availableBedOfWard = 0;
    addWard(w1);
    printAllWards();
    // 测试其他操作...
}

int main() {
    int choice;
    while (1) {
        printf("\n1. 测试患者模块\n2. 测试病房模块\n0. 退出\n");
        scanf("%d", &choice);
        switch (choice) {
        case 1: testPatient(); break;
        case 2: testWard(); break;
        case 0: exit(0);
        default: printf("无效输入\n");
        }
    }
    return 0;
}