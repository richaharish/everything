#include <mysql.h>
#include <stdio.h>

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;
void query1()
{
    char place1[20],place2[20];
    char statement[1024];
    printf("Enter the name of place from where you want to take a flight\n");
    scanf("%s",place1);
    printf("Enter the name of place to where you want to take a flight\n");
    scanf("%s",place2);
    snprintf(statement,1024,"SELECT * from flights where fromplace='%s' and toplace='%s' ",place1,place2);
    if (mysql_query(conn,statement )) 
                          {
                             fprintf(stderr, "%s\n", mysql_error(conn));
                             exit(1);
                          }
                          res = mysql_use_result(conn);
                          unsigned long *lengths;
                          unsigned int num_fields;
                          int i;
                          printf("\nflno\tfromplace\ttoplace\tdistance\tdeparts\tarrives\tprice\n\n");
                          while ((row = mysql_fetch_row(res)) != NULL)
                          {
                             num_fields = mysql_num_fields(res);
                             lengths = mysql_fetch_lengths(res);
                             for(i = 0; i < num_fields; i++)
                             {
                                printf("%s\t",row[i]);
                             }
                             printf("\n");
                          }
                          mysql_free_result(res);

}

void query2()
{
     int gender,ans;
     int age;
     printf("Are you a student 1. if yes 2. if no\n");
     scanf("%d",&ans);

     if (ans==1)
     {
        printf("you are eligible for a discount of 15%% \n\n");
     }
     
     else
     {     printf("Enter your age \n");
	   scanf("%d",&age);
	     
	     
	   if((age>65)||(age<5))
	     {
		printf("Enter the gender 1.if female 2. if male \n\n");
		scanf("%d",&gender);

		if(gender==1)
		{
		   printf("you are eligible for discount of 20%% \n\n");
		}
		else if (gender==2)
		{
		   printf("you are eligible for a  discount of 10%%\n \n");
		}
	      }
            else
            {
               printf("You are not eligible for any discount \n\n");
            }
    }
}

void query3()
{
    char airlines[20],statement[1024];
    printf("Enter the name of the airlines\n");
    scanf("%s",airlines);
    snprintf(statement,1024,"SELECT e.ename from employees e ,certified c,aircraft a where e.eid=c.eid and c.aid=a.aid and a.aname='%s' ",airlines);
    if (mysql_query(conn,statement )) 
                          {
                             fprintf(stderr, "%s\n", mysql_error(conn));
                             exit(1);
                          }
                          res = mysql_use_result(conn);
                          unsigned long *lengths;
                          unsigned int num_fields;
                          int i;
                          printf("\nnames \n\n");
                          while ((row = mysql_fetch_row(res)) != NULL)
                          {
                             num_fields = mysql_num_fields(res);
                             lengths = mysql_fetch_lengths(res);
                             for(i = 0; i < num_fields; i++)
                             {
                                printf("%s\t",row[i]);
                             }
                             printf("\n");
                          }
                          mysql_free_result(res);

}
void query4()
{
    char place1[20],place2[20],statement[512];
    printf("enter the source and the destination\n");
    scanf("%s%s",place1,place2);
    snprintf(statement,512,"select aid,aname from aircraft where cruisingrange in (select distance from flights where fromplace='%s' and toplace='%s')",place1,place2);
    if(mysql_query(conn,statement))
               {
                             fprintf(stderr, "%s\n", mysql_error(conn));
                             exit(1);
                          }
                          res = mysql_use_result(conn);
                          unsigned long *lengths;
                          unsigned int num_fields;
                          int i;
                          printf("\naircraftid\taname \n\n");
                          while ((row = mysql_fetch_row(res)) != NULL)
                          {
                             num_fields = mysql_num_fields(res);
                             lengths = mysql_fetch_lengths(res);
                             for(i = 0; i < num_fields; i++)
                             {
                                printf("%s\t\t",row[i]);
                             }
                             printf("\n");
                          }
                          mysql_free_result(res);

}
void query5()
{
   int fare;
   char statement[512];
   printf("Enter the fare range ");
   scanf("%d",&fare);
   snprintf(statement,512,"select flno,price from flights where price<=%d",fare);
   if(mysql_query(conn,statement))
   {
                             fprintf(stderr, "%s\n", mysql_error(conn));
                             exit(1);
                          }
                          res = mysql_use_result(conn);
                          unsigned long *lengths;
                          unsigned int num_fields;
                          int i;
                          printf("\nflno\t\tprice \n\n");
                          while ((row = mysql_fetch_row(res)) != NULL)
                          {
                             num_fields = mysql_num_fields(res);
                             lengths = mysql_fetch_lengths(res);
                             for(i = 0; i < num_fields; i++)
                             {
                                printf("%s\t\t",row[i]);
                             }
                             printf("\n");
                          }
                          mysql_free_result(res);
}

