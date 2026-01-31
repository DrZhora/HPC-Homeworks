
# include <stdio.h>

int main(){

    int x = 1;
    int *ptr = &x;

    printf("%p\n", &x);
    printf("%p\n", ptr);

    *ptr = 2;

    printf("%i\n", x);
    printf("%i\n", *ptr);



    return 0;
}