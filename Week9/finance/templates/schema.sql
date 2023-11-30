CREATE TABLE trade (
    transaction_id INTEGER PRIMARY KEY,
    user_id INTEGER,
    Stock TEXT,
    Quantity INTEGER,
    total_Bought FLOAT,
    total_Sold FLOAT
);
CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    username TEXT UNIQUE NOT NULL,
    hash TEXT NOT NULL,
    cash NUMERIC NOT NULL DEFAULT 10000.00);

CREATE TABLE sqlite_sequence(name,seq);

CREATE UNIQUE INDEX username ON users (username);

CREATE TABLE stockprofile(
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    user_id INTEGER,
    Stock TEXT,
    Quantity INTEGER,
    Price INTEGER
);
