/**************************************************************************************************************************************************************
*Title		: main function(Driver function)
*Description	: This function is used as the driver function for the all the functions
***************************************************************************************************************************************************************/
#include "apc.h"
int negative;
int sign1 = 1,sign2 = 1;

int main(int argc, char * argv[])
{
	/* Declare the pointers */
	Dlist *head1=NULL, *tail1=NULL, *head2=NULL, *tail2=NULL, *headR=NULL,*tailR=NULL;
	char option, operator;
	char ch;
	
	do
	{
		/* Code for reading the inputs */
		operator = argv[2][0];
		if (argc < 4) {
			printf("Usage: ./a.out <num1> <operator> <num2>\n");
			return 0;
		}

		// inserting elements in LINKED LIST.
		insert_element(&head1,&tail1,argv[1],&sign1);
		insert_element(&head2,&tail2,argv[3],&sign2);
		
		opretion_validation(&operator,&head1,&head2);
		/* Function for extracting the operator */
		//negative = 0;
		switch (operator)
		{
			case '+':
			/* call the function to perform the addition operation */
			if((addition(&head1, &tail1, &head2,&tail2,&headR,&tailR))==FAILURE){
				printf("Addition operation fail\n");
			}
			else{
				printf("Addition Successful.\n");
				Print_list_element(headR);
			}	
				break;
			case '-':	
				/* call the function to perform the subtraction operation */
			if((subtraction(&head1, &tail1, &head2,&tail2,&headR,&tailR))==FAILURE){
				printf("subtraction operation fail\n");
			}
			else{
				printf("subtraction Successful.\n");
				Print_list_element(headR);
			}
				break;
			case 'x':	
				/* call the function to perform the multiplication operation */
			
			if((multiplication(&head1, &tail1, &head2,&tail2,&headR,&tailR))==FAILURE){
				printf("multiplication operation fail\n");
			}
			else{
				printf("multiplication Successful.\n");
				Print_list_element(headR);
			}
				break;
			case '/':	
				/* call the function to perform the division operation */
			if((division(&head1, &tail1, &head2,&tail2,&headR,&tailR))==FAILURE){
				printf("Division operation fail\n");
			}
			else{
				printf("Division Successful.\n");
				Print_list_element(headR);
			}
				break;
			default:
				printf("Invalid Input:-( Try again...\n");
				break;
		}
		Delete_list(&head1,&tail1);
		Delete_list(&head2,&tail2);
		Delete_list(&headR,&tailR);
		printf("Want to continue? Press [yY | nN]: \n");
		scanf(" %c",&option);
		if(option == 'n' || option == 'N'){
			return 0;
		}
		printf("Witch Opretion you wont to execute. ( '+ ' '-' 'x' '/' )\n");
		scanf(" %c",&ch);
		argv[2][0]=ch;
	}while (option == 'y' || option == 'Y');

	return 0;
}

int insert_element(Dlist **head,Dlist **tail,char argv[],int *sign)
{
	int i=0;
	*sign = 1;
	if(argv[i] == '+'){
		i++;
	}
	if(argv[i] == '-'){
		*sign = -1;
		i++;
	}
	for(;argv[i] != '\0';i++)
	{
		if((argv[i] >= 'A' && argv[i] <= 'Z') || (argv[i] >= 'a' && argv[i] <= 'z')){
			return FAILURE;
		}
		int data = argv[i] - '0';
		if((insert_at_last(head,tail,data))==FAILURE){
			return FAILURE;
		}
	}
	return SUCCESS;
}
int insert_at_last(Dlist **head,Dlist **tail,int data)
{
	Dlist *new=malloc(sizeof(Dlist));
	if(new == NULL)	return FAILURE;
	new->data=data;
	new->prev=NULL;
	new->next=NULL;
	if((*head == NULL)|| (*tail == NULL)){
		*head=new;
		*tail=new;
		return SUCCESS;
	}
	else{
		(*tail)->next=new;
		new->prev=*tail;
		*tail=new;
	}
	return SUCCESS;
}

int insert_at_first(Dlist **head,Dlist **tail,int data){
	Dlist *new=malloc(sizeof(Dlist));
	if(new == NULL)	return FAILURE;
	new->data=data;
	new->prev=NULL;
	new->next=NULL;
	if((*head == NULL)|| (*tail == NULL)){
		*head=new;
		*tail=new;
		return SUCCESS;
	}
	else{
		(*head)->prev=new;    
		new->next=*head;
		*head=new;
	}
	return SUCCESS;
}

void Print_list_element(Dlist *head)
{
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
	else
	{
	    printf("RESULT -> ");
		if(negative == 1)
		printf("-");

	    while (head)		
	    {
			
		    /* Printing the list */
		    printf("%d", head -> data);
		    head = head -> next;
	    }
    	printf("\n");
    }
}

int Delete_list(Dlist **head, Dlist **tail)
{
    Dlist *temp = *head;

    while (temp)
    {
        Dlist *next = temp->next;
        free(temp);
        temp = next;
    }

    *head = NULL;
    *tail = NULL;

    return SUCCESS;
}


int compare(Dlist *head1, Dlist *head2)
{
    int len1 = 0, len2 = 0;
    Dlist *temp1 = head1;
    Dlist *temp2 = head2;

    /* Count length of both lists */
    while (temp1)
    {
        len1++;
        temp1 = temp1->next;
    }
    while (temp2)
    {
        len2++;
        temp2 = temp2->next;
    }

    /* Compare by length */
    if (len1 > len2)
        return 1;
    else if (len1 < len2)
        return -1;


    temp1 = head1;
    temp2 = head2;
    while (temp1 && temp2)
    {
        if (temp1->data > temp2->data)
            return 1;
        else if (temp1->data < temp2->data)
            return -1;

        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return 0;
}
void opretion_validation(char *operator, Dlist **head1 , Dlist **head2)
{
    if (*operator == '+')
    {
        if (sign1 == -1 && sign2 == -1)
        {
            negative = 1;
            *operator = '+';
        }
        else if (sign1 == -1 && sign2 == 1)
        {
            if (compare(*head2, *head1) >= 0)
            {
                *operator = '-';
                negative = 0;
            }
            else
            {
                *operator = '-';
                negative = 1;
            }
        }
        else if (sign1 == 1 && sign2 == -1)
        {
            if (compare(*head1, *head2) >= 0)
            {
                *operator = '-';
                negative = 0;
            }
            else
            {
                *operator = '-';
                negative = 1;
            }
        }
        else
        {
            negative = 0;
            *operator = '+';
        }
    }
    else if (*operator == '-')
    {
        if (sign1 == 1 && sign2 == 1)
        {
            if (compare(*head1, *head2) >= 0)
            {
                *operator = '-';
                negative = 0;
            }
            else
            {
                *operator = '-';
                negative = 1;
            }
        }
        else if (sign1 == 1 && sign2 == -1)
        {
            *operator = '+';
            negative = 0;
        }
        else if (sign1 == -1 && sign2 == 1)
        {
            *operator = '+';
            negative = 1;
        }
        else if (sign1 == -1 && sign2 == -1)
        {
            if (compare(*head2, *head1) >= 0)
            {
                *operator = '-';
                negative = 0;
            }
            else
            {
                *operator = '-';
                negative = 1;
            }
        }
    }
    else if (*operator == '/' || *operator == 'x')
    {
        if ((sign1 == 1 && sign2 == 1) || (sign1 == -1 && sign2 == -1))
        {
            negative = 0;
        }
        else
        {
            negative = 1;
        }
    }
}
