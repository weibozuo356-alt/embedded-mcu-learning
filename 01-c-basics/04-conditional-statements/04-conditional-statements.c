#include <stdio.h>

int main(void)
{
    int a;
    scanf("%d",&a);
    if(a<10)
    {
        if(a<5)
        {
            if(a<0)
            {
                printf("a is less than 0\n");
            }
            else
            {
                printf("a is greater than or equal to 0 and less than 5\n");
            }
        }
        else
        {
            printf("a is greater than or equal to 5\n");
        }
    }
    else
    {
        printf("a is greater than or equal to 10\n");
    }
    return 0;

}
