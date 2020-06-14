#include <stdio.h>
#include <conio.h>
#include <string.h>
#define N 100

/* Ñòðóêòóðà äëÿ õðàíåíèÿ èíôîðìàöèè ïðî îäíîãî ÷åëîâåêà */
typedef struct student
{
  char Surname[N], Name[N], Kafedra[N], Faculty[N],  Number_gradebook[N];
} ITEM;

/* Ìàññèâ ìàêñèìóì íà 100 ÷åëîâåê */
ITEM Men[N];

/* Êîëè÷åñòâî çàíÿòûõ ýëåìåíòîâ â ìàññèâå */
int Number;

int count_students()
{
	int line = 0;
  FILE *F = fopen("students.csv", "r");
	if (F == NULL)
	{
		printf("No opened error!\n");
	}
	else
	{
		while (!feof(F))
		{
			if (fgetc(F)=='\n')
				line++;
		}
		return ++line;
		fclose(F);
	}
}

/* Ôóíêöèÿ äëÿ âûâîäà âñåõ ýëåèåíòîâ */
void Print( void )
{
  int i;

  printf("    Number       Surname             Name          Kafedra                 Faculty\n");
  for (i = 0; i < Number; i ++)
    printf("%2i. %-10s %-20s %-20s %-20s %-20s\n", i + 1, Men[i].Number_gradebook, Men[i].Surname,
           Men[i].Name, Men[i].Kafedra, Men[i].Faculty);
} 

/* Ôóíêöèÿ äëÿ äîáàâëåíèÿ ýëåìåíòà */
void Add( void )
{
	char i[N];
	int j=0;
  if (Number == N)
  {
    fprintf(stderr, "Element don't add\n");
    return;
  }
  printf("Number gradebook > ");
  scanf("%s", &i);
  for (j=0; j<=Number; j++){ 
  if (i == Men[j].Number_gradebook) {
  printf("This number has been used\a\n");
  return;
  }
  else strcpy(Men[Number].Number_gradebook, i);
}
  printf("Surname > ");
  scanf("%s", &Men[Number].Surname);
  printf("Name > ");
  scanf("%s", &Men[Number].Name);
  printf("Kafedra > ");
  scanf("%s", &Men[Number].Kafedra);
  printf("Faculty > ");
	scanf("%s", &Men[Number].Faculty);

	Number ++;

	return;
}

int availability_student (struct student *students, char Number_g[N], int line)
{
	int i, k = -1;
	for (i = 0; i < line; i++)
	{
		if (Number_g == Men[Number].Number_gradebook)
			k = i;
	}
	return k;
}

/* Ôóíêöèÿ äëÿ ðåäàêòèðîâàíèÿ ýëåìåíòîâ */ 
struct student *Change( struct student *students, int line )
{
	struct student tmpstudents;
	int i, k;
	printf("Enter gradebook > ");
	do {
		fflush(stdin);
		scanf("%d", &tmpstudents.Number_gradebook);
		k = availability_student(students, tmpstudents.Number_gradebook, line);
		if(k == -1)
		{
			printf("No student found in file\a\n");
			printf("Enter ID student to edit : ");
		}
	} while(k == -1);

	printf("Enter new surname > ");
	gets(tmpstudents.Surname);
	printf("Enter new name > ");
	gets(tmpstudents.Name);
	printf("Enter new kafedra > ");
	gets(tmpstudents.Kafedra);
	printf("Enter new faculty > ");
	gets(tmpstudents.Faculty);

	for (i = 0; i < line; i++)
	{
		if (i == k)
		{
			strcpy(students[i].Number_gradebook, tmpstudents.Number_gradebook);
			strcpy(students[i].Surname,tmpstudents.Surname);
			strcpy(students[i].Name,tmpstudents.Name);
			strcpy(students[i].Kafedra,tmpstudents.Kafedra);
			strcpy(students[i].Faculty,tmpstudents.Faculty);
		}
	}

	return students;
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
    fprintf(stderr, "Element %i don't exists'\a\n", i);
    return;
  }

  for (i --; i < Number - 1; i ++)
    Men[i] = Men[i + 1];

  Number --;
} 
struct student *read_student_csv()
{
	struct student *student =  calloc(0, sizeof(struct student));
	FILE *F = fopen("student.csv", "r");
	int i;
	if (F == NULL)
	{
		printf("File don't opened\n");
		return 0;
	}
	else
	{
		int line = count_students();
		char tmp[N];
		for (i = 0; i < line; i++)
		{
			fgets(tmp, N, F);

			student = realloc(student, (i+1) * sizeof(struct student));

			strcpy(student[i].Number_gradebook,strtok(tmp,"\n"));
			strcpy(student[i].Surname,strtok(NULL,"\n"));
			strcpy(student[i].Name,strtok(NULL,"\n"));
			strcpy(student[i].Kafedra,strtok(NULL,"\n"));
			strcpy(student[i].Faculty,strtok(NULL,"\n"));
		}
		return student;
	}
}

/* Ôóíêöèÿ äëÿ ñîõðàíåíèÿ ìàññèâà â ôàéëå */
void Save( void )
{
  FILE *F;
  int i;

  if ((F = fopen("students.csv", "wt")) == NULL)
  {
    fprintf(stderr, "File opened error 'students.csv'\a\n");
    return;
  }

  fprintf(F, "%i\n", Number);
  for (i = 0; i < Number; i ++)
    fprintf(F, "%s\n%s\n%s\n%s\n%s\n", Men[i].Number_gradebook, Men[i].Surname, Men[i].Name, Men[i].Kafedra, Men[i].Faculty);

  fclose(F);
} 

/* Ôóíêöèÿ äëÿ ÷òåíèÿ ìàññèâà èç ôàéëà */
void Load( void )
{
  FILE *F;
  int i;

  if ((F = fopen("students.csv", "rt")) == NULL)
  {
    fprintf(stderr, "File opened error 'students.csv'\a\n");
    return;
  }

  fscanf(F, "%i", &Number);
  for (i = 0; i < Number; i ++)
    fscanf(F, "%s%s%s%s%s", &Men[i].Number_gradebook, &Men[i].Surname, &Men[i].Name, &Men[i].Kafedra, &Men[i].Faculty);

  fclose(F);
} 

/* Ôóíêöèÿ äëÿ ñîðòèðîâêè ìàññèâà ïî ôàìèëèè */
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

/* Âûâîä ìåíþ */
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

/* Îñíîâíàÿ ôóíêöèÿ */
int main()
{
  int Selection;
  int line = count_students();
  struct student *students = read_student_csv();
  Number = 0;
  while ((Selection = Menu()) != '0' && Selection != 27)
    switch (Selection)
    {
    case '1':
      Add();
      break;    
	case '2':
	students = Change(students, line);
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
