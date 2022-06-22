#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
void read_from_file();
struct ship {
	int lenght;
	int x;
	int y;
	int direction;
	int sinked;
};
int cmp(char* a, char* b) {
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

int toching_sides(int table[12][12] ,int x, int y , int lenght, int direction) {
	for (int i = x - 1 ; i < (lenght+2) * direction + 3 * !direction + x - 1; i++) {
		for (int j = y-1 ; j < (lenght+2) * !direction + 3 * direction + y-1; j++) {
			if (table[j][i])return 0;
		}
	}
	return 1;
	
}

void print_table(int table[10][10]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			printf(" _ ");
		}
		printf("\n");
		for (int j = 0; j < 10; j++) {
			char c;
			if (table[i][j] == 0)c = ' ';
			if (table[i][j] == 1)c = 'O';
			if (table[i][j] == -1)c = 'Z';
			if (table[i][j] == 2)c = 'X';
			printf("|%c|", c);
		}
		
		printf("\n");
	}
	for (int j = 0; j < 10; j++) {
		printf(" _ ");
	}
	printf("\n");
}

int* read_from_console(struct ship *ships) 
{
	int table[10][10] = { 0 };
	int lenght, ship_count_2 = 0, ship_count_3 = 0, ship_count_4 = 0, ship_count_6 = 0, row;
	char column;
	char* direction = calloc(6, sizeof(char));
	while (ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 < 10)
	{
		printf("Ship number %d\n", ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 + 1);
	new_lenght:
		printf("Enter the lenght of the ship:\n");
		scanf("%d", &lenght);
		if (lenght != 2 && lenght != 3 && lenght != 4 && lenght != 6)
		{
			printf("This lenght is unavalable!\n");
			goto new_lenght;
		}
		if (lenght == 2) {
			if (ship_count_2+1 > 4) {
				printf("There are already 4 ships with lenght 2.\n");
					goto new_lenght;
			}
		}
		if (lenght == 3) {
			if (ship_count_3 +1> 3) {
				printf("There are already 3 ships with lenght 3.\n");
				goto new_lenght;
			}
		}
		if (lenght == 4) {
			if (ship_count_4 +1> 2) {
			
				printf("There are already 2 ships with lenght 4.\n");
				goto new_lenght;
			}
		}
		if (lenght == 6) {
			
			if (ship_count_6 +1> 1) {
			
				printf("There is already a ship with lenght 6.\n");
				goto new_lenght;
			}
		}
	new_direction:
		printf("Enter a direction of the ship (up-u,down-d,left-l,right-r):\n");
		scanf("%s", direction);
		lower_case(direction);
		if (!cmp(direction, "u") && !cmp(direction, "d") && !cmp(direction, "l") && !cmp(direction, "r") && !cmp(direction, "up") && !cmp(direction, "down") && !cmp(direction, "left") && !cmp(direction, "right")) {
			printf("Wrong direction!\n");
			goto new_direction;
		}
	new_column:
		printf("Enter a column:\n");
		scanf("%s", &column);
		lower_case(&column);
		if (!(column >= 'a' && column <= 'j')) {
			printf("Wrong column!\n");
			goto new_column;
		}
	new_row:
		printf("Enter a row:\n");
		scanf("%d", &row);
		if (!(row >= 1 && row <= 10)) {
			printf("Wrong row!\n");
			goto new_row;
		}
		if ((cmp(direction, "u") || cmp(direction, "up")) && row - lenght < 0) {
			printf("This ship is outside the table!\n");
			goto new_direction;
		}
		if ((cmp(direction, "d") || cmp(direction, "down")) && row + lenght > 11) {
			printf("This ship is outside the table!\n");
			goto new_direction;
		}
		if ((cmp(direction, "l") || cmp(direction, "left")) && column - 'a' - lenght < 0) {
			printf("This ship is outside the table!\n");
			goto new_direction;
		}
		if ((cmp(direction, "r") || cmp(direction, "right")) && column - 'a' + lenght > 11) {
			printf("This ship is outside the table!\n");
			goto new_direction;
		}
		int copy[12][12] = { 0 };
		for (int i = 1; i < 11; i++) {
			for (int j = 1; j < 11; j++) {
				copy[i][j] = table[i-1][j-1];
			}
		}
		int x, y, direction_int;
		if (cmp(direction, "u") || cmp(direction, "up"))x = column - 'a', y = row - lenght, direction_int = 0;
		if (cmp(direction, "down") || cmp(direction, "d"))x = column - 'a', y = row - 1, direction_int = 0;
		if (cmp(direction, "left") || cmp(direction, "l"))x = column - 'a' - lenght+1, y = row - 1, direction_int = 1;
		if (cmp(direction, "right") || cmp(direction, "r"))x = column - 'a', y = row - 1, direction_int = 1;
		if (!toching_sides(copy, x+1, y+1, lenght, direction_int)) {
			printf("This ship can't be on this position.\n");
			goto new_lenght;
		}
		if (lenght == 2) ship_count_2++;
		if (lenght == 3) ship_count_3++;
		if (lenght == 4) ship_count_4++;
		if (lenght == 6) ship_count_6++;
		for (int i = x; i < lenght * direction_int + 1 * !direction_int + x; i++) {
			for (int j = y; j < lenght * !direction_int + 1 * direction_int + y; j++) {
				table[j][i] = 1;
			}
		}
		ships[ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6].direction = direction_int;
		ships[ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6].x = x;
		ships[ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6].y = x;
		ships[ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6].lenght = lenght;
		ships[ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6].sinked = 0;
		int choise;
		printf("Chose:\n");
		if (ship_count_2 + ship_count_3 + ship_count_4 + ship_count_6 < 10)printf("1.Place new ship.\n");
		else printf("1.Start game\n");
		printf("2.Change coordinates of a ship\n3.View the playing table\n");
	new_choise:
		scanf("%d", &choise);
		if (!(choise > 0 && choise < 4)) {
			printf("Chose again!");
			goto new_choise;
		}
		if (choise == 1)continue;
		if (choise == 2) {
			printf("Witch ship do you want to redact\n");
			int index;
			scanf("%d", &index);
			if (ships[index].lenght == 2)ship_count_2--;
			if (ships[index].lenght == 3)ship_count_3--;
			if (ships[index].lenght == 4)ship_count_4--;
			if (ships[index].lenght == 6)ship_count_6--;
			for (int i = x; i < ships[index].lenght * ships[index].direction + 1 * !ships[index].direction+x; i++) {
				for (int j = y; j < ships[index].lenght * !ships[index].direction + 1 * ships[index].direction+y; j++) {
					table[j][i] = 0;
				}
			}
			goto new_lenght;
		}
		if (choise == 3)print_table(table);
	} 
	return table;
}
int main() {
	int *table;
	struct ship *ships = malloc(sizeof(struct ship) * 10);
	
	table=read_from_console(&ships);
	print_table(table);
	return 0;
}