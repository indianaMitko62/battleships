#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>

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
    int y;
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

char* encrypt(char* string, char* password, char* table, int length)
{
    int password_length = (int)strlen(password);
    char* cipher = (char*)malloc(length);
    int idk;
    for(int i = 0, j = 0; i < length; i++, j++)
    {
        if(j == password_length)
            j = 0;
        idk = (string[i] + password[j] + password_length) % 256;
        cipher[i] = table[idk];
        //printf("%u ", (unsigned int)(string[i] + password[j]) % 256);
    }
    return cipher;
}

char* decrypt(char* string, char* password, char* table, int length)
{
    int password_length = (int)strlen(password);
    char* deciphered = (char*)malloc(length);
    for(int i = 0, j = 0; i < length; i++, j++)
    {
        if(j == password_length)
            j = 0;
        deciphered[i] = table[(string[i] - password[j] + 256 - password_length) % 256];
        //printf("%c", deciphered[i]);
    }
    return deciphered;
}

char* generateTable()
{
    char* table = (char*)malloc(65536);
    for(int i = 0; i < 256; i++)
    {
        for(int j = 0; j < 256; j++)
        {
            table[i * 256 + j]  = (char)((i + j) % 256);
        }
    }
    return table;
}

int* read_from_file(struct ship* ships, int second)
{
    int* table = calloc(100 , sizeof(int));
    printf("Enter the location of your file.\n");
    char* location = calloc(256, sizeof(char));
    scanf("%s", location);
    FILE* input = fopen(location, "r");
    if (!input) return 0;
    char  direction = 0, line[10];
    char column = 0;
    int length, ship_count_2 = 0, ship_count_3 = 0, ship_count_4 = 0, ship_count_6 = 0, row;
    char line_[10];
    if(second)
    {
        do
        {
            fgets(line_, 10, input);
            if(line_[0] == 'm') break;
        }
        while(1);
    }
    while (ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 < 10)
    {
        if (!fgets(line, 10, input))
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
            if (direction != 'u' && direction != 'd' && direction != 'l' && direction != 'r' && direction != '1' && direction != '0') {
                printf("The direction of ship %d is unavailable!\n", ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 + 1);
                return 0;
            }
            if (!(column >= 'a' && column <= 'j'))printf("The column of ship %d is unavailable!\n", ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 + 1);
            if (!(row >= 1 && row <= 10))printf("The row of ship %d is unavailable!\n", ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 + 1);
            if (direction == 'u' && row - length < 0) {
                printf("Ship %d is outside the table!\n", ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 + 1);
                return 0;
            }
            if ((direction == 'd' || direction == 0) && row + length > 11) {
                printf("Ship %d is outside the table!\n", ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 + 1);
                return 0;
            }
            if (direction == 'l' && column - 'a' - length + 1 < 0) {
                printf("Ship %d is outside the table!\n", ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 + 1);
                return 0;
            }
            if ((direction == 'r' || direction == 1) && column - 'a' + length + 1 > 11) {
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
            if (direction == 'd' || direction == '0')
                x = column - 'a', y = row - 1, direction_int = 0;
            if (direction == 'l')x = column - 'a' - length + 1, y = row - 1, direction_int = 1;
            if (direction == 'r' || direction == '1')x = column - 'a', y = row - 1, direction_int = 1;
            if (!touching_sides(copy, x + 1, y + 1, length, direction_int)){
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
            if (cmp(direction, "u") || cmp(direction, "up")) x = column - 'a', y = row - length, direction_int = 0;
            if (cmp(direction, "down") || cmp(direction, "d")) x = column - 'a', y = row - 1, direction_int = 0;
            if (cmp(direction, "left") || cmp(direction, "l")) x = column - 'a' - length + 1, y = row - 1, direction_int = 1;
            if (cmp(direction, "right") || cmp(direction, "r")) x = column - 'a', y = row - 1, direction_int = 1;
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

int* computer_pick_ships(struct ship* ships) {
    int* table = calloc(100, sizeof(int));
    int ships2 = 4, ships3 = 3, ships4 = 2, ships6 = 1, index = 0;
    int count = 0;
    while (ships2 + ships3 + ships4 + ships6 != 0) {
        int direction=rand()%2;
        int rand_index,length;
        int copy[12][12] = { 0 };
        int x, y;
        if (ships2)length = 2;
        if (ships3)length = 3;
        if (ships4)length = 4;
        if (ships6)length = 6;
        do{
            if (count >= 100) {
                table = calloc(100, sizeof(int));
                int direction = rand() % 2;
                ships2 = 4;
                ships3 = 3;
                ships4 = 2;
                ships6 = 1;
                if (ships2)length = 2;
                if (ships3)length = 3;
                if (ships4)length = 4;
                if (ships6)length = 6;
                count = 0;
                index = 0;
            }
            do {
                do {
                    rand_index = rand() % 100;
                    x = rand_index / 10;
                    y = rand_index % 10;
                } while (x + length * direction + 1 > 10);
            } while (y + length * !direction + 1 > 10);
            int y = rand_index % 10;
            for (int i = 1; i < 11; i++) {
                for (int j = 1; j < 11; j++) {
                    copy[j][i] = table[j - 1 + (i - 1) * 10];
                }
            }
            count++;
        }while (!touching_sides(copy, x+1, y+1, length,direction));
        if (length == 2)ships2--;
        if (length == 3)ships3--;
        if (length == 4)ships4--;
        if (length == 6)ships6--;
        ships[index].direction = direction;
        ships[index].length = length;
        ships[index].x = x;
        ships[index].y = y;
        ships[index].sunk = 0;
        for (int i = ships[index].x; i < ships[index].length * ships[index].direction + 1 * !ships[index].direction + ships[index].x; i++) {
            for (int j = ships[index].y; j < ships[index].length * !ships[index].direction + 1 * ships[index].direction + ships[index].y; j++) {
                table[j + i * 10] = 1;
            }
        }
        index++;
    }
    return table;
}

int computer_turn(int* table, int last_turn, int first_hit) {
    int rand_num;
    if (last_turn == 0) {
        do {
            rand_num = rand() % 100;
        } while (table[rand_num] != 0);
        return rand_num;
    }
    if (table[last_turn] == -1) {
        if (last_turn - first_hit < 10 && last_turn - first_hit > 0)return first_hit - 1;
        if (last_turn - first_hit > 9)return first_hit - 10;
        if (last_turn - first_hit < 10 && last_turn - first_hit < 0)return first_hit + 1;
        if (last_turn - first_hit < -10)return first_hit + 10;
    }

    if(table[last_turn] == 2 && last_turn!=first_hit) {
        if (last_turn - first_hit < 10 && last_turn - first_hit > 0)return last_turn + 1;
        if (last_turn - first_hit > 9)return last_turn + 10;
        if (last_turn - first_hit < 10 && last_turn - first_hit < 0)return last_turn - 1;
        if (last_turn - first_hit < -10)return last_turn - 10;
    }
    do {
        int rand_dir = rand() % 4;
        if (rand_dir == 0 && last_turn / 10 - 1 >= 0 && table[last_turn - 10] == 0)return last_turn - 10;
        if (rand_dir == 1 && last_turn / 10 + 1 <= 9 && table[last_turn + 10] == 0)return last_turn + 10;
        if (rand_dir == 2 && last_turn % 10 - 1 >= 0 && table[last_turn - 1] == 0)return last_turn - 1;
        if (rand_dir == 3 && last_turn % 10 + 1 <= 9 && table[last_turn + 1] == 0)return last_turn + 1;
    } while (1);
}

int save_formation_to_file(struct ship *ships, FILE *output)
{
    if (!output) return 1;
    for (int i = 0; i < 10; i++)
        fprintf(output, "%d %d %c %d\n", ships[i].length, ships[i].direction, ships[i].x + 'a', ships[i].y+1);
    fputs("m\n", output);
    return 0;
}

int save_moves_to_file(struct move* moves, int move_count, FILE *output)
{
    if (!output) return 1;
    for (int i = 0; i < move_count; i++)
        fprintf(output, "%d %c %d %d\n", moves[i].player, moves[i].x, moves[i].y, moves[i].res);
    return 0;
}

int get_moves_from_file(FILE* file, struct move *moves)
{
    char line[10];
    do
    {
        fgets(line, 10, file);
        if(line[0] == '0') break;
    }
    while(1);
    int player, y, res, move_cnt = 0;
    char x;
    do
    {
        sscanf(line, "%d %c %d %d", &player, &x, &y, &res);
        struct move move = {player, x, y, res};
        moves[move_cnt++] = move;
    }while(fgets(line, 9, file));
    return move_cnt;
}

int main()
{
    srand(time(0));
    int* table1, * tableEn1, * table2, * tableEn2;
    tableEn1 = calloc(100, sizeof(int));
    tableEn2 = calloc(100, sizeof(int));
    struct ship* ships1 = malloc(sizeof(struct ship) * 10);
    struct ship* ships2 = malloc(sizeof(struct ship) * 10);
    struct move *moves = calloc(200, sizeof (struct move));
    int sunk1 = 10, sunk2 = 10;
    int singleplayer, temp;
    int last_turn=0, first_hit=0, move_cnt = 0;
    printf("Do you want to play singleplayer or multiplayer?\n1.Singleplayer\n2.Multiplayer\n");
    do {
        scanf("%d", &singleplayer);
        if (singleplayer != 1 && singleplayer != 2)printf("Choose again.\n");
    } while (singleplayer != 1 && singleplayer != 2);
    system("clear");//system("clear");
    printf("Do you have template?\n1.Yes\n2.No\n");
    do {
        scanf("%d", &temp);
        if (temp != 1 && temp != 2)printf("Choose again.\n");
    } while (temp != 1 && temp != 2);
    system("clear");//system(clear)
    if (temp == 1)
        table1 = read_from_file(ships1, 0);
    else
        table1 = read_from_console(ships1);
    system("clear");//system(clear)
    if (singleplayer == 1) {
        table2 = computer_pick_ships(ships2);
    }
    else {
        printf("Do you have template?\n1.Yes\n2.No\n");
        do {
            scanf("%d", &temp);
            if (temp != 1 && temp != 2)printf("Choose again.\n");
        } while (temp != 1 && temp != 2);
        system("clear");//system(clear)
        if (temp == 1)
            table2 = read_from_file(ships2, 0);
        else
            table2 = read_from_console(ships2);
        system("clear");//system(clear)
    }
    while (sunk1 && sunk2) //for (int i = 0; i < 2; i++)
    {
        struct move move;
        int y;
        char x;
        int res, index;
        do {
            printf("Player 1\n");
            print_table(tableEn1);
            print_table(table1);
            do {
                printf("Enter column for attack (a - j): \n");
                scanf("%c", &x);
                if (x == '\n')scanf("%c", &x);
                lower_case(&x);
                if (!(x >= 'a' && x <= 'j'))printf("Wrong column!\n");
            } while (!(x >= 'a' && x <= 'j'));

            do {
                printf("Enter row for attack (1 - 10):\n");
                char* y_c = calloc(3, sizeof(char));
                scanf("%s", y_c);
                if (cmp(y_c, "10")) y = 10;
                else y = y_c[0] - '0';
                if (!(y >= 1 && y <= 10))printf("Wrong row!\n");
            } while (!(y >= 1 && y <= 10));

            res = play_turn(table2, x - 'a', y - 1, ships2);
            if (res == 0) printf("Miss!\n"), tableEn1[y - 1 + (x - 'a') * 10] = -1, table2[y - 1 + (x - 'a') * 10] = -1;
            if (res == 1) printf("Hit!\n"), tableEn1[y - 1 + (x - 'a') * 10] = 2, table2[y - 1 + (x - 'a') * 10] = 2;
            if (res == 2) printf("Ship sunk!\n"), tableEn1[y - 1 + (x - 'a') * 10] = 2, sunk2--, table2[y - 1 + (x - 'a') * 10] = 2;
            char move_end;
            printf("Next move[y]:");
            do { scanf("%c", &move_end); } while(move_end != 'y');
            system("clear");
            move.player = 0;
            move.x = x;
            move.y = y;
            if(res)
                move.res = 2;
            else
                move.res = 0;
            moves[move_cnt++] = move;
            if(sunk2 == 0) res = 0;
        } while (res!=0);
        if(sunk2 == 0) break;

        do {
            if (singleplayer == 2) {
                printf("Player 2\n");
                print_table(tableEn2);
                print_table(table2);
                do {
                    printf("Enter column for attack (a - j):\n");
                    scanf("%c", &x);
                    if (x == '\n')scanf("%c", &x);
                    lower_case(&x);
                    if (!(x >= 'a' && x <= 'j')) printf("Wrong column!\n");
                } while (!(x >= 'a' && x <= 'j'));

                do {
                    printf("Enter row for attack (1 - 10):\n");
                    char *y_c = calloc(3, sizeof(char));
                    scanf("%s", y_c);
                    if (cmp(y_c, "10"))y = 10;
                    else y = y_c[0] - '0';
                    if (!(y >= 1 && y <= 10))printf("Wrong row!\n");
                } while (!(y >= 1 && y <= 10));

                res = play_turn(table1, x - 'a', y - 1, ships1);
                if (res == 0) printf("Miss!\n"), tableEn2[y - 1 + (x - 'a') * 10] = -1, table1[y - 1 + (x - 'a') * 10] = -1;
                if (res == 1) printf("Hit!\n"), tableEn2[y - 1 + (x - 'a') * 10] = 2, table1[y - 1 + (x - 'a') * 10] = 2;
                if (res == 2) printf("Ship sunk!\n"), sunk1--, tableEn2[y - 1 + (x - 'a') * 10] = 2, table1[y - 1 + (x - 'a') * 10] = 2;

                char move_end;
                printf("Next move[y]:");
                do { scanf("%c", &move_end); } while(move_end != 'y');
                system("clear");//system(clear)
                move.player = 1;
                move.x = x;
                move.y = y;
                if(res)
                    move.res = 2;
                else
                    move.res = 0;
                moves[move_cnt++] = move;
            }
            else
            {
                index = computer_turn(tableEn2, last_turn, first_hit);
                res = play_turn(table1, index / 10, index % 10, ships1);
                if (res == 1) {
                    printf("Computer hit!\n");
                    tableEn2[index] = 2;
                    table1[index] = 2;
                    if (first_hit == 0)first_hit = index,last_turn = index;
                }
                int x_ = index / 10, y_ = index % 10;
                if (last_turn != 0)last_turn = index;
                if (res == 0) printf("Computer missed!\n"), tableEn2[index] = table1[index] = -1;
                if (res == 2)
                {
                    printf("Computer sank your ship!\n");
                    sunk1--;
                    tableEn2[index] = 2;
                    table1[index] = 2;
                    for (int i = 0; i < 10; i++){
                        if (x_ >= ships1[i].x && x_ <= ships1[i].x + ships1[i].length * ships1[i].direction && y_ >= ships1[i].y && y_ <= ships1[i].y + ships1[i].length * !ships1[i].direction) {
                            for (int k = ships1[i].x - 1; k < (ships1[i].length + 2) * ships1[i].direction + 3 * !ships1[i].direction + x-1 ; k++) {
                                for (int j = ships1[i].y - 1; j < (ships1[i].length + 2) * !ships1[i].direction + 3 * ships1[i].direction + y-1; j++) {
                                    if (k >= 0 && i <= 9 && j >= 0 && j <= 9)
                                        tableEn2[j + k * 10] = -1;
                                }
                            }
                        }
                    }
                    //print_table(tableEn2);
                    last_turn = 0;
                    first_hit = 0;
                }
                move.player = 1;
                move.x = x_ + 'a';
                move.y = y_;
                move.res = res;
                moves[move_cnt++] = move;
            }
            if(sunk1 == 0) res = 0;
        } while (res!=0);
        if(sunk1 == 0) break;
    }
    char choice = 0;
    if(!sunk1)
        printf("Player 2 wins");
    else if(!sunk2)
        printf("Player 1 wins");
    scanf("%c", &choice); //ima nqkuv shiban nov red vseki put ot predishnite vhodove qvno
    printf("Do you want to save your game [y/n]: ");
    scanf("%c", &choice);
    lower_case(&choice);
    if(choice == 'y')
    {
        char* table_c;
        printf("Enter the location of your game replay file:\n");
        char *location = calloc(4096, sizeof(char));
        //location = "/home/indiana/CLionProjects/UASD/battleships/replay.txt";
        scanf("%s", location);
        FILE *output = fopen(location, "w+");
        save_formation_to_file(ships1, output);
        save_formation_to_file(ships2, output);
        save_moves_to_file(moves, move_cnt, output);
        fclose(output);
        printf("Game saved.\nDo you want to encrypt the replay?[y/n] ");
        scanf("%c", &choice);
        scanf("%c", &choice);
        int enciphered = 0;
        if(choice =='y')
        {
            enciphered = 1;
            FILE * input = fopen("/home/indiana/CLionProjects/UASD/battleships/replay.txt", "rb");
            fseek(input, 0L, SEEK_END);
            int length = ftell(input);
            fseek(input, 0L, SEEK_SET);

            printf("Enter Your Password:");
            char* password = malloc(100);
            scanf("%s", password);
            char* buffer = (char*)malloc(length);
            system("clear");
            fread(buffer, 1, length, input);
            fclose(input);
            table_c = generateTable();
            char* cipher = encrypt(buffer, password, table_c, length);
            FILE* tmp = fopen("/home/indiana/CLionProjects/UASD/battleships/replay.txt", "wb");
            fwrite(cipher, sizeof(char), length, tmp);
            fclose(tmp);
        }
        printf("Game saved.\nDo you want to see the replay?[y/n] ");
        scanf("%c", &choice);
        scanf("%c", &choice);
        lower_case(&choice);
        if(choice == 'y')
        {
            if(enciphered)
            {
                printf("Enter Your Password:");
                char *password = malloc(100);
                scanf("%s", password);
                FILE *tmp = fopen("/home/indiana/CLionProjects/UASD/battleships/replay.txt", "rb");
                fseek(tmp, 0L, SEEK_END);
                int length = ftell(tmp);
                fseek(tmp, 0L, SEEK_SET);
                char *buffer = (char *) malloc(length);
                fread(buffer, 1, length, tmp);
                fclose(tmp);
                tmp = fopen("/home/indiana/CLionProjects/UASD/battleships/replay.txt", "wb");
                char *deciphered = decrypt(buffer, password, table_c, length);
                fwrite(deciphered, sizeof(char), length, tmp);
                fclose(tmp);
            }
            int* replay_table1 , *replay_table2 = 0;
            struct ship* replay_ships1 = malloc(sizeof(struct ship) * 10);
            struct ship* replay_ships2 = malloc(sizeof(struct ship) * 10);
            struct move *replay_moves = calloc(200, sizeof (struct move));
            replay_table1 = read_from_file(replay_ships1, 0);
            replay_table2 = read_from_file(replay_ships2, 1);
            print_table(replay_table1);
            print_table(replay_table2);
            printf("\n\n\n");
            FILE *replay_file = fopen(location, "r");
            int moves_cnt = get_moves_from_file(replay_file, replay_moves);
            puts("");
            for (int i = 0; i < moves_cnt; i++)
            {
                if(replay_moves[i].player == 0)
                {
                    if (replay_moves[i].res == 0)
                        printf("Miss!\n"), replay_table2[replay_moves[i].y - 1 + (replay_moves[i].x - 'a') * 10] = -1;
                    if (replay_moves[i].res == 2)
                        printf("Hit!\n"), replay_table2[replay_moves[i].y - 1 + (replay_moves[i].x - 'a') * 10] = 2;
                }
                if(replay_moves[i].player == 1)
                {
                    if (replay_moves[i].res == 0)
                        printf("Miss!\n"), replay_table1[replay_moves[i].y - 1 + (replay_moves[i].x - 'a') * 10] = -1;
                    if (replay_moves[i].res == 2)
                        printf("Hit!\n"), replay_table1[replay_moves[i].y - 1 + (replay_moves[i].x - 'a') * 10] = 2;
                }
                print_table(replay_table2);
                print_table(replay_table1);
                char move_end;
                printf("Next move[y]:");
                do { scanf("%c", &move_end); } while(move_end != 'y');
                //system("clear");
            }
        }
    }
    return 0;
}
