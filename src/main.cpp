#include "repositories/Repositories.h"
#include "services/Services.h"
#include "utils/Database.h"
#include <iostream>
#include <memory>
#include <stdexcept>

static void menu(){
    std::cout << "\n=== Portfolio Management System ===\n"
              << "1. Add client\n2. List clients\n3. Create portfolio\n4. List portfolios\n5. Add instrument\n6. List instruments\n7. Buy trade\n8. Sell trade\n9. Portfolio summary\n10. Transaction history\n11. Export portfolio CSV\n0. Exit\nChoice: ";
}

int main(int argc, char** argv){
    try{
        std::string dbPath = argc > 1 ? argv[1] : "portfolio.db";
        Database db(dbPath);
        db.executeFile("../sql/schema.sql");

        ClientRepository cr(db); PortfolioRepository pr(db); InstrumentRepository ir(db); TransactionRepository tr(db); HoldingRepository hr(db);
        ClientService clients(cr); PortfolioService portfolios(pr); InstrumentService instruments(ir); TradeService trades(ir,tr,hr); ReportService reports(ir,hr,tr);

        int choice;
        while(true){
            menu(); std::cin >> choice;
            if(choice == 0) break;
            try{
                if(choice==1){ std::string n,t,e; std::cout<<"Name Type Email: "; std::cin>>n>>t>>e; std::cout<<"Client ID: "<<clients.addClient(n,t,e)<<'\n'; }
                else if(choice==2){ clients.printClients(); }
                else if(choice==3){ int cid; std::string n,c; std::cout<<"ClientId Name Currency: "; std::cin>>cid>>n>>c; std::cout<<"Portfolio ID: "<<portfolios.createPortfolio(cid,n,c)<<'\n'; }
                else if(choice==4){ portfolios.printPortfolios(); }
                else if(choice==5){ std::string s,n,t,c; double p; std::cout<<"Symbol Name Type Currency Price: "; std::cin>>s>>n>>t>>c>>p; std::cout<<"Instrument ID: "<<instruments.addInstrument(s,n,t,c,p)<<'\n'; }
                else if(choice==6){ instruments.printInstruments(); }
                else if(choice==7){ int pid,qty; std::string sym; double price; std::cout<<"PortfolioId Symbol Qty Price: "; std::cin>>pid>>sym>>qty>>price; trades.buy(pid,sym,qty,price); std::cout<<"BUY booked\n"; }
                else if(choice==8){ int pid,qty; std::string sym; double price; std::cout<<"PortfolioId Symbol Qty Price: "; std::cin>>pid>>sym>>qty>>price; trades.sell(pid,sym,qty,price); std::cout<<"SELL booked\n"; }
                else if(choice==9){ int pid; std::cout<<"PortfolioId: "; std::cin>>pid; reports.printPortfolioSummary(pid); }
                else if(choice==10){ int pid; std::cout<<"PortfolioId: "; std::cin>>pid; reports.printTransactions(pid); }
                else if(choice==11){ int pid; std::string path; std::cout<<"PortfolioId OutputCsvPath: "; std::cin>>pid>>path; reports.exportPortfolioCsv(pid,path); std::cout<<"CSV exported\n"; }
            }catch(const std::exception& e){ std::cerr << "Error: " << e.what() << '\n'; }
        }
    }catch(const std::exception& e){ std::cerr << "Fatal: " << e.what() << '\n'; return 1; }
    return 0;
}
