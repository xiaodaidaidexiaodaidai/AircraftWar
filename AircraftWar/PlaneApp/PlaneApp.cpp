#include"PlaneApp.h"
#include"..\GameConfig\GameConfig.h"
#include<string>
#include"../FoePlaneBox/FoePlaneBig.h"
#include"../FoePlaneBox/FoePlaneMid.h"
#include"../FoePlaneBox/FoePlaneSma.h"
#include"../GunnerBox/PlayerGun.h"
using namespace std;
CREATE_OBJECT(CPlaneApp)
WND_PARAM(500,100,616,839,L"飞机大战")

CPlaneApp::CPlaneApp():m_score(0),hurt(GUNNER_HURT){}
CPlaneApp::~CPlaneApp() {}

void CPlaneApp::On_Init() {
	m_back.InitBack();
	m_player.InitPlayer();
	m_score = 0;
	::loadimage(&m_board, L"./res/cardboard.png",100,50);
	SetTimer();
}
void CPlaneApp::On_Close() {
	GameOver();
	//if (::MessageBox(hWnd, L"确定退出吗", L"提示", MB_OKCANCEL) == MB_OK) {

	//}
}
void CPlaneApp::On_Paint() {
	m_back.ShowBack();
	m_player.ShowPlayer();

	m_gunBox.ShowAllGunner(m_player.othergun);
	if (gift.m_is == 1)	gift.ShowGift();
	m_foeBox.ShowAllFoe();
	m_foeBox.ShowAllBoomFoe();


	ShowScore();
}
void CPlaneApp::On_WM_KEYDOWN(WPARAM w) {
	m_player.MovePlayer(w, PLAYER_MOVE_STEP);
}
void CPlaneApp::On_WM_LBUTTONDOWN(POINT po) {
	if(m_player.blue>50)m_player.blue -= 50;
	list<CFoePlane*>::iterator iteFoe = m_foeBox.m_lstFoe.begin();
	while (iteFoe != m_foeBox.m_lstFoe.end()) {
		if (*iteFoe) {
			m_foeBox.m_lstFoeBoom.push_back(*iteFoe);
			iteFoe = m_foeBox.m_lstFoe.erase(iteFoe);
			continue;
		}
		iteFoe++;
	}

}
void CPlaneApp::On_WM_TIMER(WPARAM w, LPARAM l) {
	if (m_player.blue == 0)m_player.othergun = 0;
	if ((rand() % 1000) == 0&& gift.m_is ==0) {
		gift.InitGift();
	}
	if (BACK_MOVE_TIMERID == w) {
		m_back.MoveBack(BACK_MOVE_STEP);
	}
		if(BACK_MOVE_TIMERID ==w ) {
			m_back.MoveBack(BACK_MOVE_STEP);
		}
		else if (PLAYER_MOVE_TIMERID == w) {
			if (::GetAsyncKeyState(VK_LEFT)) {
				m_player.MovePlayer(VK_LEFT, PLAYER_MOVE_STEP);
			}
			if (::GetAsyncKeyState(VK_RIGHT)) {
				m_player.MovePlayer(VK_RIGHT, PLAYER_MOVE_STEP);
			}
			if (::GetAsyncKeyState(VK_UP)) {
				m_player.MovePlayer(VK_UP, PLAYER_MOVE_STEP);
			}
			if (::GetAsyncKeyState(VK_DOWN)) {
				m_player.MovePlayer(VK_DOWN, PLAYER_MOVE_STEP);
			}
			if (::GetAsyncKeyState(VK_LSHIFT)) {
				if (m_player.blue > 0)
					m_player.othergun = 1;
			}
			if (::GetAsyncKeyState(VK_RSHIFT)) {
				if (m_player.blue > 0)
					m_player.othergun = 2;
			}
			if (::GetAsyncKeyState(VK_TAB)) {
				m_player.othergun = 0;
			}

		}
		else if (GUNNER_SEND_TIMERID == w) {
			CGunner* pGun = m_player.SendGun();
			m_gunBox.m_lstGun.push_back(pGun);
			if (m_player.othergun) {
				if (m_player.othergun) {
					m_player.m_x -= 10;
					m_gunBox.m_lstLGun.push_back(m_player.SendGun());
					m_player.m_x += 20;
					m_gunBox.m_lstRGun.push_back(m_player.SendGun());
					m_player.m_x -= 10;
					m_player.blue--;
				}
			}
			for (CFoePlane* pFoe : m_foeBox.m_lstFoe) {
				m_gunBox.m_lstGun.push_back(pFoe->SendGun());
			}
		}
		else if (GUNNER_MOVE_TIMERID == w) {
			m_gunBox.MoveAllGunner(m_player.othergun);
		}
		else if(FOESMA_CREATE_TIMERID==w){
			CFoePlane* pFoe = new CFoePlaneSma;
			pFoe->InitFoe();
			m_foeBox.m_lstFoe.push_back(pFoe);
		}
		else if (FOEMID_CREATE_TIMERID==w) {
			if (m_score > 10) {
				CFoePlane* pFoe = new CFoePlaneMid;
				pFoe->InitFoe();
				m_foeBox.m_lstFoe.push_back(pFoe);
			}
		}
		else if (FOEBIG_CREATE_TIMERID==w) {
			if (m_score > 20) {
				CFoePlane* pFoe = new CFoePlaneBig;
				pFoe->InitFoe();
				m_foeBox.m_lstFoe.push_back(pFoe);
			}
		}
		else if (FOE_MOVE_TIMERID == w) {
			m_foeBox.MoveAllFoe();
		}
		else if (CHECK_HIT_TIMERID == w) {
			if (gift.IsHitPlayer(m_player)) {
				gift.getGift(m_player, &hurt);
			}
			list<CFoePlane*>::iterator iteFoe = m_foeBox.m_lstFoe.begin();
			list<CGunner*>::iterator iteGun;
			while (iteFoe != m_foeBox.m_lstFoe.end()) {
				bool isBoom = false;
				if ((*iteFoe)->IsHitPlayer(m_player)) {
					GameOver();
					::MessageBox(hWnd, L"GameOver", L"提示", MB_OK);
					::PostMessage(hWnd, WM_CLOSE, 0, 0);
				}
				iteGun = m_gunBox.m_lstGun.begin();
				while (iteGun != m_gunBox.m_lstGun.end()) {
					if (*iteGun) {
						if ((*iteFoe)->IsHitGunner(*iteGun) && (*iteGun)->state == 0) {
							delete(*iteGun);
							(*iteGun) = nullptr;
							iteGun = m_gunBox.m_lstGun.erase(iteGun);
							(*iteFoe)->m_blood -= GUNNER_HURT;
							if ((*iteFoe)->m_blood <= 0) {
								m_score++;
								m_player.blue++;
								//m_gunBox.m_lstGunBoom.push_back(*iteGun);
								m_foeBox.m_lstFoeBoom.push_back(*iteFoe);
								iteFoe = m_foeBox.m_lstFoe.erase(iteFoe);

								isBoom = true;
								break;
							}
						}
						else if (m_player.IsHitGunner(*iteGun) && (*iteGun)->state == 1) {
							delete(*iteGun);
							(*iteGun) = nullptr;
							iteGun = m_gunBox.m_lstGun.erase(iteGun);
							m_player.blood -= hurt;
							if (m_player.blood <= 0) {
								GameOver();
								::MessageBox(hWnd, L"GameOver", L"提示", MB_OK);
								::PostMessage(hWnd, WM_CLOSE, 0, 0);
							}
						}
					}
					iteGun++;
				}

				if (m_player.othergun) {
					iteGun = m_gunBox.m_lstLGun.begin();
					while (iteGun != m_gunBox.m_lstLGun.end() && iteFoe != m_foeBox.m_lstFoe.end()) {
						if ((*iteFoe)->IsHitGunner(*iteGun)) {
							delete(*iteGun);
							(*iteGun) = nullptr;
							iteGun = m_gunBox.m_lstLGun.erase(iteGun);
							(*iteFoe)->m_blood -= hurt;
							m_score += hurt;
							m_player.blue += hurt;
							if ((*iteFoe)->m_blood <= 0) {
								m_foeBox.m_lstFoeBoom.push_back(*iteFoe);
								iteFoe = m_foeBox.m_lstFoe.erase(iteFoe);
								m_player.blue++;
								isBoom = true;
								break;
							}
							continue;
						}
						iteGun++;
					}

					iteGun = m_gunBox.m_lstRGun.begin();
					while (iteGun != m_gunBox.m_lstRGun.end() && iteFoe != m_foeBox.m_lstFoe.end()) {
						if ((*iteFoe)->IsHitGunner(*iteGun)) {
							delete(*iteGun);
							(*iteGun) = nullptr;
							iteGun = m_gunBox.m_lstRGun.erase(iteGun);

							(*iteFoe)->m_blood -= hurt;
							m_score += hurt;
							if ((*iteFoe)->m_blood <= 0) {
								m_foeBox.m_lstFoeBoom.push_back(*iteFoe);
								iteFoe = m_foeBox.m_lstFoe.erase(iteFoe);
								m_player.blue++;
								isBoom = true;
								break;
							}
							continue;
						}
						iteGun++;
					}
				}
				if (!isBoom) {
					iteFoe++;
				}
			}
		}
		else if (CHANGE_PIC_TIMERID == w) {
			list<CFoePlane*>::iterator ite= m_foeBox.m_lstFoeBoom.begin();
			while (ite != m_foeBox.m_lstFoeBoom.end()) {
				if (*ite) {
					(*ite)->m_showId--;
					if ((*ite)->m_showId < 0) {
						delete (*ite);
						(*ite) = nullptr;
						ite=m_foeBox.m_lstFoeBoom.erase(ite);
						continue;
					}
				}
				ite++;
			}
		}
}
void CPlaneApp::ShowScore() {
	::putimage(0, 0, &m_board);
	wstring str = L"分数为：";
	TCHAR s[5] = { 0 };
	_itow_s(m_score, s, 10);
	RECT rect = { 0,0,100,20 };
	::settextcolor(RGB(255, 0, 0));
	str += s;
	::drawtext(str.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	wstring strl = L"血量为：";
	TCHAR sl[5] = { 0 };
	_itow_s(m_player.blood, sl, 10);
	RECT rectl = { 0,0,100,50 };
	::settextcolor(RGB(255, 0, 0));
	strl += sl;
	::drawtext(strl.c_str(), &rectl, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	wstring strr = L"蓝量为：";
	TCHAR sr[5] = { 0 };
	 _itow_s(m_player.blue, sr, 10);
	RECT rectr = { 0,0,100,80 };
	::settextcolor(RGB(255, 0, 0));
	strr += sr;
	::drawtext(strr.c_str(), &rectr, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
void CPlaneApp::SetTimer() {
	::SetTimer(this->hWnd,BACK_MOVE_TIMERID, BACK_MOVE_INTERVAL,nullptr);
	::SetTimer(this->hWnd, PLAYER_MOVE_TIMERID, PLAYER_MOVE_INTERVAL, nullptr);

	::SetTimer(this->hWnd, GUNNER_SEND_TIMERID, GUNNER_SEND_INTERVAL, nullptr);
	::SetTimer(this->hWnd, GUNNER_MOVE_TIMERID, GUNNER_MOVE_INTERVAL, nullptr);

	::SetTimer(this->hWnd, FOESMA_CREATE_TIMERID, FOESMA_CREATE_INTERVAL, nullptr);
	::SetTimer(this->hWnd, FOEMID_CREATE_TIMERID, FOEMID_CREATE_INTERVAL, nullptr);
	::SetTimer(this->hWnd, FOEBIG_CREATE_TIMERID, FOEBIG_CREATE_INTERVAL, nullptr);

	::SetTimer(this->hWnd, FOE_MOVE_TIMERID, FOE_MOVE_INTERVAL, nullptr);

	::SetTimer(this->hWnd, CHECK_HIT_TIMERID, CHECK_HIT_INTERVAL, nullptr);
	::SetTimer(this->hWnd, CHANGE_PIC_TIMERID, CHANGE_PIC_INTERVAL, nullptr);
}
void CPlaneApp::GameOver() {
	::KillTimer(this->hWnd, BACK_MOVE_TIMERID);
	::KillTimer(this->hWnd, PLAYER_MOVE_TIMERID);

	::KillTimer(this->hWnd, GUNNER_SEND_TIMERID);
	::KillTimer(this->hWnd, GUNNER_MOVE_TIMERID);

	::KillTimer(this->hWnd, FOESMA_CREATE_TIMERID);
	::KillTimer(this->hWnd, FOEMID_CREATE_TIMERID);
	::KillTimer(this->hWnd, FOEBIG_CREATE_TIMERID);

	::KillTimer(this->hWnd, FOE_MOVE_TIMERID);

	::KillTimer(this->hWnd, CHECK_HIT_TIMERID);
	::KillTimer(this->hWnd, CHANGE_PIC_TIMERID);

}