#include"GunnerBox.h"
#include"../GameConfig/GameConfig.h"
CGunnerBox::CGunnerBox() {

}
CGunnerBox::~CGunnerBox() {
	list<CGunner*>::iterator ite = m_lstGun.begin();
	while (ite != m_lstGun.end()) {
		if (*ite) {
			delete (*ite);
			(*ite) = nullptr;
		}
		ite++;
	}
	m_lstGun.clear();

	ite = m_lstGunBoom.begin();
	while (ite != m_lstGunBoom.end()) {
		if (*ite) {
			delete (*ite);
			(*ite) = nullptr;
		}
		ite++;
	}
}

void CGunnerBox::ShowAllGunner(int othergun) {
	for (CGunner* p : m_lstGun) {
		if (p)p->ShowGunner();
	}
	if (othergun) {
		for (CGunner* p : m_lstLGun) {
			if (p)p->ShowGunner();
		}
		for (CGunner* p : m_lstRGun) {
			if (p)p->ShowGunner();
		}
	}
}
//¥Ê‘⁄Œ Ã‚
void CGunnerBox::MoveAllGunner(int othergun) {
	list<CGunner*>::iterator ite = m_lstGun.begin();
	while (ite != m_lstGun.end()) {
		if (*ite) {
			(*ite)->MoveGunner(othergun, 0, 1);

			if ((*ite)->m_y <= -IMG_GUNNER_HEIGHT) {
			delete (*ite);
			(*ite) = nullptr;
			ite = m_lstGun.erase(ite);
			continue;
		}
		}
		ite++;
	}
	if (othergun == 1) {
		ite = m_lstLGun.begin();
		while (ite != m_lstLGun.end()) {
			if (*ite) {
				(*ite)->MoveGunner(othergun, 0, 1);

				if ((*ite)->m_y <= -IMG_GUNNER_HEIGHT) {
					delete (*ite);
					(*ite) = nullptr;
					ite = m_lstLGun.erase(ite);
					continue;
				}
			}
			ite++;
		}
		ite = m_lstRGun.begin();
		while (ite != m_lstRGun.end()) {
			if (*ite) {
				(*ite)->MoveGunner(othergun, 0, 1);
				if ((*ite)->m_y <= -IMG_GUNNER_HEIGHT) {
					delete (*ite);
					(*ite) = nullptr;
					ite = m_lstRGun.erase(ite);
					continue;
				}
			}
			ite++;
		}
	}
	if (othergun == 2) {
		ite = m_lstLGun.begin();
		while (ite != m_lstLGun.end()) {
			if (*ite) {
				(*ite)->MoveGunner(othergun, 1, 0);
				if ((*ite)->m_y <= -IMG_GUNNER_HEIGHT) {
					delete (*ite);
					(*ite) = nullptr;
					ite = m_lstLGun.erase(ite);
					continue;
				}
			}
			ite++;
		}
		ite = m_lstRGun.begin();
		while (ite != m_lstRGun.end()) {
			if (*ite) {
				(*ite)->MoveGunner(othergun, 2, 0);
				if ((*ite)->m_y <= -IMG_GUNNER_HEIGHT) {
					delete (*ite);
					(*ite) = nullptr;
					ite = m_lstRGun.erase(ite);
					continue;
				}
			}
			ite++;
		}
	}
}