

# include <stdio.h>



int str_length(char *str){

    char *ptr = str;   
    int length = 0;
    
    while (*ptr != '\0') {  
        length++;
        ptr++;              
    }
    
    return length;
}


int main(){

    char *ptr = "Hello";

    for(int i=0; i<5; i++){
        printf("%c",*(ptr+i));
    }


    char user_input_str[100];
    printf("\nType a string: \n");
    scanf("%s",user_input_str); 
    
    printf("%s\n",user_input_str);

    int length = str_length(&user_input_str[0]);

    printf("User provided string length: %i\n",length);






    return 0;
}