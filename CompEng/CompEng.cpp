// CompEng.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>

#include "rendererMaster.h"
#include "master.h"
#include "baseObject.h"
#include "rendererComponent.h"
#include "transformComponent.h"
#include "lightComponent.h"

extern std::vector<BaseObject*> baseObjectCollection;

std::vector<Master*> masterCollection;	//LIST OF ALL MASTERS
std::vector<BaseObject*> baseObjectCollection;
bool closeProgramFlag = false;	//SHOULD PROGRAM EXIT ITS MAIN LOOP?

int main()
{
	//Objects Initialization
	masterCollection.push_back(new RendererMaster());


	baseObjectCollection.reserve(1024);
	//Adding TestObject
	BaseObject* object;
	Component* component;

	object = new BaseObject();
	component = new RendererComponent();
	object->AddComponent(component);
	component = new TransformComponent(glm::vec3(2.5f, 0.0f, 0.0f));
	object->AddComponent(component);
	baseObjectCollection.push_back(object);

	object = new BaseObject();
	object->AddComponent(new RendererComponent());
	object->AddComponent(new TransformComponent(glm::vec3(-1.8f, 0.0f, -1.5f)));
	baseObjectCollection.push_back(object);

	object = new BaseObject();
	object->AddComponent(new RendererComponent());
	object->AddComponent(new TransformComponent(glm::vec3(-4.8f, 0.0f, -2.5f)));
	baseObjectCollection.push_back(object);

	float intesitivity = 3.0f;
	glm::vec3 ambient = intesitivity * glm::vec3(0.05f, 0.05f, 0.05f);
	glm::vec3 diffuse = intesitivity * glm::vec3(0.4f, 0.4f, 0.4f);
	glm::vec3 specular = intesitivity * glm::vec3(0.5f, 0.5f, 0.5f);
	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;

	object = new BaseObject();
	component = new LightComponent(glm::vec3(-0.2f, -1.0f, -0.3f), ambient, diffuse, specular);
	object->AddComponent(component);
	baseObjectCollection.push_back(object);

	object = new BaseObject();
	component = new LightComponent(ambient, diffuse, specular, constant, linear, quadratic);
	object->AddComponent(component);
	object->AddComponent(new RendererComponent());
	component = new TransformComponent(glm::vec3(0.0f, 0.0f, 0.0f));
	((TransformComponent*)component)->scale = 0.1;
	object->AddComponent(component);
	baseObjectCollection.push_back(object);
	//End Objects Initialization

	//Setting Context of every component
	for (BaseObject* baseObject : baseObjectCollection)
	{
		for (Component* component : baseObject->componentCollection)
		{
			component->baseObject = baseObject;
		}
	}

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

