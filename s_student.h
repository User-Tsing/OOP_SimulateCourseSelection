#pragma once
#include <iostream>
#include "course.h"
#pragma warning( disable : 4996)
using namespace std;
#define N 81
// ѧ����
class s_student {
protected:
    string id; // ѧ��
    string name; // ����
    int num; // ѡ������
    int num1, num2, num3;
    int credit1, credit2, credit3;
    int credit; // ѡ����ѧ��
    course courses[5]; // ��ѡ�γ�
    double fee;//ѧ��
public:
    // ���캯��
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
    // ����ѧ�ѣ��麯����������ʵ��

    // ��ʾѡ����Ϣ���麯����������ʵ��
    virtual void showInfo() = 0;
    // ѡ��һ�ſγ̣�����ѡ��������ѡ����ѧ�ֺ���ѡ�γ�
    void selectcourse(course c) {

        credit += c.getCredit();
        courses[num] = c;
        num++;
        c.addNum();
        if (c.getType() == "ѧ�ƻ���") { num1++; credit1 += c.getCredit(); }
        else if (c.getType() == "רҵ����") {
            num2++;credit2 += c.getCredit();
        }
        else if (c.getType() == "רҵ����") {
            num3++;credit3 += c.getCredit();
        }

    }
};