#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

/* -------------------------------------------------------------------- */
/*                     HELPER FUNCTIONS IN THIS FILE                    */
/* -------------------------------------------------------------------- */

/* Find tail from head */
Dlist *get_tail(Dlist *head)
{
    Dlist *t = head;
    while (t && t->next)
        t = t->next;
    return t;
}

/* Remove leading zero digits (MSB side) */
void remove_leading_zeros_head(Dlist **head, Dlist **tail)
{
    while (*head && (*head)->data == 0 && (*head)->next != NULL)
    {
        Dlist *del = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(del);
    }

    if (*head == NULL)
        *tail = NULL;
    else if (*tail == NULL)
        *tail = get_tail(*head);
}

/* Multiply big integer by a single digit 0–9 */
int multiply_single_digit(Dlist *numHead, Dlist *numTail, int d,Dlist **resHead, Dlist **resTail)
{
    if (d < 0 || d > 9)
        return FAILURE;

    *resHead = NULL;
    *resTail = NULL;

    if (numHead == NULL)
    {
        insert_at_first(resHead, resTail, 0);
        return SUCCESS;
    }

    int carry = 0;
    Dlist *p = numTail;

    while (p)
    {
        int prod = p->data * d + carry;
        int digit = prod % 10;
        carry = prod / 10;

        if (insert_at_first(resHead, resTail, digit) == FAILURE)
            return FAILURE;

        p = p->prev;
    }

    while (carry)
    {
        int digit = carry % 10;
        if (insert_at_first(resHead, resTail, digit) == FAILURE)
            return FAILURE;
        carry /= 10;
    }

    remove_leading_zeros_head(resHead, resTail);
    return SUCCESS;
}

/* -------------------------------------------------------------------- */
/*                            DIVISION FUNCTION                         */
/* -------------------------------------------------------------------- */

int division(Dlist **head1, Dlist **tail1,Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    /* divide by zero */
    if (*head2 == NULL || ((*head2)->data == 0 && (*head2)->next == NULL))
        return FAILURE;

    *headR = NULL;
    *tailR = NULL;

    /* dividend = 0 */
    if (*head1 == NULL || (((*head1)->data == 0) && (*head1)->next == NULL))
    {
        insert_at_first(headR, tailR, 0);
        return SUCCESS;
    }

    /* divisor > dividend = quotient 0 */
    if (compare(*head1, *head2) < 0)
    {
        insert_at_first(headR, tailR, 0);
        return SUCCESS;
    }

    /* remainder list */
    Dlist *curH = NULL, *curT = NULL;

    /* bring-down long division */
    for (Dlist *p = *head1; p != NULL; p = p->next)
    {
        if (curH == NULL)
            insert_at_first(&curH, &curT, p->data);
        else
            insert_at_last(&curH, &curT, p->data);

        remove_leading_zeros_head(&curH, &curT);

        int qdigit = 0;
        Dlist *candH = NULL, *candT = NULL;

        /* try digits 9 → 0 */
        for (int d = 9; d >= 0; d--)
        {
            if (multiply_single_digit(*head2, *tail2, d, &candH, &candT) == FAILURE)
            {
                Delete_list(&curH, &curT);
                return FAILURE;
            }

            if (compare(candH, curH) <= 0)
            {
                qdigit = d;
                break;
            }

            Delete_list(&candH, &candT);
        }

        insert_at_last(headR, tailR, qdigit);

        /* subtract if qdigit > 0 */
        if (qdigit > 0)
        {
            Dlist *newH = NULL, *newT = NULL;

            subtraction(&curH, &curT, &candH, &candT, &newH, &newT);

            Delete_list(&curH, &curT);
            Delete_list(&candH, &candT);

            curH = newH;
            curT = newT;

            remove_leading_zeros_head(&curH, &curT);
        }
        else
        {
            Delete_list(&candH, &candT);
        }
    }

    /* remove leading zeros from quotient */
    while (*headR && (*headR)->data == 0 && (*headR)->next != NULL)
    {
        Dlist *tmp = *headR;
        *headR = (*headR)->next;
        (*headR)->prev = NULL;
        free(tmp);
    }

    if (*headR == NULL)
        insert_at_first(headR, tailR, 0);

    Delete_list(&curH, &curT);

    return SUCCESS;
}
