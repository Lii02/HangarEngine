#include "Precompiled.h"
#include "FileSystem.h"

#define COMPLETE_PATH(str) (path + "\\" + str)

namespace {
	FileSystem* g_FileSystem;
}

void FileSystem::Init() {
	g_FileSystem = new FileSystem("./");
}

void FileSystem::DeInitialize() {
	delete g_FileSystem;
}

FileSystem*& FileSystem::Get() {
	return g_FileSystem;
}

FileSystem::FileSystem(std::string path) {
	this->path = path;
	Open();
}

FileSystem ::~FileSystem() {
	for (auto& group : subgroups) {
		delete group;
	}

	for (auto& file : files) {
		delete file;
	}
}

void FileSystem::Open() {
	for (std::filesystem::directory_entry entry : std::filesystem::directory_iterator(path)) {
		if (entry.is_directory()) {
			FileSystem* group = new FileSystem(entry.path().string());
			subgroups.push_back(group);
		} else if(entry.is_regular_file()) {
			std::string filepath = entry.path().string();
			File* file = new File(filepath, FileMode::READ, filepath.substr(path.length(), filepath.length()));
			files.push_back(file);
		}
	}
}

void FileSystem::CloseFiles() {
	for (auto& file : files) {
		file->Close();
	}
}

File* FileSystem::ImmSearchFile(std::string filename) {
	for (auto& file : files) {
		if (file->GetFilename() == filename)
			return file;
	}
	return nullptr;
}

FileSystem* FileSystem::ImmSearchFolder(std::string subgroupName) {
	for (auto& group : subgroups) {
		if (group->GetPath() == COMPLETE_PATH(subgroupName))
			return group;
	}
	return nullptr;
}

File* FileSystem::AddFile(std::string filename, FileMode mode) {
	File* file = new File(COMPLETE_PATH(filename), mode, filename);
	file->Open();
	files.push_back(file);
	return file;
}

FileSystem* FileSystem::AddSubgroup(std::string subgroupName) {
	std::string name = COMPLETE_PATH(subgroupName);
	std::filesystem::create_directory(name);
	FileSystem* group = new FileSystem(name);
	subgroups.push_back(group);
	return group;
}

void FileSystem::Refresh() {
	for (auto& group : subgroups) {
		delete group;
	}

	for (auto& file : files) {
		delete file;
	}

	Open();
}