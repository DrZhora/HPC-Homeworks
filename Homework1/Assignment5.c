

# include <stdio.h>
#include <stdlib.h>



int main(){

    int *ptr = malloc(sizeof(int));
    
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    *ptr = 5;
    printf("Int\n");
    printf("%i\n",*ptr);


    int *ptr2 = malloc(sizeof(int)*5);

    if (ptr2 == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Array\n");
    for(int i=0; i<5; i++){
        *(ptr2+i) = i + 2;
    }


    for(int i=0; i<5; i++){
        printf("%i\n", *(ptr2+i));
    }


    free(ptr);
    free(ptr2);






    return 0;
}