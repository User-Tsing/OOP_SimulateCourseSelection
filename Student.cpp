// Student.cpp: 实现文件
//

#include "pch.h"
#include "CSS.h"
#include "Func.h"
#include "Login.h"
#include "Student.h"
#include "afxdialogex.h"

//用于实现选课的主要页面实现设置

// Student 对话框

IMPLEMENT_DYNAMIC(Student, CDialogEx)

Student::Student(CWnd* pParent /*=nullptr*/)//页面构造函数初始化赋值
	: CDialogEx(IDD_Student, pParent)
	, dlg_account(0)
	, ed_acc(0)
	, m_acc(0)
	, m_tui(0)
	, m_sum(0)
{
	Account = _T("");
	theClass = 0;
}

Student::~Student()//析构函数，无定义
{
}

void Student::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//控件变量声明
	DDX_Control(pDX, IDC_LIST_STUDENT_COURSE, m_course);
	DDX_Control(pDX, IDC_LIST_STUDENT_SELECTION, m_selection);
	DDX_Control(pDX, IDC_COMBO_STUDENT, m_choose);
	//值变量声明
	DDX_Text(pDX, IDC_EDIT3, m_acc);
	DDX_Text(pDX, IDC_EDIT4, m_tui);
	DDX_Text(pDX, IDC_EDIT1, m_sum);
}

//自动生成的内容
BEGIN_MESSAGE_MAP(Student, CDialogEx)
	ON_WM_CLOSE()

	ON_BN_CLICKED(IDC_ADMIN_CANCEL, &Student::OnBnClickedAdminCancel)
	
	ON_BN_CLICKED(IDC_STUDENT_SELECT, &Student::OnBnClickedStudentSelect)
	ON_CBN_EDITCHANGE(IDC_COMBO_STUDENT, &Student::OnCbnEditchangeComboStudent)

	ON_NOTIFY(NM_CLICK, IDC_LIST_STUDENT_COURSE, &Student::OnNMClickListStudentCourse)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_STUDENT_COURSE, &Student::OnNMRClickListStudentCourse)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_STUDENT_COURSE, &Student::OnNMDblclkListStudentCourse)
	ON_NOTIFY(NM_CLICK, IDC_LIST_STUDENT_SELECTION, &Student::OnNMClickListStudentSelection)

	ON_COMMAND(ID_32774, &Student::OnBnClickedStudentSelect)
	ON_COMMAND(ID_32775, &Student::OnBnClickedAdminCancel)

	ON_NOTIFY(NM_DBLCLK, IDC_LIST_STUDENT_SELECTION, &Student::OnNMDblclkListStudentSelection)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_STUDENT_COURSE, &Student::OnLvnItemchangedListStudentCourse)
	ON_BN_CLICKED(IDC_BUTTON1, &Student::OnBnClickedButton1)
END_MESSAGE_MAP()


// Student 消息处理程序


// Student对话框初始化
BOOL Student::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(title);

	// 课程列表初始化
	m_course.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);//设置课程列表的列及列的属性（宽度等）
	m_course.InsertColumn(0, L"课 程 名 称", LVCFMT_LEFT, 148);//第一列
	m_course.InsertColumn(1, L"课 程 类 型", LVCFMT_CENTER, 148);//第二列
	m_course.InsertColumn(2, L"序 号", LVCFMT_CENTER, 74);//第三列
	m_course.InsertColumn(3, L"学 分", LVCFMT_CENTER, 74);//第四列
	m_course.InsertColumn(4, L"限 选", LVCFMT_CENTER, 74);//第五列
	m_course.InsertColumn(5, L"已 选", LVCFMT_CENTER, 74);//第六列


	CourseLinkList* course = readCourseInfo();//读取课表（详见函数定义）
	RefreshCourseList(course);//刷新课表（详见函数定义）

	// 已选列表初始化
	m_selection.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);//同上
	m_selection.InsertColumn(0, L"课 程 名 称", LVCFMT_LEFT, 148);
	m_selection.InsertColumn(1, L"课 程 类 型", LVCFMT_CENTER, 148);
	m_selection.InsertColumn(2, L"序 号", LVCFMT_CENTER, 74);
	m_selection.InsertColumn(3, L"学 分", LVCFMT_CENTER, 74);
	m_selection.InsertColumn(4, L"限 选", LVCFMT_CENTER, 74);
	m_selection.InsertColumn(5, L"已 选", LVCFMT_CENTER, 74);

	SelectionLinkList* selection = readSelectionInfo();//获取选取列表（详见函数定义）
	RefreshSelectionList(selection);//刷新选取列表（详见函数定义）


	return TRUE;
}


