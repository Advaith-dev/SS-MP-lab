#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main()
{
    FILE *input, *optab, *symtab, *intermed;

    input = fopen("input.txt", "r");
    optab = fopen("optab.txt", "r");
    symtab = fopen("symtab.txt", "w+");
    intermed = fopen("intermed.txt", "w+");

    int startaddr, operand, locctr, nextloc;
    char label[20], operation[20], operandS[20], symbol[20], optaboper[20];

    fscanf(input, "%s %s %d", &label, &operation, &operand);
    if (strcmp(operation, "START") == 0)
    {
        printf("START");
        startaddr = operand;
        locctr = startaddr;
        fprintf(intermed, "%s %s %d\n", label, operation, operand);
    }

    fscanf(input, "%s %s %s", &label, &operation, &operandS);

    while (strcmp(operation, "END") != 0)
    {
        fprintf(intermed, "%d %s %s %s\n", locctr, label, operation, operandS);

        printf("\n %s %s %s", &label, &operation, &operandS);
        if (strcmp(label, "-") != 0)
        {

            fprintf(symtab, "%s %d \n", label, locctr);
        }

        while (!feof(optab))
        {
            fscanf(optab, " %s ", &optaboper);

            if (strcmp(operation, optaboper) == 0)
            {

                locctr = locctr + 3;
                printf("\nassmb dir :%d", locctr);
                break;
            }

            fscanf(optab, " %s ", &optaboper);
        }
        if (feof(optab) != 0)
        {
            printf("\n not Assembler dir");
            if (strcmp(operation, "WORD") == 0)
            {
                locctr = locctr + 3;
            }
            else if (strcmp(operation, "RESW") == 0)
            {
                printf("%d", atoi(operandS));
                locctr = locctr + (3 * atoi(operandS));
            }
            else if (strcmp(operation, "RESB") == 0)
            {
                locctr = locctr + (atoi(operandS));
            }
            else if (strcmp(operation, "BYTE") == 0)
            {
                locctr = locctr + (strlen(operandS) - 3);
            }
        }
        rewind(optab);

        fscanf(input, "%s %s %s ", &label, &operation, &operandS);
    }

    fprintf(intermed, "%d %s %s %s\n", locctr, label, operation, operandS);
    fclose(input);
    fclose(intermed);
    fclose(optab);
    fclose(symtab);
}
