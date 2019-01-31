#ifndef FIREBALLMODEL_H
#define FIREBALLMODEL_H

#include <vector> 
#include "MMath.h"
#include "Mesh.h"
#include "Entity.h"

namespace GAME {

	using namespace MATH;

class FireballModel : Model {
protected:

	class Shader *shader;
	Matrix4 modelMatrix;
	std::vector<Mesh*> meshes;

public:
	FireballModel();
	FireballModel(const Vec3 _pos, const Vec3 _orientation);
	FireballModel(const FireballModel&) = delete;
	FireballModel(FireballModel&&) = delete;
	FireballModel& operator = (const FireballModel&) = delete;
	FireballModel& operator = (FireballModel&&) = delete;

	virtual ~FireballModel();

	void setPos(const Vec3& pos_) override;
	void setOrientation(const Vec3& orienration_) override;

	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Render() const;
	virtual void Update(const float deltaTime);

	virtual bool LoadMesh(const char* filename);


protected:
	float elapsedTime;

	GLuint noiseID;
	GLuint noise;
	void updateModelMatrix();
};
} /// end of namespace

#endif //!!FIREBALLMODEL_H