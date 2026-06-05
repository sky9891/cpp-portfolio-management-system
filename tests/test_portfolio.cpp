#include "repositories/Repositories.h"
#include "services/Services.h"
#include "utils/Database.h"
#include <cassert>
#include <iostream>

int main(){
    Database db(":memory:");
    db.executeFile("../sql/schema.sql");

    ClientRepository cr(db); PortfolioRepository pr(db); InstrumentRepository ir(db); TransactionRepository tr(db); HoldingRepository hr(db);
    ClientService clients(cr); PortfolioService portfolios(pr); InstrumentService instruments(ir); TradeService trades(ir,tr,hr);

    int cid = clients.addClient("TestFund","Institutional","test@fund.com");
    int pid = portfolios.createPortfolio(cid,"CoreBook","GBP");
    instruments.addInstrument("AAPL","Apple","Equity","USD",200.0);

    trades.buy(pid,"AAPL",100,150.0);
    auto inst = ir.findBySymbol("AAPL");
    assert(inst.has_value());
    auto h = hr.find(pid, inst->id);
    assert(h.has_value());
    assert(h->quantity == 100);
    assert(h->averagePrice == 150.0);

    trades.buy(pid,"AAPL",100,250.0);
    h = hr.find(pid, inst->id);
    assert(h->quantity == 200);
    assert(h->averagePrice == 200.0);

    trades.sell(pid,"AAPL",50,260.0);
    h = hr.find(pid, inst->id);
    assert(h->quantity == 150);

    bool failed = false;
    try { trades.sell(pid,"AAPL",1000,260.0); } catch(...) { failed = true; }
    assert(failed);

    auto txs = tr.listByPortfolio(pid);
    assert(txs.size() == 3);

    std::cout << "All portfolio core tests passed.\n";
    return 0;
}
