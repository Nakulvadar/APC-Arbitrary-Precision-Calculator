/*******************************************************************************************************************************************************************
*Title                 : Multiplication
*Description           : This function performs multiplication of two given large numbers and store the result in the resultant list.
*Prototype             : int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);
*Input Parameters      : head1: Pointer to the first node of the first double linked list.
                        : tail1: Pointer to the last node of the first double linked list.
                        : head2: Pointer to the first node of the second double linked list.
                        : tail2: Pointer to the last node of the second double linked list.
                        : headR: Pointer to the first node of the resultant double linked list.
*Output                : Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    /* Definition goes here */
    Dlist *temp2 = *tail2;
    int count = 0;

    *headR = NULL;
    *tailR = NULL;
    Dlist *headR2=NULL;
    Dlist *tailR2=NULL;

    while (temp2 != NULL)
    {
        int val1 = temp2->data;
        Dlist *temp1 = *tail1;

        Dlist *headR1 = NULL;
        Dlist *tailR1 = NULL;

        int carry = 0;

        while (temp1 != NULL)
        {
            int val2 = temp1->data;
            int res = val1 * val2 + carry;

            int rem = res % 10;
            carry = res / 10;

            insert_at_first(&headR1, &tailR1, rem);

            temp1 = temp1->prev;
        }

        if (carry)
        {
            insert_at_first(&headR1, &tailR1, carry);
        }

        for (int i = 0; i < count; i++)
        {
            insert_at_last(&headR1, &tailR1, 0);
        }
        if(*headR == NULL){
            *headR = headR1;
            *tailR = tailR1;
            headR1 = NULL;
            tailR1 = NULL;
        }
        else{
            addition(headR,tailR,&headR1,&tailR1,&headR2,&tailR2);
            Delete_list(headR,tailR);
            *headR=headR2;
            *tailR=tailR2;
            Delete_list(&headR1,&tailR2);
            headR2=NULL;
            tailR2=NULL;
        }
        count++;
        temp2 = temp2->prev;
    }
    
    return SUCCESS;
}
