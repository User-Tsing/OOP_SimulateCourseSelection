#include "pch.h"
#include "Func.h"
#include "afxdialogex.h"

/* ��¼�߼�����ʵ�� */

//��������ṹ��ӱ����ļ���ȡ�ͱ���ѧ����Ϣ���γ���Ϣ��ѡ�����
//����ṹ��ĳ�Ա�����ͺ����������Func.h

// ��ȡ�����û����ݵ�����
UserLinkList* readUserInfo() 
{
	// �򿪱����û��ļ�
	FILE* fp = NULL;
	fopen_s(&fp, "res/data/user.txt", "r");

	if (fp == NULL) return NULL;

	// �����û�������
	struct UserLinkList* link = (struct UserLinkList*)malloc(sizeof(struct UserLinkList));
	if (link == NULL) { fclose(fp);return NULL; }
	link->next = NULL;

	// �����û����ݱ���
	int ID = 0;
	char Name[9] = { "\0" }, Account[10] = { "\0" }, Password[19] = { "\0" };

	while (fscanf_s(fp, "%d %s %s %s", &ID, Name,9, Account, 10, Password, 19) != EOF) {//����ѭ����ֹ�����Ƕ�ȡ�ļ����ݵ���

		// ��̬�����½��
		struct UserLinkList* node = (struct UserLinkList*)malloc(sizeof(struct UserLinkList));
		if (node != NULL) {//����ṹ�帳ֵ
			node->data.ID = ID;
			strcpy_s(node->data.Name, Name);
			strcpy_s(node->data.Account, Account);
			strcpy_s(node->data.Password, Password);
			//�е���һ��������
			node->next = link->next;
			link->next = node;
		}
	}

	fclose(fp);//�ر��ļ�
	return link;//����ѧ������ͷ
}

// �ͷ��û������ڴ�
void freeUserLinkList(UserLinkList* link)
{
	UserLinkList* p;
	while (link) {
		p = link->next;
		free(link);
		link = p;
	}
}

/* �γ��߼�����ʵ�� */

// ��ȡ���ؿγ����ݵ�����
CourseLinkList* readCourseInfo() 
{
	// �򿪱����û��ļ�
	FILE* fp = NULL;
	fopen_s(&fp, "res/data/course.txt", "a+");

	if (fp == NULL) return NULL;

	// �����γ�˫����
	struct CourseLinkList* link = (struct CourseLinkList*)malloc(sizeof(struct CourseLinkList));
	if (link == NULL) { fclose(fp); return NULL; }
	link->prev = NULL;
	link->next = NULL;

	// ����γ����ݱ���
	int Num = 0, Credit = 0, Max = 0,All[1] = {0};
	char Type[37] = { "\0" },Name[37] = { "\0" };
	while (fscanf_s(fp, "%d %s %s %d %d %d", &Num, Type,37, Name,37, &Credit, &Max, &All[0]) != EOF) {//����ѭ����ֹ�����Ƕ�ȡ�ļ����ݵ���

		// ��̬�����½��
		struct CourseLinkList* node = (struct CourseLinkList*)malloc(sizeof(struct CourseLinkList));
		if (node != NULL) {//����ֵ
			node->data.Num = Num;
			strcpy_s(node->data.Type, Type);
			strcpy_s(node->data.Name, Name);
			node->data.Credit = Credit;
			node->data.Max = Max;
			memcpy_s(node->data.All, sizeof(int) * 1, All, sizeof(int) * 1);

			if (link->prev == NULL) {
				link->prev = link->next = node;
				node->prev = node->next = NULL;
				continue;
			}
			//�е���һ��������
			link->next->prev = node;
			node->next = link->next;
			link->next = node;
			node->prev = NULL;
		}
	}


	fclose(fp);//�ر��ļ�
	return link;//����ѡ�������㣬˫��������next���ǿ�ͷ����prev���ǽ�β����
}

// ��ӡ�γ���������
int printCourseLinkList(CourseLinkList* link)
{
	// �򿪱��ؿγ��ļ�
	FILE* fp = NULL;
	fopen_s(&fp, "res/data/course.txt", "w");

	if (fp == NULL) {
		freeCourseLinkList(link);
		return 0;
	}

	CourseLinkList* p = link->prev;
	while (p) {
		fprintf_s(fp, "%d %s %s %d %d %d \n", p->data.Num, p->data.Type, p->data.Name, p->data.Credit, p->data.Max, p->data.All[0]);
		//��ѡ�γ�����������ļ�
		p = p->prev;
	}

	fclose(fp);

	freeCourseLinkList(link);

	return 1;
}

