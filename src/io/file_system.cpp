#include "precompiled.h"
#include "file_system.h"

#define COMPLETE_PATH(str) (path + "\\" + str)

namespace {
	FileSystem* g_FileSystem;
}

void FileSystem::initialize() {
	g_FileSystem = new FileSystem("./");
}

void FileSystem::deinitialize() {
	delete g_FileSystem;
}

FileSystem*& FileSystem::get() {
	return g_FileSystem;
}

FileSystem::FileSystem(std::string _fs_path) {
	path = _fs_path;
	open();
}

FileSystem ::~FileSystem() {
	for (auto& group : folders) {
		delete group;
	}

	for (auto& file : files) {
		delete file;
	}
}

void FileSystem::open() {
	for (std::filesystem::directory_entry entry : std::filesystem::directory_iterator(path)) {
		if (entry.is_directory()) {
			FileSystem* group = new FileSystem(entry.path().string());
			folders.push(group);
		} else if(entry.is_regular_file()) {
			std::string filepath = entry.path().string();
			File* file = new File(filepath, FileMode::READ, filepath.substr(path.length(), filepath.length()));
			files.push(file);
		}
	}
}

void FileSystem::close_files() {
	for (auto& file : files) {
		file->close();
	}
}

File* FileSystem::immediate_search_file(std::string filename) {
	for (auto& file : files) {
		if (file->get_filename() == filename)
			return file;
	}
	// Create a temporary file, make sure to free memory after use
	File* file = new File(filename, FileMode::READ, filename);
	return file;
}

FileSystem* FileSystem::immediate_search_folder(std::string folder_name) {
	for (auto& group : folders) {
		if (group->GetPath() == COMPLETE_PATH(folder_name))
			return group;
	}
	return nullptr;
}

File* FileSystem::add_file(std::string filename, FileMode mode) {
	File* file = new File(COMPLETE_PATH(filename), mode, filename);
	file->open();
	files.push(file);
	return file;
}

FileSystem* FileSystem::add_folder(std::string folderName) {
	std::string name = COMPLETE_PATH(folderName);
	std::filesystem::create_directory(name);
	FileSystem* group = new FileSystem(name);
	folders.push(group);
	return group;
}

void FileSystem::refresh() {
	for (auto& group : folders) {
		delete group;
	}

	for (auto& file : files) {
		delete file;
	}

	open();
}