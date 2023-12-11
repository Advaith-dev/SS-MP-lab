#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main()
{
    FILE *intmed, *sym, *optab, *output;
    int count = 0;
    intmed = fopen("intmed.txt", "r");
    sym = fopen("symtab.txt", "r");
    optab = fopen("optab.txt", "r");
    output = fopen("output.txt", "w");

    char loc[20], label[20], opcode[20], operand[20], progname[20], opc[20], opr[20], symaddr[20], symname[20], strtaddr[20];

    fscanf(intmed, "%s %s %s %s", &loc, &progname, &opcode, &strtaddr);

    if (strcmp(opcode, "START") == 0)
    {
        printf("Program name: %s \nStart Address: %s", progname, strtaddr);
        fprintf(output, "H^%s  ^00%s^000000", progname, strtaddr);
    }

    fscanf(intmed, "%s %s %s %s", &loc, &label, &opcode, &operand);
    fprintf(output, "\nT^00%s^$$^", loc);

    while (strcmp(opcode, "END") != 0)
    {

        if (strcmp(opcode, "BYTE") == 0 || strcmp(opcode, "WORD") == 0)
        {
            count += 1;
            if (operand[0] == 'C')
            {
                int clen = strlen(operand);
                for (int i = 2; i < clen - 1; i++)
                {

                    fprintf(output, "%d", operand[i]);
                }
                fputc('^', output);
            }
            else
            {
                count += 1;
                int len = strlen(operand);
                len = 6 - len;
                for (int i = 0; i < len; i++)
                {
                    fputs("0", output);
                }
                fprintf(output, "%s", operand);
            }
        }
        else
        {
            while (!feof(optab))
            {
                fscanf(optab, "%s %s", &opc, &opr);
                if (strcmp(opc, opcode) == 0)
                {

                    fprintf(output, "%s", opr);
                    break;
                }
            }
            rewind(optab);
        }

        if (strcmp(operand, "-") != 0)
        {
            while (!feof(sym))
            {
                fscanf(sym, "%s %s", symaddr, symname);
                if (strcmp(operand, symname) == 0)
                {
                    fprintf(output, "%s^", symaddr);
                    break;
                }
            }
        }
        fscanf(intmed, "%s %s %s %s", &loc, &label, &opcode, &operand);
    }
    fprintf(output, "\nE^00%s", strtaddr);
    char tlen[10];
    int totallen = atoi(loc) - atoi(strtaddr);

    rewind(output);
    fprintf(output, "H^%s  ^00%s^0000%x", progname, strtaddr, totallen);
    fseek(output, 11, SEEK_CUR);
    count = (count * 6);
    fprintf(output, "%x", count);
    printf("\nText record length  decimal: %d", count);
    fclose(output);
    fclose(optab);
    fclose(sym);
    fclose(intmed);
}