// 刷新课程列表
int Student::RefreshCourseList(CourseLinkList* course)//刷新课程列表函数定义
{
	m_course.DeleteAllItems();

	if (course == NULL) {
		MessageBox(L"读取本地课程数据失败！");
		return 0;
	}

	int count = 0;//声明排数
	CString Max, All[5];//声明变量：最大可选人数和实际选课人数
	CourseLinkList* p = course->prev;//prev，指针指向课程链表结尾
	

	while (p != NULL) {
		// 判断是否限选
		if (p->data.All[theClass] != -1) {
			p->data.Max == 0 ? Max = L"无" : Max.Format(_T("%d"), p->data.Max);//数据类型强制转换为字符串
			All[0].Format(_T("%d"), p->data.All[0]);//数据类型强制转换为字符串
			CString c_count;c_count.Format(TEXT("%d"), p->data.Num);//数据类型强制转换为字符串
			CString c_Credit;c_Credit.Format(TEXT("%d"),p->data.Credit);//数据类型强制转换为字符串
			//输出一整排数据：count是排数，紧接着是列数，均从零开始，只能输出字符串CString类型
			m_course.InsertItem(count, CString(p->data.Name));
			m_course.SetItemText(count, 1, CString(p->data.Type));
			m_course.SetItemText(count,2,CString(c_count));
			m_course.SetItemText(count, 3, CString(c_Credit));
			m_course.SetItemText(count, 5, CString(All[0]));
			m_course.SetItemText(count, 4, CString(Max));

			count++;
		}

		p = p->prev;//链表结点前移以遍历链表
	}

	freeCourseLinkList(course);

	return 1;
}

// 刷新已选列表
int Student::RefreshSelectionList(SelectionLinkList* selection)
{
    m_selection.DeleteAllItems();

	if (selection == NULL) {
		MessageBox(L"读取本地已选课程数据失败！");
		return 0;
	}

	int error = 0;
	int count = 0;
	SelectionLinkList* p = selection->prev;//prev，读取的链表结尾

	CourseLinkList* pc;//课程链表，用于遍历找课
	CourseLinkList* course = readCourseInfo();//读取数据
	if (course == NULL) {
		MessageBox(L"读取本地课程数据失败！");
		return 0;
	}


	while (p != NULL) {
		// 找到学号已选课程
		// 遍历选课课表找到学生选的课，然后遍历课程名找到该课程的信息
		//遍历选课链表
		if (Account.Compare(CString(p->data.Account)) == 0) {//学号相同
			CString name = CString(p->data.Name);//获得所选课程的课名

			// 查找课程数据，插入到列表
			pc = course->next;//双链表，next获得所选链表的开头
			while (pc) {
				if (name.Compare(CString(pc->data.Name)) == 0) {
					//课程名相同，确认链表结点
					CString Max, All[5];
					pc->data.Max == 0 ? Max = L"无" : Max.Format(_T("%d"), pc->data.Max);
					All[0].Format(_T("%d"), pc->data.All[0]);
					CString c_count;c_count.Format(TEXT("%d"), pc->data.Num);
					CString c_Credit;c_Credit.Format(TEXT("%d"), pc->data.Credit);
					//输出整行（原理同上）
					m_selection.InsertItem(count, CString(pc->data.Name));
					m_selection.SetItemText(count, 1, CString(pc->data.Type));
					m_selection.SetItemText(count, 2, CString(c_count));
					m_selection.SetItemText(count, 3, CString(c_Credit));
					m_selection.SetItemText(count, 5, CString(All[0]));
					m_selection.SetItemText(count, 4, CString(Max));

					count++;//调试计数用

					break;
				}
				//遍历课程链表寻找对应课程名
				pc = pc->next;
			}

			// 有已选课程，但是没有找到课程数据
			if (pc == NULL) {

				if (p->prev) p->prev->next = p->next;
				if (p->next) p->next->prev = p->prev;
				if (selection->next == p) selection->next = p->next;
				if (selection->prev == p) selection->prev = p->prev;
				
				pc = (CourseLinkList*)p;
				p = ((SelectionLinkList*)pc)->prev;
				free(pc);

				error++;

				continue;
			}
		}
		//循环遍历
		p = p->prev;
	}

	freeCourseLinkList(course);
	error ? printSelectionLinkList(selection) : freeSelectionLinkList(selection);

	return 1;
}

