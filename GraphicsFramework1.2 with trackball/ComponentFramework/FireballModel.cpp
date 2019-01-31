#include "Model.h"
#include "Shader.h"
#include "ObjLoader.h"
#include "Camera.h"
#include "SceneEnvironment.h"
#include "Trackball.h"
#include "Noise.h"
#include "FireballModel.h"

namespace GAME {



	FireballModel::FireballModel()
	{
	}

	FireballModel::FireballModel(const Vec3 pos_, const Vec3 orientation_)
	{
		pos = pos_;
		orientation = orientation_;
		shader = nullptr;

	}

	FireballModel::~FireballModel()
	{
		OnDestroy();
	}

	void FireballModel::setPos(const Vec3 & pos_)
	{
		Entity::setPos(pos_);
		updateModelMatrix();
	}

	void FireballModel::setOrientation(const Vec3 & orienration_)
	{
		Entity::setOrientation(orienration_);
		updateModelMatrix();
	}

	bool FireballModel::OnCreate()
	{
		shader = new Shader("fireballVert.glsl", "fireballFrag.glsl", 3, 0, "vVertex", 1, "vNormal", 2, "texCoords");

		elapsedTime = 0.0f;
		noise = CreateNoise3D();
		noiseID = glGetUniformLocation(shader->getProgram(), "noiseTexture");
		glUniform1i(noise, noiseID);
		return true;
	}

	void FireballModel::OnDestroy()
	{
		if (shader) delete shader;
	}

	void FireballModel::Render() const
	{
		GLint projectionMatrixID = glGetUniformLocation(shader->getProgram(), "projectionMatrix");
		GLint viewMatrixID = glGetUniformLocation(shader->getProgram(), "viewMatrix");
		GLint modelMatrixID = glGetUniformLocation(shader->getProgram(), "modelMatrix");
		GLint normalMatrixID = glGetUniformLocation(shader->getProgram(), "normalMatrix");
		GLint lightPosID = glGetUniformLocation(shader->getProgram(), "lightPos");
		GLint elapsedTimeID = glGetUniformLocation(shader->getProgram(), "elapsedTime");

		glUseProgram(shader->getProgram());

		glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, Camera::currentCamera->getProjectionMatrix());
		glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, Camera::currentCamera->getViewMatrix());
		glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, modelMatrix * Trackball::getInstance()->getMatrix4());

		/// Assigning the 4x4 modelMatrix to the 3x3 normalMatrix 
		/// copies just the upper 3x3 of the modelMatrix
		Matrix3 normalMatrix = modelMatrix * Trackball::getInstance()->getMatrix4();
		glUniformMatrix3fv(normalMatrixID, 1, GL_FALSE, normalMatrix);

		glUniform3fv(lightPosID, 1, SceneEnvironment::getInstance()->getLight());
		glUniform1f(elapsedTimeID, elapsedTime);
		//I thought enabling would make it appear before the skybox but maybe the camera and object are ontop of eachother
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		for (Mesh* mesh : meshes) {
			mesh->Render();
		}

	}

	void FireballModel::Update(const float deltaTime)
	{
		elapsedTime += deltaTime;
	}

	bool FireballModel::LoadMesh(const char * filename)
	{
		if (ObjLoader::loadOBJ(filename) == false) {
			return false;
		}
		/// Get the data out of the ObjLoader and into our own mesh
		meshes.push_back(new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords));
		return true;
	}

	void FireballModel::updateModelMatrix()
	{
		modelMatrix = MMath::translate(pos);
	}

}

