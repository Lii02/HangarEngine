#ifndef FILEGROUP_H
#define FILEGROUP_H
#include "File.h"

class FileSystem {
private:
	std::string path;
	std::list<File*> files;
	std::vector<FileSystem*> subgroups;
public:
	static void Init();
	static void DeInitialize();
	static FileSystem*& Get();

	FileSystem(std::string path);
	~FileSystem();
	FileSystem(const FileSystem&) = delete;

	void Open();
	void CloseFiles();
	File* ImmSearchFile(std::string filename);
	FileSystem* ImmSearchFolder(std::string subgroupName);
	File* AddFile(std::string filename, FileMode mode);
	FileSystem* AddSubgroup(std::string subgroupName);
	void Refresh();

	inline File* operator[](std::string filename) { return ImmSearchFile(filename); }
	inline std::string GetPath() const { return path; }
};

#endif