#include "precompiled.h"
#include "mesh_utils.h"
#include "containers/list.h"

void MeshUtils::compactify(MeshData3D& mesh) {
	List<StandardVertex3D> compacted_vertex_list;
	List<int> indices_list;

	int compacted_index = 0;

	for (StandardVertex3D vert_simple_mesh : mesh.vertices) {
		bool found = false;
		int found_index = 0;
		for (StandardVertex3D vert_compacted_list : compacted_vertex_list) {
			if (vert_simple_mesh.position.x == vert_compacted_list.position.x &&
				vert_simple_mesh.position.y == vert_compacted_list.position.y &&
				vert_simple_mesh.position.z == vert_compacted_list.position.z &&
				vert_simple_mesh.normal.x == vert_compacted_list.normal.x &&
				vert_simple_mesh.normal.y == vert_compacted_list.normal.y &&
				vert_simple_mesh.normal.z == vert_compacted_list.normal.z &&
				vert_simple_mesh.uv.x == vert_compacted_list.uv.x &&
				vert_simple_mesh.uv.y == vert_compacted_list.uv.y) {
				indices_list.push(found_index);
				found = true;
				break;
			}
			found_index++;
		}

		if (!found) {
			compacted_vertex_list.push(vert_simple_mesh);
			indices_list.push(compacted_index);
			compacted_index++;
		}
	}

	mesh.indices = indices_list;
	mesh.vertices = compacted_vertex_list;
}