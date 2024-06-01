#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ANSI_COLOR_RED     "\033[1;31m" //покраска в красный цвет
#define ANSI_COLOR_BLUE    "\033[1;34m" //покраска в синий цвет
#define ANSI_COLOR_CYAN    "\e[0;36m" //покраска в голубой цвет
#define ANSI_COLOR_PINK    "\e[38;5;212m" //покраска в розовый цвет
#define ANSI_COLOR_GREEN   "\x1b[32m" //покраска в зелёный
#define ANSI_COLOR_RESET   "\033[0m" //сброс цвета

struct pers
{
    int per[20]; //красные
    int vsper[20]; //синие
};

void print_colored_text(const char* color, const char* text) //покраска текста
{
    printf("%s%s%s", color, text, ANSI_COLOR_RESET);
}

void print_colored_int(const char* color, int text) //покраска чисел
{
    printf("%s%d%s", color, text, ANSI_COLOR_RESET);
}

int command(struct pers *s, int *kolvo, int pervie) //Создание двух комманд игроков
{
    if (pervie == 0)
    {
        printf("Введите количество персонажей в команде (от 1 до 20): ");
        while (scanf("%d", kolvo) != 1 || *kolvo < 1 || *kolvo > 20)
        {
            fprintf(stderr, "Некорректный ввод\n");
            while (getchar() != '\n');
            printf("Введите количество персонажей в команде (от 1 до 20): ");
        }
        pervie = 1;
    }

    printf("%sКоманда %s\n", ANSI_COLOR_RED, "Красных"); //Красные
    for (int j = 0; j < *kolvo; ++j)
    {
        printf(ANSI_COLOR_RESET "%d) " ANSI_COLOR_PINK "A%d: %d  ", j + 1, j + 1, s->per[j]);
    }
    printf(ANSI_COLOR_RESET "\n");

    printf("%sКоманда %s\n", ANSI_COLOR_BLUE, "Синих"); //Синие
    for (int j = 0; j < *kolvo; ++j)
    {
        printf(ANSI_COLOR_RESET "%d) " ANSI_COLOR_CYAN "B%d: %d  ", j + 1, j + 1, s->vsper[j]);
    }
    printf(ANSI_COLOR_RESET "\n");
    return pervie;
}

int game(struct pers* team, int kolvo, char* comand, int pervie)
{

    int x, y, sum = 0;
    int oshibka = 0;
    
    srand(time(0));
        int ran = rand() % 6; 
        int ra = rand() % 6; 
        
    int diff = abs(ran - ra);
    while (oshibka != 1)
    { 
        sum = 0; // Обнуляем сумму перед каждой итерацией
        for (int i = 0; i < kolvo; i++)
        {    
            if (strcmp(comand, "красных") == 0)
                sum += team->vsper[i];
            else
                sum += team->per[i];
        }
        if (sum != 0)
        {
            printf("\nХод команды %s:\n", comand);
            printf("Выберете атакующего персонажа: ");
            scanf("%d", &x);
            printf("Выберете атакуемого персонажа: ");
            scanf("%d", &y);

            while (x < 1 || y < 1 || y > kolvo)
            {
                printf("Некорректный ввод\n\n");
                while (getchar() != '\n');
                printf("Выберете атакующего персонажа: ");
                scanf("%d", &x);
                printf("Выберете атакуемого персонажа: ");
                scanf("%d", &y);
            }
            if ((team->per[y - 1] == 0) || (team->vsper[x - 1] == 0)) {
                    printf("Боец уже убит \n"); }
            else{ 
                if (strcmp(comand, "синих") == 0) {
                    printf("Сила атаки: %d\nСила защиты: %d\n\n", ran, ra);
                    if (ran > ra) {
                        team->per[y - 1] += diff;
                        team->vsper[x - 1] -= diff;
                        printf(ANSI_COLOR_GREEN ">>Победа красных!\n");
                    } else if (ra > ran) {
                        team->per[y - 1] -= diff;
                        team->vsper[x - 1] += diff;
                        printf(ANSI_COLOR_GREEN ">>Победа синих!\n");
                    }   else {
                        printf("Ничья! Никто не получил урона.\n");
                        printf(ANSI_COLOR_GREEN ">>Увы\n");
                    }   
                } 
                else {
                    printf("Сила атаки: %d\nСила защиты: %d\n\n", ran, ra);
                    if (ran > ra) {
                        team->per[x - 1] += diff;
                        team->vsper[y - 1] -= diff;
                        printf(ANSI_COLOR_GREEN ">>Победа красных!\n");
                    } else if (ra > ran) {
                        team->per[x - 1] -= diff;
                        team->vsper[y - 1] += diff;
                        printf(ANSI_COLOR_GREEN ">>Победа синих!\n");
                    } else {
                            printf("Ничья! Никто не получил урона.\n");
                            printf(ANSI_COLOR_GREEN ">>Увы\n");
                        }
                } 
                if (team->per[y - 1] <= 0) 
                {
                    team->per[x - 1] = 0;
                }
                if (team->vsper[x - 1] <= 0)
                {
                    team->vsper[y - 1] = 0;
                }
                return sum;
            }
        }
    }
    if (sum == 0)
{
    printf("\nПобедила команда %s\n", comand);
    exit(EXIT_SUCCESS);
    }
}

int main()
{
    int sum = 1; 
    struct pers team;
    int kolvo;
    int pervie = 0;
    char* comand = "красных";

    for (int i = 0; i < 20; ++i)
    {
        team.per[i] = 5;
        team.vsper[i] = 5;
    }

do {
    pervie = command(&team, &kolvo, pervie);
    sum = game(&team, kolvo, comand, pervie);

    if (strcmp(comand, "красных") == 0)
        comand = "синих";
    else
        comand = "красных";
} while (sum > 0);
    return 0;
}
