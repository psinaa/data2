#define _CRT_SECURE_NO_DEPRECATE
#define CountScore 20
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

int Number;

struct tm* mytime;

char* UserList[999];
int UserScore[999][20]; // технические первые 10, артистичные вторвые 10



void sort_artistry(int array[][CountScore]);

void sort_technique(int array[][CountScore]);

void rating(int array[][CountScore]);

void search();


//File functions
void writefile();
void Load(void);

//User functions
int CreatePoint();
void PrintUser(int id);
void CreateUser();
void sumA(int answercaseA);
void sumT(int answercaseT);
void sumAT(int answercaseAT);

//Sub functions
char* concat(char* s1, char* s2);//Сложение строк
int SumElemArr(int array[][CountScore], int left, int right); // Суммирование периуда в массиве
void SwapElement(int array[], int id);

//commandline interface
void tabl();


int main() {
    setlocale(LC_ALL, "RUS");
    SetConsoleCP(1251);         // !!!
    SetConsoleOutputCP(1251);   // !!!
    Load();


    int n, d = 1;
    int a, t, at;
    int userid = 0, answercasea = 0, answercaset = 0, answercaseat = 0;
    char id = Number;
    while (d == 1) {
        printf("База данных\n");
        printf("1)Создать пользователя\n");
        printf("2)Посмотреть таблицу\n");
        printf("3)Сумма за А\n");
        printf("4)Сумма за Т\n");
        printf("5)Сумма за всё\n");
        printf("6)Сортировка по А\n");
        printf("7)Сортировка по Т\n");
        printf("8)Рейтинг\n");
        printf("9)Поиск\n");
        scanf("%i", &n);
        switch (n) {
        case 1:
            CreateUser();
            break;
        case 2:
            tabl();
            for (int i = 0; i < Number; i++)
                PrintUser(i);
            break;
        case 3:
            printf("выбрать пользователя по id - 1 посмотреть всех - 2\n");
            scanf("%d", &answercasea);
            sumA(answercasea);
            break;
        case 4:
            printf("выбрать пользователя по id - 1 посмотреть всех - 2\n");
            scanf("%d", &answercaset);
            sumT(answercaset);
            break;
        case 5:
            printf("выбрать пользователя по id - 1 посмотреть всех - 2\n");
            scanf("%d", &answercaseat);
            sumAT(answercaseat);
            break;
        case 6:
            sort_artistry(UserScore);
            break;
        case 7:
            sort_technique(UserScore);
            break;
        case 8:
            printf("Для просмотра таблицы рейтинга нажмите '2'\n");
            rating(UserScore);
            break;
        case 9:
            search();
        default:
            break;
        }
    }
}


void CreateUser() {
    char surname[50];
    char name[50];
    char* string3;
    printf("Введите фамилию\n");
    getchar();
    scanf("%s", &surname);
    printf("Введите имя\n");
    getchar();
    scanf("%s", &name);
    string3 = concat(surname, name);
    UserList[Number] = string3;
    for (int j = 0; j < CountScore; j++)
    {
        UserScore[Number][j] = CreatePoint();
    }
    Number += 1;
    writefile();
}

void Load()
{
    FILE* F;
    if ((F = fopen("my.txt", "rt")) == NULL)
    {
        fprintf(stderr, "Невозможно открыть для чтения файл 'my.dta'\n");
        return;
    }

    fscanf(F, "%i", &Number);
    for (int i = 0; i < Number; i++) {
        char surname[50];
        char name[50];
        char* string3;
        fscanf(F, "%s", &surname);
        fscanf(F, "%s", &name);

        string3 = concat(surname, name);
        UserList[i] = string3;
        for (int j = 0; j < CountScore; j++)
        {
            UserScore[i][j] = CreatePoint();
        }
    }
    fclose(F);
}

int CreatePoint()
{
    return (rand() % 9) + 1;
}
void PrintUser(int id) {
    for (int i = 0; i < CountScore - 10; i++) {
        int j = i + 10;
        printf(" %d %d    ", UserScore[id][i], UserScore[id][j]);
    }
    printf(" %s ", UserList[id]);
    puts("\n");
}

char* concat(char* s1, char* s2) {
    const char* s3 = " ";
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    size_t len3 = strlen(s3);

    char* result = (char*)malloc(len1 + len3 + len2 + 1);
    if (!result) {
        fprintf(stderr, "malloc() failed: insufficient memory!\n");
        return NULL;
    }

    memcpy(result, s1, len1);
    memcpy(result + len1, s3, len3);
    memcpy(result + len1 + len3, s2, len2 + 1);
    return result;
}

int SumElemArr(int array[], int left, int right)
{
    int sum = 0;
    for (int i = left; i < right; i++) {
        sum += array[i];
    }
    return sum;
}

void SwapElement(int array[], int id)
{
    //int* tmp = UserScore[j];
    //UserScore[j] = UserScore[j + 1];
    //UserScore[j + 1] = tmp;
    for (int i = 0; i < CountScore; i++)
    {
        UserScore[id][i] = array[i];
    }

}

void writefile()
{
    FILE* F;
    if ((F = fopen("my.txt", "w")) == NULL)
    {
        fprintf(stderr, "Невозможно открыть для чтения файл 'fail.dta'\n");
        return;
    }

    fprintf(F, "%d\n", Number);
    for (int i = 0; i < Number; i++) {
        fprintf(F, "%s\n", UserList[i]);
    }
    fclose(F);
}



