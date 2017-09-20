 
#include <stdio.h>                          // Standard input and output
#include <sys/socket.h>                     // For socket(), connect(), send(), and recv()
#include <arpa/inet.h>                      // For sockaddr_in and inet_addr()
#include <stdlib.h>                         // For atoi() and exit()
#include <string.h>                         // For memset()
#include <unistd.h>                         // For close()
#include <netdb.h>                          // For gethostbyname()
#include <time.h>                           // For time_t
#define SECURITYCODE "ABC123"               // Pre-shared  security code
#define RCVBUFSIZE 120

//*************     FUNCTION PROTOTYPE      *******************//

void DieWithError(char *errorMessage);

void HandleUDPClient(int, char ip[], struct sockaddr_in, unsigned long);

/*** Structure for Documenting last served client ***/
struct{
    char ipAddress[16];
    time_t timeStamp;
} clientNode;

/*** Structure for Linked List ***/
struct Node{
    char domainName[20];
    int count;
    char ipAddr[65];
    struct Node *next;
}l;                                         // Structure variable "l"

typedef struct Node *nodePointer;           // nodePointer points to a structure of type linkedList

//************  Function Prototype Declarations  ***************//

void readInput(char *, nodePointer *);

//char * addDomain(char *, nodePointer *, int);

void displayNode(nodePointer);

void * searchDomain(char *, nodePointer *, int);

//void deleteDomain(char *, nodePointer *);

void  nodeFromStructure(nodePointer, int);

char * toString(char str[], int);


void writeLinkedListToFile(nodePointer);//

//char * resolveName(char name[]);

 

void logMe(char[]);

//*****************     Global variables   ********************//

nodePointer head = NULL;
char buffer[RCVBUFSIZE];
char fileLocation[200];
char logFileLocation[200];
char responseMessage[120];
char message[100];
char logMessage[120];
unsigned int  timeOut;
unsigned int oneTimeCount = 0;


//-------------------------------------------------------------//
//*****************     MAIN FUNCTION      ********************//
//-------------------------------------------------------------//

