#pragma once
#include <iostream>
#include <vector>
#pragma warning( disable : 4996)
using namespace std;
#define N 81
// �γ���
class course {
private:
    string type; // �γ�����
    string name; // �γ�����
    int credit; // �γ�ѧ��
    int num; // ÿ�ſ�ѡ��������
    static int total; // ���пγ�ѡ��������
public:
    // ���캯��
    course() { num = 0; };
    course(string t, string n, int c) {
        type = t;
        name = n;
        credit = c;
        num = 0;
    }
    // ����ÿ�ſ�ѡ��������
    void addNum() {
        num++;
        total++;
    }
    // �������пγ�ѡ��������
    static int getTotal() {
        return total;
    }
    // ��ȡ�γ�����
    string getType() {
        return type;
    }

    // ��ȡ�γ�����
    string getName() {
        return name;
    }
    // ��ȡ�γ�ѧ��
    int getCredit() {
        return credit;
    }
};

