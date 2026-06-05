#include "utils/Database.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

Database::Database(const std::string& dbPath) {
    if (sqlite3_open(dbPath.c_str(), &db_) != SQLITE_OK) {
        std::string err = sqlite3_errmsg(db_);
        sqlite3_close(db_);
        throw std::runtime_error("Failed to open database: " + err);
    }
    execute("PRAGMA foreign_keys = ON;");
}

Database::~Database() {
    if (db_) sqlite3_close(db_);
}

void Database::execute(const std::string& sql) {
    char* errMsg = nullptr;
    if (sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::string err = errMsg ? errMsg : "Unknown SQL error";
        sqlite3_free(errMsg);
        throw std::runtime_error(err + "\nSQL: " + sql);
    }
}

void Database::executeFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file) throw std::runtime_error("Cannot open SQL file: " + filePath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    execute(buffer.str());
}

int64_t Database::lastInsertId() const {
    return sqlite3_last_insert_rowid(db_);
}

std::vector<Database::Row> Database::query(const std::string& sql) {
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(db_));
    }

    std::unique_ptr<sqlite3_stmt, decltype(&sqlite3_finalize)> guard(stmt, sqlite3_finalize);
    std::vector<Row> rows;
    int cols = sqlite3_column_count(stmt);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Row row;
        row.reserve(cols);
        for (int i = 0; i < cols; ++i) {
            const unsigned char* text = sqlite3_column_text(stmt, i);
            row.emplace_back(text ? reinterpret_cast<const char*>(text) : "");
        }
        rows.push_back(row);
    }
    return rows;
}

sqlite3* Database::raw() { return db_; }
