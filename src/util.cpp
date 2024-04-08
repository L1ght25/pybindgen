#include "util.h"

#include <filesystem>
#include <iostream>
#include <ranges>
#include <string_view>
#include <fstream>


HeaderManager::HeaderManager(const std::vector<std::string>& source_dirs) {
    for (const auto& source_dir : source_dirs) {
        for (const auto& entry : std::filesystem::directory_iterator(source_dir)) {
            if (entry.is_regular_file() && entry.path().extension() == ".h") {
                headers_.push_back(entry.path().string());
            }
        }
    }

    for (const auto& header : headers_) {
        size_t last_slash = header.rfind('/');
        if (last_slash == std::string::npos) {
            throw std::format_error("Invalid header format");
        }

        includes_ += std::format("#include \"{}\"\n", header.substr(last_slash + 1));
    }
}

const std::string& HeaderManager::GetIncludes() const {
    return includes_;
}

const std::vector<std::string>& HeaderManager::GetHeaders() const {
    return headers_;
}

void HeaderManager::PrintHeaders() const {
    for (const auto& str : GetHeaders()) {
        std::cout << "\033[1;35mfound header: " << str << "\033[0m" << std::endl;
    }
}
