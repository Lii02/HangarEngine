#ifndef FILEGROUP_H
#define FILEGROUP_H
#include "File.h"

class FileSystem {
private:
	std::string path;
	std::list<File*> files;
	std::vector<FileSystem*> folders;
public:
	static void initialize();
	static void deinitialize();
	static FileSystem*& get();

	FileSystem(std::string _fs_path);
	~FileSystem();
	FileSystem(const FileSystem&) = delete;

	void open();
	void close_files();
	File* immediate_search_file(std::string filename);
	FileSystem* immediate_search_folder(std::string folder_name);
	File* add_file(std::string filename, FileMode mode);
	FileSystem* add_folder(std::string subgroupName);
	void refresh();

	inline File* operator[](std::string filename) { return immediate_search_file(filename); }
	inline std::string GetPath() const { return path; }
};

#endif