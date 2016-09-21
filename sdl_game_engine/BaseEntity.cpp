#pragma once
#include "BaseEntity.h"
#include <list>

using namespace std;

BaseEntity::BaseEntity() :BaseEntity(list<BaseEntity>()) {};
BaseEntity::BaseEntity(list<BaseEntity> cp)
{
	Entities = cp;
}

BaseEntity::~BaseEntity()
{

}

void BaseEntity::Update()
{
	list<BaseEntity>::iterator i;
	for (i = Entities.begin(); i != Entities.end(); i++)
	{
		i->Update();
	}
}


void BaseEntity::Draw()
{
	list<BaseEntity>::iterator i;
	for (i = Entities.begin(); i != Entities.end(); i++)
	{
		i->Draw();
	}
}