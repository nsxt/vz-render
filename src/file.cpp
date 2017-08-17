#include <boost/filesystem.hpp>
#include "file.h"

namespace fs = boost::filesystem;
using std::string;

namespace VzFileSystem {

	string current_path() {
		return fs::current_path().generic_string();
	}

	string get_path(string file) {
		fs::path current_depth = fs::current_path().append(file);
		fs::path parent_depth = fs::current_path().parent_path().append(file);

		if (fs::exists(current_depth)) {
			return current_depth.generic_string();
		}
		else if (fs::exists(parent_depth)) {
			return parent_depth.generic_string();
		}

		return {};
	}

}