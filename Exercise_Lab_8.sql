#delete tee file already existing
system rm Exercise_Lab_8.txt

# Enable outfile
tee Exercise_Lab_8.txt

# Select Database to use
# 28 Feb 2017
USE Company1;

# 1. Display all odd numbered alternate records from ‘Employee’ table.
# Declare and initiate a vaiable
SET @rn=0;
# Use that variable as read counter
SELECT E.*
FROM (SELECT
        t.*,
        (@rn := @rn + 1) AS seqnum
      FROM Employee t) E
WHERE MOD(seqnum, 2) = 1;

# 2. Display all even numbered alternate records from ‘Employee’ table.
# Declare and initiate a vaiable
SET @rn=0;
# Use that variable as read counter
SELECT E.*
FROM (SELECT
        t.*,
        (@rn := @rn + 1) AS seqnum
      FROM Employee t) E
WHERE MOD(seqnum, 2) = 0;

# 3. Find the year from the given date.
SELECT
  Fname,
  Minit,
  Lname,
  year(Bdate) AS BirthYear
FROM Employee
ORDER BY BirthYear;

# 4. Find year from birth date when the date is a VARCHAR column instead of the proper
# DATE data type.
SELECT LEFT(Bdate, 4)
FROM Employee;

# 5. Select first 3 characters of first name.
SELECT LEFT(Fname, 3)
FROM Employee;

# 6. Check whether date passed to Query is the date of a given format or not.
# Use of Nested IF
SELECT
  Bdate,
  IF(DATE_FORMAT(Bdate, '%y-%m-%d'),
     'IS OF FORMAT YYYY-MM-DD', IF(DATE_FORMAT(Bdate, '%m-%d-%y'),
                                   'IS OF FORMAT MM-DD-YYYY', IF(DATE_FORMAT(Bdate, '%d-%m-%y'),
                                                                 'IS OF FORMAT DD-MM-YYYY', 'NOT A DATE FORMAT'))) AS DATE_CHECK
FROM Employee;

# 7. Find duplicate rows in a table of your choice.
# Creating Temporary Table for this query
CREATE TABLE COPYEMP (
  Fname     VARCHAR(20),
  Minit     CHAR,
  Lname     VARCHAR(20),
  Ssn       INTEGER,
  Bdate     DATE,
  Address   VARCHAR(40),
  Sex       CHAR,
  Salary    INTEGER,
  Super_ssn INTEGER,
  Dno       INTEGER
);
# Inserting Duplicate Records
INSERT INTO
COPYEMP VALUES
  ('John','B','Smith',123456789,'1965-01-09','731 Fondren, Houston, TX','M',30000,333445555,5),
  ('Franklin','T','Wong',333445555,'1955-12-08','638 Voss, Houston, TX','M',40000,888665555,5),
  ('Franklin','T','Wong',333445555,'1955-12-08','638 Voss, Houston, TX','M',40000,888665555,5),
  ('Joyce','A','English',453453453,'1972-07-31','5631 Rice, Houston, TX','F',25000,333445555,5),
  ('Ramesh','K','Narayan',666884444,'1962-09-15','975 Fire Oak, Humble, TX','M',38000,333445555,5),
  ('James','E','Borg',888665555,'1937-11-10','450 Stone, Houston, TX','M',55000,NULL,1),
  ('John','B','Smith',123456789,'1965-01-09','731 Fondren, Houston, TX','M',30000,333445555,5),
  ('James','E','Borg',888665555,'1937-11-10','450 Stone, Houston, TX','M',55000,NULL,1),
  ('Ahmad','V','Jabbar',987987987,'1969-03-29','980 Dallas, Houston, TX','M',25000,987654321,4),
  ('Franklin','T','Wong',333445555,'1955-12-08','638 Voss, Houston, TX','M',40000,888665555,5),
  ('Alicia','J','Zelaya',999887777,'1968-01-19','3321 Castle, Spring, TX','F',25000,987654321,4);
