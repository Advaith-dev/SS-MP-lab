#include <stdio.h>
#include <string.h>

struct macrostruct
{
    char lab[10];
    char opc[10];
    char opr[10];
} m[10];

void main()
{

    FILE *input, *output, *mdef;
    int lines;

    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    mdef = fopen("mdef.txt", "w");

    char label[20], opcode[20], operand[20], macroname[10];

    while (!feof(input))
    {
        fscanf(input, "%s %s %s", label, opcode, operand);
        if (strcmp(opcode, "MACRO") == 0)
        {
            lines = 0;
            strcpy(macroname, label);
            printf("Macro name: %s", macroname);
            fscanf(input, "%s %s %s", label, opcode, operand);

            while (strcmp(opcode, "MEND") != 0)
            {

                fprintf(mdef, " %s %s %s\n", label, opcode, operand);

                strcpy(m[lines].lab, label);
                strcpy(m[lines].opc, opcode);
                strcpy(m[lines].opr, operand);
                lines += 1;
                fscanf(input, "%s %s %s", label, opcode, operand);
            }
        }
        else if (strcmp(opcode, macroname) == 0)
        {
            for (int i = 0; i < lines; i++)
            {
                fprintf(output, "%s %s %s\n", m[i].lab, m[i].opc, m[i].opr);
            }
        }
        else
        {
            fprintf(output, "%s %s %s\n", label, opcode, operand);
        }
    }
    fclose(input);
    fclose(output);
    fclose(mdef);
}