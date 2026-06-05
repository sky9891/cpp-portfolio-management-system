#include "utils/CsvWriter.h"
#include <fstream>
#include <stdexcept>

void CsvWriter::write(const std::string& path, const std::vector<std::vector<std::string>>& rows) {
    std::ofstream out(path);
    if (!out) throw std::runtime_error("Unable to write CSV: " + path);
    for (const auto& row : rows) {
        for (size_t i = 0; i < row.size(); ++i) {
            out << '"' << row[i] << '"';
            if (i + 1 < row.size()) out << ',';
        }
        out << '\n';
    }
}
