CREATE DATABASE L3;
USE L3;

CREATE TABLE `manuf` (
`IDM` int PRIMARY KEY,  
`name` varchar(20),  
`city` varchar(20));

INSERT INTO `manuf` VALUES 
(1,'Intel','Santa Clara'),
(2,'AMD','Santa Clara'),
(3,'WD','San Jose'),
(4,'seagete','Cupertino'),
(5,'Asus','Taipei'),
(6,'Dell','Round Rock');

CREATE TABLE `cpu` (
`IDC` int PRIMARY KEY ,
`IDM` int,
`Name` varchar(20),
`clock` decimal(5,2));

INSERT INTO `cpu` VALUES 
(1,1,'i5',3.20),
(2,1,'i7',4.70),
(3,2,'Ryzen 5',3.20),
(4,2,'Ryzen 7',4.70),
(5,NULL,'Power9',3.50);


CREATE TABLE `hdisk` (
`IDD` int PRIMARY KEY,
`IDM` int,
`Name` varchar(20),
`type` varchar(20),
`size` int);

INSERT INTO `hdisk` VALUES 
(1,3,'Green','hdd',1000),
(2,3,'Black','ssd',256),
(3,1,'6000p','ssd',256),
(4,1,'Optane','ssd',16);

CREATE TABLE `nb` (
`IDN` int PRIMARY KEY,
`IDM` int,
`Name` varchar(20),
`IDC` int,
`IDD` int);

INSERT INTO `nb` VALUES 
(1,5,'Zenbook',2,2),
(2,6,'XPS',2,2),
(3,9,'Pavilion',2,2),
(4,6,'Inspiron',3,4),
(5,5,'Vivobook',1,1),
(6,6,'XPS',4,1);
