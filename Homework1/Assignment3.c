
# include <stdio.h>


void swap(int *a, int *b){

    int tmp = *a;
    *a = *b;
    *b = tmp;

}

int main(){

    int a = 1;
    int b = 2;

    printf("Before the swap\n");
    printf("%i\n",a);
    printf("%i\n",b);


    swap(&a,&b);

    printf("After the swap\n");
    printf("%i\n",a);
    printf("%i\n",b);




    return 0;
}