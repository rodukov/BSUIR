-- ================================
-- Лабораторная работа №2, Вариант IV
-- ================================

-- 1. Создать базу "Поставки"
CREATE DATABASE IF NOT EXISTS Supplies;
USE Supplies;

-- 2. Создать таблицу "Импортер"
CREATE TABLE Importer (
    Name VARCHAR(100),
    Address VARCHAR(255)
);

-- 3. Удалить таблицу "Импортер"
DROP TABLE Importer;

-- 4. Вернуть таблицу "Импортер" 
CREATE TABLE IF NOT EXISTS Importer (
    Name VARCHAR(100),
    Address VARCHAR(255)
);

-- 5. Создать таблицу "Поставщик"
CREATE TABLE Supplier (
    Id INT AUTO_INCREMENT PRIMARY KEY,
    Name VARCHAR(100),
    Address VARCHAR(255)
);

-- 6. Добавить в таблицу "Импортер" поле "Код" (PK, автоинкремент)
ALTER TABLE Importer
ADD Id INT AUTO_INCREMENT PRIMARY KEY;

-- 7. Создать таблицу "Поставки"
-- Первичный ключ составной: (ImporterId, SupplierId)
-- Внешние ключи на Importer и Supplier
CREATE TABLE Supplies (
    ImporterId INT,
    SupplierId INT,
    SupplyDate DATE,
    Weight DECIMAL(10,2),
    PRIMARY KEY (ImporterId, SupplierId),
    FOREIGN KEY (ImporterId) REFERENCES Importer(Id),
    FOREIGN KEY (SupplierId) REFERENCES Supplier(Id)
);

-- 8. Переименовать поле "SupplyDate" в таблице "Supplies" на "DeliveryDate"
ALTER TABLE Supplies
CHANGE SupplyDate DeliveryDate DATE;

-- 9. Изменить тип данных для поля "Address" в таблице "Supplier" на TEXT
ALTER TABLE Supplier
MODIFY Address TEXT;

-- 10. Удалить поле "DeliveryDate" из таблицы "Supplies"
ALTER TABLE Supplies
DROP COLUMN DeliveryDate;
