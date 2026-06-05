#include "services/Services.h"
#include <iostream>
InstrumentService::InstrumentService(InstrumentRepository& r):repo_(r){}
int InstrumentService::addInstrument(const std::string& sym,const std::string& n,const std::string& t,const std::string& c,double p){ return repo_.add({0,sym,n,t,c,p}); }
void InstrumentService::printInstruments(){ for(const auto& i: repo_.list()) std::cout << i.id << " | " << i.symbol << " | " << i.name << " | " << i.type << " | " << i.currency << " | " << i.currentPrice << '\n'; }
