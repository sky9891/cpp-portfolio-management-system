#include "repositories/Repositories.h"
#include <sqlite3.h>
#include <stdexcept>

ClientRepository::ClientRepository(Database& db) : db_(db) {}

int ClientRepository::add(const Client& c) {
    sqlite3_stmt* stmt{};
    std::string sql = "INSERT INTO clients(name, type, email) VALUES(?,?,?)";
    if (sqlite3_prepare_v2(db_.raw(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) throw std::runtime_error(sqlite3_errmsg(db_.raw()));
    sqlite3_bind_text(stmt, 1, c.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, c.type.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, c.email.c_str(), -1, SQLITE_TRANSIENT);
    if (sqlite3_step(stmt) != SQLITE_DONE) { std::string e=sqlite3_errmsg(db_.raw()); sqlite3_finalize(stmt); throw std::runtime_error(e); }
    sqlite3_finalize(stmt);
    return static_cast<int>(db_.lastInsertId());
}

std::vector<Client> ClientRepository::list() {
    auto rows = db_.query("SELECT id,name,type,email FROM clients ORDER BY id");
    std::vector<Client> out;
    for (auto& r: rows) out.push_back({std::stoi(r[0]), r[1], r[2], r[3]});
    return out;
}
