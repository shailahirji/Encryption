/*
 * Author: Shaila Hirji
 * Assignment 2, CS 351 Part 2
 * This application encodes a message
 * It prompts the user for a message to be encoded and a number to encode the message with
 * It allows user to enter a message with spaces
 * Doesn't allow user to encode digits, only alphabets
 * Doesnt encrypt special symbols
 * Maximum input user can enter is 100 characters long. Average length of a sentence.
 */

void encode(char * text, int value);

#include <cstdio>
#include <cstring>
#include <cctype>

int main() {

    //reading from the user
    int value;
    char word[100];
    char *wordP=word;

    printf("Enter a word:");

    getWord:
    fgets(wordP,100,stdin);
    int i;
    for (i = 0; i < strlen(wordP); i++) { //allow user to input only alphabets, upper and/or lower case
        if (isdigit(wordP[i])) {
            printf("Please enter a valid word: ");
            goto getWord;
        }
    }

    fflush(stdin);

    printf("Enter a number: ");
    while (fscanf(stdin, "%d", &value) != 1) { //notice you're de-referencing encrypt why??
        printf("Please enter valid number: ");//allow user to re-enter valid number
        scanf("%*s");//take in the invalid value and discard

    }

    encode(wordP,value);

    printf("Encrypted text: ");
    printf("%s",wordP);

}

/*
 * This method encrypts user's input message by moving the characters of the message a specified value up
 * if the encryption value causes a spill over ( values causes going beyond the alphabets left) the algorithm loops over and starts from a
 * if user enters a value >26, we adjust it to be below 26
*/
void encode(char * text, int value){

    //traverse though the char array and increment its content
    int i;
    char c;
    int number;
    for(i=0;i<strlen(text);i++){

    c=text[i];//get char from input message

        //if user enters value greater than 26,
        if(value>26){
            value=value%26;
        }

        if(isupper(c)){

            if((value-(26-(int)c))-64>0){ //cant simply increment character, needs to loop over and start from a
                number=value-(26-c);
                c=(char) number;// replace character with encryption
            } else if(c==' '){//allow inputs with space
                goto final;//if space found, just leave it as a space
            }
            else{//can just increment by value, no need to loop over alphabets
                c = c + (char)value; //replace character with encryption
            }

        }else if(islower(c)){

            if((value-(26-(int)c)-96>0)){//looping over alphabets, cant simply encrypt by incrementing char by the value
                number=value-(26-c);
                c=(char) number;

            }else {
                c = c + (char) value;// no need to loop over, value can reach to other alphabets without looping over
            }
        }

        final:
        text[i]=c; //place new, encoded character into char array
    }

}