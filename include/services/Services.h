#pragma once
#include "repositories/Repositories.h"
#include <string>

class ClientService { public: explicit ClientService(ClientRepository& repo); int addClient(const std::string& name,const std::string& type,const std::string& email); void printClients(); private: ClientRepository& repo_; };
class PortfolioService { public: explicit PortfolioService(PortfolioRepository& repo); int createPortfolio(int clientId,const std::string& name,const std::string& currency); void printPortfolios(); private: PortfolioRepository& repo_; };
class InstrumentService { public: explicit InstrumentService(InstrumentRepository& repo); int addInstrument(const std::string& symbol,const std::string& name,const std::string& type,const std::string& currency,double price); void printInstruments(); private: InstrumentRepository& repo_; };
class TradeService { public: TradeService(InstrumentRepository& ir, TransactionRepository& tr, HoldingRepository& hr); void buy(int portfolioId,const std::string& symbol,int quantity,double price); void sell(int portfolioId,const std::string& symbol,int quantity,double price); private: InstrumentRepository& instruments_; TransactionRepository& transactions_; HoldingRepository& holdings_; };
class ReportService { public: ReportService(InstrumentRepository& ir, HoldingRepository& hr, TransactionRepository& tr); void printPortfolioSummary(int portfolioId); void printTransactions(int portfolioId); void exportPortfolioCsv(int portfolioId,const std::string& path); private: InstrumentRepository& instruments_; HoldingRepository& holdings_; TransactionRepository& transactions_; };