# Group by all fields so that we can see if entire record is duplicated
SELECT *,COUNT(*) AS "Number of Copies"
FROM COPYEMP
GROUP BY Ssn, Fname, Minit, Lname, Bdate, Address, Sex, Salary, Super_ssn, Dno
HAVING COUNT(*) > 1;

# 8. Delete the duplicate records retrieved using the above query without using a
# temporary table.
# Displaying the entire table before to check the query
SELECT * FROM COPYEMP;
# Way 1 This won't allow duplicate entries to be entered
# ALTER TABLE COPYEMP ADD UNIQUE INDEX (Fname,Minit,Lname,Ssn,Bdate,Address,Sex,Salary,Super_ssn,Dno);
# Way 2 Based on a field or say if Primary Key is assigned
# Deleting Duplicate Records
DELETE FROM COPYEMP
WHERE Ssn IN (SELECT *
              FROM (SELECT Ssn
                    FROM COPYEMP
                    GROUP BY Fname, Minit, Lname, Ssn, Bdate, Address, Sex, Salary, Super_ssn, Dno
                    HAVING (COUNT(*) > 1)) AS A);
# Again Displaying the entire table before to check the query
SELECT * FROM COPYEMP;

# 9. Delete the duplicate records retrieved using the above query using a temporary table.
# Emptying the table
DELETE FROM COPYEMP;
# Inserting Duplicate entries
INSERT INTO
COPYEMP VALUES
  ('John','B','Smith',123456789,'1965-01-09','731 Fondren, Houston, TX','M',30000,333445555,5),
  ('Franklin','T','Wong',333445555,'1955-12-08','638 Voss, Houston, TX','M',40000,888665555,5),
  ('Joyce','A','English',453453453,'1972-07-31','5631 Rice, Houston, TX','F',25000,333445555,5),
  ('Ramesh','K','Narayan',666884444,'1962-09-15','975 Fire Oak, Humble, TX','M',38000,333445555,5),
  ('James','E','Borg',888665555,'1937-11-10','450 Stone, Houston, TX','M',55000,NULL,1),
  ('John','B','Smith',123456789,'1965-01-09','731 Fondren, Houston, TX','M',30000,333445555,5),
  ('James','E','Borg',888665555,'1937-11-10','450 Stone, Houston, TX','M',55000,NULL,1),
  ('Ahmad','V','Jabbar',987987987,'1969-03-29','980 Dallas, Houston, TX','M',25000,987654321,4),
  ('Franklin','T','Wong',333445555,'1955-12-08','638 Voss, Houston, TX','M',40000,888665555,5),
  ('Alicia','J','Zelaya',999887777,'1968-01-19','3321 Castle, Spring, TX','F',25000,987654321,4);
# Displaying the entire table before to check the query
SELECT * FROM COPYEMP;
# Creating Temporary Table from only the distinct records in the original table
CREATE TABLE TTABLE AS SELECT DISTINCT *
                       FROM COPYEMP;
# Dropping Original Table
DROP TABLE COPYEMP;
# Renaming Temporary Table with Original Table Name ( Replacing )
RENAME TABLE
    TTABLE TO COPYEMP;
# Again Displaying the entire table before to check the query
SELECT * FROM COPYEMP;

# 10. Extract the 3 rd maximum salary. Also find n th max salary.
# Without using LIMIT
SELECT E.*
FROM Employee E
WHERE (SELECT COUNT(*)
       FROM Employee D
       WHERE D.Salary > E.Salary) = 2;
# Using LIMIT
SELECT *
FROM Employee
ORDER BY Salary DESC
LIMIT 2, 1;
# If multiple people have 3rd max salary
SELECT *
FROM Employee
WHERE Salary = (SELECT Salary
                FROM Employee
                ORDER BY Salary DESC
                LIMIT 2, 1);

# 11. How to get first 3 max salaries. Also find first n max salaries.
SELECT *
FROM Employee
ORDER BY Salary DESC
LIMIT 3;

