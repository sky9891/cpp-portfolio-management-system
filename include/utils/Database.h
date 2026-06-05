#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <cstdint>
#include <sqlite3.h>

class Database {
public:
    explicit Database(const std::string& dbPath);
    ~Database();

    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    void execute(const std::string& sql);
    void executeFile(const std::string& filePath);
    int64_t lastInsertId() const;

    using Row = std::vector<std::string>;
    std::vector<Row> query(const std::string& sql);

    sqlite3* raw();

private:
    sqlite3* db_{};
};
