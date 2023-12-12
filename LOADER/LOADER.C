#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *input, *output;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    int i = 2;
    int intaddrs;
    char buffer[80], progname[20], strtaddr[20];
    fscanf(input, "%s", buffer);

    while (buffer[i] != '^')
    {
        progname[i - 2] = buffer[i];
        i += 1;
    }
    printf("Program name = %s", progname);

    while (!feof(input))
    {
        fscanf(input, "%s", buffer);
        if (buffer[0] == 'E')
        {
            break;
        }
        if (buffer[0] == 'T')
        {
            i = 2;
            while (buffer[i] != '^')
            {
                strtaddr[i - 2] = buffer[i];
                i += 1;
            }
            intaddrs = atoi(strtaddr);
            printf("\nstart addrs: %d", intaddrs);
            i = 12;
            int len = strlen(buffer);
            printf("\n%s", buffer);

            for (i; i < len; i++)
            {
                if (buffer[i] == '^')
                {
                    continue;
                }
                fprintf(output, "%d     %c%c\n", intaddrs, buffer[i], buffer[i + 1]);
                printf("\n%d     %c%c", intaddrs, buffer[i], buffer[i + 1]);
                intaddrs += 1;
                i += 1;
            }
        }
    }
    fclose(input);
    fclose(output);
}