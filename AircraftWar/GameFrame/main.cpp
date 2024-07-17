#include<iostream>
#include"GameFrame.h"
#include<windowsx.h>
using namespace std;

CGameFrame* pGame = nullptr;//全员游戏壳的指针
//声明创建子类对象的函数
CGameFrame* CreateObject();
extern int wnd_pos_x;
extern int wnd_pos_y;
extern int wnd_width;
extern int wnd_height;
extern const TCHAR* wnd_title;

//窗口的回调函数,全局的函数
/*
hWnd:窗口句柄,哪个窗口发生了什么消息
uMsg:发生了什么消息,等效于msg.message
wParam,lParam:描述了消息携带一些参数
*/
//4 游戏运行的函数
LRESULT CALLBACK WindowProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	if (uMsg == WM_LBUTTONDOWN)//如果当鼠标左键按下
	{
		/*
		xPos=GET_X_LPARAM(lParam);//从lParam中获取x,y
		yPos=GET_Y_LPARAM(lParam);
		*/
		POINT po{ GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };//坐标点的结构体
		pGame->On_WM_LBUTTONDOWN(po);
	}
	if (pGame->m_MsgMap.count(uMsg))//消息存在
	{
		if (pGame->m_MsgMap[uMsg].MsgType == EM_MOUSE)//且类别为鼠标相关
		{
			POINT po{ GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };
			(pGame->*pGame->m_MsgMap[uMsg].msgFun.p_fun_EM_MOUSE)(po);
		}
		else if (pGame->m_MsgMap[uMsg].MsgType == EM_KEY)//且类别为键盘相关
		{
			(pGame->*pGame->m_MsgMap[uMsg].msgFun.p_fun_EM_KEY)(wParam);
		}
		else if (pGame->m_MsgMap[uMsg].MsgType == EM_CHAR)//且类别为字符相关
		{
			(pGame->*pGame->m_MsgMap[uMsg].msgFun.p_fun_EM_CHAR)(wParam);
		}
		else if (pGame->m_MsgMap[uMsg].MsgType == EM_WINDOW)//且类别为字符相关
		{
			(pGame->*pGame->m_MsgMap[uMsg].msgFun.p_fun_EM_WINDOW)(wParam, lParam);
		}
		if (uMsg != WM_PAINT)
		{
			RECT rect{ 0,0,500,500 };
			::InvalidateRect(pGame->hWnd, &rect, FALSE);//将窗口某个区域无效,触发重绘
		}
	}



	return DefWindowProc(hWnd, uMsg, wParam, lParam);//默认消息处理函数(系统的默认回调)
}
int main()
{
	pGame = CreateObject();
	pGame->InitGame(wnd_pos_x, wnd_pos_y, wnd_width, wnd_height, wnd_title);
	pGame->On_WM_PAINT(0, 0);//创建窗口后,不管是否有消息都重绘一下

	//pGame->RunGame();

	while (!pGame->GetQuit())
	{
		Sleep(1000);

	}
	//pGame->CloseGame();

	delete pGame;
	pGame = nullptr;
	return 0;

}