void sumA(int answercaseA) {
    int UserID = 0, sum = 0;
    switch (answercaseA) {
    case 1:
        printf("Введите ID пользователя");
        scanf("%d", &UserID);
        sum = SumElemArr(UserScore[UserID], 10, 20);
        printf("Сумма за A=%i|%s|\n", sum, UserList[UserID]);
        break;
    case 2:
        for (int i = 0; i < Number; i++) {
            sum = SumElemArr(UserScore[i], 10, 20);
            printf("Сумма за A=%i|%s|\n", sum, UserList[i]);
        }
        break;
    default:
        break;
    }
}

void sumT(int answercaseT) {
    int UserID = 0, sum = 0;
    switch (answercaseT) {
    case 1:
        printf("Введите ID пользователя");
        scanf("%d", &UserID);
        sum = SumElemArr(UserScore[UserID], 0, 10);
        printf("Сумма за T=%i|%s|\n", sum, UserList[UserID]);
        break;
    case 2:
        for (int i = 0; i < Number; i++) {
            sum = SumElemArr(UserScore[i], 0, 10);
            printf("Сумма за T=%i|%s|\n", sum, UserList[i]);
        }
        break;
    default:
        break;
    }
}

void sumAT(int answercaseAT) {
    int UserID = 0, sumA = 0, sumT = 0;
    switch (answercaseAT) {
    case 1:
        printf("Введите ID пользователя");
        scanf("%d", &UserID);
        sumT = SumElemArr(UserScore[UserID], 0, 10);
        sumA = SumElemArr(UserScore[UserID], 10, 20);
        printf("Сумма за A и T=%i|%s|\n", sumA + sumT, UserList[UserID]);
        break;
    case 2:
        for (int i = 0; i < Number; i++) {
            sumT = SumElemArr(UserScore[i], 0, 10);
            sumA = SumElemArr(UserScore[i], 10, 20);
            printf("Сумма за A и T=%i|%s|\n", sumA + sumT, UserList[i]);
        }
        break;
    default:
        break;
    }
}


void sort_artistry(int array[][CountScore])
{
    for (int i = 0; i < Number - 1; i++)
    {
        // сравниваем два соседних элемента.
        for (int j = 0; j < Number - i - 1; j++)
        {
            int one = SumElemArr(UserScore[j], 10, 20);
            int two = SumElemArr(UserScore[j + 1], 10, 20);
            if (one < two) {

                int tmp[CountScore];
                for (int k = 0; k < CountScore; k++) tmp[k] = UserScore[j][k];
                int* tmp2 = UserScore[j + 1];
                char* tmp1 = UserList[j];
                SwapElement(tmp2, j);
                SwapElement(tmp, j + 1);
                UserList[j] = UserList[j + 1];
                UserList[j + 1] = tmp1;
            }
        }
    }
}

void sort_technique(int array[][CountScore]) {
    for (int i = 0; i < Number - 1; i++)
    {
        // сравниваем два соседних элемента.
        for (int j = 0; j < Number - i - 1; j++)
        {
            int one = SumElemArr(UserScore[j], 0, 10);
            int two = SumElemArr(UserScore[j + 1], 0, 10);
            if (one < two) {

                int tmp[CountScore];
                for (int k = 0; k < CountScore; k++) tmp[k] = UserScore[j][k];
                int* tmp2 = UserScore[j + 1];
                char* tmp1 = UserList[j];
                SwapElement(tmp2, j);
                SwapElement(tmp, j + 1);
                UserList[j] = UserList[j + 1];
                UserList[j + 1] = tmp1;
            }
        }
    }
}


void rating(int array[][CountScore])
{
    for (int i = 0; i < Number - 1; i++)
    {
        // сравниваем два соседних элемента.
        for (int j = 0; j < Number - i - 1; j++)
        {
            int one = SumElemArr(UserScore[j], 0, 20);
            int two = SumElemArr(UserScore[j + 1], 0, 20);
            if (one < two) {

                int tmp[CountScore];
                for (int k = 0; k < CountScore; k++) tmp[k] = UserScore[j][k];
                int* tmp2 = UserScore[j + 1];
                char* tmp1 = UserList[j];
                SwapElement(tmp2, j);
                SwapElement(tmp, j + 1);
                UserList[j] = UserList[j + 1];
                UserList[j + 1] = tmp1;
            }
        }
    }
}

void search() {
    int m, answ = 0;
    char surname[50];
    char name[50];
    char* string3;
    printf("Поиск\n");
    printf("1)по максимумy\n");
    printf("2)по минимуму\n");
    printf("3)по месту\n");
    printf("4)по фамилии и имени\n");
    scanf("%d", &m);
    switch (m) {
    case 1:
        tabl();
        rating(UserScore);
        PrintUser(0);
        break;
    case 2:
        tabl();
        rating(UserScore);
        PrintUser(Number-1);
        break;
    case 3:
        printf("Введите место\n");
        scanf("%d", &answ);
        tabl();
        rating(UserScore);
        PrintUser(answ);
        break;
    case 4:
        printf("Введите фамилию\n");
        getchar();
        scanf("%s", surname);

        printf("Введите имя\n");
        getchar();
        scanf("%s", name);

        string3 = concat(surname, name);
        for (int i = 0; i < Number; i++) {
            if (strcmp(UserList[i], string3) == 0) {
                tabl();
                PrintUser(i);
            }
        }
        break;
    default:
        break;
    }
}
void tabl() {
    puts("\t\t    Таблица результатов по фехтованию");
    puts("\t\t\t\tСудьи\t\t\t\t\t\t");
    puts("\t Бригада судей A\t\t\t Бригада судей B\t\t\t\t\t");
    puts(" 1\t 2\t 3\t 4\t 5\t 1\t 2\t 3\t 4\t 5\t");
    puts(" а т \t а т \t а т \t а т \t а т \t а т \t а т \t а т \t а т \t а т       Участники");

}