# 12. Find the size of the SCHEMA/USER.
# Fetching required data from Information_Schema
SELECT
  table_schema                                  "Data Base Name",
  sum(data_length + index_length) / 1024 / 1024 "Data Base Size in MB"
FROM information_schema.TABLES
GROUP BY table_schema;

# 13. Display year, month, day as separate attributes from employee’s date of birth.
# not.
# Using YEAR,MONTH,DAY
SELECT
  Bdate,
  YEAR(Bdate)  Year,
  MONTH(Bdate) Month,
  DAY(Bdate)   Day
FROM Employee;
# Using EXTRACT
SELECT
  Bdate,
  EXTRACT(YEAR_MONTH FROM Bdate),
  EXTRACT(DAY_MINUTE FROM Bdate),
  EXTRACT(YEAR FROM Bdate)  Year,
  EXTRACT(MONTH FROM Bdate) Month,
  EXTRACT(DAY FROM Bdate)   Day
FROM Employee;

# 14. Display the current time.
# using the current_time Keyword
SELECT CURRENT_TIME();
# Using SYSDATE
SELECT TIME(SYSDATE());
# FROM Current time stamp
SELECT TIME(CURRENT_TIMESTAMP);
# using system command gives entire date and time and AGGREGATION WITH TIME(system date) dowsn't work
system date;

# Some more interesting keywords
# Using TIME FORMAT to change 24 HR to 12 HR
SELECT TIME_FORMAT(CURRENT_TIME(),'%r');
SELECT TIME_FORMAT(CURRENT_TIME(),'%l:%i:%s %p');

# 15. Retrieve the date part of the date or datetime expression.
# FROM custom time stamp
SELECT DATE('2008-09-22 15:24:13.970');
# FROM Current time stamp
SELECT DATE(CURRENT_TIMESTAMP);

# 16. Given a date, retrieve the next day’s date.
# adding Interval of a day because just adding +1 to a date has limits at end of month date
SELECT
  Bdate,
  (Bdate + INTERVAL 1 DAY) Next_Day
FROM Employee;

# 17. Get position of 'a' in name 'Sundar Pitchai' from employee table.
# Way 1
# using Position
SELECT
  Fname,
  POSITION('a' IN Fname) "POSITION OF First a IN NAME"
FROM Employee;
# Way2
# using Locate
SELECT
  Fname,
  LOCATE('a',Fname) "POSITION OF First a IN NAME"
FROM Employee;
# Way 3
# Using INSTR Gives the first occurence position
SELECT
  Fname,
  INSTR(Fname,'a') "POSITION OF First a IN NAME"
FROM Employee;

# 18. Get fname from employee table after removing white spaces from left side.
SELECT LTRIM(Fname)
FROM Employee;

# 19. Get length of fname from employee table.
SELECT
  Fname,
  LENGTH(Fname)
FROM Employee;

# 20. Get fname from employee table after replacing 'o' with '*'.
SELECT REPLACE(Fname, 'O', '*')
FROM Employee;

# 21. Get fname and lname as a single attribute from employee table separated by a '_'.
# Using CONCAT
SELECT CONCAT(Fname, '_', Lname)
FROM Employee;
# Using CONCAT_WS()
SELECT CONCAT_WS('_',Fname,Lname)
FROM Employee;

# 22. Find all employee records containing the word "Jai", regardless of whether it was
# stored as JAI, Jai, or jai.
# Using CONCAT and LIKE to compare entire Row
SELECT *
FROM Employee
WHERE CONCAT(Fname, Minit, Lname, Ssn, Bdate, Address, Sex, Salary, Super_ssn, Dno) LIKE '%John%';
# Using REGEXP

# 23. Find the number of employees according to the gender whose DOB is between
# 05/01/1980 to 31/12/2016.
SELECT
  Sex,
  COUNT(*)
FROM Employee
WHERE Bdate BETWEEN '1960-12-31' AND '1980-01-05'
GROUP BY Sex;

# 24. Retrieve the mysql username and password.
# To DISPLAY USER DETAILS
SELECT
  user,
  authentication_string
FROM mysql.user
WHERE user = 'root';

