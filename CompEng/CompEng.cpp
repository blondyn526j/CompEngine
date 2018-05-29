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
#include "meshComponent.h"
#include "modelMaster.h"
#include "model.h"
#include "userScriptMaster.h"

//User Scripts
#include "myTestScipt.h"

extern std::vector<BaseObject*> baseObjectCollection;

std::vector<Master*> masterCollection;	//LIST OF ALL MASTERS
std::vector<BaseObject*> baseObjectCollection;
std::vector<MeshComponent*> modelCollection;
bool closeProgramFlag = false;	//SHOULD PROGRAM EXIT ITS MAIN LOOP?

int main()
{
	//Objects Initialization
	masterCollection.push_back(new RendererMaster());
	masterCollection.push_back(new ModelMaster());
	masterCollection.push_back(new UserScriptMaster());

	//Declaring Models
	Model* nanosuitModel = new Model("D:/Projekty2/VS/CompEng/CompEng/res/nanosuit/nanosuit.obj");
	Model* carModel = new Model("D:/Projekty2/VS/CompEng/CompEng/res/car/car.obj");
	Model* ponyModel = new Model("D:/Projekty2/VS/CompEng/CompEng/res/rd/rainbow_dash_pose_01_all-in-one.obj");

	//Light Values
	float intesitivity = 3.0f;
	glm::vec3 ambient = intesitivity * glm::vec3(0.05f, 0.05f, 0.05f);
	glm::vec3 diffuse = intesitivity * glm::vec3(0.4f, 0.4f, 0.4f);
	glm::vec3 specular = intesitivity * glm::vec3(0.5f, 0.5f, 0.5f);
	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;

	//Adding TestObject
	baseObjectCollection.reserve(1024);
	BaseObject* object;
	Component* component;
	TransformComponent* transform;

	object = new BaseObject("Car");
	object->AddComponent(carModel);
	transform = new TransformComponent(glm::vec3(2.5f, 0.0f, 0.0f));
	transform->scale = 0.1;
	object->AddComponent(transform);
	component = new LightComponent(ambient, diffuse, specular, constant, linear, quadratic);
	object->AddComponent(component);
	object->AddComponent(new MyTestScript());
	baseObjectCollection.push_back(object);

	object = new BaseObject("Pony");
	object->AddComponent(ponyModel);
	transform = new TransformComponent(glm::vec3(0.0f, 0.0f, -0.7f));
	transform->scale = 0.1;
	object->AddComponent(transform);
	baseObjectCollection.push_back(object);

	object = new BaseObject("Sun");
	component = new LightComponent(glm::vec3(-0.2f, -1.0f, -0.3f), ambient, diffuse, specular);
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

