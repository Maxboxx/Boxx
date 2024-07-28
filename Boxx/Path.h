#ifndef _BOXX_PATH_HEADER
#define _BOXX_PATH_HEADER

#include "Types.h"
#include "String.h"
#include "Set.h"

///[Settings] block: indent

///[Namespace] Boxx
namespace Boxx {
	///[Heading] Static Classes

	///[Title] Path
	/// Static class for file paths.
	///[Block] Path
	class Path final {
	public:
		///[Heading] Static Functions

		/// Combines two path segments.
		static String Combine(const String& path1, const String& path2);

		/// Combines three path segments.
		static String Combine(const String& path1, const String& path2, const String& path3);

		/// Checks if {path1} is equal to {path2}.
		static bool IsEqual(const String& path1, const String& path2);

		/// Gets the directory of the path.
		static String GetDirectory(const String& path);

		/// Gets the file name and extension of the path.
		static String GetFile(const String& path);

		/// Gets the file name without the extension of the path.
		static String GetFileName(const String& path);

		/// Gets the file extension of the path.
		static String GetExtension(const String& path);

		/// Sets the file extension of the path.
		static String SetExtension(const String& path, const String& extension);

	private:
		static char ExtSeparator() {
			return '.';
		}

		static bool IsExtSeparator(char c) {
			return c == '.';
		}

		static char Separator() {
			return '/';
		}

		static bool IsSeparator(char c) {
			return c == '/' || c == '\\';
		}
	};

	inline String Path::Combine(const String& path1, const String& path2) {
		if (path1.Length() == 0) {
			return path2;
		}
		else if (path2.Length() == 0) {
			return path1;
		}
		
		bool sep1 = IsSeparator(path1[path1.Length() - 1]);
		bool sep2 = IsSeparator(path2[0]);

		if (sep1 && sep2) {
			return path1 + path2.Sub(1);
		}
		else if (sep1 != sep2) {
			return path1 + path2;
		}
		else {
			return path1 + Separator() + path2;
		}
	}

	inline String Path::Combine(const String& path1, const String& path2, const String& path3) {
		return Combine(Combine(path1, path2), path3);
	}

	inline bool Path::IsEqual(const String& path1, const String& path2) {
		UInt length1 = path1.Length();
		UInt length2 = path1.Length();

		if (length1 > 0 && IsSeparator(path1[length1 - 1])) {
			length1--;
		}

		if (length2 > 0 && IsSeparator(path2[length2 - 1])) {
			length2--;
		}

		if (length1 != length2) return false;

		for (UInt i = 0; i < length1; i++) {
			char c1 = path1[i];
			char c2 = path2[i];

			if (c1 == c2) continue;
			if (IsSeparator(c1) && IsSeparator(c2)) continue;

			return false;
		}

		return true;
	}

	inline String Path::GetDirectory(const String& path) {
		for (Int i = path.Length(); i >= 0; i--) {
			if (IsSeparator(path[i])) {
				if (i == 0) return "";
				return path.Sub(0, i - 1);
			}
		}

		return "";
	}

	inline String Path::GetFile(const String& path) {
		for (Int i = path.Length(); i >= 0; i--) {
			if (IsSeparator(path[i])) {
				return path.Sub(i + 1);
			}
		}

		return path;
	}

	inline String Path::GetFileName(const String& path) {
		String file = GetFile(path);

		for (UInt i = 0; i < file.Length(); i++) {
			if (IsExtSeparator(file[i])) {
				if (i == 0) return "";
				return file.Sub(0, i - 1);
			}
		}

		return file;
	}

	inline String Path::GetExtension(const String& path) {
		for (Int i = path.Length(); i >= 0; i--) {
			char c = path[i];

			if (IsSeparator(c)) {
				return "";
			}

			if (IsExtSeparator(c)) {
				return path.Sub(i + 1);
			}
		}

		return "";
	}

	inline String Path::SetExtension(const String& path, const String& extension) {
		String file = Path::GetFileName(path);

		if (extension.Length() > 0) {
			file += ExtSeparator() + extension;
		}

		return Path::Combine(Path::GetDirectory(path), file);
	}
}

#endif
