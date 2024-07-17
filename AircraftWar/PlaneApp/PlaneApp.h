#pragma once
#include"../GameFrame/GameFrame.h"
#include"../BackGround/BackGround.h"
#include"../Player/Player.h"
#include"../GunnerBox/GunnerBox.h"
#include"../FoePlaneBox/FoePlaneBox.h"
#include"../GunnerBox/gift.h"
class CPlaneApp:public CGameFrame{
public:
	CBackGround m_back; 
	CPlayer m_player;
	CGunnerBox m_gunBox;
	CFoePlaneBox m_foeBox;
	Gift gift;
	int m_score;
	IMAGE m_board;
	int hurt;
public:
	CPlaneApp();
	~CPlaneApp();
public:
	void ShowScore();
	void SetTimer();
	void GameOver();
	void On_Init();
	void On_Close();
	void On_Paint();
	void On_WM_KEYDOWN(WPARAM);
	virtual void On_WM_TIMER(WPARAM, LPARAM);
	void On_WM_LBUTTONDOWN(POINT po);
};