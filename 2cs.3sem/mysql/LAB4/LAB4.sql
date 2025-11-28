-- ЛАБОРАТОРНАЯ РАБОТА №4
-- Тема: Соединение таблиц (JOIN)

-- 1. Создание базы и таблиц
CREATE DATABASE L3;
USE L3;

CREATE TABLE manuf (
  IDM INT PRIMARY KEY,
  name VARCHAR(20),
  city VARCHAR(20)
);

INSERT INTO manuf VALUES
(1,'Intel','Santa Clara'),
(2,'AMD','Santa Clara'),
(3,'WD','San Jose'),
(4,'Seagate','Cupertino'),
(5,'Asus','Taipei'),
(6,'Dell','Round Rock');

CREATE TABLE cpu (
  IDC INT PRIMARY KEY,
  IDM INT,
  name VARCHAR(20),
  clock DECIMAL(5,2)
);

INSERT INTO cpu VALUES
(1,1,'i5',3.20),
(2,1,'i7',4.70),
(3,2,'Ryzen 5',3.20),
(4,2,'Ryzen 7',4.70),
(5,NULL,'Power9',3.50);

CREATE TABLE hdisk (
  IDD INT PRIMARY KEY,
  IDM INT,
  name VARCHAR(20),
  type VARCHAR(20),
  size INT
);

INSERT INTO hdisk VALUES
(1,3,'Green','hdd',1000),
(2,3,'Black','ssd',256),
(3,1,'6000p','ssd',256),
(4,1,'Optane','ssd',16);

CREATE TABLE nb (
  IDN INT PRIMARY KEY,
  IDM INT,
  name VARCHAR(20),
  IDC INT,
  IDD INT
);

INSERT INTO nb VALUES
(1,5,'Zenbook',2,2),
(2,6,'XPS',2,2),
(3,9,'Pavilion',2,2),
(4,6,'Inspiron',3,4),
(5,5,'Vivobook',1,1),
(6,6,'XPS',4,1);

-- ======================================================
-- 3. Неявное соединение (без условия)
SELECT manuf.name AS manuf_name, cpu.name AS cpu_name
FROM manuf, cpu;

-- 4. Неявное соединение (с условием WHERE)
SELECT manuf.name AS manuf_name, cpu.name AS cpu_name
FROM manuf, cpu
WHERE manuf.IDM = cpu.IDM;

-- 5. INNER JOIN
SELECT manuf.name AS manuf_name, cpu.name AS cpu_name
FROM manuf
INNER JOIN cpu ON manuf.IDM = cpu.IDM;

-- 6. LEFT JOIN
SELECT manuf.name AS manuf_name, cpu.name AS cpu_name
FROM manuf
LEFT JOIN cpu ON manuf.IDM = cpu.IDM;

-- 7. RIGHT JOIN
SELECT manuf.name AS manuf_name, cpu.name AS cpu_name
FROM manuf
RIGHT JOIN cpu ON manuf.IDM = cpu.IDM;

-- 8. CROSS JOIN (декартово произведение)
SELECT manuf.name AS manuf_name, cpu.name AS cpu_name
FROM manuf
CROSS JOIN cpu;

-- 8б. Анализ:
-- 3: каждая строка manuf × каждая строка cpu (все комбинации)
-- 4: только совпадающие IDM (как INNER JOIN)
-- 5: то же, что 4 (современный синтаксис)
-- 6: все фирмы + процессоры, если есть
-- 7: все процессоры + фирмы, если есть
-- 8: все возможные комбинации (как в 3)

-- ======================================================
-- 9. Название фирмы и модель диска (без NULL)
SELECT manuf.name AS manuf_name, hdisk.name AS disk_name
FROM manuf
JOIN hdisk ON manuf.IDM = hdisk.IDM
WHERE manuf.name IS NOT NULL AND hdisk.name IS NOT NULL;

-- 10. Модель процессора и, если есть, фирма
SELECT cpu.name AS cpu_name, manuf.name AS manuf_name
FROM cpu
LEFT JOIN manuf ON cpu.IDM = manuf.IDM;

-- 11. Модели ноутбуков без информации о фирме
SELECT nb.name AS notebook
FROM nb
LEFT JOIN manuf ON nb.IDM = manuf.IDM
WHERE manuf.name IS NULL;

-- 12. Модель ноутбука, производитель, модель процессора, модель диска
SELECT nb.name AS notebook,
       manuf.name AS manuf_name,
       cpu.name AS cpu_name,
       hdisk.name AS disk_name
FROM nb
LEFT JOIN manuf ON nb.IDM = manuf.IDM
LEFT JOIN cpu ON nb.IDC = cpu.IDC
LEFT JOIN hdisk ON nb.IDD = hdisk.IDD;

-- 13. Модель ноутбука, фирма ноутбука, модель и фирма CPU, модель и фирма HDD
SELECT nb.name AS notebook,
       m1.name AS nb_manuf,
       cpu.name AS cpu_name,
       m2.name AS cpu_manuf,
       hdisk.name AS disk_name,
       m3.name AS disk_manuf
FROM nb
LEFT JOIN manuf m1 ON nb.IDM = m1.IDM
LEFT JOIN cpu ON nb.IDC = cpu.IDC
LEFT JOIN manuf m2 ON cpu.IDM = m2.IDM
LEFT JOIN hdisk ON nb.IDD = hdisk.IDD
LEFT JOIN manuf m3 ON hdisk.IDM = m3.IDM;

-- 14. Все фирмы и все процессоры
SELECT manuf.name AS name, cpu.name AS model
FROM manuf
CROSS JOIN cpu;

-- 15. Фирмы, производящие несколько типов товаров
SELECT m.name
FROM manuf m
WHERE m.IDM IN (
  SELECT IDM FROM cpu
  UNION
  SELECT IDM FROM hdisk
  UNION
  SELECT IDM FROM nb
)
GROUP BY m.name
HAVING COUNT(*) > 1;
