#include <GL/glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "MMath.h"
#include "Window.h"
#include "Shader.h"
#include "Scene1.h"
#include "SceneEnvironment.h"
#include "Trackball.h"


#include "ObjLoader.h"

using namespace GAME;
using namespace MATH;


Scene1::Scene1(Window& windowRef):Scene(windowRef) {

}


bool Scene1::OnCreate() {
	
	camera = nullptr;
	
	/// Load Assets: as needed 
	if (addModel("sphere.obj") == false) {
		return false;
	}

	fireskull = new Model(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	fireskull->OnCreateFireball();
	fireskull->setPos(Vec3(2.0f, 0.0f, 0.0f));

	if (fireskull->LoadMesh("sphere.obj") == false) {
		return false;
	}


	toonKatie = new Model(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	toonKatie->OnCreateToon();
	toonKatie->setPos(Vec3(-2.0f, 0.0f, 0.0f));

	if (toonKatie->LoadMesh("sphere.obj") == false) {
		return false;
	}

	earthBall = new Model(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	earthBall->OnCreateEarth();
	earthBall->setPos(Vec3(-4.5f, 0.0f, 0.0f));

	if (earthBall->LoadMesh("sphere.obj") == false) {
		return false;
	}

	snowBall = new Model(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	snowBall->OnCreateSnow();
	snowBall->setPos(Vec3(0.0f, 2.5f, 0.0f));

	if (snowBall->LoadMesh("sphere.obj") == false) {
		return false;
	}

	

	/// Create a shader with attributes
	SceneEnvironment::getInstance()->setLight(Vec3(0.0f, 3.0f, 7.0f));

	OnResize(windowPtr->getWidth(), windowPtr->getHeight());
	return true;

}


bool GAME::Scene1::addModel(const char* filename)
{

	skyBox = new SkyBox("posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg");
	skyBox->OnCreate();


	skull = new Model(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	skull->OnCreateWater();




	if (skull->LoadMesh(filename) == false) {
		return false;
	}




	
	/*models.push_back(new SkyBox("posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg"));
	models.push_back(new Model(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f)));
	models[models.size() - 1]->OnCreate();

	if (models[models.size() - 1]->LoadMesh(filename) == false) {
		return false;
	}
	*/
	return true;
}

void Scene1::OnResize(int w_, int h_){
	windowPtr->setWindowSize(w_,h_);
	glViewport(0,0,windowPtr->getWidth(),windowPtr->getHeight());
	if (camera) delete camera;
	camera = new Camera(w_, h_, Vec3(0.0f, 0.0f, 10.0f));
	Camera::currentCamera = camera;
	Trackball::getInstance()->setWindowDimensions(windowPtr->getWidth(), windowPtr->getHeight());
}

void Scene1::Update(const float deltaTime) {
	skull->Update(deltaTime);
	fireskull->Update(deltaTime);
	toonKatie->Update(deltaTime);
	earthBall->Update(deltaTime);
	snowBall->Update(deltaTime);
	skyBox->Update(deltaTime);
	/*for (Model* model : models) {
		model->Update(deltaTime);
	}*/

}

void Scene1::Render() const{

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	skyBox->Render(camera->getProjectionMatrix(), camera->getViewMatrix()*Trackball::getInstance()->getMatrix4(), Matrix4(1.0f));
	skull->Render();
	fireskull->Render();
	toonKatie->Render();
	earthBall->Render();
	snowBall->Render();
	/// Draw your scene here
	/*for (Model* model : models) {
		model->Render();
	}*/
	SDL_GL_SwapWindow(windowPtr->getSDLWindow());
	
}

void Scene1::HandleEvents(const SDL_Event& SDLEvent){
	if (SDLEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN) {
		Trackball::getInstance()->onLeftMouseDown(SDLEvent.button.x, SDLEvent.button.y);
	}else if(SDLEvent.type == SDL_EventType::SDL_MOUSEBUTTONUP){
		Trackball::getInstance()->onLeftMouseUp(SDLEvent.button.x, SDLEvent.button.y);
	}else if (SDLEvent.type == SDL_EventType::SDL_MOUSEMOTION && 
		SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		Trackball::getInstance()->onMouseMove(SDLEvent.button.x, SDLEvent.button.y);
	}
		
}

Scene1::~Scene1() {
	OnDestroy();
}

void Scene1::OnDestroy() {
	/// Cleanup Assets
	if (camera) delete camera;
	for (Model* model : models) {
		if (model) delete model;
	}
}
