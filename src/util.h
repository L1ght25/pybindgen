#pragma once

#include <format>
#include <vector>
#include <ranges>
#include <string_view>


class HeaderManager {
public:
    HeaderManager(const std::vector<std::string>& source_dirs);

    const std::string& GetIncludes() const;
    const std::vector<std::string>& GetHeaders() const;

    void PrintHeaders() const;

private:
    std::vector<std::string> headers_;
    std::string includes_;
};
