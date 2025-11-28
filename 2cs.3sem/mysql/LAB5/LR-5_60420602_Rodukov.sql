CREATE DATABASE IF NOT EXISTS LAB5;
USE LAB5;

-- ----------------------------------------------------------------------------------------------------------------------------------------
/*  №1 Создание таблиц  */
CREATE TABLE IF NOT EXISTS Author (
    IDA INT PRIMARY KEY,
    NameA VARCHAR(255) NOT NULL
);

CREATE TABLE IF NOT EXISTS Books (
    IDB INT PRIMARY KEY,
    Title VARCHAR(500) NOT NULL,
    ISBN VARCHAR(32),
    EAN VARCHAR(32),
    Cover VARCHAR(255),
    AgeLimit VARCHAR(10),
    Pages INT,
    Price DECIMAL(10,2)
);

CREATE TABLE IF NOT EXISTS Theme (
    IDT INT PRIMARY KEY,
    Theme VARCHAR(100) NOT NULL
);

CREATE TABLE IF NOT EXISTS ba (
    IDB INT,
    IDA INT
);

CREATE TABLE IF NOT EXISTS BT (
    IDB INT,
    IDT INT
);

CREATE TABLE IF NOT EXISTS users (
    IDU INT PRIMARY KEY,
    mail VARCHAR(100),
    login VARCHAR(50),
    pass VARCHAR(50)
);

CREATE TABLE IF NOT EXISTS bubuy (
    IDU INT,
    IDB INT,
    DateTimeBuy DATETIME
);

-- ----------------------------------------------------------------------------------------------------------------------------------------
/* 	№2 Найти книги, которым в соответствие ставится только одна тема. */
SELECT Books.Title, Theme.Theme
FROM BT
JOIN Books using(idb)
JOIN Theme using(idt)
WHERE BT.idb IN (
    SELECT idb FROM BT
    GROUP BY idb
    HAVING COUNT(DISTINCT idt) = 1
);

-- ----------------------------------------------------------------------------------------------------------------------------------------
/* 	№3 Найти все книги автора – Толстой Лев Николаевич. Учесть все возможные комбинации имени. */
SELECT * FROM books JOIN ba using(idb) JOIN author using(ida)
Where author.NameA LIKE "%Толстой%" And (author.nameA Like "%ЛЕВ%" OR author.nameA Like "%Л.Н.%");

-- ----------------------------------------------------------------------------------------------------------------------------------------
/* 	№4 Найти самую дорогую книгу или книги. */
-- Решение №1 (только одну самую дешёвую книгу):
SELECT Title, Price
FROM Books
WHERE IDB = (
  SELECT MIN(IDB) FROM Books
  WHERE Price = (SELECT MIN(Price) FROM Books)
);

-- Решение №2 (Все самые дешёвые книги):
SELECT Title, Price
FROM books
WHERE Price = (SELECT MIN(Price) FROM books);

-- Решение №3 (одну самую дешёвую книгу, которая стоит меньше, чем все остальные. Если такой книги нет – вывести null):
SELECT Title, Price
FROM books
WHERE Price = (SELECT MIN(Price) FROM books)
  AND (SELECT COUNT(*) FROM books WHERE Price = (SELECT MIN(Price) FROM books)) = 1;

-- ----------------------------------------------------------------------------------------------------------------------------------------
/* 	№5 Найти тему, в которой было выпущено меньше всего книг. */
SELECT Theme.Theme, COUNT(BT.IDB) AS ThemeNumber FROM Theme JOIN BT ON Theme.IDT = BT.IDT JOIN Books ON BT.IDB = Books.IDB
GROUP BY Theme.Theme
HAVING COUNT(BT.IDB) = (
    SELECT MIN(BooksPerTheme)
    FROM (
        SELECT COUNT(BT.IDB) AS BooksPerTheme FROM Theme JOIN BT ON Theme.IDT = BT.IDT
        GROUP BY Theme.IDT
    ) AS sub
);