# 25. Find all the employee first name/s whose name consists of three or more words.
# Using LIKE
SELECT Fname
FROM Employee
WHERE Fname LIKE '% % %';
# Using REGEXP
SELECT Fname
FROM Employee
WHERE Fname REGEXP ' . ';
# Using Length and Replace to count the number of substrings present
SELECT Fname
FROM Employee
WHERE (LENGTH(Fname) - LENGTH(REPLACE(CONCAT(Fname), ' ', '')))/LENGTH(' ')=2;

# 26. Get employee details from employee table whose first name ends with 'n' and name
# contains 4 letters.
# Using Like and Length
SELECT *
FROM Employee
WHERE Fname LIKE '%n' AND LENGTH(Fname) = 4;
# Using just Like
SELECT *
FROM Employee
WHERE Fname LIKE '___N';
# Using REGEXP and Length
SELECT *
FROM Employee
WHERE Fname REGEXP 'n$' AND LENGTH(Fname) = 4;
# Using Just REGEXP
SELECT *
FROM Employee
WHERE Fname REGEXP '^.{3}n$';

# 27. Get employee details from employee table whose joining month is “January”.
SELECT *
FROM Employee
WHERE MONTH(Bdate) = 01;

# 28. Get database date.
# CURRENT DATE
SELECT DATE(NOW());
# DB CREATION DATE
SELECT MIN(create_time)
FROM INFORMATION_SCHEMA.TABLES
WHERE table_schema = 'Company1';
# TABLE CREATION DATE
SELECT create_time
FROM INFORMATION_SCHEMA.TABLES
WHERE table_schema = 'Company1' AND table_name = 'Department';

# 29. Fetch data that are common in two query results.
# Using Join
SELECT A.*
FROM (SELECT *
      FROM Employee
      WHERE Sex = 'F') A
  JOIN (SELECT *
        FROM Employee
        WHERE Salary > 40000) B ON A.Ssn = B.Ssn;

# 30. Get first names of employees who has '*' in last_name.
# Using Like
SELECT Fname
FROM Employee
WHERE Lname LIKE '%*%';
# Using REGEXP
SELECT Fname
FROM Employee
WHERE Lname REGEXP '[*]';

# 31. Find department from dept table after replacing special character with a white space.
SELECT REPLACE(Address, '', ' ')
FROM Employee;

# 32. Retrieve the number of employees joined with respect to a particular year and a
# particular month from employee table.
SELECT
  YEAR(Bdate),
  MONTH(Bdate),
  COUNT(*)
FROM Employee
GROUP BY YEAR(Bdate), MONTH(Bdate);

# 33. Extract characters within a specified range of length from department field.
# Using SUBSTR
SELECT
  SUBSTR(Dname, 3, 6),
  SUBSTR(Dname FROM 3 FOR 6)
FROM Department;
# Using SUBSTRING
SELECT
  SUBSTRING(Dname, 3, 6),
  SUBSTRING(Dname FROM 3 FOR 6)
FROM Department;

# 34. Convert the name of the employee to lowercase and then as uppercase.
# JUST DISPLAY
SELECT
  LOWER(Fname),
  LCASE(Fname),
  UPPER(Fname),
  UCASE(Fname)
FROM Employee;
# TO LOWER
UPDATE Employee
SET Fname = LOWER(Fname);
# TO UPPER
UPDATE Employee
SET Fname = UPPER(Fname);
# TO LCASE
UPDATE Employee
SET Fname = LCASE(Fname);
# TO UCASE
UPDATE Employee
SET Fname = UCASE(Fname);

# 35. Select FIRST n records from a department table.
# Using LIMIT
SELECT *
FROM Department
LIMIT 2;

# 36. Select LAST n records from a department table.
# SET @rn=0;
# SELECT @rn:=COUNT(*)-3 FROM Employee;
# Using Offset of M-n where M=size of table and n=to be shown rows
SELECT *
FROM Employee
LIMIT 3 OFFSET 6;

