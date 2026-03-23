
-- 0. ПОДГОТОВКА СТРУКТУРЫ (без внешних ключей)
CREATE TABLE Users (IDU SERIAL PRIMARY KEY, login VARCHAR(50), mail VARCHAR(100), pass VARCHAR(255));
CREATE TABLE Books (IDB SERIAL PRIMARY KEY, Title VARCHAR(255), Price DECIMAL(10,2), Pages INT);
CREATE TABLE Author (IDA SERIAL PRIMARY KEY, NameA VARCHAR(100));
CREATE TABLE Theme (IDT SERIAL PRIMARY KEY, Theme VARCHAR(100));
CREATE TABLE BT (IDB INT, IDT INT);
CREATE TABLE ba (IDB INT, IDA INT);

-- --------------------------------------------------------------------------------
-- №1 Пример успешной транзакции
BEGIN;
INSERT INTO Books (IDB, Title, Price, Pages) VALUES (100000, 'Маргарита', 600.00, 400);
INSERT INTO BT (IDB, IDT) VALUES (100000, 17);
COMMIT; 

-- --------------------------------------------------------------------------------
-- №2 Пример отклоненной транзакции
BEGIN;
UPDATE Books SET Price = Price * 1.1 WHERE IDB = 1;
ROLLBACK; 

-- --------------------------------------------------------------------------------
-- №3 Создание таблицы Buy
CREATE TABLE Buy (
    ID SERIAL PRIMARY KEY,                         
    IDB INT,
    IDU INT,
    TimeBuy TIMESTAMP DEFAULT CURRENT_TIMESTAMP,  
    CONSTRAINT idx_book_user UNIQUE (IDB, IDU)
);
CREATE INDEX idx_timebuy_desc ON Buy (TimeBuy DESC);

-- --------------------------------------------------------------------------------
-- №4 Модификация Buy
ALTER TABLE Buy ADD COLUMN Cost DECIMAL(10, 2);

-- --------------------------------------------------------------------------------
-- {Процедура покупки}
CREATE OR REPLACE PROCEDURE AddBookPurchase(u_id INT, b_id INT)
LANGUAGE plpgsql
AS $$
DECLARE
    b_price DECIMAL(10,2);
BEGIN
    SELECT Price INTO b_price FROM Books WHERE IDB = b_id;
    INSERT INTO Buy (IDB, IDU, TimeBuy, Cost) 
    VALUES (b_id, u_id, CURRENT_TIMESTAMP, COALESCE(b_price, 0) * 0.95);
END;
$$;

-- --------------------------------------------------------------------------------
-- №5 Триггер на изменение email
DROP TRIGGER IF EXISTS trg_update_mail ON Users;
DROP FUNCTION IF EXISTS func_trg_update_mail;

CREATE FUNCTION func_trg_update_mail()
RETURNS TRIGGER AS $$
BEGIN
    IF OLD.mail IS DISTINCT FROM NEW.mail THEN
        RAISE NOTICE 'Почта пользователя % изменена с % на %', NEW.IDU, OLD.mail, NEW.mail;
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_update_mail
AFTER UPDATE ON Users
FOR EACH ROW
EXECUTE FUNCTION func_trg_update_mail();

-- --------------------------------------------------------------------------------
-- №6 Хеширование паролей
ALTER TABLE Users ALTER COLUMN pass TYPE VARCHAR(32);
UPDATE Users SET pass = MD5(pass);

-- --------------------------------------------------------------------------------
-- №7 Книги, которые просмотрели, но не купили
SELECT COUNT(b.IDB) AS CountNotBought, AVG(b.Price) AS AveragePrice
FROM Books b
LEFT JOIN Buy bb ON b.IDB = bb.IDB
WHERE bb.IDB IS NULL;

-- --------------------------------------------------------------------------------
-- №8 Статистика покупок для тем 1-6
SELECT COUNT(bb.IDB) AS TotalQty, SUM(b.Price) AS TotalSum
FROM Buy bb
JOIN Books b ON bb.IDB = b.IDB
JOIN BT ON b.IDB = BT.IDB
WHERE BT.IDT BETWEEN 1 AND 6;

-- --------------------------------------------------------------------------------
-- №9 Выборка с фильтрами по 2018 году
SELECT b.Title, a.NameA, u.login
FROM Buy bb
JOIN Books b ON bb.IDB = b.IDB
JOIN Users u ON bb.IDU = u.IDU
JOIN ba ON b.IDB = ba.IDB
JOIN Author a ON ba.IDA = a.IDA
JOIN BT ON b.IDB = BT.IDB
JOIN Theme t ON BT.IDT = t.IDT
WHERE bb.TimeBuy BETWEEN '2018-06-01' AND '2018-08-31'
  AND t.Theme IN ('фэнтези', 'классика')
  AND b.Pages BETWEEN 700 AND 800
  AND b.Price < 500;