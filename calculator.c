#include<stdio.h>
#include<string.h>
#include<ctype.h>

// Terminal calculator with alias
// Execute this file and create an alias to work

int calc(int n1, char *op, int n2)
{
    int res;
    switch(*op){
        case '+':
            res = n1 + n2;
            break;
        case '-':
            res = n1 - n2;
            break;
        case '*':
        case 'x':
            res = n1 * n2;
            break;
        case '/':
            if(n2 != 0)
                res = n1 / n2;
            else{
                printf("Cannot divide by 0\n");
                *op = 0;
            }
            break;
        default:
            *op = '\0';
            break;
    }
    return res;
}

int main(int argc, char* argv[]){
    int n1, n2, res = 10;
    char op, current;
    int size, sign, i;

    if(argc == 1){ // Check if when executed it was executed without any arguments
        printf("calc: missing operand\n");
        printf("Try 'calc --help' for more information\n");
    }
    else if(strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "--h") == 0){ // Check if it was executed with the --help or --h arguments
        printf("Usage: calc [OPERATION]\naddition, subtraction, multiplication and/or division.\n");
        printf("Solve the [OPERATION] given.\n");
        printf("\nCalculate the result of any operation given as long as it contains only\n");
        printf("The [OPERATION] given must only contain:\n");
        printf("\t-numbers\n\t-addition simbol (+)\n\t-subtraction simbol (-)\n\t-multiplication simbol (*)/(x)\n\t-division simbol (/)\n");
        printf("\nFor more information: <https://github.com/OrangeWolfy>\n");
    }
    else{ // Run
        sizeOperation = strlen(argv[1]);

        sign = argv[1][0] == '-' ? 1 : 0; // Check if the first element is '-' as in negative

        for(i = sign; i < sizeOperation; i++) // Get the first digit and operator
        {
            current = argv[1][i];
            // Check if the current argument is a number or if not save it as the operator
            if(isdigit(current)){
                n1 += current - '0';
                n1 *= 10;
            }
            else{
                op = argv[1][i++];
                break;
            }
        }
        // Remove last cero and turn it negative if necessary
        n1 /= 10;
        if(sign == 1)
            n1 *= -1;

        while(i < sizeOperation){ // Loop in case there is more than one operation needed
            for(; i < sizeOperation; i++) // Get the second digit
            {
            // Check if the current argument is a number
                current = argv[1][i];
                if(isdigit(current)){
                    n2 += current - '0';
                    n2 *= 10;
                }
                else break;
            }
            n2 /= 10;
            
            res = calc(n1, &op, n2);
            printf("%d %c %d = %d\n", n1, op, n2, res);

            if(op == '\0' || n2 == '\0'){ // Check for invalid or missing arguments
                printf("Invalid operation\n");
                return 0;
            }

            // Apply the result to the first number in case of looping to keep count and get the next operator if it exists
            n1 = res;
            n2 = 0;
            op = argv[1][i++];
        }
    }
    
    return 0;
}
