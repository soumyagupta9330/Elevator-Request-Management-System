#include<stdio.h>
#include<stdlib.h>

#define SIZE 20
#define FLOORS 10

struct Request
{
    int id;
    int source;
    int destination;
};

struct Node
{
    int id;
    int source;
    int destination;
    struct Node *next;
};

struct Request queue[SIZE];

int front=-1;
int rear=-1;

int currentFloor=1;
int requestID=1;

struct Node *head=NULL;


/* Add Request */

void addRequest()
{
    int source,destination;

    if(rear==SIZE-1)
    {
        printf("Queue is full\n");
        return;
    }

    printf("Enter source floor: ");
    scanf("%d",&source);

    printf("Enter destination floor: ");
    scanf("%d",&destination);

    if(source<1 || source>FLOORS ||
       destination<1 || destination>FLOORS)
    {
        printf("Invalid floor\n");
        return;
    }

    if(source==destination)
    {
        printf("Source and destination cannot be same\n");
        return;
    }

    if(front==-1)
    {
        front=0;
    }

    rear++;

    queue[rear].id=requestID;
    queue[rear].source=source;
    queue[rear].destination=destination;

    printf("Request added. Request ID = %d\n",requestID);

    requestID++;
}


/* Display Pending Requests */

void displayRequests()
{
    int i;

    if(front==-1)
    {
        printf("No pending requests\n");
        return;
    }

    printf("\nPending Requests:\n");

    for(i=front;i<=rear;i++)
    {
        printf("ID: %d  %d -> %d\n",
               queue[i].id,
               queue[i].source,
               queue[i].destination);
    }
}


/* Move Elevator */

void moveElevator(int floor)
{
    while(currentFloor<floor)
    {
        currentFloor++;
        printf("Elevator at floor %d\n",currentFloor);
    }

    while(currentFloor>floor)
    {
        currentFloor--;
        printf("Elevator at floor %d\n",currentFloor);
    }
}


/* Add completed request to linked list */

void addHistory(int id,int source,int destination)
{
    struct Node *newnode;
    struct Node *temp;

    newnode=(struct Node*)malloc(sizeof(struct Node));

    newnode->id=id;
    newnode->source=source;
    newnode->destination=destination;
    newnode->next=NULL;

    if(head==NULL)
    {
        head=newnode;
    }
    else
    {
        temp=head;

        while(temp->next!=NULL)
        {
            temp=temp->next;
        }

        temp->next=newnode;
    }
}


/* Process Request */

void processRequest()
{
    struct Request r;
    int i;

    if(front==-1)
    {
        printf("No pending requests\n");
        return;
    }

    r=queue[front];

    printf("\nProcessing Request %d\n",r.id);

    printf("Moving to source floor %d\n",r.source);
    moveElevator(r.source);

    printf("Passenger entered\n");

    printf("Moving to destination floor %d\n",r.destination);
    moveElevator(r.destination);

    printf("Passenger reached destination\n");

    addHistory(r.id,r.source,r.destination);

    for(i=front;i<rear;i++)
    {
        queue[i]=queue[i+1];
    }

    rear--;

    if(rear<front)
    {
        front=-1;
        rear=-1;
    }

    printf("Request completed\n");
}


/* Cancel Request */

void cancelRequest()
{
    int search;
    int i;
    int found=0;

    if(front==-1)
    {
        printf("No pending requests\n");
        return;
    }

    printf("Enter Request ID to cancel: ");
    scanf("%d",&search);

    for(i=front;i<=rear;i++)
    {
        if(queue[i].id==search)
        {
            found=1;

            for(;i<rear;i++)
            {
                queue[i]=queue[i+1];
            }

            rear--;

            if(rear<front)
            {
                front=-1;
                rear=-1;
            }

            printf("Request cancelled\n");
            break;
        }
    }

    if(found==0)
    {
        printf("Request not found\n");
    }
}


/* Display History */

void displayHistory()
{
    struct Node *temp;

    if(head==NULL)
    {
        printf("No completed requests\n");
        return;
    }

    printf("\nCompleted Requests:\n");

    temp=head;

    while(temp!=NULL)
    {
        printf("ID: %d  %d -> %d\n",
               temp->id,
               temp->source,
               temp->destination);

        temp=temp->next;
    }
}


/* Main */

int main()
{
    int choice;

    do
    {
        printf("\n===== ELEVATOR SYSTEM =====\n");

        printf("1. Add Request\n");
        printf("2. Process Request\n");
        printf("3. Display Pending Requests\n");
        printf("4. Cancel Request\n");
        printf("5. Display Completed Requests\n");
        printf("6. Display Current Floor\n");
        printf("7. Exit\n");

        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                addRequest();
                break;

            case 2:
                processRequest();
                break;

            case 3:
                displayRequests();
                break;

            case 4:
                cancelRequest();
                break;

            case 5:
                displayHistory();
                break;

            case 6:
                printf("Current floor = %d\n",currentFloor);
                break;

            case 7:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice\n");
        }

    }while(choice!=7);

    return 0;
}
