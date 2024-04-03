#include "util.h"

#include <ranges>
#include <string_view>
#include <fstream>


std::string GetLibName() {
    std::ifstream file("lib_file");
    std::string line;

    std::getline(file, line);
    file.close();

    return line;
}

HeaderManager::HeaderManager(const std::vector<std::string>& headers) {
    for (const auto& header : headers) {
        size_t last_slash = header.rfind('/');
        if (last_slash == std::string::npos) {
            throw std::format_error("Invalid header format");
        }

        source_dirs_.emplace_back(header.substr(0, last_slash));

        includes_ += std::format("#include \"{}\"\n", header.substr(last_slash + 1));
    }
}

void GenerateLib(const HeaderManager& manager, const std::string& libName) {
    std::string build_dirs;
    for (const auto& dir : manager.GetSourceDirs()) {
        build_dirs += std::format("-I{} ", dir);
    }

    std::string command = std::format("c++ -O3 -Wall -shared -std=c++20 -undefined dynamic_lookup $(python3.9 -m pybind11 --includes) $(python3.9-config --include) -fPIC {} generated.cpp {} -o {}$(python3.9-config --extension-suffix)", build_dirs, GetLibName(), libName);
    std::system(command.c_str());
}
