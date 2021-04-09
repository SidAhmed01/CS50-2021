//logicial by language c

#include <stdio.h>
#include <cs50.h>


int main(void)
{   
    //variable
    string name = get_string("what is your name?\n");
    
    //print hello name 
    printf("Hello, %s", name);
    
}