// 关闭返回
void Student::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int ret = MessageBox(L"将返回登录界面，请问是否立即退出？", L"关闭提示", MB_YESNO);

	if (ret == IDYES)
	{
		CDialogEx::OnClose();
	}
	else
	{
		// 返回登录界面
		Login dlg;

		CDialog::OnOK();
		dlg.DoModal();
	}
}


// 选课按钮事件
void Student::OnBnClickedStudentSelect()
{

	CString name;
	m_choose.GetWindowText(name);//获得列表第一列的名称，即课程名，并赋给name

	if (name.GetLength() < 2 || name.GetLength() > 18)
	{
		MessageBox(L"请选中一条已选列表中的课程数据", L"提示", MB_ICONEXCLAMATION);
		return;
	}

	if (stu->data.sel_num >= 5)
	{
		MessageBox(L"每个学生最多只能选五门课");//没啥用，不是这里实现的
		return;
	}

	SelectionLinkList* selection = readSelectionInfo();
	if (selection == NULL) {
		MessageBox(L"读取本地已选课程数据失败！");
		return;
	}
	SelectionLinkList* ps = selection->next;//双链表，获得选课链表开头

	CourseLinkList* course = readCourseInfo();
	if (course == NULL) {
		MessageBox(L"读取本地课程数据失败！");
		freeSelectionLinkList(selection);
		return;
	}

	CourseLinkList* pc = course->next;//双链表，next获得链表开头

	int num = 0;//选课计数

	while (ps) {
		//查找已选的课看是否与当前选的课重复，或查看已选课数是否达到上限5门
		if (name.Compare(CString(ps->data.Name)) == 0) {
			if (Account.Compare(CString(ps->data.Account)) == 0) {
				MessageBox(L"你已选择该课程，请勿重复操作！");
				break;
			}
		}
		
		if (Account.Compare(CString(ps->data.Account)) == 0)
		{
			num++;//查到选的课计数+1
		}
		if (num >= 5)
		{
			MessageBox(L"每个学生只能选5门课");
			break;
		}
		ps = ps->next;
	}

	pc = course->next;//双链表，获得课程链表开头
	while (pc && ps == NULL) {
		// 找到指定课程，选课人数加一
		if (name.Compare(CString(pc->data.Name)) == 0) {//课程链表中找到了当前课程
			
			if (pc->data.All[0] == -1) {//详见限选定义，这里没啥用
				MessageBox(L"你所在班级被限选！");
				break;
			}

			if (pc->data.Max != 0 && pc->data.All[0] >= pc->data.Max) {//限选不为零但选课人数达到课程容量
				MessageBox(L"该课程已选满，请选择其他课程！");
				break;
			}

			// 打开本地选课文件，添加选课数据
			FILE* fp = NULL;
			fopen_s(&fp, "res/data/selection.txt", "a");

			if (fp == NULL) {
				MessageBox(L"本地选课文件打开失败！");
				break;
			}

			// 添加选课数据
			//在本地文件保存选课
			fprintf_s(fp, "\r%s %s", WcharToChar(name), WcharToChar(Account));

			fclose(fp);

			// 选课数据增加
			pc->data.All[0]++;
			printCourseLinkList(course);
			
			freeSelectionLinkList(selection);

			stu->data.sel_num++;
			CString a;a.FormatMessage(TEXT("%d"), stu->data.sel_num);
			MessageBox(L"选课成功");
			// 刷新列表
			course = readCourseInfo();
			RefreshCourseList(course);//刷新课程列表选课人数增加
			selection = readSelectionInfo();
			RefreshSelectionList(selection);//刷新选课列表，新增一行课程

			return;
		}
		//遍历
		pc = pc->next;
	}

	if (pc == NULL) MessageBox(L"不存在该课程，请重新选择！");

	freeCourseLinkList(course);
	freeSelectionLinkList(selection);
}

