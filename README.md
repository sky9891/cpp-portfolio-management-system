# C++ Portfolio Management System

An interview-ready C++17 finance/backend systems project that simulates a simplified portfolio accounting platform for institutional, retail, and private client accounts.

This project is designed for C++ Developer roles in investment management, asset management, banking technology, and enterprise backend systems.

## Why This Project Matters

Investment management firms run long-lived portfolio accounting systems that manage clients, portfolios, holdings, trades, valuations, reports, and database records. This project demonstrates the same core ideas in a compact, runnable C++ application.

It shows practical skill in:

- C++17 backend development
- SQL database design
- Linux/Unix-friendly tooling
- OOP and clean architecture
- Trade processing logic
- Portfolio valuation
- CSV reporting
- GitHub-ready documentation

## Tech Stack

| Area | Technology |
|---|---|
| Core Engine | C++17 |
| Database | SQLite |
| Build System | CMake |
| Interface | CLI |
| Deployment | Docker |
| Platform | Linux/Unix compatible |

SQLite is used deliberately because it makes the project easy to run locally and deploy in Docker without external setup. The repository pattern makes it straightforward to replace SQLite with PostgreSQL later.

## System Architecture

```text
CLI Layer
  |
  v
Service Layer
  |-- ClientService
  |-- PortfolioService
  |-- InstrumentService
  |-- TradeService
  |-- ReportService
  |
  v
Repository Layer
  |-- ClientRepository
  |-- PortfolioRepository
  |-- InstrumentRepository
  |-- TransactionRepository
  |-- HoldingRepository
  |
  v
SQLite Database
```

## Project Structure

```text
cpp-portfolio-management-system/
├── CMakeLists.txt
├── Dockerfile
├── README.md
├── include/
│   ├── models/
│   ├── repositories/
│   ├── services/
│   └── utils/
├── src/
│   ├── main.cpp
│   ├── repositories/
│   ├── services/
│   └── utils/
├── sql/
│   ├── schema.sql
│   └── seed.sql
└── tests/
    └── test_portfolio.cpp
```

## Database Schema

```text
clients
  id PK
  name
  type
  email

portfolios
  id PK
  client_id FK -> clients.id
  name
  base_currency

instruments
  id PK
  symbol UNIQUE
  name
  type
  currency
  current_price

transactions
  id PK
  portfolio_id FK -> portfolios.id
  instrument_id FK -> instruments.id
  side BUY/SELL
  quantity
  price
  trade_date

holdings
  id PK
  portfolio_id FK -> portfolios.id
  instrument_id FK -> instruments.id
  quantity
  average_price
  UNIQUE(portfolio_id, instrument_id)
```

## Features

### Client Management

- Add clients
- View clients
- Supports Institutional, Retail, and PrivateClient types

### Portfolio Management

- Create portfolios for clients
- Multiple portfolios per client
- Base currency support

### Instrument Management

- Add instruments
- Supports Equity, Bond, MutualFund, and ETF
- Stores symbol, currency, and current market price

### Trade Processing

- Buy instrument
- Sell instrument
- Prevents selling more than owned quantity
- Stores every trade in transaction history

### Holdings Calculation

- Maintains quantity owned
- Recalculates average buy price on buys
- Maintains holdings after sells

### Portfolio Valuation

- Total invested amount
- Current market value
- Unrealized profit/loss
- Asset allocation by instrument type

### Reporting

- Portfolio summary report
- Transaction history
- CSV export

## Setup Locally

### Linux / macOS

```bash
sudo apt-get update
sudo apt-get install -y build-essential cmake sqlite3 libsqlite3-dev

git clone <your-repo-url>
cd cpp-portfolio-management-system
mkdir build
cd build
cmake ..
cmake --build .
./portfolio_app
```

### Windows

Use WSL Ubuntu. Do not waste time fighting native Windows C++ setup if your target role is Linux/Unix.

```bash
sudo apt-get update
sudo apt-get install -y build-essential cmake sqlite3 libsqlite3-dev
mkdir build
cd build
cmake ..
cmake --build .
./portfolio_app
```

## Run With Docker

```bash
docker build -t cpp-portfolio-management-system .
docker run -it cpp-portfolio-management-system
```

## Run Tests

```bash
cd build
./portfolio_tests
```

Expected output:

```text
All portfolio core tests passed.
```

## Example CLI Usage

```text
=== Portfolio Management System ===
1. Add client
2. List clients
3. Create portfolio
4. List portfolios
5. Add instrument
6. List instruments
7. Buy trade
8. Sell trade
9. Portfolio summary
10. Transaction history
11. Export portfolio CSV
0. Exit
```

Example flow:

```text
1. Add client
Name Type Email: AcmeFund Institutional ops@acme.com

3. Create portfolio
ClientId Name Currency: 1 GrowthBook GBP

5. Add instrument
Symbol Name Type Currency Price: AAPL Apple Equity USD 195.50

7. Buy trade
PortfolioId Symbol Qty Price: 1 AAPL 100 150

9. Portfolio summary
PortfolioId: 1
```

## Interview Talking Points

### Why C++ was used

C++ is suitable for finance systems because it provides high performance, deterministic resource control, strong typing, and the ability to build long-running backend services efficiently. In investment management systems, reliability and performance are important because the application may process large volumes of trades, holdings, and valuation data.

### How OOP is applied

The application separates business concepts into models such as Client, Portfolio, Instrument, Transaction, and Holding. Business logic is placed inside service classes, while database access is isolated inside repository classes. This makes the code easier to maintain and test.

### How SQL is used

SQL is used to persist clients, portfolios, instruments, transactions, and holdings. The schema is normalized to avoid unnecessary duplication. Foreign keys maintain relationships between clients and portfolios, portfolios and transactions, and instruments and holdings.

### How trades update holdings

When a BUY trade is booked, the system updates the holding quantity and recalculates weighted average price. When a SELL trade is booked, the system validates that the portfolio owns enough quantity before reducing the holding.

### How portfolio valuation works

The system calculates invested value using quantity multiplied by average price. Current market value is calculated using quantity multiplied by current instrument price. Unrealized profit/loss is current market value minus invested value.

### How this resembles real portfolio accounting systems

Real systems maintain clients, portfolios, trades, holdings, and valuations. This project models those same core workflows at a smaller scale. It also follows enterprise-style separation between services, repositories, database schema, and reporting.

### Possible scaling improvements

- Replace SQLite with PostgreSQL or Oracle
- Add REST API layer
- Add authentication and role-based access
- Add market price ingestion
- Add batch reconciliation jobs
- Add multi-threaded report generation
- Add audit logs
- Add FIX message trade ingestion
- Add Docker Compose with PostgreSQL

## Honest Limitations

This is not a real production trading platform. It is an educational/interview project. It does not include compliance workflows, corporate actions, settlement processing, benchmark comparison, tax lots, FX conversion, or real-time market feeds.

That is acceptable for an interview project, but you should be honest if asked.

## Resume Bullet Suggestions

```text
Portfolio Management System — C++17, SQLite, CMake, Linux
• Built a C++17 portfolio accounting simulator supporting clients, portfolios, instruments, trade booking, holdings calculation, valuation, transaction history, and CSV reporting.
• Designed normalized SQL schema for clients, portfolios, instruments, transactions, and holdings with foreign keys and indexes.
• Implemented service/repository architecture using OOP, STL, RAII-based database handling, exception handling, and modular CMake build system.
• Added trade validation logic for insufficient holdings, weighted average price calculation, unrealized P&L, and asset allocation reporting.
```

## License

MIT License.
