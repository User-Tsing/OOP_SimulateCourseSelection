#pragma once
#include <iostream>
#include <vector>
#pragma warning( disable : 4996)
using namespace std;
#define N 81
// 课程类
class course {
private:
    string type; // 课程类型
    string name; // 课程名称
    int credit; // 课程学分
    int num; // 每门课选课总人数
    static int total; // 所有课程选课总人数
public:
    // 构造函数
    course() { num = 0; };
    course(string t, string n, int c) {
        type = t;
        name = n;
        credit = c;
        num = 0;
    }
    // 计算每门课选课总人数
    void addNum() {
        num++;
        total++;
    }
    // 计算所有课程选课总人数
    static int getTotal() {
        return total;
    }
    // 获取课程类型
    string getType() {
        return type;
    }

    // 获取课程名称
    string getName() {
        return name;
    }
    // 获取课程学分
    int getCredit() {
        return credit;
    }
};

