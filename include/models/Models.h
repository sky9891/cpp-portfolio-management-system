#pragma once
#include <string>

struct Client {
    int id{};
    std::string name;
    std::string type;
    std::string email;
};

struct Portfolio {
    int id{};
    int clientId{};
    std::string name;
    std::string baseCurrency;
};

struct Instrument {
    int id{};
    std::string symbol;
    std::string name;
    std::string type;
    std::string currency;
    double currentPrice{};
};

struct Transaction {
    int id{};
    int portfolioId{};
    int instrumentId{};
    std::string side;
    int quantity{};
    double price{};
    std::string tradeDate;
};

struct Holding {
    int id{};
    int portfolioId{};
    int instrumentId{};
    int quantity{};
    double averagePrice{};
};
