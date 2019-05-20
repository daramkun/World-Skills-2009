#include "Item.h"
#include "Lib.h"

CItem::CItem(void)
{
}

CItem::~CItem(void)
{
}

void CItem::Initial(ItemType type, int x)
{
	switch(type)
	{
	case IT_Ssanghwatang:
		myImg.Create("Content/Item/SS.png");
		y = 350;
		break;
	case IT_Sword:
		myImg.Create("Content/Item/°Ë.png");
		y = 350;
		break;
	case IT_Bow:
		myImg.Create("Content/Item/Bow.png");
		y = 350;
		break;
	case IT_Shield:
		myImg.Create("Content/Item/½Çµå.png");
		y = 350;
		break;
	}

	isUse = false;

	this->type = type;
	this->x = x;
}

void CItem::Update(CHero& hero, int cx)
{
	if(isUse) return;

	if(CLib::Crash(hero.x - cx, hero.y, 130, hero.GetHeight(),
		x, y, myImg.GetWidth(), myImg.GetHeight()))
	{
		switch(type)
		{
		case IT_Ssanghwatang:
			hero.haveSsanghwa++;
			if(hero.haveSsanghwa > 2)
				hero.haveSsanghwa = 2;
			break;
		case IT_Sword:
			hero.haveSword = true;
			hero.myEquip = HCE_SWORD;
			break;
		case IT_Bow:
			hero.haveBow = true;
			hero.myEquip = HCE_BOW;
			break;
		case IT_Shield:
			hero.haveShield = true;
			break;
		}

		CLib::SoundPlay("Content/Sound/GetItem.wav");
		isUse = true;
	}
}

void CItem::Draw(int cx)
{
	if(isUse) return;
	myImg.Draw(x + cx, y);
}

void CItem::Destroy()
{

}