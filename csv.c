#include <stdio.h>
#include <conio.h>
#include <string.h>

/* Ñòðóêòóðà äëÿ õðàíåíèÿ èíôîðìàöèè ïðî îäíîãî ÷åëîâåêà */
typedef struct tagITEM
{
  char Surname[20], Name[20];
  int Age;
} ITEM;

/* Ìàññèâ ìàêñèìóì íà 20 ÷åëîâåê */
ITEM Men[20];

/* Êîëè÷åñòâî çàíÿòûõ ýëåìåíòîâ â ìàññèâå */
int Number;

/* Ôóíêöèÿ äëÿ âûâîäà âñåõ ýëåèåíòîâ */
void Print( void )
{
  int i;

  printf(" N  Surname             Name                 Age\n");
  for (i = 0; i < Number; i ++)
    printf("%2i. %-20s %-20s %3i\n", i + 1, Men[i].Surname,
           Men[i].Name, Men[i].Age);
} 

/* Ôóíêöèÿ äëÿ äîáàâëåíèÿ ýëåìåíòà */
void Add( void )
{
  if (Number == 19)
  {
    fprintf(stderr, "Element don't add'\n");
    return;
  }

  printf("Surname > ");
  scanf("%s", Men[Number].Surname);
  printf("Name > ");
  scanf("%s", Men[Number].Name);
  printf("Age> ");
  scanf("%i", &Men[Number].Age);

  Number ++;
} 

/* Ôóíêöèÿ äëÿ óäàëåíèÿ ýëåìåíòà */
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

/* Ôóíêöèÿ äëÿ ñîõðàíåíèÿ ìàññèâà â ôàéëå */
void Save( void )
{
  FILE *F;
  int i;

  if ((F = fopen("task1.csv", "wt")) == NULL)
  {
    fprintf(stderr, "File opened error 'task1.csv'\n");
    return;
  }

  fprintf(F, "%i\n", Number);
  for (i = 0; i < Number; i ++)
    fprintf(F, "%s\n%s\n%i\n", Men[i].Surname, Men[i].Name, Men[i].Age);

  fclose(F);
} 

/* Ôóíêöèÿ äëÿ ÷òåíèÿ ìàññèâà èç ôàéëà */
void Load( void )
{
  FILE *F;
  int i;

  if ((F = fopen("task1.csv", "rt")) == NULL)
  {
    fprintf(stderr, "File opened Error\n");
    return;
  }

  fscanf(F, "%i", &Number);
  for (i = 0; i < Number; i ++)
    fscanf(F, "%s%s%i", Men[i].Surname, Men[i].Name, &Men[i].Age);

  fclose(F);
} 

/* Ôóíêöèÿ äëÿ óïîðÿäî÷èâàíèÿ ìàññèâà ïî ôàìèëèè */
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

/* Âûâîä ìåíþ è ÷òåíèå íîìåðà âûáðàííîãî ïóíêòà */
int Menu( void )
{
  int c = 0;

  while ((c < '0' || c > '6') && c != 27)
  {
    printf("0 : Exit\n"
           "1 : Add\n"
           "2 : Save\n"
           "3 : Load\n"
           "4 : Enter\n"
           "5 : Sort\n"
           "6 : Delete\n"
           ">");
    c = getch();
    printf("%c\n", c);
  }
  return c;
} 

/* Îñíîâíàÿ ôóíêöèÿ */
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
      Save();
      break;
    case '3':
      Load();
      break;
    case '4':
      Print();
      break;
    case '5':
      Sort();
      break;
    case '6':
      Del();
      break;
    }
}

