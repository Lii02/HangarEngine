#include "Precompiled.h"
#include "OBJLoader.h"
#include "../IO/File.h"
#include "../Math/MeshUtils.h"
#include <Debug/Logger.h>

std::vector<MeshData3D> OBJLoader::Load(File* file) {
	std::vector<MeshData3D> vec;
	if (!file->ReOpen()) {
		Logger::Error("Failed to load 3D model file: " + file->GetPath());
		delete file;
		return vec;
	}
	std::istringstream input;
	input.str(file->ReadString(file->Length()));
	std::string line;

	struct TempMesh {
		std::string name;
		int first;
		int count;
	};

	std::vector<Vector3> positions, normals;
	std::vector<Vector2> uvs;
	std::vector<int> positionIndices, normalIndices, uvIndices;
	std::vector<TempMesh> temps;
	TempMesh* current;
	int index = 0;
	while (std::getline(input, line)) {
		float x, y, z;
		if (line.contains("v ")) {
			sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
			positions.push_back(Vector3(x, y, z));
		} else if (line.contains("vn ")) {
			sscanf(line.c_str(), "vn %f %f %f", &x, &y, &z);
			normals.push_back(Vector3(x, y, z));
		} else if (line.contains("vt ")) {
			sscanf(line.c_str(), "vt %f %f", &x, &y);
			uvs.push_back(Vector2(x, y));
		} else if (line.contains("f ")) {
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			positionIndices.push_back(vertexIndex[0]);
			positionIndices.push_back(vertexIndex[1]);
			positionIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
			current->count += 3;
			index += 3;
		} else if (line.contains("o ")) {
			char name[16];
			sscanf(line.c_str(), "o %s", name);
			temps.push_back(TempMesh());
			current = &temps.back();
			current->name = name;
			current->first = index;
		}
	}
	file->Rewind();
	Logger::Confirmation("Loaded " + file->GetFilename() + " mesh file");

	for (auto& temp : temps) {
		MeshData3D mesh;
		mesh.name = temp.name;
		for (size_t i = 0; i < temp.count; i++) {
			StandardVertex3D vertex;
			int realIndex = temp.first + i;
			mesh.indices.push_back(i);
			vertex.position = positions[positionIndices[realIndex] - 1];
			vertex.uv = uvs[uvIndices[realIndex] - 1];
			vertex.normal = normals[normalIndices[realIndex] - 1];
			mesh.vertices.push_back(vertex);
		}
		size_t preNumVertices = mesh.vertices.size();
		MeshUtils::Compactify(mesh);
		size_t postNumVertices = mesh.vertices.size();
		Logger::Message("Compacted mesh: " + mesh.name + " from " + std::to_string(preNumVertices) + " vertices to " + std::to_string(postNumVertices) + " vertices");
		vec.push_back(mesh);
	}

	return vec;
}