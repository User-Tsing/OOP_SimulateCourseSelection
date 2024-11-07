#include "pch.h"
#include "Func.h"
#include "afxdialogex.h"

/* 登录逻辑函数实现 */

//设置链表结构体从本地文件读取和保存学生信息、课程信息和选课情况
//链表结构体的成员变量和函数声明详见Func.h

// 读取本地用户数据到链表
UserLinkList* readUserInfo() 
{
	// 打开本地用户文件
	FILE* fp = NULL;
	fopen_s(&fp, "res/data/user.txt", "r");

	if (fp == NULL) return NULL;

	// 创建用户单链表
	struct UserLinkList* link = (struct UserLinkList*)malloc(sizeof(struct UserLinkList));
	if (link == NULL) { fclose(fp);return NULL; }
	link->next = NULL;

	// 定义用户数据变量
	int ID = 0;
	char Name[9] = { "\0" }, Account[10] = { "\0" }, Password[19] = { "\0" };

	while (fscanf_s(fp, "%d %s %s %s", &ID, Name,9, Account, 10, Password, 19) != EOF) {//设置循环截止条件是读取文件内容到底

		// 动态申请新结点
		struct UserLinkList* node = (struct UserLinkList*)malloc(sizeof(struct UserLinkList));
		if (node != NULL) {//链表结构体赋值
			node->data.ID = ID;
			strcpy_s(node->data.Name, Name);
			strcpy_s(node->data.Account, Account);
			strcpy_s(node->data.Password, Password);
			//切到下一个链表结点
			node->next = link->next;
			link->next = node;
		}
	}

	fclose(fp);//关闭文件
	return link;//返回学生链表开头
}

// 释放用户链表内存
void freeUserLinkList(UserLinkList* link)
{
	UserLinkList* p;
	while (link) {
		p = link->next;
		free(link);
		link = p;
	}
}

/* 课程逻辑函数实现 */

// 读取本地课程数据到链表
CourseLinkList* readCourseInfo() 
{
	// 打开本地用户文件
	FILE* fp = NULL;
	fopen_s(&fp, "res/data/course.txt", "a+");

	if (fp == NULL) return NULL;

	// 创建课程双链表
	struct CourseLinkList* link = (struct CourseLinkList*)malloc(sizeof(struct CourseLinkList));
	if (link == NULL) { fclose(fp); return NULL; }
	link->prev = NULL;
	link->next = NULL;

	// 定义课程数据变量
	int Num = 0, Credit = 0, Max = 0,All[1] = {0};
	char Type[37] = { "\0" },Name[37] = { "\0" };
	while (fscanf_s(fp, "%d %s %s %d %d %d", &Num, Type,37, Name,37, &Credit, &Max, &All[0]) != EOF) {//设置循环截止条件是读取文件内容到底

		// 动态申请新结点
		struct CourseLinkList* node = (struct CourseLinkList*)malloc(sizeof(struct CourseLinkList));
		if (node != NULL) {//链表赋值
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
			//切到下一个链表结点
			link->next->prev = node;
			node->next = link->next;
			link->next = node;
			node->prev = NULL;
		}
	}


	fclose(fp);//关闭文件
	return link;//返回选课链表结点，双链表，后续next就是开头正序，prev就是结尾倒序
}

// 打印课程链表到本地
int printCourseLinkList(CourseLinkList* link)
{
	// 打开本地课程文件
	FILE* fp = NULL;
	fopen_s(&fp, "res/data/course.txt", "w");

	if (fp == NULL) {
		freeCourseLinkList(link);
		return 0;
	}

	CourseLinkList* p = link->prev;
	while (p) {
		fprintf_s(fp, "%d %s %s %d %d %d \n", p->data.Num, p->data.Type, p->data.Name, p->data.Credit, p->data.Max, p->data.All[0]);
		//所选课程内容输入回文件
		p = p->prev;
	}

	fclose(fp);

	freeCourseLinkList(link);

	return 1;
}

// 释放课程列表链表内存
void freeCourseLinkList(CourseLinkList* link)
{
	CourseLinkList* p;
	while (link) {
		p = link->next;
		free(link);
		link = p;
	}
}


/* 已选逻辑函数实现 */

// 读取本地已选数据到链表
SelectionLinkList* readSelectionInfo()
{
	// 打开本地用户文件
	FILE* fp = NULL;
	fopen_s(&fp, "res/data/selection.txt", "a+");

	if (fp == NULL) return NULL;

	// 创建课程双链表
	struct SelectionLinkList* link = (struct SelectionLinkList*)malloc(sizeof(struct SelectionLinkList));
	if (link == NULL) { fclose(fp); return NULL; }
	link->prev = NULL;
	link->next = NULL;

	// 定义课程数据变量
	char Name[37] = { "\0" }, Account[10] = { "\0" };//定义课程名和学生名

	while (fscanf_s(fp, "%s %s", Name, 37, Account, 10) != EOF) {//设置循环截止条件是读取文件内容到底

		// 动态申请新结点
		struct SelectionLinkList* node = (struct SelectionLinkList*)malloc(sizeof(struct SelectionLinkList));
		if (node != NULL) {//链表赋值
			strcpy_s(node->data.Name, Name);
			strcpy_s(node->data.Account, Account);

			if (link->prev == NULL) {
				link->prev = link->next = node;
				node->prev = node->next = NULL;
				continue;
			}
			//切到下一个链表结点
			link->next->prev = node;
			node->next = link->next;
			link->next = node;
			node->prev = NULL;
		}
	}

	fclose(fp);//关闭文件
	return link;//返回选课链表结点，双链表，后续next就是开头正序，prev就是结尾倒序
}

// 打印已选链表到本地
int printSelectionLinkList(SelectionLinkList* link)
{
	// 打开本地课程文件
	FILE* fp = NULL;
	fopen_s(&fp, "res/data/selection.txt", "w");

	if (fp == NULL) {
		freeSelectionLinkList(link);
		return 0;
	}

	SelectionLinkList* p = link->prev;
	while (p) {
		fprintf_s(fp, "%s %s\n", p->data.Name, p->data.Account);
		//将选课情况输入到本地文件，用以保存选课情况，下次运行是从本地文件调取数据，本地文件不要随便手动进入更改
		p = p->prev;
	}

	fclose(fp);//关闭文件

	freeSelectionLinkList(link);

	return 1;
}

// 释放已选列表链表内存
void freeSelectionLinkList(SelectionLinkList* link)
{
	SelectionLinkList* p;
	while (link) {
		p = link->next;
		free(link);
		link = p;
	}
}

/* 其他小工具 */

// 宽字节转多字节
char* WcharToChar(const wchar_t* wp)

{

	char* m_char;

	int len = WideCharToMultiByte(CP_ACP, 0, wp, wcslen(wp), NULL, 0, NULL, NULL);

	m_char = new char[len + 1];

	WideCharToMultiByte(CP_ACP, 0, wp, wcslen(wp), m_char, len, NULL, NULL);

	m_char[len] = '\0';

	return m_char;

}

// 统计课程选课情况
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

// 清空限选原已选数据
//用处不大，原定“教务系统”使用
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