DROP DATABASE IF EXISTS DEV;
CREATE DATABASE IF NOT EXISTS DEV;
USE DEV;

CREATE TABLE products (
	ID INTEGER PRIMARY KEY,
    Title varchar(25),
    Price Double
);

CREATE TABLE orders (
	UID INT PRIMARY KEY,
    ID INT,
    Username varchar(45),
    Quantity SMALLINT DEFAULT 1 CHECK(Quantity > 0 AND Quantity < 25)
    -- CONSTRAINT product_idf FOREIGN KEY (ID) REFERENCES products(ID) ON DELETE RESTRICT
);

CREATE TABLE stuff (
	UID2 INT PRIMARY KEY,
    PASSWD varchar(25),
    INFO varchar(25)
);

INSERT INTO products(ID, Title, Price) VALUES
(1, 'Apple MacBook M1', 600),
(2, 'Apple MacBook M2', 750),
(3, 'Apple MacBook M3 Classic', 900),
(4, 'Apple MacBook M4+', 1200);

INSERT INTO orders(UID, Username, Quantity) VALUES
(4934, 1, 'Alexey Palas', 1),
(1255, 2, 'Volodymir Bravskoy', 4),
(1011, 1, 'Alkan Bolkan', 1),
(9687, 4, 'Yarik Lapa', 1);

