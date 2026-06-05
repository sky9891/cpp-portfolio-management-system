#pragma once
#include "models/Models.h"
#include "utils/Database.h"
#include <optional>
#include <vector>

class ClientRepository {
public:
    explicit ClientRepository(Database& db);
    int add(const Client& client);
    std::vector<Client> list();
private: Database& db_;
};

class PortfolioRepository {
public:
    explicit PortfolioRepository(Database& db);
    int add(const Portfolio& portfolio);
    std::vector<Portfolio> listByClient(int clientId);
    std::vector<Portfolio> listAll();
private: Database& db_;
};

class InstrumentRepository {
public:
    explicit InstrumentRepository(Database& db);
    int add(const Instrument& instrument);
    std::optional<Instrument> findBySymbol(const std::string& symbol);
    std::optional<Instrument> findById(int id);
    std::vector<Instrument> list();
private: Database& db_;
};

class TransactionRepository {
public:
    explicit TransactionRepository(Database& db);
    int add(const Transaction& tx);
    std::vector<Transaction> listByPortfolio(int portfolioId);
private: Database& db_;
};

class HoldingRepository {
public:
    explicit HoldingRepository(Database& db);
    std::optional<Holding> find(int portfolioId, int instrumentId);
    void upsert(const Holding& holding);
    std::vector<Holding> listByPortfolio(int portfolioId);
private: Database& db_;
};
