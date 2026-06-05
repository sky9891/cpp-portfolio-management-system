CREATE TABLE IF NOT EXISTS clients (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    type TEXT NOT NULL CHECK(type IN ('Institutional','Retail','Private','PrivateClient')),
    email TEXT
);

CREATE TABLE IF NOT EXISTS portfolios (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    client_id INTEGER NOT NULL,
    name TEXT NOT NULL,
    base_currency TEXT NOT NULL DEFAULT 'GBP',
    FOREIGN KEY(client_id) REFERENCES clients(id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS instruments (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    symbol TEXT NOT NULL UNIQUE,
    name TEXT NOT NULL,
    type TEXT NOT NULL CHECK(type IN ('Equity','Bond','MutualFund','ETF')),
    currency TEXT NOT NULL,
    current_price REAL NOT NULL CHECK(current_price > 0)
);

CREATE TABLE IF NOT EXISTS transactions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    portfolio_id INTEGER NOT NULL,
    instrument_id INTEGER NOT NULL,
    side TEXT NOT NULL CHECK(side IN ('BUY','SELL')),
    quantity INTEGER NOT NULL CHECK(quantity > 0),
    price REAL NOT NULL CHECK(price > 0),
    trade_date TEXT NOT NULL,
    FOREIGN KEY(portfolio_id) REFERENCES portfolios(id) ON DELETE CASCADE,
    FOREIGN KEY(instrument_id) REFERENCES instruments(id)
);

CREATE TABLE IF NOT EXISTS holdings (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    portfolio_id INTEGER NOT NULL,
    instrument_id INTEGER NOT NULL,
    quantity INTEGER NOT NULL CHECK(quantity >= 0),
    average_price REAL NOT NULL CHECK(average_price >= 0),
    UNIQUE(portfolio_id, instrument_id),
    FOREIGN KEY(portfolio_id) REFERENCES portfolios(id) ON DELETE CASCADE,
    FOREIGN KEY(instrument_id) REFERENCES instruments(id)
);

CREATE INDEX IF NOT EXISTS idx_portfolios_client ON portfolios(client_id);
CREATE INDEX IF NOT EXISTS idx_transactions_portfolio ON transactions(portfolio_id);
CREATE INDEX IF NOT EXISTS idx_holdings_portfolio ON holdings(portfolio_id);
CREATE INDEX IF NOT EXISTS idx_instruments_symbol ON instruments(symbol);
