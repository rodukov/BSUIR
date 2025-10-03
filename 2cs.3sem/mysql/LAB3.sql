-- ================================
-- Лабораторная работа: 3
-- ================================

-- 1. Создать базу данных и таблицу
CREATE DATABASE IF NOT EXISTS StarsDB;
USE StarsDB;

CREATE TABLE Stars (
    Id INT PRIMARY KEY,
    StarName VARCHAR(100),
    Constellation VARCHAR(100),
    SpectralClass VARCHAR(5),
    TemperatureK INT,
    MassSun FLOAT,
    RadiusSun FLOAT,
    DistanceLY FLOAT,
    AbsMagnitude FLOAT,
    AppMagnitude FLOAT
);

-- 2. Добавить первую запись
INSERT INTO Stars (Id, StarName, Constellation, SpectralClass, TemperatureK, MassSun, RadiusSun, DistanceLY, AbsMagnitude, AppMagnitude)
VALUES (1, 'Альдебаран', 'Телец', 'M', 3500, 5, 45, 68, -0.63, 0.85);

-- 3. Вывести содержимое таблицы
SELECT * FROM Stars;

-- 4. Добавить несколько записей за один запрос
INSERT INTO Stars (Id, StarName, Constellation, SpectralClass, TemperatureK, MassSun, RadiusSun, DistanceLY, AbsMagnitude, AppMagnitude)
VALUES
(2, 'Гакрукс', 'Южный крест', 'M', 3400, 3, 113, 88, -0.56, 1.59),
(3, 'Полярная', 'Малая Медведица', 'F', 7000, 6, 30, 430, -3.6, 1.97),
(4, 'Беллатрикс', 'Орион', 'B', 22000, 8.4, 6, 240, -2.8, 1.64),
(5, 'Арктур', 'Волопас', 'K', 4300, 1.25, 26, 37, -0.28, -0.05),
(6, 'Альтаир', 'Орел', 'A', 8000, 1.7, 1.7, 360, 2.22, 0.77),
(7, 'Антарес', 'Скорпион', 'K', 4000, 10, 880, 600, -5.28, 0.96),
(8, 'Ригель', 'Орион', 'B', 11000, 18, 75, 864, -7.84, 0.12),
(9, 'Бетельгейзе', 'Орион', 'M', 3100, 20, 900, 650, -5.14, 1.51);

-- 5. Добавить запись (часть полей)
INSERT INTO Stars (Id, StarName, Constellation, SpectralClass, TemperatureK, MassSun, RadiusSun)
VALUES (10, 'Сириус', 'Большой Пес', 'A', 9900, 2, 1.7);

-- 6. Изменить запись: для кода = 10 установить Видимую звёздную величину = 1.4
UPDATE Stars
SET AppMagnitude = 1.4
WHERE Id = 10;

-- 7. Удалить запись с кодом = 1
DELETE FROM Stars
WHERE Id = 1;

-- 8. Изменить запись для Сириуса (одним запросом)
SET SQL_SAFE_UPDATES = 0;
UPDATE Stars
SET AbsMagnitude = -1.46, DistanceLY = 8.6
WHERE StarName = 'Сириус';

-- 9. Удалить запись, где название звезды = Сириус
DELETE FROM Stars
WHERE StarName = 'Сириус';

-- 10. Вывести поля: название звезды и температура, отсортировать по алфавиту
SELECT StarName, TemperatureK
FROM Stars
ORDER BY StarName ASC;

-- 11. Вывести список звезд из созвездия Орион
SELECT * FROM Stars
WHERE Constellation = 'Орион';

-- 12. Вывести список звезд спектрального класса B из созвездия Орион
SELECT * FROM Stars
WHERE Constellation = 'Орион' AND SpectralClass = 'B';

-- 13. Вывести самую далекую звезду
SELECT * FROM Stars
ORDER BY DistanceLY DESC
LIMIT 1;

-- 14. Вывести звезду с наименьшим радиусом
SELECT * FROM Stars
ORDER BY RadiusSun ASC
LIMIT 1;

-- 15. Вывести среднюю температуру для каждого класса спектра
SELECT SpectralClass, AVG(TemperatureK) AS AvgTemp
FROM Stars
GROUP BY SpectralClass;

-- 16. Подсчитать количество звезд в каждом спектральном классе
SELECT SpectralClass, COUNT(*) AS StarCount
FROM Stars
GROUP BY SpectralClass;

-- 17. Какая суммарная масса звезд в таблице
SELECT SUM(MassSun) AS TotalMass
FROM Stars;

-- 18. Вывести минимальную температуру звезды спектрального класса "K"
SELECT MIN(TemperatureK) AS MinTempK
FROM Stars
WHERE SpectralClass = 'K';