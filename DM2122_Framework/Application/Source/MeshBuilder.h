#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"
#include "LoadOBJ.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string &meshName, Color color, float lengthX, float lengthY);
	static Mesh* GenerateCube(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateCircle(const std::string &meshName, Color color, unsigned numSlices = 10, float radius = 1.f);
	static Mesh* GenerateOctagon(const std::string &meshName, Color color, unsigned numSlices, float radius, float height);
	static Mesh* GenerateRing(const std::string &meshName, Color color, unsigned numSlices = 10, float radius = 2.f, float innerRadius = 1.0);
	static Mesh* GenerateHemisphere(const std::string &meshName, Color color, unsigned numSlices, unsigned numStacks, float radius = 1.f);
	static Mesh* GenerateSphere(const std::string &meshName, Color color, unsigned numSlices, unsigned numStacks, float radius = 1.f);
	static Mesh* GenerateCylinder(const std::string &meshName, Color color, unsigned numSlices, float radius, float height);
	static Mesh* GenerateCone(const std::string &meshName, Color color, unsigned numSlices, float radius, float height);
	static Mesh* GenerateTorus(const std::string &meshName, Color color, unsigned numSlices = 36, unsigned numStacks = 36, float outerR = 1.f, float innerR = 0.5f);
	static Mesh* GenerateOBJ(const std::string &meshName, const std::string &file_path);
	static Mesh* GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol);
};

#endif