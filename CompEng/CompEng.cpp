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
#include "colliderComponent.h"
#include "SphereCollider.h"

//User Scripts
#include "myTestScipt.h"

extern std::vector<BaseObject*> baseObjectCollection;

std::vector<Master*> masterCollection;	//LIST OF ALL MASTERS
std::vector<BaseObject*> baseObjectCollection;
std::vector<MeshComponent*> modelCollection;
RendererMaster* rendererMaster = new RendererMaster();

int main()
{
	//Masters Initialization
	masterCollection.push_back(rendererMaster);
	masterCollection.push_back(new ModelMaster());
	masterCollection.push_back(new UserScriptMaster());

	//Declaring Models

	//Light Values
	float intesitivity = 3.0f;
	glm::vec3 ambient = intesitivity * glm::vec3(0.05f, 0.05f, 0.05f);
	glm::vec3 diffuse = intesitivity * glm::vec3(0.4f, 0.4f, 0.4f);
	glm::vec3 specular = intesitivity * glm::vec3(0.5f, 0.5f, 0.5f);
	float constant = 1.0f;
	float linear = 0.09f;
	float quadratic = 0.032f;

	//Adding TestObjects
	baseObjectCollection.reserve(1024);
	BaseObject* object;
	Component* component;
	TransformComponent* transform;
	MeshComponent* mesh;

	object = new BaseObject("Car");
	object->AddComponent(new MeshComponent("D:/Projekty2/VS/CompEng/CompEng/res/car/car.obj"));
	transform = new TransformComponent(glm::vec3(12.5f, 0.0f, 0.3f));
	transform->scale = glm::vec3(0.1);
	object->AddComponent(transform);
	object->AddComponent(new MyTestScript());
	baseObjectCollection.push_back(object);

	object = new BaseObject("Triangle");
	mesh = new MeshComponent("D:/Projekty2/VS/CompEng/CompEng/res/triangle/triangle.obj");
	mesh->diffuseColor = glm::vec3(0.6, 0.6, 0.6);
	mesh->specularColor = glm::vec3(0.7, 0.7, 0.7);
	object->AddComponent(mesh);
	transform = new TransformComponent(glm::vec3(10.0f, 0.0f, 0.0f));
	transform->scale = glm::vec3(0.3);
	object->AddComponent(transform);
	baseObjectCollection.push_back(object);

	/*object = new BaseObject("Ground");
	mesh = new MeshComponent("D:/Projekty2/VS/CompEng/CompEng/res/plane/plane.obj");
	mesh->diffuseColor = glm::vec3(0.6, 0.2, 0.2);
	mesh->specularColor = glm::vec3(0.7, 0.3, 0.3);
	object->AddComponent(mesh);
	transform = new TransformComponent(glm::vec3(0.0f, 0.0f, 0.0f));
	transform->scale = 10;
	object->AddComponent(transform);
	baseObjectCollection.push_back(object);*/

	object = new BaseObject("Cube1");
	transform = new TransformComponent(glm::vec3(0.2f, 1.0f, 0.0f));
	transform->scale = glm::vec3(0.8f, 0.8, 0.8);
	object->AddComponent(transform);
	mesh = new MeshComponent("D:/Projekty2/VS/CompEng/CompEng/res/cube/cube.obj");
	//mesh = new MeshComponent("D:/Projekty2/VS/CompEng/CompEng/res/sphere/sphere.obj");
	mesh->diffuseColor = glm::vec3(0.2, 0.6, 0.2);
	mesh->specularColor = glm::vec3(0.3, 0.7, 0.3);
	object->AddComponent(mesh);
	baseObjectCollection.push_back(object);
	object->AddComponent(new ColliderComponent());
	//object->AddComponent(new SphereCollider());

	object = new BaseObject("Cube2");
	transform = new TransformComponent(glm::vec3(0.0f, -4.0f, 0.0f));
	transform->scale = glm::vec3(38.8, 0.5, 10.0);
	object->AddComponent(transform);
	mesh = new MeshComponent("D:/Projekty2/VS/CompEng/CompEng/res/cube/cube.obj");
	mesh->diffuseColor = glm::vec3(0.6, 0.3, 0.2);
	mesh->specularColor = glm::vec3(0.9, 0.4, 0.3);
	object->AddComponent(mesh);
	//object->AddComponent(new RigidbodyComponent());
	object->AddComponent(new ColliderComponent());
	//object->AddComponent(new RigidbodyComponent());
	baseObjectCollection.push_back(object);

	object = new BaseObject("Cube3");
	mesh = new MeshComponent("D:/Projekty2/VS/CompEng/CompEng/res/cube/cube.obj");
	mesh->diffuseColor = glm::vec3(0.4, 0.3, 0.2);
	mesh->specularColor = glm::vec3(0.9, 0.4, 0.3);
	object->AddComponent(mesh);
	transform = new TransformComponent(glm::vec3(10.5f, 1.0f, 0.0f));
	transform->scale = glm::vec3(0.1, 0.1, 0.4);
	object->AddComponent(transform);
	baseObjectCollection.push_back(object);

	object = new BaseObject("Sphere0");
	mesh = new MeshComponent("D:/Projekty2/VS/CompEng/CompEng/res/sphere/sphere.obj");
	mesh->diffuseColor = glm::vec3(0.7, 0.7, 0.7);
	mesh->specularColor = glm::vec3(1, 1, 1);
	object->AddComponent(mesh);
	transform = new TransformComponent(glm::vec3(0.0f, -3.0f, 2.0f));
	transform->scale = glm::vec3(0.2);
	object->AddComponent(transform);
	component = new LightComponent(ambient, diffuse, specular, constant, linear, quadratic);
	object->AddComponent(component);
	baseObjectCollection.push_back(object);

	object = new BaseObject("Sphere1");
	mesh = new MeshComponent("D:/Projekty2/VS/CompEng/CompEng/res/sphere/sphere.obj");
	mesh->diffuseColor = glm::vec3(0.7, 0.7, 0.7);
	mesh->specularColor = glm::vec3(1, 1, 1);
	object->AddComponent(mesh);
	transform = new TransformComponent(glm::vec3(-6.0f, 0.0f, 0.0f));
	transform->scale = glm::vec3(0.2);
	object->AddComponent(transform);
	//component = new LightComponent(ambient, diffuse, specular, constant, linear, quadratic);
	//object->AddComponent(component);
	baseObjectCollection.push_back(object);

	object = new BaseObject("Sphere2");
	mesh = new MeshComponent("D:/Projekty2/VS/CompEng/CompEng/res/sphere/sphere.obj");
	mesh->diffuseColor = glm::vec3(0.7, 0.7, 0.7);
	mesh->specularColor = glm::vec3(1, 1, 1);
	object->AddComponent(mesh);
	transform = new TransformComponent(glm::vec3(0.0f, 2.2f, 0.0f));
	transform->scale = glm::vec3(0.2);
	object->AddComponent(transform);
	//component = new LightComponent(ambient, diffuse, specular, constant, linear, quadratic);
	//object->AddComponent(component);
	baseObjectCollection.push_back(object);

	object = new BaseObject("Sphere3");
	mesh = new MeshComponent("D:/Projekty2/VS/CompEng/CompEng/res/sphere/sphere.obj");
	mesh->diffuseColor = glm::vec3(0.7, 0.7, 0.7);
	mesh->specularColor = glm::vec3(1, 1, 1);
	object->AddComponent(mesh);
	transform = new TransformComponent(glm::vec3(-6.0f, 0.0f, 0.0f));
	transform->scale = glm::vec3(0.2);
	object->AddComponent(transform);
	//component = new LightComponent(ambient, diffuse, specular, constant, linear, quadratic);
	//object->AddComponent(component);
	baseObjectCollection.push_back(object);

	object = new BaseObject("Sphere4");
	mesh = new MeshComponent("D:/Projekty2/VS/CompEng/CompEng/res/sphere/sphere.obj");
	mesh->diffuseColor = glm::vec3(0.7, 0.7, 0.7);
	mesh->specularColor = glm::vec3(1, 1, 1);
	object->AddComponent(mesh);
	transform = new TransformComponent(glm::vec3(-6.0f, 0.0f, 0.0f));
	transform->scale = glm::vec3(0.2);
	object->AddComponent(transform);
	//component = new LightComponent(ambient, diffuse, specular, constant, linear, quadratic);
	//object->AddComponent(component);
	baseObjectCollection.push_back(object);

	object = new BaseObject("Sphere5");
	mesh = new MeshComponent("D:/Projekty2/VS/CompEng/CompEng/res/sphere/sphere.obj");
	mesh->diffuseColor = glm::vec3(0.7, 0.7, 0.7);
	mesh->specularColor = glm::vec3(1, 1, 1);
	object->AddComponent(mesh);
	transform = new TransformComponent(glm::vec3(-6.0f, 0.0f, 0.0f));
	transform->scale = glm::vec3(0.2);
	object->AddComponent(transform);
	//component = new LightComponent(ambient, diffuse, specular, constant, linear, quadratic);
	//object->AddComponent(component);
	baseObjectCollection.push_back(object);

	object = new BaseObject("Sphere6");
	mesh = new MeshComponent("D:/Projekty2/VS/CompEng/CompEng/res/sphere/sphere.obj");
	mesh->diffuseColor = glm::vec3(0.7, 0.7, 0.7);
	mesh->specularColor = glm::vec3(1, 1, 1);
	object->AddComponent(mesh);
	transform = new TransformComponent(glm::vec3(-6.0f, 0.0f, 0.0f));
	transform->scale = glm::vec3(0.2);
	object->AddComponent(transform);
	//component = new LightComponent(ambient, diffuse, specular, constant, linear, quadratic);
	//object->AddComponent(component);
	baseObjectCollection.push_back(object);

	object = new BaseObject("Sphere7");
	mesh = new MeshComponent("D:/Projekty2/VS/CompEng/CompEng/res/sphere/sphere.obj");
	mesh->diffuseColor = glm::vec3(0.7, 0.7, 0.7);
	mesh->specularColor = glm::vec3(1, 1, 1);
	object->AddComponent(mesh);
	transform = new TransformComponent(glm::vec3(-6.0f, 0.0f, 0.0f));
	transform->scale = glm::vec3(0.2);
	object->AddComponent(transform);
	//component = new LightComponent(ambient, diffuse, specular, constant, linear, quadratic);
	//object->AddComponent(component);
	baseObjectCollection.push_back(object);

	object = new BaseObject("Sphere8");
	mesh = new MeshComponent("D:/Projekty2/VS/CompEng/CompEng/res/sphere/sphere.obj");
	mesh->diffuseColor = glm::vec3(0.7, 0.7, 0.7);
	mesh->specularColor = glm::vec3(1, 1, 1);
	object->AddComponent(mesh);
	transform = new TransformComponent(glm::vec3(-6.0f, 0.0f, 0.0f));
	transform->scale = glm::vec3(0.2);
	object->AddComponent(transform);
	//component = new LightComponent(ambient, diffuse, specular, constant, linear, quadratic);
	//object->AddComponent(component);
	baseObjectCollection.push_back(object);

	object = new BaseObject("Sun");
	component = new LightComponent(glm::vec3(-0.2f, -1.0f, -0.3f), ambient, diffuse, specular);
	object->AddComponent(component);
	baseObjectCollection.push_back(object);


	//End Objects Initialization

	//Setting Context of every component
	/*for (BaseObject* baseObject : baseObjectCollection)
	{
		for (Component* component : baseObject->componentCollection)
		{
			component->baseObject = baseObject;
		}
	}*/

	//CALL INITIALIZE() ON EACH MASTER
	for (Master* m : masterCollection)
	{
		m->Initialize();
	}

	//MAIN LOOP
	while (!rendererMaster->closeProgramFlag)
	{
		//CALL UPDATE() ON EACH MASTER
		for (Master* m : masterCollection)
		{
			m->Update();
		}
	}

	for (Master* m : masterCollection)
	{
		delete m;
	}

	for (BaseObject* baseObject : baseObjectCollection)
	{
		delete baseObject;
	}
	system("pause");
    return 0;
}

