#pragma once
#include<easyx.h>
class CBackGround{
public:
	int m_x;
	int m_y;
	IMAGE m_back;
public:
	CBackGround();
	~CBackGround();

public:
	void InitBack();
	void ShowBack();
	void MoveBack(int step);
};