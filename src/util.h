#pragma once

#include <format>
#include <vector>
#include <ranges>
#include <string_view>


class HeaderManager {
public:
    HeaderManager(const std::vector<std::string>& source_dirs);

    const std::string& GetIncludes() const {
        return includes_;
    }

    const std::vector<std::string>& GetHeaders() const {
        return headers_;
    }

private:
    std::vector<std::string> headers_;
    std::string includes_;
};


std::tuple<std::string, std::string, std::string, std::vector<std::string>> ParseArguments(int argc, const char** argv);