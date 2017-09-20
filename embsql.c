#include <mysql.h>
#include <stdio.h>

void main() 
{
   MYSQL *conn;
   MYSQL_RES *res;
   MYSQL_ROW row;


   char *server = "localhost"; // localhost for accessing local mysql
   char *user = "root";// root for students
   char *password = "priyanka"; /* set me first - pwd : iiitdm123 */ 
   char *database = "flight"; // Here you need to enter the database name if you have already other wise leave it free.

    conn = mysql_init(NULL);

   /* Connect to database */
   if (!mysql_real_connect(conn, server,   user, password, database, 0, NULL, 0))
     {

      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);

     }



    int no,distance,q,no1,eid1,aid1,eid2,aid2;
    double price;
    char frm[20],too[20],departs[20],arrives[20];
    char statement4[512], *my_str4 = "MyString";
    char aname[20];
    int aid,cruisingrange,n,ch,op;
    char statement1[512], *my_str1 = "MyString";
    char statement3[512], *my_str3 = "MyString";
    char ename[20];
    int  eid,salary,m;
    char statement2[512], *my_str2 = "MyString";
    char statement5[512], *my_str5 = "MyString";
    char statement6[512], *my_str6 = "MyString";
    char statement7[512], *my_str7 = "MyString";
    char statement8[512], *my_str8 = "MyString";
    char statement9[1024], *my_str9 = "MyString";
    char statement10[1024], *my_str10 = "MyString";
    char statement11[1024], *my_str11 = "MyString";
    char statement12[1024], *my_str12 = "MyString";
    char statement13[1024], *my_str13 = "MyString";
    int p=8;
    //schema flight


