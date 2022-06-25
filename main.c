#include<stdio.h>
#include<stdlib.h>

struct ship
{
    int length;
    int x;
    int y;
    int direction;
    int sunk;
};

struct move
{
    int player;
    char x;
    char y;
    int res;
};

int cmp(const char* a, const char* b) {
    int i = 0;
    while (a[i]) {
        if (a[i] != b[i])return 0;
        i++;
    }
    if (!b[i])return 1;
    return 0;
}

void lower_case(char* a) {
    int i = 0;
    while (a[i]) {
        if (a[i] >= 'A' && a[i] <= 'Z')a[i] = a[i] + ('a' - 'A');
        i++;
    }
}

int touching_sides(int table[12][12], int x, int y, int length, int direction) {
    for (int i = x - 1; i < (length + 2) * direction + 3 * !direction + x - 1; i++) {
        for (int j = y - 1; j < (length + 2) * !direction + 3 * direction + y - 1; j++) {
            if (table[j][i]) return 0;
        }
    }
    return 1;

}

void print_table(const int *table) {
    printf(" ");
    for (int j = 0; j < 10; j++) {
        printf("   %c  ", 'A' + j);
    }
    printf("\n");
    for (int i = 0; i < 10; i++) {
        printf("  ");
        for (int j = 0; j < 10; j++) {
            printf(" ---  ");
        }
        printf("\n");
        for (int j = 0; j < 10; j++) {
            char c;
            if (table[i + j * 10] == 0)c = ' ';
            if (table[i + j * 10] == 1)c = 'O';
            if (table[i + j * 10] == -1)c = 'Z';
            if (table[i + j * 10] == 2)c = 'X';
            if (j == 0)printf("%d", i + 1);
            if (j == 0 && i + 1 != 10)printf(" ");
            printf("| %c | ", c);
        }

        printf("\n");
    }
    printf("  ");
    for (int j = 0; j < 10; j++) {
        printf(" ---  ");
    }
    printf("\n");
}
////////////////////////////////////////////////////
int* read_from_file(struct ship* ships) {
    int* table = calloc(100 , sizeof(int));
    printf("Enter the location of your file.\n");
    char* location = calloc(100, sizeof(char));
    scanf("%s", location);
    FILE* input = fopen(location, "r");
    if (!input)return 0;
    char  direction = 0, line[9];
    char column = 0;
    int length, ship_count_2 = 0, ship_count_3 = 0, ship_count_4 = 0, ship_count_6 = 0, row;
    while (ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 < 10)
    {
        if (!fgets(line, 9, input))
            return 0;
        else
        {
            sscanf(line, "%d %c %c %d", &length, &direction, &column, &row);
            if (length != 2 && length != 3 && length != 4 && length != 6)
            {
                printf("The length of ship %d is unavailable!\n", ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 + 1);
            }
            if (length == 2) {
                if (ship_count_2 + 1 > 4) {
                    printf("The length of ship %d is unavailable!\n", ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 + 1);
                    return 0;
                }
            }
            if (length == 3) {
                if (ship_count_3 + 1 > 3) {
                    printf("The length of ship %d is unavailable!\n", ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 + 1);
                    return 0;
                }
            }
            if (length == 4) {
                if (ship_count_4 + 1 > 2) {
                    printf("The length of ship %d is unavailable!\n", ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 + 1);
                    return 0;
                }
            }
            if (length == 6) {
                if (ship_count_6 + 1 > 1) {
                    printf("The length of ship %d is unavailable!\n", ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 + 1);
                    return 0;
                }
            }
            if (direction != 'u' && direction != 'd' && direction != 'l' && direction != 'r') {
                printf("The direction of ship %d is unavailable!\n", ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 + 1);
                return 0;
            }
            if (!(column >= 'a' && column <= 'j'))printf("The column of ship %d is unavailable!\n", ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 + 1);
            if (!(row >= 1 && row <= 10))printf("The row of ship %d is unavailable!\n", ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 + 1);
            if (direction == 'u' && row - length < 0) {
                printf("Ship %d is outside the table!\n", ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 + 1);
                return 0;
            }
            if (direction == 'd' && row + length > 11) {
                printf("Ship %d is outside the table!\n", ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 + 1);
                return 0;
            }
            if (direction == 'l' && column - 'a' - length + 1 < 0) {
                printf("Ship %d is outside the table!\n", ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 + 1);
                return 0;
            }
            if (direction == 'r' && column - 'a' + length + 1 > 11) {
                printf("Ship %d is outside the table!\n", ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 + 1);
                return 0;
            }
            int copy[12][12] = { 0 };
            for (int i = 1; i < 11; i++) {
                for (int j = 1; j < 11; j++) {
                    copy[j][i] = table[j - 1 + (i - 1) * 10];
                }
            }
            int x, y, direction_int;
            if (direction == 'u')x = column - 'a', y = row - length, direction_int = 0;
            if (direction == 'd')x = column - 'a', y = row - 1, direction_int = 0;
            if (direction == 'l')x = column - 'a' - length + 1, y = row - 1, direction_int = 1;
            if (direction == 'r')x = column - 'a', y = row - 1, direction_int = 1;
            if (!touching_sides(copy, x + 1, y + 1, length, direction_int)) {
                printf("Ship %d can't be on this position.\n", ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 + 1);
                return 0;
            }
            if (length == 2) ship_count_2++;
            if (length == 3) ship_count_3++;
            if (length == 4) ship_count_4++;
            if (length == 6) ship_count_6++;

            for (int i = x; i < length * direction_int + 1 * !direction_int + x; i++) {
                for (int j = y; j < length * !direction_int + 1 * direction_int + y; j++) {
                    table[j + i * 10] = 1;
                }
            }
            ships[ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 - 1].direction = direction_int;
            ships[ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 - 1].x = x;
            ships[ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 - 1].y = y;
            ships[ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 - 1].length = length;
            ships[ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 - 1].sunk = 0;
        }
    }
    return table;
}
////////////////////////////////////
int* read_from_console(struct ship* ships)
{
    int* table = calloc(100,sizeof(int));
    int length, ship_count_2 = 0, ship_count_3 = 0, ship_count_4 = 0, ship_count_6 = 0, row;
    char column;
    char* direction = calloc(6, sizeof(char));
    while (ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 < 10)
    {
        printf("Ship number %d\n", ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 + 1);
        int valid_length;
        do {
            valid_length = 1;
            printf("Enter the length of the ship (You can place one ship with length 6, two ships with length 4, three ships with length 3 and four ships with length 2):\n");
            char length_c;
            scanf("%c", &length_c);
            if (length_c == '\n')scanf("%c", &length_c);
            length = length_c - '0';
            if (length != 2 && length != 3 && length != 4 && length != 6)
            {
                printf("This length is unavailable!\n");
                valid_length = 0;
                continue;
            }
            if (length == 2) {
                if (ship_count_2 + 1 > 4) {
                    printf("There are already 4 ships with length 2.\n");
                    valid_length = 0;
                    continue;
                }
            }
            if (length == 3) {
                if (ship_count_3 + 1 > 3) {
                    printf("There are already 3 ships with length 3.\n");
                    valid_length = 0;
                    continue;
                }
            }
            if (length == 4) {
                if (ship_count_4 + 1 > 2) {
                    printf("There are already 2 ships with length 4.\n");
                    valid_length = 0;
                    continue;
                }
            }
            if (length == 6) {
                if (ship_count_6 + 1 > 1) {
                    printf("There is already a ship with length 6.\n");
                    valid_length = 0;
                    continue;
                }
            }

            int valid;
            do {
                valid = 1;
                printf("Enter a direction of the ship (up-u, down-d, left-l, right-r):\n");
                scanf("%s", direction);
                lower_case(direction);
                if (!cmp(direction, "u") && !cmp(direction, "d") && !cmp(direction, "l") && !cmp(direction, "r") && !cmp(direction, "up") && !cmp(direction, "down") && !cmp(direction, "left") && !cmp(direction, "right")) {
                    printf("Wrong direction!\n");
                    valid = 0;
                    continue;
                }

                do {
                    printf("Enter a column (a - j):\n");
                    scanf("%c", &column);
                    if (column == '\n')scanf("%c", &column);
                    lower_case(&column);
                    if (!(column >= 'a' && column <= 'j'))printf("Wrong column!\n");
                } while (!(column >= 'a' && column <= 'j'));

                do {
                    printf("Enter a row (1 - 10):\n");
                    char* row_c=calloc(3,sizeof(char));
                    scanf("%s", row_c);
                    if(cmp(row_c,"10")) row=10;
                    else row = row_c[0] - '0';
                    if (!(row >= 1 && row <= 10))printf("Wrong row!\n");
                } while (!(row >= 1 && row <= 10));

                if ((cmp(direction, "u") || cmp(direction, "up")) && row - length < 0) {
                    printf("This ship is outside the table!\n");
                    valid = 0;
                }
                if ((cmp(direction, "d") || cmp(direction, "down")) && row + length > 11) {
                    printf("This ship is outside the table!\n");
                    valid = 0;
                }
                if ((cmp(direction, "l") || cmp(direction, "left")) && column - 'a' - length + 1 < 0) {
                    printf("This ship is outside the table!\n");
                    valid = 0;
                }
                if ((cmp(direction, "r") || cmp(direction, "right")) && column - 'a' + length + 1> 11) {
                    printf("This ship is outside the table!\n");
                    valid = 0;
                }
            } while (!valid);

            int copy[12][12] = { 0 };
            for (int i = 1; i < 11; i++) {
                for (int j = 1; j < 11; j++) {
                    copy[j][i] = table[j - 1 + (i - 1) * 10];
                }
            }

            int x, y, direction_int;
            if (cmp(direction, "u") || cmp(direction, "up"))x = column - 'a', y = row - length, direction_int = 0;
            if (cmp(direction, "down") || cmp(direction, "d"))x = column - 'a', y = row - 1, direction_int = 0;
            if (cmp(direction, "left") || cmp(direction, "l"))x = column - 'a' - length + 1, y = row - 1, direction_int = 1;
            if (cmp(direction, "right") || cmp(direction, "r"))x = column - 'a', y = row - 1, direction_int = 1;
            if (!touching_sides(copy, x + 1, y + 1, length, direction_int)) {
                printf("This ship can't be on this position.\n");
                valid_length = 0;
                continue;
            }

            if (length == 2) ship_count_2++;
            if (length == 3) ship_count_3++;
            if (length == 4) ship_count_4++;
            if (length == 6) ship_count_6++;

            for (int i = x; i < length * direction_int + 1 * !direction_int + x; i++) {
                for (int j = y; j < length * !direction_int + 1 * direction_int + y; j++) {
                    table[j + i * 10] = 1;
                }
            }
            ships[ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 - 1].direction = direction_int;
            ships[ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 - 1].x = x;
            ships[ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 - 1].y = y;
            ships[ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 - 1].length = length;
            ships[ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 - 1].sunk = 0;
            int choice;
            printf("Choose:\n");

            if (ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 < 10) printf("1.Place new ship.\n");
            else printf("1.Start game\n");
            printf("2.Change coordinates of a ship\n3.View the playing table\n");

            do {
                char choice_c;
                scanf("%c", &choice_c);
                if (choice_c == '\n')scanf("%c", &choice_c);
                choice = choice_c - '0';
                if (!(choice > 0 && choice < 4))printf("Choose again!\n");
            } while (!(choice > 0 && choice < 4));

            if (choice == 1)continue;
            if (choice == 2) {
                printf("Which ship do you want to change the position of:\n");
                int index;
                scanf("%d", &index);
                index--;
                if (ships[index].length == 2)ship_count_2--;
                if (ships[index].length == 3)ship_count_3--;
                if (ships[index].length == 4)ship_count_4--;
                if (ships[index].length == 6)ship_count_6--;
                for (int i = ships[index].x; i < ships[index].length * ships[index].direction + 1 * !ships[index].direction + ships[index].x; i++) {
                    for (int j = ships[index].y; j < ships[index].length * !ships[index].direction + 1 * ships[index].direction + ships[index].y; j++) {
                        table[j + i * 10] = 0;
                    }
                }
                valid_length = 0;
                continue;
            }
            if (choice == 3)print_table(table);
        } while (!valid_length);

    }
    return table;
}