# 37. Select first name from employee table which contain only numbers.
# USING ASCII AND LOWER UPPER
SELECT *
FROM Employee
WHERE ASCII(LOWER(Fname)) = ASCII(UPPER(Fname));
# USING REGEXP
SELECT *
FROM Employee
WHERE Fname REGEXP '^[0-9]+$';

# 38. Get fname, lname from employee table as separate rows.
# Using GROUP_CONCAT
(SELECT
   "Fname: ",
   GROUP_CONCAT(Fname SEPARATOR ', ')
 FROM Employee)
UNION (SELECT
         "Lname: ",
         GROUP_CONCAT(Lname SEPARATOR ', ')
       FROM Employee);

# 39. Create an empty table emptem with the same structure as emp.
# Way 1
CREATE TABLE Emptem AS SELECT *
                       FROM Employee
                       WHERE 1 != 1;
# Way 2
CREATE TABLE Emptem AS SELECT *
                       FROM Employee
                       LIMIT 0;
# Way 3
CREATE TABLE Emptem LIKE Employee;
# Displaying entire new table to check the query
SELECT *
FROM Emptem;

# 40. If there are two tables emp1 and emp2, and both have common records. Fetch all the
# records, but common records only once?
# Inserting some records into emptem
INSERT INTO
Emptem VALUES
  ('John','B','Smith',123456789,'1965-01-09','731 Fondren, Houston, TX','M',30000,333445555,5),
  ('Franklin','T','Wong',333445555,'1955-12-08','638 Voss, Houston, TX','M',40000,888665555,5),
  ('Joyce','A','English',453453453,'1972-07-31','5631 Rice, Houston, TX','F',25000,333445555,5);
# Using UNION
(SELECT *
 FROM Emptem)
UNION (SELECT *
       FROM Employee);

# 41. Extract only common records from two tables emp1 and emp2?
# Using INNER JOIN
SELECT Emptem.*
FROM Emptem
  JOIN Employee WHERE Emptem.Ssn=Employee.Ssn;

# 42. Retrieve all records of emp1 those should not present in emp2?
SELECT *
FROM Employee
WHERE NOT EXISTS(SELECT *
                 FROM Emptem
                 WHERE Emptem.Ssn = Employee.Ssn);

# 43. Returns the default (current) database name.
# Using Database()
SELECT DATABASE();
# Using Schema()
SELECT SCHEMA();

# 44. Retrieve the current MySQL user name and host name.
# Using CURRENT_USER()
SELECT CURRENT_USER;
# Using User()
SELECT USER();

# 45. Find the string that tells the MySQL server version.
SELECT
  SUBSTR(VERSION(), LOCATE('-', VERSION()) + 1)    AS "OS",
  SUBSTR(VERSION(), 1, LOCATE('-', VERSION()) - 1) AS "Mysql Server Version";

# 46. Perform Bitwise OR, Bitwise XOR and Bitwise AND.
# Declaring 2 Variables and Initializing them
SET @a=15,@b=39;
# Using |,&,^ to do the required Bitwise Operation
SELECT (@a | @b) AS "BITWISE OR (a,b)",
       (@a & @b) AS "BITWISE AND (a,b)",
       (@a ^ @b) AS "BITWISE XOR (a,b)";

# 47. Find rows that contain at least one of the two words ‘voss’, ‘castle’.
# Using CONCAT and REGEXP to compare entire Row (Other way is to use LIKE and DO an OR)
SELECT *
FROM Employee
WHERE CONCAT(Fname, Minit, Lname, Ssn, Bdate, Address, Sex, Salary, Super_ssn, Dno) REGEXP 'voss|castle';
# Comparing Entire row

# 48. Find the difference between two dates and print in terms of the number of days.
# Using DATEDIFF
SELECT
  Fname,
  Lname,
  DATEDIFF(CURRENT_DATE,Bdate) AS "AGE IN DAYS"
FROM Employee;

