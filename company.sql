-- MySQL dump 10.13  Distrib 5.7.17, for Linux (x86_64)
--
-- Host: localhost    Database: companies
-- ------------------------------------------------------
-- Server version	5.7.17-0ubuntu0.16.04.1

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
-- Table structure for table `company_details`
--

DROP TABLE IF EXISTS `company_details`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `company_details` (
  `company_id` int(11) NOT NULL,
  `company_name` varchar(30) DEFAULT NULL,
  `company_email` varchar(20) DEFAULT NULL,
  `address` varchar(50) DEFAULT NULL,
  `description` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`company_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `company_details`
--

LOCK TABLES `company_details` WRITE;
/*!40000 ALTER TABLE `company_details` DISABLE KEYS */;
INSERT INTO `company_details` VALUES (1,'google','google123@gmail.com','A 42,plaza,parel,Mumbai','software company'),(2,'Intel','Intel@gmail.com','A 21,Hitechcity,Bengaluru','hardware'),(3,'BHEL','bhel@gmail.com','A 2,gindi,chennai','electrical'),(4,'hyndai','hyndai@gmail.com','A 32,Chennai,Tamil Nadu','automobiles,mechanical'),(5,'Surya Groups','surya@gmail.com','A 5,kolkata,West Bengal','electrical'),(6,'ECIL','ecil@gmail.com','A 5,gachiboli,hyderabad','electrical'),(7,'microsoft','microsoft@gmail.com','A 17,kormangala,Bengaluru','computer software,personal computers '),(8,'CISCO','cisco@gmail.com','B 5,madhapur,Andhra Pradesh','networking hardware '),(9,'Mahindra','mahindra@gmail.com','D 5,,Andhra Pradesh','mechanical '),(10,'Apple','apple@gmail.com','D 15,Hitechcity,Telangana','consumer electronic ,computer software ');
/*!40000 ALTER TABLE `company_details` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `contact_details`
--

DROP TABLE IF EXISTS `contact_details`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `contact_details` (
  `company_id` int(11) NOT NULL,
  `contact_name` varchar(20) DEFAULT NULL,
  `contact_number` char(10) DEFAULT NULL,
  `contact_email` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`company_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `contact_details`
--

LOCK TABLES `contact_details` WRITE;
/*!40000 ALTER TABLE `contact_details` DISABLE KEYS */;
INSERT INTO `contact_details` VALUES (1,'Rajat Kunj','9999234918','rajat@yahoo.co.in'),(2,'Keerti khanna','9999234945','keerti@yahoo.co.in'),(3,'Riya Sen','9999237945','riya@gmail.co.in'),(4,'roshan bhat','9939237945','roshan@gmail.com'),(5,'Suraj Sharma','9939237345','suraj@gmail.com'),(6,'Parul Verma','9939232345','parul@gmail.com'),(7,'Anaya Prakash','8939232345','ana@gmail.com'),(8,'Vipul Rakesh','8931232345','vipul@gmail.com'),(9,'Sonal Shah','8931232345','sonal@yahoo.com'),(10,'Karthik Kapur','8931032345','karthik@yahoo.com');
/*!40000 ALTER TABLE `contact_details` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `eligible_departments`
--

DROP TABLE IF EXISTS `eligible_departments`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `eligible_departments` (
  `job_id` int(11) NOT NULL,
  `department` char(3) NOT NULL,
  PRIMARY KEY (`job_id`,`department`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `eligible_departments`
--

LOCK TABLES `eligible_departments` WRITE;
/*!40000 ALTER TABLE `eligible_departments` DISABLE KEYS */;
INSERT INTO `eligible_departments` VALUES (1,'CED'),(1,'COE'),(2,'CED'),(2,'COE'),(3,'CED'),(3,'COE'),(4,'CED'),(5,'CED'),(5,'COE'),(5,'EDS'),(6,'EDS'),(6,'EVD'),(7,'EVD'),(8,'COE'),(9,'EDS'),(10,'CED'),(11,'EDS'),(12,'MDM'),(12,'MDS'),(13,'CED'),(14,'COE'),(15,'MDM'),(16,'CDS'),(17,'CDS'),(17,'CED');
/*!40000 ALTER TABLE `eligible_departments` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `hiring_details`
--

DROP TABLE IF EXISTS `hiring_details`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `hiring_details` (
  `job_id` int(11) NOT NULL,
  `time` char(9) DEFAULT NULL,
  `date` date DEFAULT NULL,
  `on_campus` char(1) DEFAULT NULL,
  PRIMARY KEY (`job_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `hiring_details`
--

LOCK TABLES `hiring_details` WRITE;
/*!40000 ALTER TABLE `hiring_details` DISABLE KEYS */;
INSERT INTO `hiring_details` VALUES (1,'09:30:00','2017-12-03','Y'),(2,'10:15:00','2017-07-06','N'),(3,'10:36:00','2017-07-06','Y'),(4,'10:36:00','2017-05-06','Y'),(5,'13:OO:00','2017-05-06','N'),(6,'13:45:00','2017-08-06','N'),(7,'13:45:00','2017-08-06','N'),(8,'13:45:00','2017-08-16','Y'),(9,'09:45:00','2017-08-16','Y'),(10,'09:00:00','2017-08-01','N'),(11,'09:30:00','2017-08-13','N'),(12,'09:50:00','2017-09-13','Y'),(13,'09:50:00','2017-09-13','Y'),(14,'11:00:00','2017-09-13','Y'),(15,'08:00:00','2017-09-11','N'),(16,'08:30:00','2017-09-11','N'),(17,'08:40:00','2017-09-11','Y'),(18,'08:00:00','2017-09-19','Y'),(19,'09:00:00','2017-09-18','N');
/*!40000 ALTER TABLE `hiring_details` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `job_profiles`
--

DROP TABLE IF EXISTS `job_profiles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `job_profiles` (
  `job_id` int(11) NOT NULL,
  `job_type` varchar(20) DEFAULT NULL,
  `cost_to_company` int(11) DEFAULT NULL,
  `designation` varchar(15) DEFAULT NULL,
  `location` char(50) DEFAULT NULL,
  PRIMARY KEY (`job_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `job_profiles`
--

LOCK TABLES `job_profiles` WRITE;
/*!40000 ALTER TABLE `job_profiles` DISABLE KEYS */;
INSERT INTO `job_profiles` VALUES (1,'internship',23220,' engineer','A 42,plaza,parel,Mumbai'),(2,'full time',23280,'generalmanager','A 42,plaza,parel,Mumbai'),(3,'full time',234800,'manager','A 42,plaza,parel,Mumbai'),(4,'full time',79970,' engineer','A 17,koramangala,Bengaluru'),(5,'internship ',59000,'designer','A 21,hitechcity,bengaluru'),(6,'internship ',59000,'designer','A 21,A 2,gindi,chennai'),(7,'full time ',899070,'manager','A 5,gachiboli,hyderabad'),(8,'internship',99070,' engineer','A 17,koramangala,Bengaluru'),(9,'full time ',799070,'designer','A 5,kolkata,West Bengal'),(10,'full time',99970,'generalmanager','A 17,koramangala,Bengaluru'),(11,'full time ',522990,'manager','A 21,hitechcity,bengaluru'),(12,'internship ',59700,'generalmanager','A 32,chennai,Tamil Nadu'),(13,'full time ',422990,'generalmanager','A 21,hitechcity,bengaluru'),(14,'intership',434990,'engineer','A 42,plaza,parel,Mumbai'),(15,'full time ',570700,'engineer','A 32,chennai,Tamil Nadu'),(16,'full time',79970,'designer','D 5,Andhra Pradesh'),(17,'full time ',422990,'manager','A 42,plaza,parel,Mumbai'),(18,'full time',59970,'generalmanager','B 5,madhapur,Andhra Pradesh');
/*!40000 ALTER TABLE `job_profiles` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2017-04-23 14:49:10
