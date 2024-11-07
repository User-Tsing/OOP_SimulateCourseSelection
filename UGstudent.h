#pragma once
#include "s_student.h"
#include <iostream>
#include "course.h"
#include <string>
#pragma warning( disable : 4996)
using namespace std;
#define N 81
// 本科生类，继承自学生类
class UGstudent : public s_student {
private:
    string id;
    string name;
    string tutor;// 班导师姓名
    int num1, num2, num3;
public:
    // 构造函数，调用父类构造函数，并初始化班导师姓名
    UGstudent() {};
    UGstudent(string i, string n, string t) : s_student(i, n) {
        id = i;name = n;tutor = t;
    }
    void set_stu_inf(string i, string n, string t) {
        id = i; name = n; tutor = t;
    }
    // 计算学费，重写父类虚函数
    int calcFee() {
        return 200 * credit1 + 150 * credit2 + 100 * credit3 + 360;
    }
    // 显示选课信息，重写父类虚函数，输出学号、姓名、班导师姓名、选课门数、选课总学分、所选课程和学费等信息
    void showInfo() {
        cout << "学号: " << id << endl;
        cout << "姓名: " << name << endl;
        cout << "班导师姓名: " << tutor << endl;
        cout << "选课门数: " << num << endl;
        cout << "选课总学分: " << credit << endl;
        cout << "所选课程: " << endl;
        for (int i = 0;i < 5;i++) {
            cout << courses[i].getType() << " " << courses[i].getName() << " " << courses[i].getCredit() << endl;
        }
        cout << "学费: " << calcFee() << endl;
    }
    string Getid() {
        return id;
    }
};