// 退选按钮事件
void Student::OnBnClickedAdminCancel()
{
	int ID = 0;
	CString name;
	m_choose.GetWindowText(name);//获得选取行的第一列字符串，即课名

	if (name.GetLength() < 2 || name.GetLength() > 18)
	{
		MessageBox(L"请选中一条已选列表中的课程数据", L"提示", MB_ICONEXCLAMATION);
		return;
	}

	SelectionLinkList* selection = readSelectionInfo();
	if (selection == NULL) {
		MessageBox(L"读取本地已选课程数据失败！");
		return;
	}
	SelectionLinkList* ps = selection->next;//双链表，获得选课链表开头

	CourseLinkList* course = readCourseInfo();
	if (course == NULL) {
		MessageBox(L"读取本地课程数据失败！");
		freeSelectionLinkList(selection);
		return;
	}

	CourseLinkList* pc = course->next;//双链表，获得课程链表开头

	while (ps) {
		// 找到已选课程
		//循环遍历，找到和选中的课程名相同的两个链表结点
		if (Account.Compare(CString(ps->data.Account)) == 0 && name.Compare(CString(ps->data.Name)) == 0) {
			while (pc) {
				// 找到该课程，人数减一
				if (name.Compare(CString(pc->data.Name)) == 0) {
					if ( pc->data.All[0] <= 0) {//数据异常，选课人数为负，一般是擅改本地文件导致的
						MessageBox(L"数据异常代码-FailX001！");
						return;
					}

					
					pc->data.All[0]--;//选课人数减一

					stu->data.sel_num--;
					MessageBox(L"退课成功");
					//释放链表对应结点，去掉该结点
					if (ps->prev) ps->prev->next = ps->next;
					if (ps->next) ps->next->prev = ps->prev;
					if (selection->next == ps) selection->next = ps->next;
					if (selection->prev == ps) selection->prev = ps->prev;
					free(ps);

					// 保存失败
					if (printSelectionLinkList(selection) == 0 || printCourseLinkList(course) == 0) {
						countSelectionNumber() ? MessageBox(L"数据异常代码-FailX002！") : MessageBox(L"退选课程失败！");
					}

					// 刷新列表
					course = readCourseInfo();
					RefreshCourseList(course);
					selection = readSelectionInfo();
					RefreshSelectionList(selection);

					return;
				}

				pc = pc->next;
			}

			return;
		}

		ps = ps->next;
	}

	MessageBox(L"你未选择该课程！");
}


// 选课编辑框改变提示
//用的windows的API函数，可自动生成(?)
void Student::OnCbnEditchangeComboStudent()
{
	CString name;
	CString list;

	m_choose.GetWindowText(name);
	int num = m_choose.GetCount();

	for (int i = 0; i < num; i++) m_choose.DeleteString(num - i - 1);

	if (name.GetLength() < 1 || name.GetLength() > 18) return m_choose.ShowDropDown(FALSE);

	for (int i = 0; i < m_course.GetItemCount(); i++) {
		list = m_course.GetItemText(i, 0);
		if (list.Find(name) != -1) m_choose.AddString(list);
	}

	m_choose.ShowDropDown(m_choose.GetCount());
}


// 点击课程列表选中
//用的windows的API函数，可自动生成(?)
void Student::OnNMClickListStudentCourse(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	int ID = 0;
	CString name;
	POSITION pos = m_course.GetFirstSelectedItemPosition();
	if (pos == NULL) return;

	ID = (int)m_course.GetNextSelectedItem(pos);
	name = m_course.GetItemText(ID, 0);

	m_choose.SetWindowText(name);

}

// 点击已选列表选中
//用的windows的API函数，可自动生成(?)
void Student::OnNMClickListStudentSelection(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	int ID = 0;
	CString name;
	POSITION pos = m_selection.GetFirstSelectedItemPosition();
	if (pos == NULL) return;

	ID = (int)m_selection.GetNextSelectedItem(pos);
	name = m_selection.GetItemText(ID, 0);

	m_choose.SetWindowText(name);
}


// 双击课程列表直接选课
//用的windows的API函数，可自动生成(?)
void Student::OnNMDblclkListStudentCourse(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	// 判断是否选择选中
	POSITION pos = m_course.GetFirstSelectedItemPosition();
	if (pos == NULL) return;

	OnBnClickedStudentSelect();
}

