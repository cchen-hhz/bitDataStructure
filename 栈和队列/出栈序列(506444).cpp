#include <stdio.h>
int main()
{
    int n, m, f = 0;
    while (scanf("%d%d", &n, &m) == 2 && (n || m))
    {
        if (f)
            printf("\n");
        else
            f = 1;
        for (int j = 0; j < m; j++)
        {
            int s[100001], tp = 0, nn = 0;
            for (int i = 0; i < n; i++)
            {
                int x;
                scanf("%d", &x);
                if (x > nn)
                {
                    for (int k = nn + 1; k < x; k++)
                        s[++tp] = k;
                    nn = x;
                }
                else if (tp > 0 && s[tp] == x)
                {
                    tp--;
                }
                else
                {
                    printf("No\n");
                    while (++i < n)
                        scanf("%*d");
                    goto next;
                }
            }
            printf("Yes\n");
        next:;
        }
    }
}
