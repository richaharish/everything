
//To install mysql header files -> apt-get install libmysqlclient-dev
//To run embedded sql in c -> gcc test1.c `mysql_config --cflags --libs`

#include <mysql.h>
#include <stdio.h>

void main() {
   MYSQL *conn;
   MYSQL_RES *res;
   MYSQL_ROW row;

   char *server = "localhost"; // localhost for accessing local mysql
   char *user = "root";// root for students
   char *password = "iiitdm123"; /* set me first - pwd : iiitdm123 */ 
   char *database = "test"; // Here you need to enter the database name if you have already other wise leave it free.

   conn = mysql_init(NULL);

   /* Connect to database */
   if (!mysql_real_connect(conn, server,
         user, password, database, 0, NULL, 0)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
//char name[20];
//int age,n=5,tmp;
//printf("Enter the new name and new age");
//scanf("%s %d",name,&age);

/*// create employee table
if (mysql_query(conn, "create table employee (name varchar(50),ssn int, dob date,salary int, superssn int, dno int)")) 
{
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
*/
/* Add primary key 
if (mysql_query(conn, "alter table employee add primary key (ssn)")) 
{
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
//add auto_increment
if (mysql_query(conn, "ALTER TABLE employee modify column ssn int not null auto_increment")) 
{
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
*/
/*
*/


/*
// Insertion on employee table Example-- start
char name[20];
int yr,mnth,date,sal,sssn,dno,n;
char statement[512], *my_str = "MyString";
printf("Enter the number of records:");
scanf("%d",&n);
for (int i=0;i<n;i++)
{
printf("Enter the name ");
scanf("%s",name);
printf("Enter the dob (yyyy-mm-dd)");
scanf("%d-%d-%d",&yr,&mnth,&date);
printf("Enter the salary ");
scanf("%d",&sal);
printf("Enter the super SSN ");
scanf("%d",&sssn);
printf("Enter the Department No: ");
scanf("%d",&dno);
snprintf(statement, 512, "INSERT INTO employee VALUES ('%s',ssn,'%d-%d-%d',%d,%d,%d)", name,yr,mnth,date,sal,sssn,dno);
mysql_query(conn, statement);
}
*/


/*
// create department table
if (mysql_query(conn, "create table department (dname varchar(50),dnumber int not null auto_increment, mssn int,primary key(dnumber))")) 
{
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }

//Add primary key on Department table 
if (mysql_query(conn, "alter table department add primary key (dnumber)")) 
{
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
//add auto_increment on Department No
if (mysql_query(conn, "ALTER TABLE department modify column dnumber int not null auto_increment")) 
{
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }



// set foreign key for super ssn (superssn)
if (mysql_query(conn, "alter table employee add constraint c1 foreign key (superssn) references employee(ssn) ")) 
{
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }


// Insertion on department table Example-- start
char dname[20];
int mssn,n;
char statement[512], *my_str = "MyString";
printf("Enter the number of records:");
scanf("%d",&n);
for (int i=0;i<n;i++)
{
printf("Enter the department name ");
scanf("%s",dname);
printf("Enter the manager ssn");
scanf("%d",&mssn);
snprintf(statement, 512, "INSERT INTO department VALUES ('%s',dnumber,%d)", dname,mssn);
mysql_query(conn, statement);
}


// set foreign key for department no (dno)
if (mysql_query(conn, "alter table employee add foreign key (dno) references department(dnumber) ")) 
{
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }


if (mysql_query(conn, "alter table department add foreign key (mssn) references employee(ssn) ")) 
{
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }


// Update employee table 
char dname[20];
int age,n=5,tmp,salary,ssn;
char statement[1024], *my_str = "MyString";
printf("Enter the ssn number");
scanf("%d",&ssn);
printf("Enter the new employee Name");
scanf("%s",dname);
printf("Enter the new employee salary");
scanf("%d",&salary);
snprintf(statement, 1024, "UPDATE employee SET name='%s',salary=%d  WHERE ssn=%d", dname,salary,ssn);
mysql_query(conn, statement);



// select key word queries
if (mysql_query(conn, "select max(salary) from employee")) 
{
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
   res = mysql_use_result(conn);
while ((row = mysql_fetch_row(res)) != NULL)
      printf("%s \n", row[0]);
mysql_free_result(res);


*/

if (mysql_query(conn,"SELECT * from employee")) 
{
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
res = mysql_use_result(conn);

unsigned long *lengths;
unsigned int num_fields;
/*
the arguments for "%.*s"  are the string width and the target string.
it's syntax is :
printf("%.*s", string_width, string);
*/
int i;
while ((row = mysql_fetch_row(res)) != NULL)
{
num_fields = mysql_num_fields(res);
    lengths = mysql_fetch_lengths(res);
    for(i = 0; i < num_fields; i++)
    {
//printf("%d",lengths[i]);
printf("%s\t",row[i]);
//printf("%7.*s \t", (int) lengths[i],row[i] ? row[i] : "NULL");
         //printf("Column %u is %lu bytes in length.\n",i, lengths[i]);
//printf("%s \n", row[i]);
    }
printf("\n");
}
      //printf("%s \n", row[0]);

mysql_free_result(res);




// Update Example-- End



/*
// Update Example-- start
char name[20];
int age,n=5,tmp;
char statement[1024], *my_str = "MyString";

for (int i=0;i<n;i++)
{
printf("Enter the old age");
scanf("%d",&tmp);

printf("Enter the new name and new age");
scanf("%s %d",name,&age);
snprintf(statement, 1024, "UPDATE employee SET name='%s' WHERE rno=%d", name,tmp);
mysql_query(conn, statement);

}
// Update Example-- End

// Insertion Example-- End

   /* send SQL query */
  /* if (mysql_query(conn, "insert into employee values ('ram',2);\
 insert into employee values ('raja',22);\
")) 
{
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }
*/
   res = mysql_use_result(conn);

   /* output table name */
/*
printf("MySQL Tables in mysql database:\n");
   while ((row = mysql_fetch_row(res)) != NULL)
      printf("%s \n", row[0]);
*/
   /* close connection */

   mysql_free_result(res);
   mysql_close(conn);
}
