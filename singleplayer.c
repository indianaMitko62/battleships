#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct ship {
    int length;
    int x;
    int y;
    int direction;
    int sunk;
};

int play_turn(int table[10][10], int x, int y, struct ship *ships) {
    if (table[y][x]) {
        for (int i = 0; i < 10; i++) {
            if (x >= ships[i].x && x <= ships[i].x + ships[i].length * ships[i].direction && y >= ships[i].y && y <= ships[i].y + ships[i].length * !ships[i].direction) {
                ships[i].sunk++;
                if (ships[i].sunk == ships[i].length)return 2;
                return 1;
            }
        }
    }
    return 0;
}

void print_table(int table[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf(" ---  ");
        }
        printf("\n");
        for (int j = 0; j < 10; j++) {
            char c;
            if (table[i][j] == 0)c = ' ';
            if (table[i][j] == 1)c = 'O';
            if (table[i][j] == -1)c = 'Z';
            if (table[i][j] == 2)c = 'X';
            printf("| %c | ", c);
        }

        printf("\n");
    }
    for (int j = 0; j < 10; j++) {
        printf(" ---  ");
    }
    printf("\n");
}

int* computer_pick_ships(struct ship* ships) {
    int* table = calloc(100, sizeof(int));
    int ships2 = 4, ships3 = 3, ships4 = 2, index = 0;

    while(ships2+ships3+ships4 != 0) {
        int rand_direction = rand() % 4;
        int rand_index = rand() % 100;
        while(table[rand_index] == 1) //trqbva da ima i proverki dali e v blizost do drugo zaeto//
            {
            rand_index = rand() % 100;
        }
        int x = rand_index % 10;
        int y = rand_index / 10;
        int length = 0;
        printf("%d %d %d %d\n", rand_direction, rand_index, x, y);
        if (index == 0) {
            length = 6;
            if (y <= 5) {
                for(int j = 0; j < 6; j++) {
                    table[j*10 + x] = 1;
                }
            }
            else {
                for(int j = 9; j > 3; j--) {
                    table[j*10 + x] = 1;
                }
            }
        }
        else {
            for(int j = 1; j < 5; j++) {
                int direction;
                if(rand_direction == 0) direction = 10; //up
                if(rand_direction == 1) direction = -10; // down
                if(rand_direction == 2) direction = 1; // left
                if(rand_direction == 3) direction = -1; // right
                if (table[y * 10 + x + j * direction] && table[y * 10 + x + j * direction] == 0) continue;
                else {
                    if(j < 2) break;
                    if(j == 2 && ships2 > 0) {
                        table[y*10+x] = 1;
                        table[y*10+x+direction] = 1;
                        ships2--;
                    }
                    if(j == 3 && ships3 > 0) {
                        table[y*10+x] = 1;
                        table[y*10+x+direction] = 1;
                        table[y*10+x+2*direction] = 1;
                        ships3--;
                    }
                    if(ships4 > 0) {
                        table[y*10+x] = 1;
                        table[y*10+x+direction] = 1;
                        table[y*10+x+2*direction] = 1;
                        table[y*10+x+3*direction] = 1;
                        ships4--;
                    }
                }
            }
        }
        ships[index].direction = rand_direction % 2;
        ships[index].length = length;
        ships[index].x = x;
        ships[index].y = y;
        ships[index].sunk = 0;
        index++;
    }
    return table;
}

int computer_turn(int** table, int last_turn) {
    if(last_turn == 0) {
        int rand_num = rand()%100;
        while(*table[rand_num] == 1 || *table[rand_num] == 2) {
            rand_num = rand()%100;
        }
        *table[rand_num] = 1;
        return rand_num;
    }
    if(*table[last_turn+1] && *table[last_turn+1] != 1 && *table[last_turn+1] != 2) return *table[last_turn+1];
    if(*table[last_turn-1] && *table[last_turn-1] != 1 && *table[last_turn-1] != 2) return *table[last_turn-1];
    if(*table[last_turn+10] && *table[last_turn+10] != 1 && *table[last_turn+10] != 2) return *table[last_turn+10];
    if(*table[last_turn-10] && *table[last_turn-10] != 1 && *table[last_turn-10] != 2) return *table[last_turn-1];
}

int main() {
    srand(time(NULL));
    int *table1, *table2, *empty_table;
    struct ship *ships1 = malloc(sizeof(struct ship) * 10);
    struct ship *ships2 = malloc(sizeof(struct ship) * 10);
    empty_table = malloc(100*sizeof(int));
    for(int i = 0; i < 100; i++) {
        empty_table[i] = -1;
    }
    int sunk1 = 10, sunk2 = 10;
    // table1 = read_from_console(ships1);
    table2 = computer_pick_ships(ships2);
    while(sunk1 && sunk2) {
        //kod za hod na chovek
        int last_turn = 0;
        int computer_hits = computer_turn(empty_table, last_turn);
        int res = play_turn(table1, computer_hits % 10, computer_hits / 10, ships2);
        if(res == 0) printf("Computer missed!");
        if(res == 1) {
            printf("Computer hit!");
            empty_table[computer_hits] = 2;
            last_turn = computer_hits;
            while(res != 0) {
                computer_hits = computer_turn(empty_table, last_turn);
                res = play_turn(table1, computer_hits % 10, computer_hits / 10, ships2);
            }
        }
        if(res == 2) {
            printf("Computer has sunk your ship!");
            sunk2--;
            empty_table[computer_hits] = 2;
            last_turn = 0;
            while(res != 0) {
                computer_hits = computer_turn(empty_table, last_turn);
                res = play_turn(table1, computer_hits % 10, computer_hits / 10, ships2);
            }
        }
    }
    print_table(ships2);
    return 0;
}