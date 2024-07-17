#pragma once
#include<easyx.h>
#include<map>
using namespace std;

//window ��׼�ص�����
LRESULT CALLBACK WindowProc(_In_  HWND hwnd,_In_  UINT uMsg,_In_  WPARAM wParam,_In_  LPARAM lParam);


#define INIT_MSGMAP(MSG_ID,MSG_TYPE)\
	m_MsgMap[MSG_ID].MsgType = MSG_TYPE;\
	m_MsgMap[MSG_ID].msgFun.p_fun_##MSG_TYPE = &CGameFrame::On_##MSG_ID;




class CGameFrame {

	//friend ��������Ԫ, WindowProc ������CGameFrame �����ѣ����������ѵĺ����������ֱ��ʹ��˽�е�
	friend LRESULT CALLBACK WindowProc(HWND,UINT , WPARAM , LPARAM );
protected:
	HWND hWnd;
private:
	bool m_isQuit;   //��ʶ�Ƿ��˳�, true ���˳���false :���˳�
	/*
	#define EM_MOUSE	1
	#define EM_KEY		2
	#define EM_CHAR		4
	#define EM_WINDOW	8
	*/

	typedef void (CGameFrame ::* P_FUN_MOUSE)(POINT);  //��������Ϣ������
	typedef void (CGameFrame::* P_FUN_KEY)(WPARAM ); //���������Ϣ������
	typedef void (CGameFrame::* P_FUN_CHAR)(WPARAM);
	typedef void (CGameFrame::* P_FUN_WINDOW)(WPARAM,LPARAM);

	struct MsgFun {
		size_t MsgType;    //��Ϣ�����
		union Fun {
			P_FUN_MOUSE p_fun_EM_MOUSE;   //ָ���������Ϣ���ĺ���ָ��
			P_FUN_KEY p_fun_EM_KEY;   //ָ���������Ϣ���ĺ���ָ��
			P_FUN_CHAR p_fun_EM_CHAR;
			P_FUN_WINDOW p_fun_EM_WINDOW;
		} msgFun;
	};

	map<UINT, MsgFun>  m_MsgMap;  //��Ϣӳ���

	void InitMsgMap() {
		//���һ����Ϣ�ʹ���
			/*m_MsgMap[WM_LBUTTONDOWN].MsgType = EM_MOUSE;
			m_MsgMap[WM_LBUTTONDOWN].msgFun.p_fun_EM_MOUSE = &CGameFrame::On_WM_LBUTTONDOWN;*/
		INIT_MSGMAP(WM_LBUTTONDOWN, EM_MOUSE)

			//���һ����Ϣ��WM_KEYDOWN���ʹ���
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
	//1. ��ʼ����Ϸ
	void InitGame(int x,int y,int width,int height,const TCHAR* pTitle) {
		//���ڴ�СΪ 
		hWnd = ::initgraph(width, height);   //��������

		//�ƶ�����
		::MoveWindow(hWnd, x,y, width, height,TRUE);

		//���ô��ڱ���
		::SetWindowText(hWnd, pTitle);

		//�趨����ɫ
		::setbkcolor(RGB(255, 255, 255));   //��ɫ
		::cleardevice();   //ʹ���õİ�ɫ��������Ч

		//Ϊ hWnd �����趨�ص�����
		::SetWindowLong(hWnd, GWL_WNDPROC,(LONG)&WindowProc);

		InitMsgMap();  //��ʼ����Ϣӳ���

		//������Ϸ�ĳ�ʼ��
		On_Init();

	}
	//2. �ر�
	void CloseGame() {
		On_Close();  //������Ϸ�Ĺر�
		::closegraph();  //�رմ���
	}
	//3. �ػ溯��
	void On_WM_PAINT(WPARAM,LPARAM) {
		::BeginBatchDraw();  //��ʼ������ͼ
		::cleardevice();  //����

		//----������Ϸ�ػ棨��ʾ�Ĵ��룩--------------------------
		On_Paint();  //������Ϸ�Ļ��ƴ���

		//------------------------------
		::EndBatchDraw();  //����������ͼ
	}

	void On_WM_CLOSE(WPARAM,LPARAM) {
		CloseGame();
		m_isQuit = true;  //�����Ѿ��رգ�������������whileѭ�� ,������ѭ��
	}


	//---������Ϸ��صĺ���-----------------------------------
	virtual void On_Init() = 0;
	virtual void On_Close() = 0;
	virtual void On_Paint() = 0;

	virtual void On_WM_LBUTTONDOWN(POINT po) {}

	virtual void On_WM_KEYDOWN(WPARAM wParam) {  //wParam ���������ĸ���
	
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