#pragma once
#include <list>
using namespace std;

class BaseEntity {
public:
	list<BaseEntity> Entities;
	BaseEntity();
	BaseEntity(list<BaseEntity> cp);
	~BaseEntity();
	void Update();
	void Draw();
private:
	
};