# 49. Add one day to the current date.
# Using + INTERVAL
SELECT CURRENT_DATE + INTERVAL 1 DAY;
# Using DATE_ADD
SELECT DATE_ADD(CURRENT_DATE,INTERVAL 1 DAY);
# Using ADDDATE
SELECT ADDDATE(CURRENT_DATE,INTERVAL 1 DAY);
SELECT ADDDATE('2017-03-31',1); # ADD DATE CAN BE USED WITHOUT INTERVAL ADDING DAYS IN DEFAULT

# 50. Add two hours and 5000 minutes to the current date and print the new date.
# Using +INTERVAL
SELECT CURRENT_TIMESTAMP + INTERVAL 2 HOUR + INTERVAL 5000 MINUTE;

# 51. Find the floor and ceil values of a floating point number. Also operate on the power,
# log, modulus, round off and truncate functions.
# Declaring a variabkle and initialising it
SET @flop1=3.2554;
# Using all possible Mathematical Functions in mysql
SELECT
  @flop1,
  ABS(-33),
  FLOOR(@flop1),
  CEIL(@flop1),
  ROUND(@flop1,2),
  ROUND(POWER(@flop1,2),4),
  LOG10(@flop1),
  LOG2(@flop1),
  LOG(2,@flop1),
  MOD(FLOOR(@flop1),CEIL(@flop1)),
  TRUNCATE(@flop1,2);

# 52. In a string attribute of the company schema, match the following using regular
# expression.
# -----NOTE: For CASE SENSITIVE Comparisons sue REGEXP BINARY
# a) Beginning of the string.
SELECT *
FROM Employee
WHERE Fname REGEXP '^[a-f]';

# b) Match any character (including carriage return and newline).
SELECT *
FROM Employee
WHERE Address REGEXP '^.*$';

# c) Match the end of a string.
SELECT *
FROM Employee
WHERE Fname REGEXP '[a-f]$';

# d) Any sequence of zero or more 'a' characters.
SELECT *
FROM Employee
WHERE Fname REGEXP 'a*';

# e) Either of the sequences xy or abc.
SELECT *
FROM Employee
WHERE Fname REGEXP 'ahm|fra|ali';

# 53. Compare two strings and print the value ‘yes’ if they are equal, else ‘no’.
# Using STRCMP
SELECT IF(STRCMP('test', 'test'), 'NO', 'YES') STRING_COMPARE;
# Using LIKE
SELECT IF('test' LIKE 'test1', 'YES', 'NO') STRING_COMPARE;

# 54. Simulate the “IF... ELSE” construct in Mysql for a mark and grade setup.
# Using only NESTED IF
SET @mark=65;
SELECT IF(@mark > 90,
          'A', IF(@mark > 80,
                  'B', IF(@mark > 70,
                          'C', IF(@mark > 60,
                                  'D', IF(@mark > 50,
                                          'E', IF(@mark > 40,
                                                  'F', 'U')))))) AS GRADE;
# CASE WHEN THEN ELSE
SET @mark=65;
SELECT
  @mark        AS MARK,
  CASE WHEN @mark > 90
    THEN 'A'
  WHEN @mark > 80
    THEN 'B'
  WHEN @mark > 70
    THEN 'C'
  WHEN @mark > 60
    THEN 'D'
  WHEN @mark > 50
    THEN 'E'
  WHEN @mark > 40
    THEN 'F'
  ELSE 'U' END AS GRADE;

# 55. Use IFNULL to check whether an mathematical expression gives a NULL value or
# not.
SELECT IFNULL(1/0,'YES');

# 56. Grant all the access privileges to a user.
# GRANT ALL PRIVILEGES ON *.* TO 'user'@'%'
# WITH GRANT OPTION;
# GRANT ALL PRIVILEGES ON mydb.* TO myuser@localhost
# IDENTIFIED BY 'mypasswd';
GRANT ALL PRIVILEGES ON Company1.* TO akshay@localhost
IDENTIFIED BY 'qaz';

# Deleting unnecessary Tables
DROP TABLE IF EXISTS Emptem;
DROP TABLE IF EXISTS COPYEMP;

# Disable Outfile
notee;
