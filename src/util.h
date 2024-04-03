#pragma once

#include <format>
#include <vector>
#include <ranges>
#include <string_view>


class HeaderManager {
public:
    HeaderManager(const std::vector<std::string>& headers);

    const std::string& GetIncludes() const {
        return includes_;
    }

    const std::vector<std::string>& GetSourceDirs() const {
        return source_dirs_;
    }

private:
    std::vector<std::string> source_dirs_;
    std::string includes_;
};

void GenerateLib(const HeaderManager& manager, const std::string& libName);
