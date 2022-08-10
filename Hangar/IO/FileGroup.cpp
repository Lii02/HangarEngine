#include "Precompiled.h"
#include "FileGroup.h"

#define COMPLETE_PATH(str) (path + "\\" + str)

FileGroup::FileGroup(std::string path) {
	this->path = path;
	Open();
}

FileGroup::~FileGroup() {
	for (auto& group : subgroups) {
		delete group;
	}

	for (auto& file : files) {
		delete file;
	}
}

void FileGroup::Open() {
	for (std::filesystem::directory_entry entry : std::filesystem::directory_iterator(path)) {
		if (entry.is_directory()) {
			FileGroup* group = new FileGroup(entry.path().string());
			subgroups.push_back(group);
		} else if(entry.is_regular_file()) {
			std::string filepath = entry.path().string();
			File* file = new File(filepath, FileMode::READ, filepath.substr(path.length(), filepath.length()));
			file->Open();
			files.push_back(file);
		}
	}
}

void FileGroup::CloseFiles() {
	for (auto& file : files) {
		file->Close();
	}
}

File* FileGroup::ImmSearchFile(std::string filename) {
	for (auto& file : files) {
		if (file->GetFilename() == filename)
			return file;
	}
	return nullptr;
}

FileGroup* FileGroup::ImmSearchFolder(std::string subgroupName) {
	for (auto& group : subgroups) {
		if (group->GetPath() == COMPLETE_PATH(subgroupName))
			return group;
	}
	return nullptr;
}

File* FileGroup::AddFile(std::string filename, FileMode mode) {
	File* file = new File(COMPLETE_PATH(filename), mode, filename);
	file->Open();
	files.push_back(file);
	return file;
}

FileGroup* FileGroup::AddSubgroup(std::string subgroupName) {
	std::string name = COMPLETE_PATH(subgroupName);
	std::filesystem::create_directory(name);
	FileGroup* group = new FileGroup(name);
	subgroups.push_back(group);
	return group;
}