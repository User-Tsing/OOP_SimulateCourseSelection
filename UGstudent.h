#pragma once
#include "s_student.h"
#include <iostream>
#include "course.h"
#include <string>
#pragma warning( disable : 4996)
using namespace std;
#define N 81
// �������࣬�̳���ѧ����
class UGstudent : public s_student {
private:
    string id;
    string name;
    string tutor;// �ർʦ����
    int num1, num2, num3;
public:
    // ���캯�������ø��๹�캯��������ʼ���ർʦ����
    UGstudent() {};
    UGstudent(string i, string n, string t) : s_student(i, n) {
        id = i;name = n;tutor = t;
    }
    void set_stu_inf(string i, string n, string t) {
        id = i; name = n; tutor = t;
    }
    // ����ѧ�ѣ���д�����麯��
    int calcFee() {
        return 200 * credit1 + 150 * credit2 + 100 * credit3 + 360;
    }
    // ��ʾѡ����Ϣ����д�����麯�������ѧ�š��������ർʦ������ѡ��������ѡ����ѧ�֡���ѡ�γ̺�ѧ�ѵ���Ϣ
    void showInfo() {
        cout << "ѧ��: " << id << endl;
        cout << "����: " << name << endl;
        cout << "�ർʦ����: " << tutor << endl;
        cout << "ѡ������: " << num << endl;
        cout << "ѡ����ѧ��: " << credit << endl;
        cout << "��ѡ�γ�: " << endl;
        for (int i = 0;i < 5;i++) {
            cout << courses[i].getType() << " " << courses[i].getName() << " " << courses[i].getCredit() << endl;
        }
        cout << "ѧ��: " << calcFee() << endl;
    }
    string Getid() {
        return id;
    }
};
