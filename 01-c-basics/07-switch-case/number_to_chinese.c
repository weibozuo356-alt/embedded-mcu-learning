#include <stdio.h>

int main(void)
{
    int number;

    printf("Enter an integer from 1 to 10: ");
    scanf("%d", &number);

    switch (number)
    {
        case 1:
            printf("一\n");
            break;
        case 2:
            printf("二\n");
            break;
        case 3:
            printf("三\n");
            break;
        case 4:
            printf("四\n");
            break;
        case 5:
            printf("五\n");
            break;
        case 6:
            printf("六\n");
            break;
        case 7:
            printf("七\n");
            break;
        case 8:
            printf("八\n");
            break;
        case 9:
            printf("九\n");
            break;
        case 10:
            printf("十\n");
            break;
        default:
            printf("输入不在 1 到 10 的范围内。\n");
            break;
    }

    return 0;
}
