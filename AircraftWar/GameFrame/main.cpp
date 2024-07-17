#include<iostream>
#include"GameFrame.h"
#include<windowsx.h>
using namespace std;

CGameFrame* pGame = nullptr;//ȫԱ��Ϸ�ǵ�ָ��
//���������������ĺ���
CGameFrame* CreateObject();
extern int wnd_pos_x;
extern int wnd_pos_y;
extern int wnd_width;
extern int wnd_height;
extern const TCHAR* wnd_title;

//���ڵĻص�����,ȫ�ֵĺ���
/*
hWnd:���ھ��,�ĸ����ڷ�����ʲô��Ϣ
uMsg:������ʲô��Ϣ,��Ч��msg.message
wParam,lParam:��������ϢЯ��һЩ����
*/
//4 ��Ϸ���еĺ���
LRESULT CALLBACK WindowProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	if (uMsg == WM_LBUTTONDOWN)//���������������
	{
		/*
		xPos=GET_X_LPARAM(lParam);//��lParam�л�ȡx,y
		yPos=GET_Y_LPARAM(lParam);
		*/
		POINT po{ GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };//�����Ľṹ��
		pGame->On_WM_LBUTTONDOWN(po);
	}
	if (pGame->m_MsgMap.count(uMsg))//��Ϣ����
	{
		if (pGame->m_MsgMap[uMsg].MsgType == EM_MOUSE)//�����Ϊ������
		{
			POINT po{ GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam) };
			(pGame->*pGame->m_MsgMap[uMsg].msgFun.p_fun_EM_MOUSE)(po);
		}
		else if (pGame->m_MsgMap[uMsg].MsgType == EM_KEY)//�����Ϊ�������
		{
			(pGame->*pGame->m_MsgMap[uMsg].msgFun.p_fun_EM_KEY)(wParam);
		}
		else if (pGame->m_MsgMap[uMsg].MsgType == EM_CHAR)//�����Ϊ�ַ����
		{
			(pGame->*pGame->m_MsgMap[uMsg].msgFun.p_fun_EM_CHAR)(wParam);
		}
		else if (pGame->m_MsgMap[uMsg].MsgType == EM_WINDOW)//�����Ϊ�ַ����
		{
			(pGame->*pGame->m_MsgMap[uMsg].msgFun.p_fun_EM_WINDOW)(wParam, lParam);
		}
		if (uMsg != WM_PAINT)
		{
			RECT rect{ 0,0,500,500 };
			::InvalidateRect(pGame->hWnd, &rect, FALSE);//������ĳ��������Ч,�����ػ�
		}
	}



	return DefWindowProc(hWnd, uMsg, wParam, lParam);//Ĭ����Ϣ������(ϵͳ��Ĭ�ϻص�)
}
int main()
{
	pGame = CreateObject();
	pGame->InitGame(wnd_pos_x, wnd_pos_y, wnd_width, wnd_height, wnd_title);
	pGame->On_WM_PAINT(0, 0);//�������ں�,�����Ƿ�����Ϣ���ػ�һ��

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
