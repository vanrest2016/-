#include <stdio.h>
#include <conio.h>
#include <string.h>
#define N 100

/* Структура для хранения информации про одного человека */
typedef struct tagITEM
{
  char Surname[N], Name[N], Kafedra[N], Faculty[N], Number_gradebook[N];
} ITEM;

/* Массив максимум на 100 человек */
ITEM Men[N];

/* Количество занятых элементов в массиве */
int Number;

/* Функция для вывода всех элеиентов */
void Print( void )
{
  int i;

  printf(" Number       Surname             Name          Kafedra                 Faculty\n");
  for (i = 0; i < Number; i ++)
    printf("%2i. %-10s %-20s %-20s %-20s %-20s\n", i + 1, Men[i].Number_gradebook, Men[i].Surname,
           Men[i].Name, Men[i].Kafedra, Men[i].Faculty);
} 

/* Функция для добавления элемента */
void Add( void )
{
  if (Number == N)
  {
    fprintf(stderr, "Element don't add'\n");
    return;
  }
  printf("Number gradebook > ");
  scanf("%s", Men[Number].Number_gradebook);
  printf("Surname > ");
  scanf("%s", Men[Number].Surname);
  printf("Name > ");
  scanf("%s", Men[Number].Name);
  printf("Kafedra > ");
  scanf("%s", &Men[Number].Kafedra);
  printf("Faculty > ");
  scanf("%s", &Men[Number].Faculty);

  Number ++;
} 
void Change( void )
{
  FILE *F;
  int i;

  if ((F = fopen("students.csv", "wt")) == NULL)
  {
    fprintf(stderr, "File opened error 'students.csv'\n");
    return;
  }
  printf("Enter number of element > ");
  scanf("%i", &i);
    if (i < 1 || i > Number)
  {
    fprintf(stderr, "Element %i don't exists'\n", i);
    return;
  }
  
  fclose(F);
}

/* Функция для удаления элемента */
void Del( void )
{
  int i;

  Print();
  printf("Enter number of element > ");
  scanf("%i", &i);
  if (i < 1 || i > Number)
  {
    fprintf(stderr, "Element %i don't exists'\n", i);
    return;
  }

  for (i --; i < Number - 1; i ++)
    Men[i] = Men[i + 1];

  Number --;
} 

/* Функция для сохранения массива в файле */
void Save( void )
{
  FILE *F;
  int i;

  if ((F = fopen("students.csv", "wt")) == NULL)
  {
    fprintf(stderr, "File opened error 'students.csv'\n");
    return;
  }

  fprintf(F, "%i\n", Number);
  for (i = 0; i < Number; i ++)
    fprintf(F, "%s,%s,%s,%s,%s\n", Men[i].Number_gradebook, Men[i].Surname, Men[i].Name, Men[i].Kafedra, Men[i].Faculty);

  fclose(F);
} 

/* Функция для чтения массива из файла */
void Load( void )
{
  FILE *F;
  int i;

  if ((F = fopen("students.csv", "rt")) == NULL)
  {
    fprintf(stderr, "File opened Error\n");
    return;
  }

  fscanf(F, "%i", &Number);
  for (i = 0; i < Number; i ++)
    fscanf(F, "%s%s%s%s%s", Men[i].Number_gradebook, Men[i].Surname, Men[i].Name, &Men[i].Kafedra, Men[i].Faculty);

  fclose(F);
} 

/* Функция для упорядочивания массива по фамилии */
void Sort( void )
{
  int i, j;
  ITEM Temp;

  for (j = Number - 1; j > 0; j --)
    for (i = 0; i < j; i ++)
      if (strcmp(Men[i].Surname, Men[i + 1].Surname) > 0)
      {
        Temp = Men[i];
        Men[i] = Men[i + 1];
        Men[i + 1] = Temp;
      }
} 

/* Вывод меню и чтение номера выбранного пункта */
int Menu( void )
{
  int c = 0;

  while ((c < '0' || c > '7') && c != 27)
  {
    printf("0 : Exit\n"
            "1 : Add\n"
        	"2 : Change\n"
            "3 : Save\n"
            "4 : Load\n"
            "5 : Enter\n"
            "6 : Sort\n"
            "7 : Delete\n"
           ">");
    c = getch();
    printf("%c\n", c);
  }
  return c;
} 

/* Основная функция */
int main()
{
  int Selection;

  Number = 0;
  while ((Selection = Menu()) != '0' && Selection != 27)
    switch (Selection)
    {
    case '1':
      Add();
      break;    
	case '2':
      Change();
      break;
    case '3':
      Save();
      break;
    case '4':
      Load();
      break;
    case '5':
      Print();
      break;
    case '6':
      Sort();
      break;
    case '7':
      Del();
      break;
    }
}

