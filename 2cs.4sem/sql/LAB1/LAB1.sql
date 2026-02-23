-- Переименовать название файла. Вместо 'x' - номер группы. Фамилию указать латиницей. (shift + ctrl + S -> сохранить как)
-- Все решения должны быть оформлены в виде запросов, и записаны в этот текстовый файл (в том числе создание хранимых процедур, функций и т.д.).
-- Задания рекомендуется выполнять по порядку.  
-- Задания {} - выполнять по желанию.

-- ----------------------------------------------------------------------------------------------------------------------------------------
/*   №1 Создать базу данных.
Открыть SQL скрипты

В названии файла Insert###, где ### название таблицы.
Создать необходимые таблицы, названия и порядок полей взять в первой строке SQL скрипта, название таблицы из его названия. 
Выполнить запросы для заполнения таблиц

 */

-- Решение (только создания БД и таблиц):

create table Author
(
IDA int primary key,
NameA varchar(50)
);
create table ba
(
IDB int,
IDA int
);
create table Books
(
IDB int primary key,
Title varchar(200),
ISBN varchar(50),
EAN varchar(50),
Cover varchar(70),
AgeLimit varchar(3),
Pages int,
Price decimal(10,2)
);
create table BT
(
IDB int,
IDT varchar(2)
);
create table bubuy
(
IDU int,
IDB int,
DateTimeBuy timestamp
);
create table Theme
(
IDT int primary key,
Theme varchar(50),
Description varchar(100) 
);
create table users
(
IDU int primary key,
mail varchar(50),
login varchar(50),
pass varchar(20)
);

-- ----------------------------------------------------------------------------------------------------------------------------------------
/*   №2 Найти книги, которым в соответствие ставится только одна тема. */
-- Решение:
select Title from Books
join (
    select IDB from (
        select bt.IDB, count(bt.IDT) as CountIDT
        from BT bt
        join Books on bt.IDB = Books.IDB
        join Theme on bt.IDT::integer = Theme.IDT
        group by bt.IDB
    ) as Pub where CountIDT = 1::bigint
) as Subquery on Books.IDB = Subquery.IDB;

-- ----------------------------------------------------------------------------------------------------------------------------------------
/*   №3 Найти все книги автора – Толстой Лев Николаевич. Учесть все возможные комбинации имени. */
-- Решение:
select * from ba
join Author using (IDA)
join Books using (IDB)
where Author.NameA like '%Толстой%'
and
(
Author.NameA like '%Л.Н.%'
or Author.NameA like '%Лев%'
);

-- ----------------------------------------------------------------------------------------------------------------------------------------
/*   №4 Найти самую дорогую книгу или книги. */
-- Решение №1 (только одну самую дешёвую книгу):
select Title from Books
where Price = (select min(Price) from Books)
limit 1;
-- Решение №2 (Все самые дешёвые книги):
select Title from Books
where Price = (select min(Price) from Books);
-- Решение №3 (одну самую дешёвую книгу, которая стоит меньше, чем все остальные. Если такой книги нет – вывести null):
select 
case
when (select count(*) from Books where Price = (select min(Price) from Books)) = 1
then (
select Title from Books where Price = (select min(Price) from Books) 
)
else null
end as CheapestBook;

-- ----------------------------------------------------------------------------------------------------------------------------------------
/*   №5 Найти тему, в которой было выпущено меньше всего книг. */
-- Решение:
select Theme, count(Theme) as Amount from BT
join Books using (IDB)
join Theme on BT.IDT::integer = Theme.IDT
group by Theme
having count(Theme) = 
(
	select min(Amount) 
	from (
		select Theme, count(Theme) as Amount 
		from BT
join Books using (IDB)
join Theme on BT.IDT::integer = Theme.IDT
group by Theme) as something);

-- ----------------------------------------------------------------------------------------------------------------------------------------
/*   №6 Для каждого автора вывести все жанры, в которых он публиковался, объединить все значения жанров в одину ячейку для каждого автора. */
-- Решение:
select NameA, string_agg(distinct Theme , '; ') as h from Books
join ba using (IDB)
join Author using (IDA)
join BT using (IDB)
join Theme on BT.IDT::integer = Theme.IDT
group by NameA;

-- ----------------------------------------------------------------------------------------------------------------------------------------
/*  **  {Найти все разные почтовые домены (например: gmail.com, mail.ru и т.д.)} */
select distinct split_part(mail, '@', 2) from users;
-- ----------------------------------------------------------------------------------------------------------------------------------------
/*  ** {Найти количество пользователей по каждому почтовому домену} */
select count(*), mailDomen from (
select IDU, split_part(mail, '@', 2) as mailDomen from users
) as something
group by mailDomen;
-- ----------------------------------------------------------------------------------------------------------------------------------------
/*  ** {Найти самый часто встречающийся почтовый домен} */
with domain_counts as (
    select split_part(mail, '@', 2) as domain,
           count(*) as frequency
    from users
    where mail like '%@%'
    group by split_part(mail, '@', 2)
)
select domain, frequency
from domain_counts
where frequency = (select max(frequency) from domain_counts);
-- ----------------------------------------------------------------------------------------------------------------------------------------
/*   №7 Найти аторов у которых  только одна книга. */
-- Решение:
select NameA, IDA, count(IDB) from ba 
join Author using(IDA)
join Books using(IDB)
group by IDA, NameA
having count(IDB) = 1;

