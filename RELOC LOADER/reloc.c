#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convert(char relocbit[3], char valuearray[12]);

void main()
{
    FILE *input, *output;

    input = fopen("input.txt", "r");
    output = fopen("oputput.txt", "w");
    char buffer[50], addrs[20], buffer2[20], relocbit[3], valuearray[12], recname[1];
    int intorgaddrs, newaddrs, dispaddrs;

    fscanf(input, "%s %s %x %s", buffer, buffer, addrs, buffer);
    intorgaddrs = atoi(addrs);

    printf("Enter the new address of the program: ");
    scanf("%x", &newaddrs);
    newaddrs += intorgaddrs;
    dispaddrs = newaddrs;
    printf("%x", newaddrs);

    fscanf(input, "%s %s %s %s ", recname, buffer, buffer, relocbit);
    printf("reloc bit : %s recname: %s", relocbit, recname);
    convert(relocbit, valuearray);
    printf("\nValue array : %s", valuearray);
    int j = 0;
    fscanf(input, "%s", buffer2);

    while (strcmp(buffer2, "E") != 0)
    {

        if (strcmp(buffer2, "T") == 0)
        {
            strcpy(valuearray, "");
            j = 0;
            fscanf(input, "%s", relocbit);
            fscanf(input, "%s", relocbit);
            fscanf(input, "%s", relocbit);
            convert(relocbit, valuearray);
            printf("\nrelocarray: %s", valuearray);
            continue;
        }
        if (valuearray[j] == '1')
        {
            int intobjcode = atoi(buffer2) + newaddrs;
            printf("\n %x : %d ", dispaddrs, intobjcode);
            dispaddrs += 3;
            j += 1;
        }
        else if (valuearray[j] == '0')
        {
            printf("\n %x : %s ", dispaddrs, buffer2);
            dispaddrs += 3;
        }
        fscanf(input, "%s", buffer2);
    }
}

void convert(char relocbit[3], char valuearray[12])
{
    for (int i = 0; i < 3; i++)
    {
        char x = relocbit[i];
        switch (x)
        {
        case '0':
            strcat(valuearray, "0000");
            break;
        case '1':
            strcat(valuearray, "0001");
            break;
        case '2':
            strcat(valuearray, "0010");
            break;
        case '3':
            strcat(valuearray, "0011");
            break;
        case '4':
            strcat(valuearray, "0100");
            break;
        case '5':
            strcat(valuearray, "0101");
            break;
        case '6':
            strcat(valuearray, "0110");
        case '7':
            strcat(valuearray, "0111");
        case '8':
            strcat(valuearray, "1000");
            break;
        case '9':
            strcat(valuearray, "1001");
            break;
        case 'A':
            strcat(valuearray, "1010");
            break;
        case 'B':
            strcat(valuearray, "1011");
            break;
        case 'C':
            strcat(valuearray, "1100");
            break;
        case 'D':
            strcat(valuearray, "1101");
            break;
        case 'E':
            strcat(valuearray, "1110");
            break;
        case 'F':
            strcat(valuearray, "1111");
            break;
        }
    }
}