// 右击课程列表弹出菜单
//用的windows的API函数，可自动生成(?)
void Student::OnNMRClickListStudentCourse(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	int ID = 0;
	CString name;

	// 判断是否选择选中
	POSITION pos = m_course.GetFirstSelectedItemPosition();
	if (pos == NULL) return;

	ID = (int)m_course.GetNextSelectedItem(pos);
	name = m_course.GetItemText(ID, 0);

	m_choose.SetWindowText(name);

	POINT pt;
	CMenu menu;
	GetCursorPos(&pt);
	menu.LoadMenuW(IDR_MENU_STUDENT_LIST);
	CMenu* pop = menu.GetSubMenu(0);


	pop->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
}


// 双击已选列表直接退课
//用的windows的API函数，可自动生成(?)
void Student::OnNMDblclkListStudentSelection(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	// 判断是否选择选中
	POSITION pos = m_selection.GetFirstSelectedItemPosition();
	if (pos == NULL) return;

	OnBnClickedAdminCancel();
}


void Student::OnLvnItemchangedListStudentCourse(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

//点击按钮计算学分学费的函数
void Student::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//前面一段获取链表的代码直接照搬了前面获取链表的代码，详见前面的解释
	SelectionLinkList* selection = readSelectionInfo();
	if (selection == NULL) {
		MessageBox(L"读取本地已选课程数据失败！");
		freeSelectionLinkList(selection);
		return;
	}
	SelectionLinkList* ps = selection->next;

	CourseLinkList* course = readCourseInfo();
	if (course == NULL) {
		MessageBox(L"读取本地课程数据失败！");
		freeCourseLinkList(course);
		return;
	}

	CourseLinkList* pc = course->next;

	UserLinkList* stu = readUserInfo();
	if (stu == NULL) {
		MessageBox(L"读取本地学生数据失败！");
		freeUserLinkList(stu);
		return;
	}
	UserLinkList* pst = stu->next;
	while (pst) {
		if (Account.Compare(CString(pst->data.Account)) == 0) { break; }
		pst = pst->next;//单链表获得开头
	}
	//利用学号判断研究生还是本科生
	if (pst->data.Account[4] == 1) { pst->data.u_gu = 1; }//研究生
	else if (pst->data.Account[4] == 0) { pst->data.u_gu = 0; }//本科生
	int sum = 0;//计数调试，顺便被用作计算选课数
	m_acc = 0;m_tui = 0;//绑定editctrl控件（输出框）的学分和学费变量，用于输出数据
	int acc=0, tui=0;//定义学分和学费的变量
	while (ps) {
		//循环遍历选课链表
		if (Account.Compare(CString(ps->data.Account)) == 0)//找到该学生的选的课 
		{
			CString name;name = ps->data.Name;//获得选的课的课名
			while (pc) {
				//遍历课程链表
				if (name.Compare(CString(pc->data.Name))==0 ){//找到对应课程信息
					acc=acc+pc->data.Credit;//计算学分（叠加的方法）
					//获得课程信息并判断课程类型
					if(strcmp(pc->data.Type,"学科基础")==0)
				    {
					    tui = tui + pc->data.Credit * 200;//计算学费
				    }
				    else if(strcmp(pc->data.Type,"专业基础")==0)
				    {
						//本科生和研究生有不同的学费要求，分类讨论
					    if(pst->data.u_gu==1)
					    {
						    tui = tui + pc->data.Credit * 180;
					    }
					    else { tui = tui + pc->data.Credit * 150; }
				    }
					else if (strcmp(pc->data.Type, "专业核心") == 0)
					{
						//同上
						if (pst->data.u_gu == 1) {
							tui = tui + pc->data.Credit * 150;
						}
						else {
							tui = tui + pc->data.Credit * 100;
						}
					}
				}
				pc = pc->next;
			}
			pc = course->next;
			sum += 1;//计算遍历数，在if范围里，即是选课数
		}
		ps = ps->next;
	}
	m_acc = acc;//学分赋值给输出框1
	m_tui = tui;//学费赋值给输出框2
	pst->data.sel_num = m_acc;//没啥用，又不保存到本地文件，每次打开还是重新算
	pst->data.tuition = m_tui;//没啥用，又不保存到本地文件，每次打开还是重新算
	m_sum = sum;//选课数或遍历数赋值给输出框3
	UpdateData(FALSE);//更新数据，输出给编辑框（即输出框）
	//UpdateData函数选TRUE是从编辑框获得数据，选FALSE是输出数据给编辑框
}
