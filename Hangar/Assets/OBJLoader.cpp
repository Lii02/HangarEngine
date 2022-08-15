#include "Precompiled.h"
#include "OBJLoader.h"
#include "../IO/File.h"
#include "../Math/MeshUtils.h"

std::vector<MeshData3D> OBJLoader::Load(File* file) {
	std::vector<MeshData3D> vec;
	if(!file->IsOpen())
		file->Open();
	std::istringstream input;
	input.str(file->ReadString(file->Length()));
	std::string line;

	struct TempMesh {
		std::string name;
		std::vector<Vector3> positions, normals;
		std::vector<Vector2> uvs;
		std::vector<int> positionIndices, normalIndices, uvIndices;
	};

	std::vector<TempMesh> temps;
	TempMesh* current;
	while (std::getline(input, line)) {
		float x, y, z;
		if (line.contains("v ")) {
			sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
			current->positions.push_back(Vector3(x, y, z));
		} else if (line.contains("vn ")) {
			sscanf(line.c_str(), "vn %f %f %f", &x, &y, &z);
			current->normals.push_back(Vector3(x, y, z));
		} else if (line.contains("vt ")) {
			sscanf(line.c_str(), "vt %f %f", &x, &y);
			current->uvs.push_back(Vector2(x, y));
		} else if (line.contains("f")) {
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			current->positionIndices.push_back(vertexIndex[0]);
			current->positionIndices.push_back(vertexIndex[1]);
			current->positionIndices.push_back(vertexIndex[2]);
			current->uvIndices.push_back(uvIndex[0]);
			current->uvIndices.push_back(uvIndex[1]);
			current->uvIndices.push_back(uvIndex[2]);
			current->normalIndices.push_back(normalIndex[0]);
			current->normalIndices.push_back(normalIndex[1]);
			current->normalIndices.push_back(normalIndex[2]);
		} else if (line.contains("o ")) {
			char name[16];
			sscanf(line.c_str(), "o %s", name);
			temps.push_back(TempMesh());
			current = &temps.back();
			current->name = name;
		} else if (line.contains("mtllib")) {
			
		} else if (line.contains("usemtl")) {

		}
	}

	for (auto& temp : temps) {
		MeshData3D mesh;
		mesh.name = temp.name;
		for (size_t i = 0; i < temp.positionIndices.size(); i++) {
			StandardVertex3D vertex;
			mesh.indices.push_back(i);
			vertex.position = temp.positions[temp.positionIndices[i] - 1];
			vertex.uv = temp.uvs[temp.uvIndices[i] - 1];
			vertex.normal = temp.normals[temp.normalIndices[i] - 1];
			mesh.vertices.push_back(vertex);
		}
		MeshUtils::Compactify(mesh);
		vec.push_back(mesh);
	}

	return vec;
}