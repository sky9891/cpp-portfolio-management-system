INSERT INTO clients(name,type,email) VALUES
('Acme Pension Fund','Institutional','ops@acmefund.com'),
('John Smith','PrivateClient','john@example.com'),
('Retail Demo User','Retail','retail@example.com');

INSERT INTO portfolios(client_id,name,base_currency) VALUES
(1,'Global Equity Income','GBP'),
(2,'Private Client Growth','GBP'),
(3,'Retail Starter Portfolio','GBP');

INSERT INTO instruments(symbol,name,type,currency,current_price) VALUES
('AAPL','Apple Inc','Equity','USD',195.50),
('MSFT','Microsoft Corp','Equity','USD',420.00),
('VUSA','Vanguard S&P 500 UCITS ETF','ETF','GBP',82.10),
('UKGILT10','UK 10Y Government Bond','Bond','GBP',99.40);
