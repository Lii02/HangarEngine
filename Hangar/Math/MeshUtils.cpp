#include "Precompiled.h"
#include "MeshUtils.h"

void MeshUtils::Compactify(MeshData3D& mesh) {
	std::vector<StandardVertex3D> compactedVertexList;
	std::vector<int> indicesList;

	int compactedIndex = 0;

	for (StandardVertex3D vertSimpleMesh : mesh.vertices) {
		bool found = false;
		int foundIndex = 0;
		for (StandardVertex3D vertCompactedList : compactedVertexList) {
			if (vertSimpleMesh.position.x == vertCompactedList.position.x &&
				vertSimpleMesh.position.y == vertCompactedList.position.y &&
				vertSimpleMesh.position.z == vertCompactedList.position.z &&
				vertSimpleMesh.normal.x == vertCompactedList.normal.x &&
				vertSimpleMesh.normal.y == vertCompactedList.normal.y &&
				vertSimpleMesh.normal.z == vertCompactedList.normal.z &&
				vertSimpleMesh.uv.x == vertCompactedList.uv.x &&
				vertSimpleMesh.uv.y == vertCompactedList.uv.y) {
				indicesList.push_back(foundIndex);
				found = true;
				break;
			}
			foundIndex++;
		}

		if (!found) {
			compactedVertexList.push_back(vertSimpleMesh);
			indicesList.push_back(compactedIndex);
			compactedIndex++;
		}
	}

	mesh.indices = indicesList;
	mesh.vertices = compactedVertexList;
}