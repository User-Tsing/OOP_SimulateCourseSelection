#pragma once
#include <iostream>
#include "course.h"
#pragma warning( disable : 4996)
using namespace std;
#define N 81
// 学生类
class s_student {
protected:
    string id; // 学号
    string name; // 姓名
    int num; // 选课门数
    int num1, num2, num3;
    int credit1, credit2, credit3;
    int credit; // 选课总学分
    course courses[5]; // 所选课程
    double fee;//学费
public:
    // 构造函数
    s_student() {
        num = 0;
        credit = 0;
    };
    s_student(string i, string n) {
        id = i;
        name = n;
        num = 0;
        num1 = 0;num2 = 0;num3 = 0;
        credit1 = 0;credit2 = 0;credit3 = 0;
        credit = 0;
    }
    string getid() {
        return id;
    }
    string getName() {
        return name;
    }
    // 计算学费，虚函数，由子类实现

    // 显示选课信息，虚函数，由子类实现
    virtual void showInfo() = 0;
    // 选择一门课程，更新选课门数、选课总学分和所选课程
    void selectcourse(course c) {

        credit += c.getCredit();
        courses[num] = c;
        num++;
        c.addNum();
        if (c.getType() == "学科基础") { num1++; credit1 += c.getCredit(); }
        else if (c.getType() == "专业基础") {
            num2++;credit2 += c.getCredit();
        }
        else if (c.getType() == "专业核心") {
            num3++;credit3 += c.getCredit();
        }

    }
};