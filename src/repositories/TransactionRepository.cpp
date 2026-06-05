#include "repositories/Repositories.h"
#include <sqlite3.h>
#include <stdexcept>

TransactionRepository::TransactionRepository(Database& db):db_(db){}
int TransactionRepository::add(const Transaction& t){ sqlite3_stmt* stmt{}; std::string sql="INSERT INTO transactions(portfolio_id,instrument_id,side,quantity,price,trade_date) VALUES(?,?,?,?,?,datetime('now'))"; if(sqlite3_prepare_v2(db_.raw(),sql.c_str(),-1,&stmt,nullptr)!=SQLITE_OK) throw std::runtime_error(sqlite3_errmsg(db_.raw())); sqlite3_bind_int(stmt,1,t.portfolioId); sqlite3_bind_int(stmt,2,t.instrumentId); sqlite3_bind_text(stmt,3,t.side.c_str(),-1,SQLITE_TRANSIENT); sqlite3_bind_int(stmt,4,t.quantity); sqlite3_bind_double(stmt,5,t.price); if(sqlite3_step(stmt)!=SQLITE_DONE){std::string e=sqlite3_errmsg(db_.raw()); sqlite3_finalize(stmt); throw std::runtime_error(e);} sqlite3_finalize(stmt); return (int)db_.lastInsertId(); }
std::vector<Transaction> TransactionRepository::listByPortfolio(int pid){ auto rows=db_.query("SELECT id,portfolio_id,instrument_id,side,quantity,price,trade_date FROM transactions WHERE portfolio_id="+std::to_string(pid)+" ORDER BY id"); std::vector<Transaction> out; for(auto&r:rows) out.push_back({std::stoi(r[0]),std::stoi(r[1]),std::stoi(r[2]),r[3],std::stoi(r[4]),std::stod(r[5]),r[6]}); return out; }
