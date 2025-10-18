#include<stdio.h>   
#include<stdlib.h>   
#define LEN sizeof(struct node)   
typedef struct node   
{   
    int orderid;   
    int squencecode;   
    int quantity;   
    char type;   
    struct node *next;   
    float price;  
}Stack, *order;   
int stock_code, num;  
float money;   
char dealtype;   
int cal = 1;   
order buy,sell,b,s,b1,s1,b2,s2,b3,s3,q,p,q1,p1;  
  
  
void treat1();  
void treat2();  
void treat3();  
int main()   
{   
    buy = (order)malloc(LEN); buy->next = NULL;   
    sell = (order)malloc(LEN); sell->next = NULL;   
    int whattodo ;   
    while (1)   
   {   
        scanf("%d", &whattodo );   
        if (whattodo  == 0) break;   
        switch (whattodo)   
        {   
          case 1:treat1(); break;   
          case 2:treat2(); break;   
          case 3:treat3(); break;   
        }   
  }   
  return 0;   
}    
  
void treat1()   
{   
    b = buy; s = sell; b1 = b->next; s1 = s->next;   
    scanf("%d %f %d %c", &stock_code, &money, &num, &dealtype);   
    printf("orderid: %04d\n", cal++);   
    if (dealtype == 'b')   
    {   
      while (s1 != NULL)   
     {   
          if (money >= s1->price)   
          {   
              if (stock_code == s1->squencecode)   
                {   
                  if (num == s1->quantity)   
                    {   
                      printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (money + s1->price) / 2, num, cal - 1, s1->orderid);   
                      num = 0;   
                      s->next = s1->next;   
                      free(s1); s1 = s->next; break;   
                  }   
                  else if (num < s1->quantity)   
                 {   
                    printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (money + s1->price) / 2, num, cal - 1, s1->orderid);   
                    s1->quantity -= num;   
                    num = 0;   
                    break;   
                 }   
                  else if (num>s1->quantity)   
                   {   
                    printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (money + s1->price) / 2, s1->quantity, cal - 1, s1->orderid);   
                    num -= s1->quantity;   
                    s->next = s1->next;   
                    free(s1);   
                    s1 = s->next;   
                    continue;   
                  }   
              }   
              else   
             {   
                  s = s->next; s1 = s->next; continue;   
             }   
          }   
          else break;   
     }   
      if (num != 0)   
      {   
        q = buy; p = q->next;   
        while (p)   
        {   
              if (money > p->price)   
                {   
                  order neop = (order)malloc(LEN); neop->orderid = cal - 1; neop->price = money; neop->quantity = num; neop->squencecode = stock_code; neop->type = dealtype;   
                  q->next = neop; neop->next = p;   
                  break;   
                }   
              else   
               {   
                  q = q->next, p = q->next;   
                }   
        }   
          if (p == NULL)   
         {   
              order neop = (order)malloc(LEN); neop->orderid = cal- 1; neop->price = money; neop->quantity = num; neop->squencecode = stock_code; neop->type = dealtype;   
               q->next = neop; neop->next = NULL;   
         }   
      }   
  }   
  if (dealtype == 's')   
 {   
      while (b1 != NULL)   
     {   
          if (money <= b1->price)   
          {   
              if (stock_code == b1->squencecode)   
                {   
                  if (num == b1->quantity)   
                    {   
                      printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (money + b1->price) / 2, num, cal - 1, b1->orderid);   
                      num = 0;   
                      b->next = b1->next;   
                      free(b1); b1 = b->next; break;   
                  }   
                  else if (num < b1->quantity)   
                 {   
                    printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (money + b1->price) / 2, num,cal - 1, b1->orderid);   
                    b1->quantity -= num;   
                    num = 0;   
                    break;   
                 }   
                  else if (num>b1->quantity)   
                   {   
                      printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (money + b1->price) / 2, b1->quantity, cal - 1, b1->orderid);   
                      num -= b1->quantity;   
                      b->next = b1->next;   
                      free(b1); b1 = b->next;   
                      continue;   
                  }   
              }   
              else   
               {   
                  b = b->next; b1 = b->next; continue;   
              }   
          }   
          else  break;   
     }   
      if (num != 0)   
      {   
          q = sell; p = q->next;   
          while (p)   
          {   
              if (money < p->price)   
                {   
                    order neop = (order)malloc(LEN); neop->orderid = cal - 1; neop->price = money; neop->quantity = num; neop->squencecode = stock_code; neop->type = dealtype;   
                    q->next = neop; neop->next = p;   
                    break;   
               }   
              else   
               {   
                  q = q->next, p = q->next;   
                }   
          }   
          if (p == NULL)   
          {   
            order neop = (order)malloc(LEN); neop->orderid = cal- 1; neop->price = money; neop->quantity = num; neop->squencecode = stock_code; neop->type = dealtype;   
            q->next = neop; neop->next = NULL;   
         }   
      }   
  }   
}   
  
void treat2()   
{   
    scanf("%d", &stock_code);   
    p = buy; q = p->next; p1 = sell; q1 = p1->next;   
    printf("buy orders:\n");   
    while (q)   
    {   
        if (q->squencecode == stock_code)   
        printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n",q->orderid,q->squencecode,q->price,q->quantity,q->type);   
        p = p->next; q = p->next;   
    }   
    printf("sell orders:\n");   
    while (q1)   
    {   
        if (q1->squencecode == stock_code)   
        printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", q1->orderid, q1->squencecode, q1->price, q1->quantity, q1->type);   
        p1 = p1->next; q1 = p1->next;   
    }   
}   
  
void treat3()   
{   
    int id;   
    int flag1 = 0, flag2 = 0;   
    scanf("%d", &id);   
    p = buy; q = p->next; p1 = sell; q1 = p1->next;   
    while (q&&!flag1)   
    {   
        if (q->orderid == id)   
        {   
           printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n",q->orderid,q->squencecode,q->price,q->quantity,q->type);   
           p->next = q->next; free(q); flag1 = 1; break;   
        }   
        else   
        {   
          p = p->next; q = p->next;   
        }   
    }   
    while (q1&&!flag2&&!flag1)   
    {   
        if (q1->orderid == id)   
        {   
          printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", q1->orderid, q1->squencecode, q1->price, q1->quantity, q1->type);   
          p1->next = q1->next; free(q1); flag2 = 1; break;   
        }   
        else   
        {   
          p1 = p1->next; q1 = p1->next;   
        }   
    }   
    if (!flag1&&!flag2)   
    {   
      printf("not found\n");   
    }   
}