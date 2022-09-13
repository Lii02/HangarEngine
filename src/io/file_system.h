#ifndef FILEGROUP_H
#define FILEGROUP_H
#include "File.h"
#include "containers/list.h"

class FileSystem {
private:
	AString path;
	List<File*> files;
	List<FileSystem*> folders;
public:
	static void initialize();
	static void deinitialize();
	static FileSystem*& get();

	FileSystem(AString _fs_path);
	~FileSystem();
	FileSystem(const FileSystem&) = delete;

	void open();
	void close_files();
	File* immediate_search_file(AString filename);
	FileSystem* immediate_search_folder(AString folder_name);
	File* add_file(AString filename, FileMode mode);
	FileSystem* add_folder(AString folder_name);
	void refresh();

	HANGAR_FORCE_INLINE File* operator[](AString filename) { return immediate_search_file(filename); }
	HANGAR_FORCE_INLINE AString GetPath() const { return path; }
};

#endif