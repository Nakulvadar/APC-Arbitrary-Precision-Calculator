/*******************************************************************************************************************************************************************
*Title			: Subtraction
*Description		: This function performs subtraction of two given large numbers and store the result in the resultant list.
*Prototype		: int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR,Dlist **tailR)
{
	/* Definition goes here */
	if(*head1== NULL && *head2==NULL)	return FAILURE;
	Dlist *temp1 = *tail1;
	Dlist *temp2 = *tail2;
	
	int cmp = compare(*head1, *head2);
    
    if (cmp < 0) 
    {
        Dlist *tmpHead = *head1;
        Dlist *tmpTail = *tail1;
        *head1 = *head2;
        *tail1 = *tail2;
        *head2 = tmpHead;
        *tail2 = tmpTail;
        temp1 = *tail1;
        temp2 = *tail2;
    }
	int borrow=0,result=0;
	while(temp1 != NULL || temp2 != NULL)
	{
		 
		int val1 = (temp1) ? temp1->data : 0;
        int val2 = (temp2) ? temp2->data : 0;

        result = val1 - val2 - borrow;

		if(result < 0){
			result+=10;
			borrow=1;
		}
		else{
			borrow=0;
		}
		
		insert_at_first(headR,tailR,result);
		if (temp1)	temp1 = temp1->prev;
		if (temp2)	temp2 = temp2->prev;
	}
	
	return SUCCESS;
}
