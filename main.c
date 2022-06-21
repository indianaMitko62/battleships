#include <stdio.h>

int main()
{
    int game_table[10][10] = { 0 };
    FILE *formation = fopen("./formation.txt", "r");
    char row = 0, direction = 0, line[8];
    int column = 0, length = 0;
    while(1)
    {
        if(!fgets(line, 9, formation))
            break;
        else
        {
            sscanf(line, "%c %d %c %d", &row, &column, &direction, &length);
            if(row == '\n') break;
            printf("%s", line);
            printf("\ndata: %c %d %c %d\n\n", row, column, direction, length);
            //put in table
        }
    }

    return 0;
}
