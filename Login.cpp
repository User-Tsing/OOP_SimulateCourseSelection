﻿#include "pch.h"
#include "CSS.h"
#include "Func.h"
#include "Login.h"
//#include "Admin.h"
#include "Student.h"
#include "framework.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//登录页面设置

// CLogin 对话框

Login::Login(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Login, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Login::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Login, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &Login::OnBnClickedButtonLogin)
	ON_EN_CHANGE(IDC_EDIT_LOGIN_PASSWORD, &Login::OnEnChangeEditLoginPassword)
END_MESSAGE_MAP()


// CLogin 消息处理程序

BOOL Login::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	// 默认选中学生模式
	((CButton*)GetDlgItem(IDC_RADIO_LOGIN_STUDENT))->SetCheck(TRUE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Login::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Login::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 登录事件
void Login::OnBnClickedButtonLogin()
{
	// 读取编辑框账号和密码
	CString Account, Password;//定义变量
	GetDlgItemTextW(IDC_EDIT_LOGIN_ACCOUNT, Account);//读取输入框数据并赋值给变量
	GetDlgItemTextW(IDC_EDIT_LOGIN_PASSWORD, Password);//读取输入框数据并赋值给变量

	// 学号格式判断
	if (Account.GetLength() != 7 ) {
		MessageBox(L"学号格式错误");//弹窗设置
		return;
	}

	// 密码长度判断
	if (Password.GetLength() > 18 || Password.GetLength() < 6) {
		MessageBox(L"密码长度为6-18个字符！");
		return;
	}

	// 读取本地用户数据
	struct UserLinkList* link = readUserInfo();
	if (link == NULL) {
		MessageBox(L"读取本地用户数据失败！");
		return;
	}

	// 0学生模式 1教务模式
	struct UserLinkList* p = link;//本地文件的学生信息读取
	if (((CButton*)GetDlgItem(IDC_RADIO_LOGIN_ADMIN))->GetCheck() == 0) {//自带生成语句afxwin
		do {//循环遍历查找输入学号对应学生的链表节点
			p = p->next;
			if (p->data.ID != 0) {
				if (Account.Compare(CString(p->data.Account)) == 0) {//输入学号和某个链表结点学号相同，找到学生
					if (Password.Compare(CString(p->data.Password)) == 0) {//输入密码与链表结点密码相同

						// 学生模式登录成功
						Student dlg;
						//进入下一个页面的初始化内容
						dlg.title = CString(p->data.Name);
						dlg.Account = CString(p->data.Account);
						dlg.title.Insert(-1, CString(p->data.Account));
						dlg.theClass = _ttoi((CString(p->data.Account).Right(3)).Left(1));
						dlg.stu=p;
						CDialog::OnOK();
						dlg.DoModal();
					}
					else {
						MessageBox(L"密码错误！");
					}

					return freeUserLinkList(link);
				}
			}

		} while (p->next != NULL);

		MessageBox(L"学生账号不存在！");
	}
}
	/*else {
		do {
			p = p->next;
			if (p->data.ID == 0) {
				if (Account.Compare(CString(p->data.Account)) == 0) {
					if (Password.Compare(CString(p->data.Password)) == 0) {

						// 教务模式登录成功
						Admin dlg;

						CDialog::OnOK();
						dlg.DoModal();
					}
					else {
						MessageBox(L"密码错误！");
					}
					return freeUserLinkList(link);
				}
			}

		} while (p->next != NULL);

		MessageBox(L"教务账号不存在！");
	}

	return freeUserLinkList(link);
}*/


void Login::OnEnChangeEditLoginPassword()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
