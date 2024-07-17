#pragma once
#include<easyx.h>
#include<map>
using namespace std;

//window 标准回调函数
LRESULT CALLBACK WindowProc(_In_  HWND hwnd,_In_  UINT uMsg,_In_  WPARAM wParam,_In_  LPARAM lParam);


#define INIT_MSGMAP(MSG_ID,MSG_TYPE)\
	m_MsgMap[MSG_ID].MsgType = MSG_TYPE;\
	m_MsgMap[MSG_ID].msgFun.p_fun_##MSG_TYPE = &CGameFrame::On_##MSG_ID;




class CGameFrame {

	//friend ：定义友元, WindowProc 函数是CGameFrame 的朋友，所以在朋友的函数里面可以直接使用私有的
	friend LRESULT CALLBACK WindowProc(HWND,UINT , WPARAM , LPARAM );
protected:
	HWND hWnd;
private:
	bool m_isQuit;   //标识是否退出, true ：退出，false :不退出
	/*
	#define EM_MOUSE	1
	#define EM_KEY		2
	#define EM_CHAR		4
	#define EM_WINDOW	8
	*/

	typedef void (CGameFrame ::* P_FUN_MOUSE)(POINT);  //鼠标类别消息处理函数
	typedef void (CGameFrame::* P_FUN_KEY)(WPARAM ); //键盘类别消息处理函数
	typedef void (CGameFrame::* P_FUN_CHAR)(WPARAM);
	typedef void (CGameFrame::* P_FUN_WINDOW)(WPARAM,LPARAM);

	struct MsgFun {
		size_t MsgType;    //消息的类别
		union Fun {
			P_FUN_MOUSE p_fun_EM_MOUSE;   //指向处理鼠标消息类别的函数指针
			P_FUN_KEY p_fun_EM_KEY;   //指向处理键盘消息类别的函数指针
			P_FUN_CHAR p_fun_EM_CHAR;
			P_FUN_WINDOW p_fun_EM_WINDOW;
		} msgFun;
	};

	map<UINT, MsgFun>  m_MsgMap;  //消息映射表

	void InitMsgMap() {
		//添加一条消息和处理
			/*m_MsgMap[WM_LBUTTONDOWN].MsgType = EM_MOUSE;
			m_MsgMap[WM_LBUTTONDOWN].msgFun.p_fun_EM_MOUSE = &CGameFrame::On_WM_LBUTTONDOWN;*/
		INIT_MSGMAP(WM_LBUTTONDOWN, EM_MOUSE)

			//添加一条消息（WM_KEYDOWN）和处理
			/*m_MsgMap[WM_KEYDOWN].MsgType = EM_KEY;
			m_MsgMap[WM_KEYDOWN].msgFun.p_fun_EM_KEY = &CGameFrame::On_WM_KEYDOWN;*/
			INIT_MSGMAP(WM_KEYDOWN, EM_KEY)

			INIT_MSGMAP(WM_CHAR, EM_CHAR)
			INIT_MSGMAP(WM_CLOSE, EM_WINDOW)
			INIT_MSGMAP(WM_MOUSEMOVE,EM_MOUSE)
			INIT_MSGMAP(WM_PAINT, EM_WINDOW)
			INIT_MSGMAP(WM_TIMER,EM_WINDOW)

	}
public:
	CGameFrame():m_isQuit(false) {
	}
	virtual~CGameFrame() {
	}

	bool GetQuit() {
		return m_isQuit;
	}
public:
	//1. 初始化游戏
	void InitGame(int x,int y,int width,int height,const TCHAR* pTitle) {
		//窗口大小为 
		hWnd = ::initgraph(width, height);   //创建窗口

		//移动窗口
		::MoveWindow(hWnd, x,y, width, height,TRUE);

		//设置窗口标题
		::SetWindowText(hWnd, pTitle);

		//设定背景色
		::setbkcolor(RGB(255, 255, 255));   //白色
		::cleardevice();   //使设置的白色，立即生效

		//为 hWnd 窗口设定回调函数
		::SetWindowLong(hWnd, GWL_WNDPROC,(LONG)&WindowProc);

		InitMsgMap();  //初始化消息映射表

		//具体游戏的初始化
		On_Init();

	}
	//2. 关闭
	void CloseGame() {
		On_Close();  //具体游戏的关闭
		::closegraph();  //关闭窗口
	}
	//3. 重绘函数
	void On_WM_PAINT(WPARAM,LPARAM) {
		::BeginBatchDraw();  //开始批量绘图
		::cleardevice();  //清屏

		//----具体游戏重绘（显示的代码）--------------------------
		On_Paint();  //具体游戏的绘制代码

		//------------------------------
		::EndBatchDraw();  //结束批量绘图
	}

	void On_WM_CLOSE(WPARAM,LPARAM) {
		CloseGame();
		m_isQuit = true;  //窗口已经关闭，告诉主函数的while循环 ,该跳出循环
	}


	//---具体游戏相关的函数-----------------------------------
	virtual void On_Init() = 0;
	virtual void On_Close() = 0;
	virtual void On_Paint() = 0;

	virtual void On_WM_LBUTTONDOWN(POINT po) {}

	virtual void On_WM_KEYDOWN(WPARAM wParam) {  //wParam ：按下了哪个键
	
	}
	virtual void On_WM_CHAR(WPARAM wParam){}
	virtual void On_WM_MOUSEMOVE(POINT po) {}
	virtual void On_WM_TIMER(WPARAM, LPARAM) {}

};
#define CREATE_OBJECT(CLASS)\
CGameFrame* CreateObject(){\
	return new CLASS;\
}
#define WND_PARAM(X,Y,WIDTH,HEIGHT,TITLE)\
int wnd_pos_x=X;\
int wnd_pos_y=Y;\
int wnd_width=WIDTH;\
int wnd_height=HEIGHT;\
const TCHAR* wnd_title=TITLE;