int play_turn(const int *table, int x, int y, struct ship* ships) {
    if (table[y+10*x]) {
        for (int i = 0; i < 10; i++) {
            if (x >= ships[i].x && x <= ships[i].x + ships[i].length * ships[i].direction && y >= ships[i].y && y <= ships[i].y + ships[i].length * !ships[i].direction) {
                ships[i].sunk++;
                if (ships[i].sunk == ships[i].length) return 2;
                return 1;
            }
        }
    }
    return 0;
}

int save_formation_to_file(struct ship *ships, FILE *output)
{
    if (!output) return 1;
    for (int i = 0; i < 4; i++)
        fprintf(output, "%d %d %d %d\n", ships[i].length, ships[i].direction, ships[i].x, ships[i].y);
    fputs("\n", output);
    return 0;
}

int save_moves_to_file(struct move* moves, int move_count, FILE *output)
{
    if (!output) return 1;
    for (int i = 0; i < move_count; i++)
        fprintf(output, "%d %c %c %d\n", moves[i].player, moves[i].x, moves[i].y, moves[i].res);
    return 0;
}

int main() {
    int* table1, * table2;
    struct ship* ships1 = malloc(sizeof(struct ship) * 10);
    struct ship* ships2 = malloc(sizeof(struct ship) * 10);
    struct move *moves = malloc(sizeof (struct move) * 100);
    int sunk1 = 10, sunk2 = 10, move_cnt = 0;
    table1 = read_from_console(ships1);
    print_table(table1);
    table2 = read_from_console(ships2);
    while (sunk1 && sunk2)
    {
        char y;
        char x;
        struct move move;
        do {
            printf("Enter column for attack (a - j): \n");
            scanf("%c", &x);
            if (x == '\n')scanf("%c", &x);
            lower_case(&x);
            if (!(x >= 'a' && x <= 'j'))printf("Wrong column!\n");
        } while (!(x >= 'a' && x <= 'j'));

        do {
            printf("Enter row for attack (1 - 10):\n");
            scanf("%c", &y);
            if (y == '\n')scanf("%c", &y);
            if (!(y - '0' >= 1 && y - '0' <= 10))printf("Wrong row!\n");
        } while (!(y - '0' >= 1 && y - '0' <= 10));

        int res = play_turn(table2, x - 'a', y - '1', ships2);
        if (res == 0)printf("Miss!\n");
        if (res == 1)printf("Hit!\n");
        if (res == 2)printf("Ship sunk!\n"), sunk2--;

        move.player = 0;
        move.x = x;
        move.y = y;
        move.res = res;
        moves[move_cnt++] = move;

        do {
            printf("Enter column for attack (a - j):\n");
            scanf("%c", &x);
            if (x == '\n')scanf("%c", &x);
            lower_case(&x);
            if (!(x >= 'a' && x <= 'j')) printf("Wrong column!\n");
        } while (!(x >= 'a' && x <= 'j'));

        do {
            printf("Enter row for attack (1 - 10):\n");
            scanf("%c", &y);
            if (y == '\n')scanf("%c", &y);
            if (!(y - '0' >= 1 && y - '0' <= 10))printf("Wrong row!\n");
        } while (!(y - '0' >= 1 && y - '0' <= 10));

        int res1 = play_turn(table1, x - 'a', y - '1', ships1);
        if (res1 == 0) printf("Miss!\n");
        if (res1 == 1) printf("Hit!\n");
        if (res1 == 2) printf("Ship sunk!\n"), sunk1--;

        move.player = 1;
        move.x = x;
        move.y = y;
        move.res = res;
        moves[move_cnt++] = move;
    }
    char choice;
    if(!sunk1)
        printf("Player 2 wins");
    else if(!sunk2)
        printf("Player 1 wins");
    printf("Do you want to save your game [y/n]:\n");
    scanf("%c", &choice);
    if(choice == 'y')
    {
        printf("Enter the location of your game replay file:\n");
        char *location = calloc(256, sizeof(char));
        location = "/home/indiana/CLionProjects/UASD/battleships/formation.txt";
        //scanf("%s", location);
        FILE *output = fopen(location, "w+");
        save_formation_to_file(ships1, output);
        save_formation_to_file(ships2, output);
        save_moves_to_file(moves, move_cnt, output);
        fclose(output);
    }
    return 0;
}