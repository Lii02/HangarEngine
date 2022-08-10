#ifndef FILEGROUP_H
#define FILEGROUP_H
#include "File.h"

class FileGroup {
private:
	std::string path;
	std::list<File*> files;
	std::vector<FileGroup*> subgroups;
public:
	FileGroup(std::string path);
	~FileGroup();

	void Open();
	void CloseFiles();
	File* ImmSearchFile(std::string filename);
	FileGroup* ImmSearchFolder(std::string subgroupName);
	File* AddFile(std::string filename, FileMode mode);
	FileGroup* AddSubgroup(std::string subgroupName);

	inline std::string GetPath() const { return path; }
};

#endif