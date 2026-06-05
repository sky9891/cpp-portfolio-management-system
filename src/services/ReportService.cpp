#include "services/Services.h"
#include "utils/CsvWriter.h"
#include <iomanip>
#include <iostream>
#include <map>

ReportService::ReportService(InstrumentRepository& ir,HoldingRepository& hr,TransactionRepository& tr):instruments_(ir),holdings_(hr),transactions_(tr){}

void ReportService::printPortfolioSummary(int pid){
    auto hs = holdings_.listByPortfolio(pid);
    double invested = 0, current = 0;
    std::map<std::string,double> allocation;
    std::cout << "\nPortfolio Summary for ID " << pid << "\n";
    std::cout << "Symbol | Qty | Avg Price | Current Price | Market Value | Unrealized P&L\n";
    for(const auto& h: hs){
        auto inst = instruments_.findById(h.instrumentId);
        if(!inst) continue;
        double cost = h.quantity * h.averagePrice;
        double mv = h.quantity * inst->currentPrice;
        invested += cost; current += mv; allocation[inst->type] += mv;
        std::cout << inst->symbol << " | " << h.quantity << " | " << h.averagePrice << " | " << inst->currentPrice << " | " << mv << " | " << (mv-cost) << '\n';
    }
    std::cout << "Total Invested: " << invested << "\nCurrent Value: " << current << "\nTotal P&L: " << (current-invested) << "\n";
    std::cout << "Asset Allocation:\n";
    for(auto& [type,value]: allocation) std::cout << " - " << type << ": " << std::fixed << std::setprecision(2) << (current>0? value*100/current:0) << "%\n";
}

void ReportService::printTransactions(int pid){
    for(const auto& t: transactions_.listByPortfolio(pid)){
        auto inst = instruments_.findById(t.instrumentId);
        std::cout << t.id << " | " << t.tradeDate << " | " << t.side << " | " << (inst?inst->symbol:"UNKNOWN") << " | qty=" << t.quantity << " | price=" << t.price << '\n';
    }
}

void ReportService::exportPortfolioCsv(int pid,const std::string& path){
    std::vector<std::vector<std::string>> rows{{"Symbol","Type","Quantity","Average Price","Current Price","Market Value","Unrealized P&L"}};
    for(const auto& h: holdings_.listByPortfolio(pid)){
        auto inst = instruments_.findById(h.instrumentId);
        if(!inst) continue;
        double mv = h.quantity * inst->currentPrice;
        double cost = h.quantity * h.averagePrice;
        rows.push_back({inst->symbol, inst->type, std::to_string(h.quantity), std::to_string(h.averagePrice), std::to_string(inst->currentPrice), std::to_string(mv), std::to_string(mv-cost)});
    }
    CsvWriter::write(path, rows);
}