void main() 
{
	  
	   char *server = "localhost"; // localhost for accessing local mysql
	   char *user = "root";// root for students
	   char *password = "lovemum"; /* set me first - pwd : lovemum */ 
	   char *database = "flight"; // Here you need to enter the database name if you have  already other wise leave it free.

	   conn = mysql_init(NULL);

   /* Connect to database */
   if (!mysql_real_connect(conn, server,user, password, database, 0, NULL, 0))
	 {
	      fprintf(stderr, "%s\n", mysql_error(conn));
	      exit(1);
	 }
 
	int choice=0,ch,n,a;
	int aid,aid1,aid2,aid3,aid4,aid6,aid5,cruisingrange ,eid,eid2,eid6,eid3,eid5,eid4,salary;
	int flno,flno1,flno2,distance;
        double price;
	char fromplace[20],toplace[20],departs[10],arrives[10];
	char statement [512];
        char statement1[512];
        char statement2[512];
        char statement3[512];
        
        char statement4[1024];
        char statement5[1024];
        char statement6[1024];
        char statement7[1024];
        char statement8 [512];
        char statement9[512];
        char statement10[512];
        char statement11[512];
        char aname[20],ename[20];
	char *my_str = "MyString";
	 
	 
	while(choice!=6)
{ 
// Insertion on employee table Example-- start
	printf("Enter\n1. manipulate tables \n2. look at available flights to a destination\n3. discounts available \n4. names of employees of a particular airline \n5. aircrafts that can be used for a particular route  \n6. check flights according to their cost  \n7. details\n8. exit\n");
	scanf("%d",&choice);
	switch(choice)
	{
            case 1:
               printf("\n1. to insert \n2. to delete \n3. to update\n\n");
               scanf("%d",&a);
               switch(a)
            {
               case 1:
               printf("\nEnter \n1. into aircraft \n2. into certified \n3. into employees \n4. into flights\n   ");

               scanf("%d ",&ch);

               if(ch==1)
	     {
                  printf("Enter the number of records:\n");
                  scanf("%d",&n);

                  for(int i=0;i<n;i++)
                  {
                     printf("Enter the aircraftid ");
                     scanf("%d",&aid);
                     printf("\n");
                     printf("Enter the aircraftname ");
                     scanf("%s",aname);
                     printf("\n");
                     printf("Enter the cruisingrange");
                     scanf("%d",&cruisingrange);
                     printf("\n");
                     snprintf(statement, 512, "INSERT INTO aircraft VALUES ('%d','%s','%d')", aid,aname,cruisingrange);
                     mysql_query(conn, statement);
                  }

             }	
               if(ch==2)
               {
                   printf("Enter the number of records:");

                   scanf("%d",&n); 

                  for(int i=0;i<n;i++)
                  {
                     printf("Enter the employeeid ");
                     scanf("%d",&eid);
                     printf("\n");
                     printf("Enter the aircraftid ");
                     scanf("%d",&aid);
                     printf("\n");
                      
                     snprintf(statement1, 512, "INSERT INTO certified VALUES ('eid','aid')");
                     mysql_query(conn, statement1);
                  }
                   
               }
               if(ch==3)
               {
                printf("Enter the number of records:");
                  scanf("%d",&n);

                  for(int i=0;i<n;i++)
                  {
                     printf("Enter the employeeid ");
                     scanf("%d",&eid);
                     printf("\n");
                     printf("Enter the employeename ");
                     scanf("%s",ename);
                     printf("\n");
                     printf("Enter the salary");
                     scanf("%d",&salary);
                     printf("\n");
                     snprintf(statement2, 512, "INSERT INTO employees VALUES ('%d','%s','%d')", eid,ename,salary);
                     mysql_query(conn, statement2);
                  }

               }

              
               if(ch==4)
               {
                printf("Enter the number of records:");
                  scanf("%d",&n);
                  for(int i=0;i<n;i++)
                  {
                     printf("Enter the flightnumber ");
                     scanf("%d",&flno);
                     printf("\n");
                     printf("Enter the fromplace");
                     scanf("%s",fromplace);
                     printf("\n");
                     printf("Enter the toplace");
                     scanf("%s",toplace);
                     printf("\n");
                     printf("Enter the distance");
                     scanf("%d",&distance);
                     printf("\n");
                     printf("Enter the departs");
                     scanf("%s",departs);
                     printf("\n");
                     printf("Enter the arrives");
                     scanf("%s",arrives);
                     printf("\n");
                     printf("Enter the price");
                     scanf("%lf",&price);
                     printf("\n");
                     snprintf(statement3, 512, "INSERT INTO flights VALUES ('%d','%s','%s','%d','%s','%s','%lf')",flno,fromplace,toplace,distance,departs,arrives,price);
                     mysql_query(conn, statement3);
                  }
               }
               
               break;
               
            case 2:
         
         printf("Enter \n1. update aircraft\n2. update certified\n3. update employees\n4. update flights\n   ");
               scanf("%d ",&ch);
               if(ch==1)
	     {
                     printf("Enter the aircraftid ");
                     scanf("%d",&aid1);
                     printf("\n");
                     printf("Enter the new aircraftname ");
                     scanf("%s",aname);
                     printf("\n");
                     printf("Enter the new cruisingrange");
                     scanf("%d",&cruisingrange);
                     printf("\n");
                     snprintf(statement4, 1024, "UPDATE aircraft SET cruisingrange=%d,aname='%s'  WHERE aid=%d",cruisingrange,aname,aid1);
                     mysql_query(conn, statement4);
                   
             }	
               if(ch==2)
             {
                    
                     printf("Enter the new employeeid ");
                     scanf("%d",&eid2);
                     printf("\n");
                     printf("Enter the new aircraftid ");
                     scanf("%d",&aid2);
                     printf("\n");
                      
                     snprintf(statement5, 1024, "UPDATE  certified SET  eid=%d,aid=%d WHERE aid=%d and eid=%d",eid,aid,aid2,eid2);
                    
                     mysql_query(conn, statement5);
                   
                   
            }
               if(ch==3)
               {
                
                     printf("Enter the   employeeid ");
                     scanf("%d",&eid3);
                     printf("\n");
                     printf("Enter the new employeename ");
                     scanf("%s",ename);
                     printf("\n");
                     printf("Enter the  new salary");
                     scanf("%d",&salary);
                     printf("\n");
                     snprintf(statement6, 1024, "UPDATE employees SET employeename='%s',newsalary=%d WHERE employeeid=%d" ,ename,salary,eid3);
                     mysql_query(conn, statement6);
                   
               }
               if(ch==4)
                 {
                     printf("Enter the flightnumber ");
                     scanf("%d",&flno1);
                     printf("\n");
                     printf("Enter the new fromplace");
                     scanf("%s",fromplace);
                     printf("\n");
                     printf("Enter the new toplace");
                     scanf("%s",toplace);
                     printf("\n");
                     printf("Enter the new distance");
                     scanf("%d",&distance);
                     printf("\n");
                     printf("Enter the new departure time");
                     scanf("%s",departs);
                     printf("\n");
                     printf("Enter the new arrival time");
                     scanf("%s",arrives);
                     printf("\n");
                     printf("Enter the new price");
                     scanf("%lf",&price);
                     printf("\n");
                     snprintf(statement7, 1024, "UPDATE flights SET fromplace='%s',toplace='%s',distance=%d,departs='%s',arrives='%s',price='%lf' WHERE flno=%d" ,fromplace,toplace,distance,departs,arrives,price,flno1);
                     mysql_query(conn, statement7);
                   
               }
               break;
            case 3:
               printf("delete \n1. aircraft\n2. certified\n3. employees\n4. flights\n"); 
               scanf("%d",&ch);
               if(ch==1)
               {
                   printf("Enter the aid of the record which has to be deleted ");
                   scanf("%d",&aid4);
                   printf("\n");
                   snprintf(statement8, 512 ,"DELETE FROM aircraft WHERE aid=%d ",aid4);
                   mysql_query(conn,statement8);
               }
               else if(ch==2)
               {
                   printf("Enter the aid and the eid of the record that has to be deleted");
                   scanf("%d%d",&aid5,&eid5);
                   printf("\n");
                   snprintf(statement9,512,"delete from certified where aid=%d and eid=%d",aid5,eid5);
                   mysql_query(conn,statement9);
               }
               else if(ch==3)
               {
                   printf("Enter the eid of the record which has to be deleted ");
                   scanf("%d",&eid6);
                   printf("\n");
                   snprintf(statement10, 512 ,"DELETE FROM eemployee WHERE eid=%d ",eid6);
                   mysql_query(conn,statement10);
               }
               else if(ch==4)
               {
                   printf("Enter the flno of the record that has to be deleted");
                   scanf("%d",&flno2);
                   printf("\n");
                   snprintf(statement11,512,"delete from flights where flno=%d ",flno2);
                   mysql_query(conn,statement11);
               }
               break;
              }
               break;
        case 2:
               query1();
               break; 
        case 3:
              query2();
              break;
        case 4:
              query3();
              break; 
        case 5:
              query4();
              break;
       case 6:
              query5();
                break;
        case 7:
               printf("Enter \n1. to display aircraft \n2. to display certified \n3. to display employees \n4. to display flights\n");
               scanf("%d",&ch);
               if(ch==1)
              {
                          if (mysql_query(conn,"SELECT * from aircraft")) 
                          {
                             fprintf(stderr, "%s\n", mysql_error(conn));
                             exit(1);
                          }
                          res = mysql_use_result(conn);
                          unsigned long *lengths;
                          unsigned int num_fields;
                          int i;
                          printf("\naid\taname\t\tcruisingrange\n\n");
                          while ((row = mysql_fetch_row(res)) != NULL)
                          {
                             num_fields = mysql_num_fields(res);
                             lengths = mysql_fetch_lengths(res);
                             for(i = 0; i < num_fields; i++)
                             {
                                printf("%s\t",row[i]);
                             }
                             printf("\n");
                          }
                          mysql_free_result(res);

			  
              }  
               if (ch==2)
               {
                    if (mysql_query(conn,"SELECT * from certified")) 
                                {
                                fprintf(stderr, "%s\n", mysql_error(conn));
                                exit(1);
                                }
                                res = mysql_use_result(conn);
                                unsigned long *lengths;
                                unsigned int num_fields;
                                int i;
                                printf("\neid\taid\n\n");
                                while ((row = mysql_fetch_row(res)) != NULL)
                                {
                                 num_fields = mysql_num_fields(res);
                                 lengths = mysql_fetch_lengths(res);
                                 for(i = 0; i < num_fields; i++)
                                  {
                                   printf("%s\t",row[i]);
                                  }
                                   printf("\n");
                                }
                                mysql_free_result(res);

				
               }  
               if (ch==3)
               {
                  if (mysql_query(conn,"SELECT * from employees")) 
                                {
                                fprintf(stderr, "%s\n", mysql_error(conn));
                                exit(1);
                                }
                                res = mysql_use_result(conn);
                                unsigned long *lengths;
                                unsigned int num_fields;
                                int i;
                                printf("\neid\tename\tsalary\n\n");
                                while ((row = mysql_fetch_row(res)) != NULL)
                                {
                                 num_fields = mysql_num_fields(res);
                                 lengths = mysql_fetch_lengths(res);
                                 for(i = 0; i < num_fields; i++)
                                  {
                                   printf("%s\t",row[i]);
                                  }
                                   printf("\n");
                                }
                                mysql_free_result(res);

				
               }
              if(ch==4)
              {
                  if (mysql_query(conn,"SELECT * from flights")) 
                                {
                                fprintf(stderr, "%s\n", mysql_error(conn));
                                exit(1);
                                }
                                res = mysql_use_result(conn);
                                unsigned long *lengths;
                                unsigned int num_fields;
                                int i;
                                printf("\nflno\t\tfromplace\t\ttoplace\t\tdistance\t\tdeparts\t\tarrives\t\tprice\n\n");
                                while ((row = mysql_fetch_row(res)) != NULL)
                                {
                                 num_fields = mysql_num_fields(res);
                                 lengths = mysql_fetch_lengths(res);
                                 for(i = 0; i < num_fields; i++)
                                  {
                                   printf("%s\t\t",row[i]);
                                  }
                                   printf("\n");
                                }
                                mysql_free_result(res);

				
              }
               break;
           case 8:
               exit(0);
               break;
        }
 }
 

 

   
}
