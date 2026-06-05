#pragma once
#include <string>
#include <vector>

class CsvWriter {
public:
    static void write(const std::string& path, const std::vector<std::vector<std::string>>& rows);
};
