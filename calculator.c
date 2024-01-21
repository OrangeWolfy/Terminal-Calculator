#include<stdio.h>
#include<string.h>
#include<ctype.h>

// Terminal calculator as alias
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
    int n1 = 0, n2 = 0, res = 0;
    char op, current;
    int sizeOperation, sign, i;

    // Check if no arguments where given
    if(argc == 1){
        printf("calc: missing operand\n");
        printf("Try 'calc --help' for more information\n");
    }
    // Check for help command
    else if(strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "--h") == 0){
        printf("Usage: calc [OPERATION]\naddition, subtraction, multiplication and/or division.\n");
        printf("Solve the [OPERATION] given.\n");
        printf("\nCalculate the result of any operation given as long as it contains only\n");
        printf("The [OPERATION] given must only contain:\n");
        printf("\t-numbers\n\t-addition simbol (+)\n\t-subtraction simbol (-)\n\t-multiplication simbol (*)/(x)\n\t-division simbol (/)\n");
        printf("\nFor more information: <https://github.com/OrangeWolfy/Terminal-Calculator>\n");
    }
    // Run main program
    else{
        sizeOperation = strlen(argv[1]);

        // Check if the first number is negative
        sign = argv[1][0] == '-' ? 1 : 0;

        // Get the first digit and operator
        for(i = sign; i < sizeOperation; i++)
        {
            current = argv[1][i];
            if(isdigit(current)){
                n1 += current - '0';
                n1 *= 10;
            }
            else{
                op = argv[1][i++];
                break;
            }
        }
        n1 /= 10;
        if(sign == 1)
            n1 *= -1;

        while(i < sizeOperation){
            // Get the second digit
            for(; i < sizeOperation; i++)
            {
                current = argv[1][i];
                if(isdigit(current)){
                    n2 += current - '0';
                    n2 *= 10;
                }
                else break;
            }
            n2 /= 10;
            
            res = calc(n1, &op, n2);
            
            // Check for invalid or missing arguments
            if(op == '\0' || n2 == '\0'){
                printf("Invalid operation\n");
                return 0;
            }
            
            printf("%d %c %d = %d\n", n1, op, n2, res);

            // Apply the result to the first number in case of looping to keep count and get the next operator if it exists
            n1 = res;
            n2 = 0;
            op = argv[1][i++];
        }
    }
    
    return 0;
}