do
{
   printf("Enter\n 1. to insert\n 2. to delete\n 3.update\n 4.display\n 5.exit\n");
   scanf("%d",&ch);
   switch(ch)
   {
      case 1: do
             { 
                printf("Enter\n1.insert in flight\n 2.insert in aircraft\n 3.insert in employees\n 4.insert in certified\n 5.exit\n");
                scanf("%d",&op);
                switch(op)
                    {
                         case 1:printf("Enter flight no : ");
                                scanf("%d",&no);
                                printf("\n");
                                printf("Enter frm : ");
                                scanf("%s",frm);
                                printf("\n");
                                printf("Enter too : ");
                                scanf("%s",too);
                                printf("\n");
                                printf("Enter distance: ");
                                scanf("%d",&distance);
                                printf("\n");
                                printf("Enter depart time: ");
                                scanf("%s",departs);
                                printf("\n");
                                printf("Enter arrive time: ");
                                scanf("%s",arrives);
                                printf("\n");
                                printf("Enter price: ");
                                scanf("%lf",&price);
                                printf("\n");
                                snprintf(statement4, 512, "INSERT INTO flight VALUES (%d,'%s','%s',%d,'%s','%s',%lf)",no,frm,too,distance,departs,arrives,price);
                                mysql_query(conn, statement4);

                                 
                                break;
                         case 2:printf("Enter aircraft id no: ");
                                scanf("%d",&aid);
                                printf("\n");
				printf("Enter the name ");
                                scanf("%s",aname);
                                printf("\n");
                                printf("Enter cruising range: ");
                                scanf("%d",&cruisingrange);
                                printf("\n");

                                snprintf(statement1, 512, "INSERT INTO aircraft VALUES (%d,'%s',%d)",aid,aname,cruisingrange);
                                mysql_query(conn, statement1);
                                  
                               break;
                         case 3:printf("Enter the name ");
                                scanf("%s",ename);
                                printf("\n");
                                printf("Enter employee id no: ");
                                scanf("%d",&eid);
                                printf("\n");
                                printf("Enter salary: ");
                                scanf("%d",&salary);
                                printf("\n");

                                snprintf(statement2, 512, "INSERT INTO employees VALUES (%d,'%s',%d)",eid,ename,salary);
                                mysql_query(conn, statement2);
                               
                                break;
                         case 4:printf("Enter employee id no: ");
                                scanf("%d",&eid);
                                printf("\n");
                                printf("Enter aircraft id no ");
                                scanf("%d",&aid);
                                printf("\n");
                                snprintf(statement3, 512, "INSERT INTO certified VALUES (%d,%d)",eid,aid);
                                mysql_query(conn, statement3);
                                break;
                         case 5:p=50;break;
                    }
             }while(p!=50);

      case 2:do
             { 
                printf("Enter\n1.delete from flight\n 2.delete from aircraft\n 3.delete from employees\n 4.delete from certified\n 5.exit\n");
                scanf("%d",&op);
                switch(op)
                    {
                         case 1:printf("enter the flight no to be deleted:");
    			        scanf("%d",&no1);
				printf("\n");
				snprintf(statement5, 512, "delete from flight where no=%d",no1);
                                mysql_query(conn, statement5);
				
				break;
			case 2:printf("enter the aircraft id to be deleted:");
    			        scanf("%d",&aid1);
				printf("\n");
				snprintf(statement6, 512, "delete from aircraft where aid=%d",aid1);
                                mysql_query(conn, statement6);	

				break;
			case 3:printf("enter the employee id to be deleted:");
    			        scanf("%d",&eid1);
				printf("\n");
				snprintf(statement7, 512, "delete from employees where eid=%d",eid1);
                                mysql_query(conn, statement7);	

				break;	
                        case 4:printf("enter the employee id to be deleted:");
    			        scanf("%d",&eid1);
				printf("\n");
				printf("enter the aircraft id to be deleted:");
    			        scanf("%d",&aid1);
				printf("\n");
				snprintf(statement8, 512, "delete from aircraft where eid=%d and aid=%d",eid1,aid1);
                                mysql_query(conn, statement8);	

				break;
		        case 5:	p=60;
				break;
                    }
	     }while(p!=60);
      case 3:do
	     { 
                printf("Enter\n1.update in flight\n 2.update in aircraft\n 3.update in employees\n 4.update in certified\n 5.exit\n");
                scanf("%d",&op);
                switch(op)
                    {
                         case 1:printf("enter the flight no to be updated:");
    			        scanf("%d",&no1);
 				printf("\n");
				printf("enter the new frm");
				scanf("%s",frm);
                                printf("\n");
                                printf("Enter the new too : ");
                                scanf("%s",too);
                                printf("\n");
                                printf("Enter the new distance: ");
                                scanf("%d",&distance);
                                printf("\n");
                                printf("Enter the new depart time: ");
                                scanf("%s",departs);
                                printf("\n");
                                printf("Enter the new arrive time: ");
                                scanf("%s",arrives);
                                printf("\n");
                                printf("Enter the new price: ");
                                scanf("%lf",&price);
                                printf("\n");
				snprintf(statement9, 1024, "UPDATE flight set frm='%s',too='%s',distance=%d,departs='%s',arrives='%s',price=%lf where no=%d",frm,too,distance,departs,arrives,price,no);
                                mysql_query(conn, statement9);
                                
				break;
			   case 2:
                                printf("Enter aircraft id no to be updated: ");
                                scanf("%d",&aid);
                                printf("\n");
				printf("Enter the new name ");
                                scanf("%s",aname);
                                printf("\n");
                                printf("Enter the new cruising range: ");
                                scanf("%d",&cruisingrange);
                                printf("\n");

                                snprintf(statement10, 1024, "UPDATE aircraft set aname='%s',cruisingrange=%d where aid=%d",aname,cruisingrange,aid);
                                mysql_query(conn, statement10);
                                  
                               break;
			    case 3:
                                printf("Enter employee id no to be updated: ");
                                scanf("%d",&eid);
                                printf("\n");
				printf("Enter the new ename ");
                                scanf("%s",ename);
                                printf("\n");
                                printf("Enter the new salary: ");
                                scanf("%d",&salary);
                                printf("\n");

                                snprintf(statement11, 1024, "UPDATE employees set ename='%s',salary=%d where eid=%d",ename,salary,eid);
                                mysql_query(conn, statement11);
                                  
                               break;
			   case 4:printf("enter the employee id to be updated:");
    			        scanf("%d",&eid1);
				printf("\n");
				printf("enter the aircraft id to be updated:");
    			        scanf("%d",&aid1);
				printf("enter the  new employee id:");
    			        scanf("%d",&eid2);
				printf("\n");
				printf("enter the new aircraft id:");
    			        scanf("%d",&aid2);
				printf("\n");
				snprintf(statement12, 1024, "UPDATE certified set aid=%d where eid=%d and aid=%d",aid2,eid1,aid1);
                                mysql_query(conn, statement12);	
				snprintf(statement13, 1024, "UPDATE certified set eid=%d where eid=%d and aid=%d",eid2,eid1,aid1);
                                mysql_query(conn, statement13);	

				break;
		        case 5:	p=70;
				break;
                    }
	     }while(p!=70);
      case 4:do
            {
                printf("Enter\n1.display flight\n 2.display aircraft\n 3.display employees\n 4.display certified\n 5.exit\n");
                scanf("%d",&op);
                switch(op)
                    {
                         case 1:if (mysql_query(conn,"SELECT * from flight")) 
                                {
                                fprintf(stderr, "%s\n", mysql_error(conn));
                                exit(1);
                                }
                                res = mysql_use_result(conn);
                                unsigned long *lengths;
                                unsigned int num_fields;
                                int i;
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

				break;

			  case 2:if (mysql_query(conn,"SELECT * from aircraft")) 
                                {
                                fprintf(stderr, "%s\n", mysql_error(conn));
                                exit(1);
                                }
                                res = mysql_use_result(conn);
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

				break;
			  case 3:if (mysql_query(conn,"SELECT * from employees")) 
                                {
                                fprintf(stderr, "%s\n", mysql_error(conn));
                                exit(1);
                                }
                                res = mysql_use_result(conn);
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

				break;
                           case 4:if (mysql_query(conn,"SELECT * from certified")) 
                                {
                                fprintf(stderr, "%s\n", mysql_error(conn));
                                exit(1);
                                }
                                res = mysql_use_result(conn);
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

				break;
		            case 5:p=80;
				   break;
                    }
	     }while(p!=80);

      case 5:exit(0);
             break;
     
   }
}while(1);
}