int main(int argc, char *argv[])
{
    int serverSock;                         // Socket descriptor for server
    
    struct sockaddr_in serverAddr;          // Structure variable for Local address
    struct sockaddr_in clientAddr;          // Structure variable for Client address
    
    unsigned int clientLen;                 // Length of incoming message
    unsigned short serverPort;              // Server port
    unsigned long recvMsgSize;              // Size of received message
    
    if (argc != 5)                          // Test for correct number of parameters
    {
        fprintf(stderr,"Usage:  %s <UDP SERVER PORT>\n", argv[0]);
        exit(1);
    }
    char line[1024];                        // String variable to read input from file
    serverPort = atoi(argv[1]);             // First arg:  local port
    strcpy(fileLocation,argv[2]);
    timeOut = atoi(argv[3]);
    strcpy(logFileLocation,argv[4]);

    printf("\n\t\tDNS Doisser listening on Port Number is: %s\n",argv[1]);
    FILE *fp = fopen(argv[2],"r");
  
    
    if( fp == NULL ){                       // If any error opening file, return -1
        if ((fp = fopen(argv[2],"w")) == NULL)
            return -1;
    }
    
    else{
        while(fgets(line,1024,fp))          // If file opened properly, start reading line by line
            readInput(line, &head);
        }
    
        displayNode(head);                  // Calling the function to display the nodes in Linked List
    
    printf("\n\n\t\tFile opened and data read success");
    fclose(fp);                            // Close the file DOMAIN_IP_MAP.TXT
    
    /* Opening the log File */
    FILE *lp;
    if ((lp = fopen(argv[4],"w")) == NULL)
            return -1;
    
    strcpy(logMessage,"DNS Dossier listening on port ");
    strcat(logMessage,argv[1]);
    
    
    logMe(logMessage);
    
    
    printf("\n\n\t\tWelcome to the DNS Doisser System \t\t\n");
    // Print available operations at the Server
    printf("\n\t\tRequest Code \t\tAction"
           "\n\t\t\t1. \t\t\tFind IP for a domain"
           "\n\t\t\t2. \t\t\tAdd a record to the list"
           "\n\t\t\t3. \t\t\tDelete a record from the list"
           "\n\t\t\t4. \t\t\tReport the most requested record(s)"
           "\n\t\t\t5. \t\t\tReport the least requested record(s)"
           "\n\t\t\t6. \t\t\tShutdown");
    
   
    /* Create socket for sending/receiving datagrams */
    if ((serverSock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
        logMe("Socket creation error ");
        DieWithError("socket() failed");
    }
    
    logMe("Socket creation successful");

    /* Construct local address structure */
    memset(&serverAddr, 0, sizeof(serverAddr));         // Zero out structure
    serverAddr.sin_family = AF_INET;                    // Internet address family
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);     // Any incoming interface
    serverAddr.sin_port = htons(serverPort);            // Local port
    
    /* Bind to the local address */
    if (bind(serverSock, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0){
        logMe("Bind Failed. Terminating with exit code 1!");
        DieWithError("bind() failed");
    }
    
    logMe("Bind successful");
    fclose(lp);
    int i =0;

    for (;;) /* Run forever */
    {
        /* Set the size of the in-out parameter */
        clientLen = sizeof(clientAddr);
        
        /* Block until receive message from a client */
        if ((recvMsgSize = recvfrom(serverSock, buffer, RCVBUFSIZE, 0,
                                    (struct sockaddr *) &clientAddr, &clientLen)) < 0){
            logMe("Error receving message from client. Terminating with exit code 1!");
            DieWithError("recvfrom() failed");
        }
        
        while(i==0){
            strcpy(clientNode.ipAddress, inet_ntoa(clientAddr.sin_addr));
            clientNode.timeStamp= time(NULL);
            i++;
        }
    
        if (recvMsgSize > 0){
          
            HandleUDPClient(serverSock,inet_ntoa(clientAddr.sin_addr),clientAddr, recvMsgSize);
        }
        
    }
    
    /* NOT REACHED */
}

//-------------------------------------------------------------//
//*****************     MAIN FUNCTION      ********************//
//-------------------------------------------------------------//

/* Send received datagram back to the client */

void HandleUDPClient(int socket,char clientIp[], struct sockaddr_in clientAddr, unsigned long recvMsgSize)
{
    printf("\n\n\n########################################################################################");
    printf("\n\t\tEntered UDP handler for %s ", clientIp);
    char *word;                             // Temporary word variable to obtain words from string
    int  action;                            // Action requested
    char dName[40];                         // Domain name
    time_t now;                             // Time variable
    char sec[5];
    char *ipPointer;
    char *securityCode;                     // SECURITY CODE required to shutdown the Server
    int  statusCode = 0;                    //
    
    buffer[recvMsgSize]='\0';               //Terminating the receive buffer with null character
    
    now =time(NULL);                        // Current time
    
    if ((now - clientNode.timeStamp )< 10 && oneTimeCount != 0){
        // Calculates the time elapsed since previous query
        statusCode = 3;                     // Do not process the query, ask Client to wait till the timeout
    }
    else{
        strcpy(clientNode.ipAddress, clientIp);
        clientNode.timeStamp = now;         // Timestamp the current time for a Client
    }
    if( statusCode == 0){                   // Normal operation - Prcoess the query received from the Client
        
        switch(buffer[0]){
                
            case '4':                       // If arguments are 3, find most/least requested domain
                
                if (buffer[2] == '4'){
                    printf("\n\n\t\tIncoming request from client  %s : Most requested domain\n", clientIp);
                    
                    printf("\n\t\tDNS Dossier will present at most 3 most requested domains in case of tie b/w counts\n");
                    strcpy(logMessage,clientIp);
                    strcat(logMessage," : Requesting for most requested domain(s) ");
                    strcat(logMessage,dName);
                    logMe(logMessage);
                    
                    strcpy(logMessage,"Sending Response to client: ");
                    strcat(logMessage,buffer);
                    logMe(logMessage);
                    // Function to print top three domains at most
                    break;
                }
                
                else if (buffer[2] == '5'){
                    printf("\n\n\t\tIncoming request from client  %s : Least requested domain\n", clientIp);
                    strcpy(logMessage,clientIp);
                    strcat(logMessage," : Requesting for least requested domain(s) ");
                    strcat(logMessage,dName);
                    logMe(logMessage);
                    printf("\n\t\tDNS Dossier will present at most 3 Least requested domains in case of tie b/w counts\n");
                
                    strcpy(logMessage,"Sending Response to client: ");
                    strcat(logMessage,buffer);
                    logMe(logMessage);
                    break;
                    // Function to find the bottom 3 domains requested
                }
                else
                {
                    printf("\n\t\tTransmission Error via client");    // if command isn't in right format
                    strcpy(buffer,"Incorrect request passed by client ");
                    strcat(buffer,clientIp);
                    logMe(buffer);
                    break;
                }

                
                
            case '5':                        // If arguments are 4 find IP or shutdown
                
                        if (buffer[2] == '6'){ // When requested action is SHUTDOWN
                                printf("\n\n\t\tIncoming request from client  %s : Shutdown DNS Dossier", clientIp);
                                strcpy(logMessage,"Incoming request from client ");
                                strcat(logMessage,clientIp);
                                strcat(logMessage, " Shutdown DNS Dossier");
                                logMe(logMessage);
                    
                                securityCode=strtok(buffer+4,"#");
                    
                    
                                if (strcmp(SECURITYCODE, securityCode) == 0){   // Verify SECURITY CODE
                                    printf("\n\n\t\tSecurity code verified");
                                    printf("\n\n\t\tSaving LinkedList into the file");
                                    strcpy(logMessage,"Server shutdown request from ");
                                    strcat(logMessage,clientIp);
                                    strcat(logMessage," : Accepted and Authenticated");
                                    logMe(logMessage);
                        
                                    logMe("Saving linked List data base to file");
                        
                                    writeLinkedListToFile(head);                // Write to file all the nodes
                                    printf("\n\n\t\tLinked List written to the File\n");
                                    statusCode = 1;
                                    strcpy(buffer,"Server is going down. Connection will be lost!!");
                                    logMe("Server is going down. Connection will be lost!!");

                        
                                }
                                else{
                                    printf("\n\n\t\tSecurity code incorrect");     // Security code provided is incorrect
                                    logMe("Incorrect Security code" );
                                    strcpy(buffer,"Server shutdown by client ");
                                    strcat(buffer,clientIp);
                                    strcat(buffer," failed");
                                    logMe(buffer);
                        
                                }
                            break;
                        }// end of if
                
                        else if (buffer[2] == '1'){          // ACTION requested is Find IP for a domain
                            action = (int)buffer[0];
                            word = strtok(buffer,"#");
                            word = strtok(NULL,"#");
                            word = strtok(NULL,"#");
                            strcpy(dName,word);
                            printf("\n\n\t\tIncoming request from client  %s : Search IP for domain %s", clientIp, word);
                            strcpy(logMessage,clientIp);
                            strcat(logMessage," : Requesting to search IP for the domain name ");
                            strcat(logMessage,dName);
                            logMe(logMessage);
                    
                            if((ipPointer = searchDomain(word, &head, 1)) !=NULL){
                                strcpy(buffer, ipPointer);
                                buffer[strlen(ipPointer)]='\0';
                                strcpy(logMessage,"Sending response to client: ");
                                strcat(logMessage,"Domain IP resolved for ");
                                strcat(logMessage,dName);
                                logMe(logMessage);
                            }
                    
                            else{
                                strcpy(buffer,"IP not found");
                                strcpy(logMessage,"DNS Dossier unable to resolve domain IP");
                                logMe(logMessage);
                            }
                            break;
                        }
                
              
                
                        else if(buffer[2] == '3'){           // ACTION requested is DELETE a specific domain
                            word = strtok(buffer,"#");
                            word = strtok(NULL,"#");
                            word = strtok(NULL,"#");
                            strcpy(dName,word);
                            printf("\n\n\t\tIncoming request from client  %s : Delete domain %s", clientIp, word);
                            strcpy(logMessage,clientIp);
                            strcat(logMessage," : Requesting to delete domain name ");
                            strcat(logMessage,dName);
                            logMe(logMessage);
                            deleteDomain(dName, &head);
                            strcpy(buffer,responseMessage);
                            strcpy(logMessage,buffer);
                            logMe(logMessage);
                            break;
                        }
                        else{
                            printf("\n\t\tTransmission Error via client");    // if command isn't in right format
                            strcpy(buffer,"Incorrect request passed by client ");
                            strcat(buffer,clientIp);
                            logMe(buffer);
                            break;
                        }
                
                
            case '6':   if( buffer[2] == '2'){              // ACTION requested is ADD domain
                
                            word = strtok(buffer,"#");
                            word = strtok(NULL,"#");
                            word = strtok(NULL,"#");
                            printf("\n\n\t\tIncoming request from client  %s : Add domain %s", clientIp, word);
                            strcpy(dName,word);
                            strcpy(logMessage,clientIp);
                            strcat(logMessage," : Requesting to add domain name ");
                            strcat(logMessage,dName);
                            logMe(logMessage);
                            strcpy(buffer,addDomain(dName, &head,2));
                            strcpy(logMessage,"Sending Response to client: ");
                            strcat(logMessage,buffer);
                            logMe(logMessage);
                            break;
                        }
                        else{
                
                            printf("\n\t\tTransmission Error via client");    // if command isn't in right format
                            strcpy(buffer,"Incorrect request passed by client ");
                            strcat(buffer,clientIp);
                            logMe(buffer);
                            break;
                        }
                
                        break;
                
                
            default:    {
                            printf("\n\t\tTransmission Error via client");    // if command isn't in right format
                            strcpy(buffer,"Incorrect request passed by client ");
                            strcat(buffer,clientIp);
                            logMe(buffer);
                            break;
                        }
                
        }
        
        /* Send received string and receive again until end of transmission */
        if (sendto(socket, buffer, RCVBUFSIZE, 0,
                   (struct sockaddr *) &clientAddr, sizeof(clientAddr)) != RCVBUFSIZE)
            DieWithError("sendto() sent a different number of bytes than expected");
        
        printf("\n\t\tSent Response to the Client: %s", buffer);
        printf("\n\n########################################################################################");
        
    }// end of if loop with STATUS code 0
    
    
    // Do not process the query, ask Client to wait till the timeout
    
    if(statusCode == 3){
        strcpy(buffer,"Another inquiry had been made by ");
        strcat(buffer,toString(sec, (int) (now - clientNode.timeStamp)));
        strcat(buffer," seconds ago, wait ");
        strcat(buffer,toString(sec,timeOut));
        strcat(buffer," seconds before another submission" );
        strcpy(logMessage,buffer);
        logMe(logMessage);
        
        if (sendto(socket, buffer, RCVBUFSIZE, 0,
                   (struct sockaddr *) &clientAddr, sizeof(clientAddr)) != RCVBUFSIZE)
            DieWithError("sendto() sent a different number of bytes than expected");
        printf("\n\n\t\tSent Response to the Client: %s", buffer);
        printf("\n\n########################################################################################");
        
    }
    
    // Save the linkedlist to the file, and SHUTDOWN the server
    
    if (statusCode == 1){
        logMe("Closing Server listening socket");
        printf("\n\t\tClosing Server listening socket");
        close(socket);
        logMe("Saving the logfile");
        exit(0);
        
    }
    oneTimeCount = 1;
}

//********** Function to read lines from txt file into linked list data structure *****************//

void readInput(char ch[], nodePointer *first)
{
    char *word;                                     // Temporary word
    
    nodePointer current = malloc(sizeof(l));        // Allocating memory for the current pointer to the structure
    
    if((*first) == NULL){                           // Zero element in linked List test
        *first = current;
        (*first)->next = NULL;
    }
    else{                                           // If its not the first element
        (*current).next = *first;
        *first = current;
    }
    
    /* Extracting the data structure members from string read from the file */
    
    word = strtok(ch," ");
    strcpy((*first)->domainName, word);
    
    word = (strtok(NULL," "));
    (*first)->count = atoi(word);
    
    word = (strtok(NULL,"\n"));
    strcpy((*first)->ipAddr, word);
    
}


//********* Function to search a Domain Name ***************//

void * searchDomain(char *dName, nodePointer *first, int type){
    
    char temp[100];
    int flag=0;                                 // FLAG=0/1, Tells if a domain is found or not
    nodePointer cur = *first;
    
    while(cur!=NULL){                           // Search for domain till the end of the linked list
        
        if(strcmp((cur)->domainName,dName)==0){ // Compare the domain name received to those existing in database
            printf("\n\n\t\tMatch Found");
            printf("\t\t%s %d %s\n",(cur)->domainName,(cur)->count,(cur)->ipAddr);
            flag = 1;                           // Set FLAG = 1, if domain is found
            break;
        }
        cur=cur->next;
    }
    
    
    if (flag == 0 && type == 1){                // If IP for the domain is NOT found
        printf("\n\n\t\tDomain record not found, trying gethostbyname() : ");
        
        if (resolveName(dName)!=NULL){
            strcpy(message,resolveName(dName));
            /* Search to find its IP and add if found */
            strcpy(temp, dName);
            strcat(temp, " ");
            strcat(temp, message);
            
            if(*first != NULL)                  // Add domain
                addDomain(temp,&head,1);
            else
                addDomain(temp,&head,2);
            
            return (char *) message;
        }
        else
            return NULL;
    }
    
    else if (flag == 1 && type==1){             // If domain match found and action requested is type 1
        cur->count += 1;
        return (char *) cur->ipAddr;            // Return the pointer to the node found
    }
    
    else if (flag == 1 && type == 2){           // If Domain match found and action requested is of type 2
            return (nodePointer) cur;           // Return the pointer of the searched node
    }
    
    else
        return NULL;                            // No match found
}

 


/* Returns node details as a string */

void nodeFromStructure(nodePointer node, int n){
    char * content = node->domainName;
    char nodeCount[8];
    char * count = toString(nodeCount,node->count);     // Converting the Integer variable, 'count' to string
    
    /* Creating a string to be sent as a reply to the Client */
    if( n == 0){
        strcpy(buffer, content);
        strcat(buffer, " ");
        strcat(buffer,count);
    }
    else{
        strcat(buffer, content);
        strcat(buffer, " ");
        strcat(buffer,count);
    }
    
    strcat(buffer, " ");
    
}


 


//******* Function to convert Integer value to String   ************//

char * toString(char * str, int num)
{
    int i, rem, len = 0, n;
    
    if(num >0){
        n = num;
        while (n != 0)      // Count the number of digits
        {   len++;
            n /= 10;
        }
        for (i = 0; i < len; i++)
        {   rem = num % 10; // Convert each digit to char and store in the char array
            num = num / 10;
            str[len - (i + 1)] = rem +'0' ;
        }
        str[len] = '\0';
    }
    else
        return "0";
    
    return str;
}


//*************** Function to SHUTDOWN the server  *********************//

void writeLinkedListToFile(nodePointer first){
    
    FILE *fp;
    char line[100];
    char str[8];
    printf("\n\n\t\tLocation is :%s",fileLocation);
    
    /* Open the file to write */
    if( (fp = fopen(fileLocation, "w") ) == NULL )
        DieWithError("\nError opening file to save linked list");
    
    else{
        while(first != NULL){          // Add all the nodes in the linked list
            strcpy (line, first->domainName);
            strcat (line, " ");
            strcat (line, toString(str,first->count));
            strcat (line, " ");
            strcat (line, first->ipAddr);
            strcat (line,"\n");
            fprintf(fp,"%s",line);
            first = first->next;        // Incrementing to next node
        }
        
        fclose(fp);                     // CLOSE FILE
    }
    
}

 


//*********** Resolving domain name  ************//
char * resolveName(char name[])
{
    struct hostent *hp = gethostbyname(name);
    
    if (hp == NULL) {                                   // If gethostby name is unable to find the IP
        printf("gethostbyname() failed\n");
        return NULL;
    }
    else {
        printf(" Domain Name Resolved");                 // If gethostby name returns an IP address
        unsigned int i=0;
        
        while ( hp -> h_addr_list[i] != NULL) {         // Add it to the existing domain IP map
            if (i == 0){
                strcpy(responseMessage, inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[i])));
                strcat(responseMessage, " ");
            }
            
            i++;
        }
        return responseMessage;
    }
    
}

//********* Function to display linked list nodes **************//

void displayNode(nodePointer first){
    while(first != NULL){
        printf("\n\t\t%s %d %s",first->domainName,first->count,first->ipAddr);
        first=first->next;
    }
}

 

//*************Function to write to log file ************//
void logMe(char message[] ){

    FILE *lp;
    if ((lp = fopen(logFileLocation,"a")) == NULL)
        DieWithError("\n\n\t\tError opening log file");

     
    strcat(responseMessage," ");
    strcat(responseMessage,message);
    fputs(responseMessage,lp);
    fputs("\n",lp);
    fclose(lp);
}


//************Function to deal with unexpected errors ******//
void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}
 


