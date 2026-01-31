

# include <stdio.h>




int main(){

    // Version A

    // char* ptr1 = "High";
    // char* ptr2 = "Performance";
    // char* ptr3 = "Conputing";

    // char **str[] = {&ptr1,&ptr2,&ptr3};

    // printf("Old Array:\n");
    // for(int i=0; i<3; i++){
    //    printf("%s\n",**(str+i));
    // }

    // ptr1 = "Low";

    // printf("\nModified Array:\n");
    // for(int i=0; i<3; i++){
    //    printf("%s\n",**(str+i));
    // }


    // Version B

    char *fruits[] = {"High", "Performance", "Computing"};
    int size = sizeof(fruits) / sizeof(fruits[0]);
   
    printf("Old Array:\n");    
    for (int i = 0; i < size; i++) {
        printf("%s\n", *(fruits + i));
    }
    
    fruits[0] = "Low";  

    printf("\nModified Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%s\n", *(fruits + i));
    }
    

    return 0;
}