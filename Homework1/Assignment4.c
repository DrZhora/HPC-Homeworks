
# include <stdio.h>



int main(){

    int x = 1;
    int *ptr1 = &x;
    int **ptr2 = &ptr1;

    printf("%i\n",*ptr1);
    printf("%i\n",**ptr2);


    return 0;
}