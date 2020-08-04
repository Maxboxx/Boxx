#pragma once

#include "Types.h"
#include "String.h"
#include "Array.h"
#include "List.h"
#include "Error.h"

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <codecvt>
#include <locale>

#ifdef BOXX_WINDOWS
	#include <direct.h>
	#include <windows.h>
#endif

///N System

namespace Boxx {
	///B System
	/// Static class for communicating with the operating system
	class System {
	public:
		///T Execute
		/// Executes a system command
		static void Execute(const String& command);

		///T File Exists
		/// Checks if a file exists
		static bool FileExists(const String& file);

		///T Directory Exists
		/// Checks if a directory exists
		static bool DirectoryExists(const String& directory);

		///T Create Directory
		/// Creates a directory
		///R bool success: <code>true</code> if the directory was created. <code>false</code> otherwise.
		static bool CreateDirectory(const String& directory);

		///T Get Files in Directory
		/// Gets a list of all files in the specified directory
		///E SystemNotSupportedError: Thrown if the operating system is not Windows
		static List<String> GetFilesInDirectory(const String& directory);
	};

	inline void System::Execute(const String& command) {
		system(command);
	}

	inline bool System::FileExists(const String& file) {
		struct stat info;
		return stat(file, &info) == 0;
	}

	inline bool System::DirectoryExists(const String& directory) {
		struct stat info;

		if (stat(directory, &info) != 0)
			return false;
		else if (info.st_mode & S_IFDIR)
			return true;
		else
			return false;
	}

	inline bool System::CreateDirectory(const String& directory) {
		#ifdef BOXX_WINDOWS
			return _mkdir(directory) != -1;
		#else
			return mkdir(directory, 0777) != -1;
		#endif
	}

	inline List<String> System::GetFilesInDirectory(const String& directory) {
		#ifdef BOXX_WINDOWS
			List<String> files;
			
			String searchPath;
			
			if (directory[directory.Size() - 1] == '/' || directory[directory.Size() - 1] == '\\') {
				searchPath = directory + "*.*";
			}
			else {
				searchPath = directory + "/*.*";
			}

			std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

			std::wstring path = converter.from_bytes(std::string((const char*)searchPath));

			WIN32_FIND_DATA fd; 
			HANDLE hFind = ::FindFirstFile(path.c_str(), &fd); 

			if (hFind != INVALID_HANDLE_VALUE) { 
				do {
					if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
						files.Add(String(converter.to_bytes(std::wstring(fd.cFileName))));
					}
				}
				while (::FindNextFile(hFind, &fd));

				::FindClose(hFind); 
			}

			return files;
		#else
			throw SystemNotSupportedError();
			return List<String>();
		#endif
	}
}