-- ----------------------------------------------------------------------------------------------------------------------------------------
/* 	№6 Для каждого автора вывести все жанры, в которых он публиковался, объединить все значения жанров в одину ячейку для каждого автора. */
Select NameA, GROUP_CONCAT(Theme SEPARATOR ", ") AS Genres From books INNER JOIN bt using(idb) INNER JOIN theme using(idt) INNER JOIN ba using(idb) INNER JOIN Author using(ida)
GROUP BY NameA;
-- ----------------------------------------------------------------------------------------------------------------------------------------
/* 	** {Найти все разные почтовые домены (например: gmail.com, mail.ru и т.д.)} */
-- не решено.
-- ----------------------------------------------------------------------------------------------------------------------------------------
/* 	** {Найти количество пользователей по каждому почтовому домену} */
-- не решено.
-- ----------------------------------------------------------------------------------------------------------------------------------------
/*  ** {Найти самый часто встречающийся почтовый домен} */
-- не решено.
-- ----------------------------------------------------------------------------------------------------------------------------------------
/* 	№7 Найти аторов у которых  только одна книга. */
Select NameA From books JOIN ba using(idb) JOIN Author using(ida)
GROUP BY NameA
HAVING COUNT(NameA) = 1;
-- ----------------------------------------------------------------------------------------------------------------------------------------
/* 	№8 Найти самого покупаемого автора. */
SELECT Author.NameA, COUNT(Author.NameA) AS BuyTimes FROM Books JOIN BUBuy USING (IDB) JOIN Ba USING (IDB) JOIN Author USING (IDA)
GROUP BY Author.NameA
HAVING BuyTimes = (
    SELECT MAX(BuyCount)
    FROM (
        SELECT COUNT(Author.NameA) AS BuyCount FROM Books JOIN BUBuy USING (IDB) JOIN Ba USING (IDB) JOIN Author USING (IDA)
        GROUP BY Author.NameA
    ) AS sub
);

-- ----------------------------------------------------------------------------------------------------------------------------------------
/* 	№9 Найти первую приобретенную книгу для каждого читателя. */
SELECT Users.login, Books.Title, BUBuy.DateTimeBuy
FROM BUBuy
JOIN Users ON BUBuy.IDU = Users.IDU
JOIN Books ON BUBuy.IDB = Books.IDB
WHERE BUBuy.DateTimeBuy = (
    SELECT MIN(BUBuy2.DateTimeBuy)
    FROM BUBuy AS BUBuy2
    WHERE BUBuy2.IDU = BUBuy.IDU
);

-- ----------------------------------------------------------------------------------------------------------------------------------------
/* 	** {Найти самую покупаемую книгу для каждого автора} */
-- не решено.
-- ----------------------------------------------------------------------------------------------------------------------------------------
/* 	№10 Вывести статистику: количество купленных книг по каждому дню. */
SELECT DATE(BUBuy.DateTimeBuy) AS BuyDate, COUNT(BUBuy.IDB) AS BoughtBooks
FROM BUBuy
GROUP BY DATE(BUBuy.DateTimeBuy)
ORDER BY BuyDate;

-- ----------------------------------------------------------------------------------------------------------------------------------------
/* 	№11 Вывести статистику: количество купленных разных книг по каждому дню. */
SELECT Orders.OrderDate, COUNT(DISTINCT Orders.IDB) AS DifferentBooksCount
FROM Orders
GROUP BY Orders.OrderDate
ORDER BY Orders.OrderDate;

-- ----------------------------------------------------------------------------------------------------------------------------------------
/* 	** {Вывести среднее количество (одно число, порядок: до одного знака после запятой) приобретенных книг для всех пользователей которые совершали покупки} */
-- не решено.
-- ----------------------------------------------------------------------------------------------------------------------------------------
/*	№12	Вывести количество купленных книг, а также суммарную их стоимость для тем с кодом с 1 по 6 включительно.*/
SELECT 
    COUNT(*) AS BoughtBooksCount,
    SUM(Books.Price) AS TotalPrice
FROM Orders
JOIN Books ON Orders.idb = Books.idb
JOIN BT ON Books.idb = BT.idb
WHERE BT.idt BETWEEN 1 AND 6;
-- ----------------------------------------------------------------------------------------------------------------------------------------
/*	**	Вывести Название книги, Имя автора, Логин покупателя для книг, которые были куплены в период с июня по август 2024 года включительно, написаны
 в тематике 'фэнтези' и 'классика', при условии, что число страниц должно быть от 700 до 800 включительно и цена книги меньше 500.*/
-- не решено.
-- ----------------------------------------------------------------------------------------------------------------------------------------