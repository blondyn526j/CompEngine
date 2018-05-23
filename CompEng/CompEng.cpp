// CompEng.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>

#include "rendererMaster.h"
#include "master.h"
#include "baseObject.h"
#include "rendererComponent.h"

std::vector<Master*> masterCollection;	//LIST OF ALL MASTERS
std::vector<BaseObject*> baseObjectCollection;
bool closeProgramFlag = false;	//SHOULD PROGRAM EXIT ITS MAIN LOOP?

int main()
{
	//Objects Initialization
	masterCollection.push_back(new RendererMaster());

	//Adding TestObject
	baseObjectCollection.push_back(new BaseObject());
	baseObjectCollection[0]->AddComponent(new RendererComponent());

	std::cout << (baseObjectCollection[0]->componentCollection[0]->type()) << std::endl;

	//End Objects Initialization

	//CALL INITIALIZE() ON EACH MASTER
	for (Master* m : masterCollection)
	{
		m->Initialize();
	}

	//MAIN LOOP
	while (!closeProgramFlag)
	{
		//CALL UPDATE() ON EACH MASTER
		for (Master* m : masterCollection)
		{
			m->Update();
		}
	}

	system("pause");
    return 0;
}

