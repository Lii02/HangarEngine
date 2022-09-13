#include "precompiled.h"
#include "file_system.h"
#include <filesystem>

#define COMPLETE_PATH(str) (path + "/" + str)

namespace {
	FileSystem* g_file_system;
}

void FileSystem::initialize() {
	g_file_system = new FileSystem("./");
}

void FileSystem::deinitialize() {
	delete g_file_system;
}

FileSystem*& FileSystem::get() {
	return g_file_system;
}

FileSystem::FileSystem(AString _fs_path) {
	path = _fs_path;
	open();
}

FileSystem ::~FileSystem() {
	for (auto& folder : folders) {
		delete folder;
	}

	for (auto& file : files) {
		delete file;
	}
}

void FileSystem::open() {
	for (std::filesystem::directory_entry entry : std::filesystem::directory_iterator(path.ptr())) {
		AString filepath_string = entry.path().string().c_str();
		if (entry.is_directory()) {
			FileSystem* folder = new FileSystem(filepath_string);
			folders.push(folder);
		} else if(entry.is_regular_file()) {
			AString filename = filepath_string.substring(path.get_length() + 1, filepath_string.get_length());
			File* file = new File(filepath_string, FileMode::READ, filename);
			files.push(file);
		}
	}
}

void FileSystem::close_files() {
	for (auto& file : files) {
		file->close();
	}
}

File* FileSystem::immediate_search_file(AString filename) {
	for (auto& file : files) {
		if (file->get_filename() == filename)
			return file;
	}
	// Create a temporary file, make sure to free memory after use
	File* file = new File(filename, FileMode::READ, filename);
	return file;
}

FileSystem* FileSystem::immediate_search_folder(AString folder_name) {
	for (auto& group : folders) {
		if (group->GetPath() == COMPLETE_PATH(folder_name))
			return group;
	}
	return nullptr;
}

File* FileSystem::add_file(AString filename, FileMode mode) {
	File* file = new File(COMPLETE_PATH(filename), mode, filename);
	file->open();
	files.push(file);
	return file;
}

FileSystem* FileSystem::add_folder(AString folder_name) {
	AString name = COMPLETE_PATH(folder_name);
	std::filesystem::create_directory(name.ptr());
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