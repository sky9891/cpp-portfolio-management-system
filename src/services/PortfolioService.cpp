#include "services/Services.h"
#include <iostream>
PortfolioService::PortfolioService(PortfolioRepository& r):repo_(r){}
int PortfolioService::createPortfolio(int cid,const std::string& n,const std::string& cur){ return repo_.add({0,cid,n,cur}); }
void PortfolioService::printPortfolios(){ for(const auto& p: repo_.listAll()) std::cout << p.id << " | client=" << p.clientId << " | " << p.name << " | " << p.baseCurrency << '\n'; }