-- ----------------------------------------------------------------------------------------------------------------------------------------
/*   №8 Найти самого покупаемого автора. */
-- Решение:
select IDA, NameA, count(IDB) as total from Author
join ba using(IDA)
join Books using(IDB)
join bubuy using(IDB)
group by IDA
having count(IDB) = 
(select max(total) from (select IDA, NameA, count(IDB) as total from Author
join ba using(IDA)
join Books using(IDB)
join bubuy using(IDB)
group by IDA) as something);

-- ----------------------------------------------------------------------------------------------------------------------------------------
/*   №9 Найти первую приобретенную книгу для каждого читателя. */
-- Решение:
select someSelect.IDU, someSelect.IDB, someSelect.Title, someSelect.DateTimeBuy
from (
    select IDU, IDB, Title, DateTimeBuy
    from bubuy 
    join users using(IDU)
    join Books using(IDB)
) as someSelect
join (
select IDU, MIN(DateTimeBuy) as minDateTime
from bubuy
group by IDU
) as minDatesTimes on someSelect.IDU = minDatesTimes.IDU and someSelect.DateTimeBuy = minDatesTimes.minDateTime;

-- ----------------------------------------------------------------------------------------------------------------------------------------
/*  **  {Найти самую покупаемую книгу для каждого автора} */
with allJunk as (select count(*) as cunt, title, NameA from author
join ba using(ida)
join books using(idb)
join bubuy using(idb)
group by NameA, title, IDB
order by NameA),
maxNumbers as (select max(cunt) as cunt, NameA from allJunk
group by NameA)
select allJunk.cunt, allJunk.title, allJunk.NameA from allJunk
join maxNumbers on maxNumbers.cunt = allJunk.cunt and maxNumbers.NameA = allJunk.NameA
order by NameA;

-- ----------------------------------------------------------------------------------------------------------------------------------------
/*   №10 Вывести статистику: количество купленных книг по каждому дню. */
-- Решение:
select date(DateTimeBuy), count(IDB) from Books
join bubuy using(IDB)
group by date(DateTimeBuy);

-- ----------------------------------------------------------------------------------------------------------------------------------------
/*   №11 Вывести статистику: количество купленных разных книг по каждому дню. */
-- Решение:
select date(DateTimeBuy), count(distinct IDB) from Books
join bubuy using(IDB)
group by date (DateTimeBuy);

-- ----------------------------------------------------------------------------------------------------------------------------------------
/*  **  {Вывести среднее количество (одно число, порядок: до одного знака после запятой) приобретенных книг для всех пользователей которые совершали покупки} */
WITH userPurchaseCounts AS (
    SELECT 
        IDU,
        COUNT(*) AS booksPurchased
    FROM bubuy
    GROUP BY IDU
)
SELECT 
    ROUND(AVG(booksPurchased)::numeric, 1)
FROM userPurchaseCounts;
-- ----------------------------------------------------------------------------------------------------------------------------------------
/*  №12  Вывести количество купленных книг, а также суммарную их стоимость для тем с кодом с 1 по 6 включительно.*/
-- Решение:
select count(IDB) as totalAmount, sum(Price) as totalPrice from BT
join Books Using (IDB)
join Theme on BT.IDT::integer = Theme.IDT
where Theme.IDT between 1 and 6;

-- ----------------------------------------------------------------------------------------------------------------------------------------
/*  **  Вывести Название книги, Имя автора, Логин покупателя для книг, которые были куплены в период с июня по август 2024 года включительно, написаны
 в тематике 'фэнтези' и 'классика', при условии, что число страниц должно быть от 700 до 800 включительно и цена книги меньше 500.*/
with allBooks as (
select distinct title, NameA, login, theme 
from books
join bubuy using(IDB)
join users using(IDU)
join ba using(IDB)
join author using(IDA)
join bt using(IDB)
join theme on bt.IDT::integer = theme.IDT
WHERE 
	bubuy.DateTimeBuy >= '2025-06-01' 
AND bubuy.DateTimeBuy <= '2025-08-31'
AND books.Pages BETWEEN 700 AND 800
AND books.Price < 500),

fantasyBooks as(
select * from allBooks
where theme = 'фэнтези'),

classicalBooks as (
select * from allBooks
where theme = 'классика')

select distinct title, classicalBooks.NameA,classicalBooks.login
from classicalBooks
join fantasyBooks using(title)
order by title;