// �ͷſγ��б������ڴ�
void freeCourseLinkList(CourseLinkList* link)
{
	CourseLinkList* p;
	while (link) {
		p = link->next;
		free(link);
		link = p;
	}
}


/* ��ѡ�߼�����ʵ�� */

// ��ȡ������ѡ���ݵ�����
SelectionLinkList* readSelectionInfo()
{
	// �򿪱����û��ļ�
	FILE* fp = NULL;
	fopen_s(&fp, "res/data/selection.txt", "a+");

	if (fp == NULL) return NULL;

	// �����γ�˫����
	struct SelectionLinkList* link = (struct SelectionLinkList*)malloc(sizeof(struct SelectionLinkList));
	if (link == NULL) { fclose(fp); return NULL; }
	link->prev = NULL;
	link->next = NULL;

	// ����γ����ݱ���
	char Name[37] = { "\0" }, Account[10] = { "\0" };//����γ�����ѧ����

	while (fscanf_s(fp, "%s %s", Name, 37, Account, 10) != EOF) {//����ѭ����ֹ�����Ƕ�ȡ�ļ����ݵ���

		// ��̬�����½��
		struct SelectionLinkList* node = (struct SelectionLinkList*)malloc(sizeof(struct SelectionLinkList));
		if (node != NULL) {//����ֵ
			strcpy_s(node->data.Name, Name);
			strcpy_s(node->data.Account, Account);

			if (link->prev == NULL) {
				link->prev = link->next = node;
				node->prev = node->next = NULL;
				continue;
			}
			//�е���һ��������
			link->next->prev = node;
			node->next = link->next;
			link->next = node;
			node->prev = NULL;
		}
	}

	fclose(fp);//�ر��ļ�
	return link;//����ѡ�������㣬˫��������next���ǿ�ͷ����prev���ǽ�β����
}

// ��ӡ��ѡ��������
int printSelectionLinkList(SelectionLinkList* link)
{
	// �򿪱��ؿγ��ļ�
	FILE* fp = NULL;
	fopen_s(&fp, "res/data/selection.txt", "w");

	if (fp == NULL) {
		freeSelectionLinkList(link);
		return 0;
	}

	SelectionLinkList* p = link->prev;
	while (p) {
		fprintf_s(fp, "%s %s\n", p->data.Name, p->data.Account);
		//��ѡ��������뵽�����ļ������Ա���ѡ��������´������Ǵӱ����ļ���ȡ���ݣ������ļ���Ҫ����ֶ��������
		p = p->prev;
	}

	fclose(fp);//�ر��ļ�

	freeSelectionLinkList(link);

	return 1;
}

// �ͷ���ѡ�б������ڴ�
void freeSelectionLinkList(SelectionLinkList* link)
{
	SelectionLinkList* p;
	while (link) {
		p = link->next;
		free(link);
		link = p;
	}
}

/* ����С���� */

// ���ֽ�ת���ֽ�
char* WcharToChar(const wchar_t* wp)

{

	char* m_char;

	int len = WideCharToMultiByte(CP_ACP, 0, wp, wcslen(wp), NULL, 0, NULL, NULL);

	m_char = new char[len + 1];

	WideCharToMultiByte(CP_ACP, 0, wp, wcslen(wp), m_char, len, NULL, NULL);

	m_char[len] = '\0';

	return m_char;

}

// ͳ�ƿγ�ѡ�����
int countSelectionNumber() 
{
	CourseLinkList* course = readCourseInfo();
	if (course == NULL) return 0;

	SelectionLinkList* selection = readSelectionInfo();
	if (selection == NULL) return 0;

	SelectionLinkList* ps;
	CourseLinkList* pc = course->next;



	freeSelectionLinkList(selection);
	return printCourseLinkList(course);
}

// �����ѡԭ��ѡ����
//�ô�����ԭ��������ϵͳ��ʹ��
void clearMaxSelection(CString name,int theClass) {
	SelectionLinkList* selection = readSelectionInfo();
	SelectionLinkList* p = selection->next;
	SelectionLinkList* q;

	while (p) {
		if (name.Compare(CString(p->data.Name)) == 0 && _ttoi((CString(p->data.Account).Right(3)).Left(1)) == theClass) {

			if (p->prev) p->prev->next = p->next;
			if (p->next) p->next->prev = p->prev;
			if (selection->next == p) selection->next = p->next;
			if (selection->prev == p) selection->prev = p->prev;

			q = p->next;
			free(p);
			p = q;

			continue;
		}

		p = p->next;
	}
	
	printSelectionLinkList(selection);
}