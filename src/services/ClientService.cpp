#include "services/Services.h"
#include <iostream>
#include <stdexcept>
ClientService::ClientService(ClientRepository& r):repo_(r){}
int ClientService::addClient(const std::string& n,const std::string& t,const std::string& e){ if(n.empty()) throw std::invalid_argument("Client name cannot be empty"); return repo_.add({0,n,t,e}); }
void ClientService::printClients(){ for(const auto& c: repo_.list()) std::cout << c.id << " | " << c.name << " | " << c.type << " | " << c.email << '\n'; }
