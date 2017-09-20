-- MySQL dump 10.13  Distrib 5.7.17, for Linux (x86_64)
--
-- Host: localhost    Database: Company1
-- ------------------------------------------------------
-- Server version	5.7.17-0ubuntu0.16.10.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Department`
--

DROP TABLE IF EXISTS `Department`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Department` (
  `Dname` varchar(20) DEFAULT NULL,
  `Dnumber` int(11) NOT NULL,
  `Mgr_ssn` int(11) DEFAULT NULL,
  `Mgr_start_date` date DEFAULT NULL,
  PRIMARY KEY (`Dnumber`),
  KEY `MGKEY` (`Mgr_ssn`),
  CONSTRAINT `MGKEY` FOREIGN KEY (`Mgr_ssn`) REFERENCES `Employee` (`Ssn`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Department`
--

LOCK TABLES `Department` WRITE;
/*!40000 ALTER TABLE `Department` DISABLE KEYS */;
INSERT INTO `Department` VALUES ('Headquarters',1,888665555,'1981-06-19'),('Administration',4,987654321,'1995-01-01'),('Research',5,123456789,'2007-10-01'),('Production',10,943775543,'2007-10-01');
/*!40000 ALTER TABLE `Department` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Dependent`
--

DROP TABLE IF EXISTS `Dependent`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Dependent` (
  `Essn` int(11) NOT NULL,
  `Dependent_name` varchar(20) NOT NULL,
  `Sex` char(1) DEFAULT NULL,
  `Bdate` date DEFAULT NULL,
  `Relationship` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`Essn`,`Dependent_name`),
  CONSTRAINT `DEPKEY` FOREIGN KEY (`Essn`) REFERENCES `Employee` (`Ssn`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Dependent`
--

LOCK TABLES `Dependent` WRITE;
/*!40000 ALTER TABLE `Dependent` DISABLE KEYS */;
INSERT INTO `Dependent` VALUES (123456789,'Alice','F','1988-12-30','Daughter'),(123456789,'Elizabeth','F','1967-05-05','Spouse'),(123456789,'Michael','M','1988-01-04','Son'),(333445555,'Alice','F','1986-04-05','Daughter'),(333445555,'Joy','F','1958-05-03','Spouse'),(333445555,'Theodore','M','1983-10-25','Son'),(453453453,'John','M','1990-12-12','spouse'),(987654321,'Abner','M','1942-02-28','Spouse');
/*!40000 ALTER TABLE `Dependent` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Dept_Locations`
--

DROP TABLE IF EXISTS `Dept_Locations`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Dept_Locations` (
  `Dnumber` int(11) NOT NULL,
  `Dlocation` varchar(30) NOT NULL,
  PRIMARY KEY (`Dnumber`,`Dlocation`),
  CONSTRAINT `DLKEY` FOREIGN KEY (`Dnumber`) REFERENCES `Department` (`Dnumber`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Dept_Locations`
--

LOCK TABLES `Dept_Locations` WRITE;
/*!40000 ALTER TABLE `Dept_Locations` DISABLE KEYS */;
INSERT INTO `Dept_Locations` VALUES (1,'Houston'),(4,'Stafford'),(5,'Bellaire'),(5,'Houston'),(5,'Sugarland');
/*!40000 ALTER TABLE `Dept_Locations` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Employee`
--

DROP TABLE IF EXISTS `Employee`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Employee` (
  `Fname` varchar(20) DEFAULT NULL,
  `Minit` varchar(20) DEFAULT NULL,
  `Lname` varchar(20) DEFAULT NULL,
  `Ssn` int(11) NOT NULL,
  `Bdate` date DEFAULT NULL,
  `Address` varchar(40) DEFAULT NULL,
  `Sex` char(1) DEFAULT NULL,
  `Salary` int(11) DEFAULT NULL,
  `Super_ssn` int(11) DEFAULT NULL,
  `Dno` int(11) DEFAULT NULL,
  PRIMARY KEY (`Ssn`),
  KEY `SUPKEY` (`Super_ssn`),
  KEY `DKEY` (`Dno`),
  CONSTRAINT `DKEY` FOREIGN KEY (`Dno`) REFERENCES `Department` (`Dnumber`),
  CONSTRAINT `SUPKEY` FOREIGN KEY (`Super_ssn`) REFERENCES `Employee` (`Ssn`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Employee`
--

LOCK TABLES `Employee` WRITE;
/*!40000 ALTER TABLE `Employee` DISABLE KEYS */;
INSERT INTO `Employee` VALUES ('JOHN','B','Smith',123456789,'1965-01-09','731 Fondren, Houston, TX','M',30000,333445555,5),('FRANKLIN','T','Wong',333445555,'1955-12-08','638 Voss, Houston, TX','M',40000,888665555,5),('JOYCE','A','English',453453453,'1972-07-31','5631 Rice, Houston, TX','F',25000,333445555,5),('RAMESH','K','Narayan',666884444,'1962-09-15','975 Fire Oak, Humble, TX','M',38000,333445555,5),('JAMES','E','Borg',888665555,'1937-11-10','450 Stone, Houston, TX','M',55000,NULL,1),('ROBERT','F','Scott',943775543,'1972-06-21','2365 Newcastle Rd, Bellaire, TX','M',58000,888665555,1),('JENNIFER','S','Wallace',987654321,'1941-06-21','291 Berry, Bellaire, TX','F',43000,888665555,4),('AHMAD','V','Jabbar',987987987,'1969-03-29','980 Dallas, Houston, TX','M',25000,987654321,4),('ALICIA','J','Zelaya',999887777,'1968-01-19','3321 Castle, Spring, TX','F',25000,943775543,4);
/*!40000 ALTER TABLE `Employee` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Project`
--

DROP TABLE IF EXISTS `Project`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Project` (
  `Pname` varchar(20) DEFAULT NULL,
  `Pnumber` int(11) NOT NULL,
  `Plocation` varchar(20) DEFAULT NULL,
  `Dnum` int(11) DEFAULT NULL,
  PRIMARY KEY (`Pnumber`),
  KEY `PDKEY` (`Dnum`),
  CONSTRAINT `PDKEY` FOREIGN KEY (`Dnum`) REFERENCES `Department` (`Dnumber`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Project`
--

LOCK TABLES `Project` WRITE;
/*!40000 ALTER TABLE `Project` DISABLE KEYS */;
INSERT INTO `Project` VALUES ('ProductX',1,'Bellaire',5),('ProductY',2,'Sugarland',5),('ProductZ',3,'Houston',5),('Computerization',10,'Stafford',4),('Reorganistaion',20,'Houston',1),('Newbenefits',30,'Stafford',4);
/*!40000 ALTER TABLE `Project` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Works_On`
--

DROP TABLE IF EXISTS `Works_On`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Works_On` (
  `Essn` int(11) NOT NULL,
  `Pno` int(11) NOT NULL,
  `Hours` decimal(3,1) DEFAULT NULL,
  PRIMARY KEY (`Essn`,`Pno`),
  KEY `WPKEY` (`Pno`),
  CONSTRAINT `ETSKEY` FOREIGN KEY (`Essn`) REFERENCES `Employee` (`Ssn`),
  CONSTRAINT `WPKEY` FOREIGN KEY (`Pno`) REFERENCES `Project` (`Pnumber`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Works_On`
--

LOCK TABLES `Works_On` WRITE;
/*!40000 ALTER TABLE `Works_On` DISABLE KEYS */;
INSERT INTO `Works_On` VALUES (123456789,1,32.5),(123456789,2,7.5),(453453453,1,20.0),(453453453,2,20.0),(666884444,3,40.0),(888665555,20,NULL),(987654321,20,15.0),(987654321,30,20.0),(987987987,10,35.0),(987987987,30,5.0),(999887777,10,5.0),(999887777,30,30.0);
/*!40000 ALTER TABLE `Works_On` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2017-03-10  7:29:33
