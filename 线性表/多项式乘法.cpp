/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{   int    coef, exp;
    struct node  *next;
} NODE;

void multiplication( NODE *, NODE * , NODE * );
void input( NODE * );
void output( NODE * );

void input( NODE * head )
{   int flag, sign, sum, x;
	char c;

    NODE * p = head;

	while ( (c=getchar()) !='\n' )
	{
		if ( c == '<' )
	    {    sum = 0;
	         sign = 1;
	         flag = 1;
        }
		else if ( c =='-' )
             sign = -1;
		else if( c >='0'&& c <='9' )
		{    sum = sum*10 + c - '0';
        }
		else if ( c == ',' )
        {    if ( flag == 1 )
             {    x = sign * sum;
                  sum = 0;
                  flag = 2;
		  sign = 1;
             }
        }
		else if ( c == '>' )
        {    p->next = ( NODE * ) malloc( sizeof(NODE) );
             p->next->coef = x;
             p->next->exp  = sign * sum;
             p = p->next;
             p->next = NULL;
             flag = 0;
        }
    }
}

void output( NODE * head )
{
    while ( head->next != NULL )
    {   head = head->next;
        printf("<%d,%d>,", head->coef, head->exp );
    }
    printf("\n");
}

int main()
{   NODE * head1, * head2, * head3;

    head1 = ( NODE * ) malloc( sizeof(NODE) );
    input( head1 );

    head2 = ( NODE * ) malloc( sizeof(NODE) );
    input( head2 );

    head3 = ( NODE * ) malloc( sizeof(NODE) );
    head3->next = NULL;
    multiplication( head1, head2, head3 );

	output( head3 );
	return 0;
}

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */
typedef struct {
    long long coef; 
    int exp;
} Term;

int cmpTerm(const void *a, const void *b) {
    int ea = ((Term*)a)->exp;
    int eb = ((Term*)b)->exp;
    return (ea < eb) ? -1 : (ea > eb) ? 1 : 0;
}

void multiplication(NODE *h1, NODE *h2, NODE *h3) {
    if (h1->next == NULL || h2->next == NULL) {
        NODE *z = (NODE*)malloc(sizeof(NODE));
        z->coef = 0; z->exp = 0; z->next = NULL;
        h3->next = z;
        return;
    }

    int n1 = 0, n2 = 0;
    for (NODE *p = h1->next; p; p = p->next) n1++;
    for (NODE *p = h2->next; p; p = p->next) n2++;

    Term *arr = (Term*)malloc(sizeof(Term) * n1 * n2);
    int idx = 0;
    for (NODE *p1 = h1->next; p1; p1 = p1->next) {
        for (NODE *p2 = h2->next; p2; p2 = p2->next) {
            arr[idx].coef = (long long)p1->coef * (long long)p2->coef;
            arr[idx].exp  = p1->exp + p2->exp;
            idx++;
        }
    }

    qsort(arr, idx, sizeof(Term), cmpTerm);

    NODE *tail = h3;
    int i = 0;
    while (i < idx) {
        int exp = arr[i].exp;
        long long coef = 0;
        while (i < idx && arr[i].exp == exp) {
            coef += arr[i].coef;
            i++;
        }
        if (coef != 0) {
            NODE *nd = (NODE*)malloc(sizeof(NODE));
            nd->coef = (int)coef;
            nd->exp  = exp;
            nd->next = NULL;
            tail->next = nd;
            tail = nd;
        }
    }

    if (h3->next == NULL) {
        NODE *z = (NODE*)malloc(sizeof(NODE));
        z->coef = 0; z->exp = 0; z->next = NULL;
        h3->next = z;
    }

    free(arr);
}