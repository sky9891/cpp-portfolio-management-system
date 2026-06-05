#include "repositories/Repositories.h"
#include <sqlite3.h>
#include <stdexcept>

PortfolioRepository::PortfolioRepository(Database& db) : db_(db) {}
int PortfolioRepository::add(const Portfolio& p) {
    sqlite3_stmt* stmt{}; std::string sql="INSERT INTO portfolios(client_id,name,base_currency) VALUES(?,?,?)";
    if (sqlite3_prepare_v2(db_.raw(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) throw std::runtime_error(sqlite3_errmsg(db_.raw()));
    sqlite3_bind_int(stmt,1,p.clientId); sqlite3_bind_text(stmt,2,p.name.c_str(),-1,SQLITE_TRANSIENT); sqlite3_bind_text(stmt,3,p.baseCurrency.c_str(),-1,SQLITE_TRANSIENT);
    if (sqlite3_step(stmt)!=SQLITE_DONE){std::string e=sqlite3_errmsg(db_.raw()); sqlite3_finalize(stmt); throw std::runtime_error(e);} sqlite3_finalize(stmt); return (int)db_.lastInsertId();
}
std::vector<Portfolio> PortfolioRepository::listByClient(int clientId){ auto rows=db_.query("SELECT id,client_id,name,base_currency FROM portfolios WHERE client_id="+std::to_string(clientId)); std::vector<Portfolio> out; for(auto&r:rows) out.push_back({std::stoi(r[0]),std::stoi(r[1]),r[2],r[3]}); return out; }
std::vector<Portfolio> PortfolioRepository::listAll(){ auto rows=db_.query("SELECT id,client_id,name,base_currency FROM portfolios ORDER BY id"); std::vector<Portfolio> out; for(auto&r:rows) out.push_back({std::stoi(r[0]),std::stoi(r[1]),r[2],r[3]}); return out; }
