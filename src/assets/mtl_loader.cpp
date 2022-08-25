#include "Precompiled.h"
#include "MTLLoader.h"
#include <IO/File.h>
#include <Debug/Logger.h>

std::unordered_map<std::string, Material*> MTLLoader::Load(File* file) {
	std::unordered_map<std::string, Material*> vec;
	if (!file->ReOpen()) {
		Logger::Error("Failed to load material file: " + file->GetPath());
		delete file;
		return vec;
	}
	std::istringstream ss;
	ss.str(file->ReadString(file->Length()));
	std::string line;
	Material* current;
	while (std::getline(ss, line)) {
		float r, g, b;
		if (line.contains("Kd")) {
			sscanf(line.c_str(), "Kd %f %f %f", &r, &g, &b);
			current->SetDiffuse(MaterialAttribute<Color>(Color(r, g, b), MaterialAttributeType::COLOR_VALUE));
		} else if (line.contains("Ks")) {
			sscanf(line.c_str(), "Ks %f %f %f", &r, &g, &b);
			current->SetSpecular(MaterialAttribute<Color>(Color(r, g, b), MaterialAttributeType::COLOR_VALUE));
		} else if (line.contains("Ns")) {
			sscanf(line.c_str(), "Ns %f", &r);
			current->SetSpecularExponent(r);
		} else if (line.contains("newmtl")) {
			char name[16];
			sscanf(line.c_str(), "newmtl %s", name);
			Material* mat = new Material(name);
			vec.emplace(std::make_pair(name, mat));
			current = mat;
		}
	}
	Logger::Confirmation("Loaded " + file->GetFilename() + " material file");

	for (auto& [name, material] : vec) {
		material->Update();
	}

	file->Rewind();
	return vec;
}