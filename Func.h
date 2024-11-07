/* �û�������ṹ�� */

// �û�����
struct UserInfo
{
	int ID; // ����������0Ϊ�������Ա
	char Name[9]; // ѧ������
	char Account[10]; // ѧ��ѧ��
	char Password[19]; // ��Ӧ���룬��ʼ��Ϊ123456
	int sel_num=0;//ѡ����
	int tuition=0;//ѧ��
	int u_gu = 0;//���������о���
};

// �û�������
struct UserLinkList
{
	struct UserInfo data; // �û�����
	struct UserLinkList* next; // ��һ���ڵ�
};

/* �û���¼�߼�ʵ�� */

extern UserLinkList* readUserInfo();
extern void freeUserLinkList(UserLinkList* link);

/* �γ�˫����ṹ�� */

// �γ�����
struct CourseInfo
{
	int Num; // �γ̱��
	char Type[10]; // �γ�����
	char Name[37]; // �γ�����
	int Credit; // �γ�ѧ��
	int Max=15; // �γ��������
	int All[1]; // �γ̸��׶�����
};


// �γ�������
// ���� CourseLinkList �ṹ��
struct CourseLinkList
{
	struct CourseInfo data; // ����ָ��
	struct CourseLinkList* prev; // ��һ�����ָ��
	struct CourseLinkList* next; // ��һ�����ָ��

};



extern CourseLinkList* readCourseInfo(); // ��ȡ�γ��ļ����ݵ�����
extern int printCourseLinkList(CourseLinkList* link); // ��ӡ�γ������ļ�
extern void freeCourseLinkList(CourseLinkList* link); // �ͷſγ������ڴ�

/* ѡ��˫����ṹ�� */

// ѡ������
struct SelectionInfo {
	char Name[37]; // �γ�����
	char Account[10]; // ѧ��ѧ��
	
};

// ѡ��������
struct SelectionLinkList
{
	struct SelectionInfo data; // ����ָ��
	struct SelectionLinkList* prev; // ��һ�����ָ��
	struct SelectionLinkList* next; // ��һ�����ָ��
};

extern SelectionLinkList* readSelectionInfo(); // ��ȡѡ���ļ����ݵ�����
extern int printSelectionLinkList(SelectionLinkList* link); // ��ӡѡ�������ļ�
extern void freeSelectionLinkList(SelectionLinkList* link); // �ͷſγ������ڴ�

/* ����С���� */
extern int countSelectionNumber(); // ͳ��ѡ���������γ������ļ�
extern char* WcharToChar(const wchar_t* wp); // ���ֽ�ת���ֽڣ���������ַ���
extern void clearMaxSelection(CString name,int theClass); // �����ѡ�γ̴��ڵ���ѡ����