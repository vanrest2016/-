#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

#define N 100

struct student {char id[N]; char Surname[N]; char Name[N]; char Middlename[N]; char Faculty[N]; char Specialty[N]; };

int count_students()
{
	int line = 0;
	FILE *F = fopen("student.csv", "r");
	
	if (F == NULL)
	{
		printf("No file\a\n");
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

struct student *read_student_csv()
{
	int i;
	struct student *student =  calloc(0, sizeof(struct student));
	FILE *F = fopen("student.csv", "r");
	
	if (F == NULL)
	{
		printf("Not file\a\n");
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

			strcpy(student[i].id,strtok(tmp,";"));
			strcpy(student[i].Surname,strtok(NULL,";"));
			strcpy(student[i].Name,strtok(NULL,";"));
			strcpy(student[i].Middlename,strtok(NULL,";"));
			strcpy(student[i].Faculty,strtok(NULL,";"));
			strcpy(student[i].Specialty,strtok(NULL,"\n"));
		}
		return student;
	}
}

struct student *write_student_csv(struct student *students, int line)
{
	FILE *F = fopen("student.csv", "w+");
	rewind(F);
	
	int i;
	
	for (i = 0; i < 1; i++)
	{
		fprintf(F,"%s",students[i].id); 
		fprintf(F,";%s",students[i].Surname); 
		fprintf(F,";%s",students[i].Name);
		fprintf(F,";%s",students[i].Middlename); 
		fprintf(F,";%s",students[i].Faculty); 
		fprintf(F,";%s",students[i].Specialty);
	}
	
	for (i = 1; i < line; i++)
	{
		fprintf(F,"\n%s",students[i].id); 
		fprintf(F,";%s",students[i].Surname); 
		fprintf(F,";%s",students[i].Name);
		fprintf(F,";%s",students[i].Middlename); 
		fprintf(F,";%s",students[i].Faculty); 
		fprintf(F,";%s",students[i].Specialty);
	}
	
	fclose(F);
}

int availability_student(struct student *students, char id[N], int line)
{
	int i;
	int k = -1;
	
	for (i = 0; i < line; i++)
	{
		if (strcmp(id, students[i].id) == 0)
			k = i;
	}
	return k;
}

void print_student_csv(struct student *students, int line)
{
	int i;
	
	for( i = 0; i < line; i++)
	{
		if (students[i].id != 0) printf("%s; %s; %s; %s; %s; %s\n", students[i].id, students[i].Surname, students[i].Name, students[i].Middlename, students[i].Faculty, students[i].Specialty);
	}
}

struct student *add_student(struct student *students, int line)
{
	struct student newstudent;

	int k;
	
	printf("Enter ID : ");
	
	do {
		scanf("%s", newstudent.id);
		k = availability_student(students, newstudent.id, line);
		if( k != -1)
		{
			printf("This student in the file\a\n");
			printf("Enter ID : ");
		}
		
	}
	 while( k != -1);

	printf("Enter surname : ");
	scanf("%s", newstudent.Surname);
	printf("Enter name : ");
	scanf("%s", newstudent.Name);
	printf("Enter middlename : ");
	scanf("%s", newstudent.Middlename);
	printf("Enter faculty : ");
	scanf("%s", newstudent.Faculty);
	printf("Enter specialty : ");
	scanf("%s", newstudent.Specialty);

	students = realloc(students, (line+1) * sizeof(struct student));

	strcpy(students[line].id,newstudent.id);
	strcpy(students[line].Surname,newstudent.Surname);
	strcpy(students[line].Name,newstudent.Name);
	strcpy(students[line].Middlename,newstudent.Middlename);
	strcpy(students[line].Faculty,newstudent.Faculty);
	strcpy(students[line].Specialty,newstudent.Specialty);

	return students;
}

struct student *delete_student(struct student *students, int line)
{
	struct student *tmpstudents = calloc(line-1, sizeof(struct student));
	int i;
	int k;
	printf("Enter ID : ");
	do {
		char id[N];
		gets(id);
		k = availability_student(students, id, line);
		if(k == -1)
		{
			printf("No student found in file\a\n");
			printf("Enter ID : ");
		}
	} while(k == -1);

	for (i = 0; i < line; i++)
	{
		if (i < k)
		{
			strcpy(tmpstudents[i].id,students[i].id);
			strcpy(tmpstudents[i].Surname,students[i].Surname);
			strcpy(tmpstudents[i].Name,students[i].Name);
			strcpy(tmpstudents[i].Middlename,students[i].Middlename);
			strcpy(tmpstudents[i].Faculty,students[i].Faculty);
			strcpy(tmpstudents[i].Specialty,students[i].Specialty);
		}
		else if (i > k)
		{
			strcpy(tmpstudents[i-1].id,students[i].id);
			strcpy(tmpstudents[i-1].Surname,students[i].Surname);
			strcpy(tmpstudents[i-1].Name,students[i].Name);
			strcpy(tmpstudents[i-1].Middlename,students[i].Middlename);
			strcpy(tmpstudents[i-1].Faculty,students[i].Faculty);
			strcpy(tmpstudents[i-1].Specialty,students[i].Specialty);
		}
	}
	
	return tmpstudents;
}

struct student *edit_student(struct student *students, int line)
{
	struct student tmpstudents;
	int k;
	int i;
	printf("Enter ID : ");
	do {
		scanf("%s", tmpstudents.id);
		k = availability_student(students, tmpstudents.id, line);
		if(k == -1)
		{
			printf("No student found in file\a\n");
			printf("Enter ID student to edit : ");
		}
	} while(k == -1);

	printf("Enter new surname : ");
	scanf("%s", tmpstudents.Surname);
	
	printf("Enter new name :");
	scanf("%s", tmpstudents.Name);
	
	printf("Enter new middlename :");
	scanf("%s", tmpstudents.Middlename);
	
	printf("Enter new faculty :");
	scanf("%s", tmpstudents.Faculty);
	
	printf("Enter new specialty :");
	scanf("%s", tmpstudents.Specialty);

	for ( i = 0; i < line; i++)
	{
		if (i == k)
		{
			strcpy(students[i].id, tmpstudents.id);
			strcpy(students[i].Surname,tmpstudents.Surname);
			strcpy(students[i].Name,tmpstudents.Name);
			strcpy(students[i].Middlename,tmpstudents.Middlename);
			strcpy(students[i].Faculty,tmpstudents.Faculty);
			strcpy(students[i].Specialty,tmpstudents.Specialty);
		}
	}

	return students;
}

void info_student(struct student *students, int line)
{
	int i;
	int k;
	printf("Enter ID : ");
	do {
		char id[N];
		scanf("%s", id);
		k = availability_student(students, id, line);
		if(k == -1)
		{
			printf("No student found in file\a\n");
			printf("Enter ID : ");
		}
	} 
	while(k == -1);

	for (i = 0; i < line; i++)
	{
		if (i == k)
		printf("ID: %s;\n Surname: %s;\n Name: %s;\n Middlename: %s;\n Faculty: %s;\n Specialty: %s\n", students[i].id,students[i].Surname, students[i].Name, students[i].Middlename, students[i].Faculty, students[i].Specialty);
	}
}
void mainstudent()
{
	struct student *students = read_student_csv();
	int line = count_students();
	FILE *flog;
	time_t now;
	struct tm  ts;
	char buf[N];
	time(&now);
	ts = *localtime(&now);
	strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S", &ts);

	flog = fopen("library.log","a");
	for(;;)
	{
		printf("0 : Exit\n"
            "1 : Add\n"
        	"2 : Delete\n"
            "3 : Change\n"
            "4 : Information\n"
            "5 : Print all\n"
           ">");
           
		int comand;
		
		scanf("%d",&comand);
		
		switch(comand)
		{
			case 1:
				students = add_student(students, line);
				++line;
				break;
			case 2:
				students = delete_student(students, line);
				--line;
				break;
			case 3:
				students = edit_student(students, line);
				break;
			case 4:
				info_student(students, line);
				break;
			case 5:
				print_student_csv(students, line);
				break;
		}
		if(comand == 0)
			break;

		fprintf(flog,"\n\"%s\"",buf);
		if(comand==1)
			fprintf(flog,",\"Add\"");
		else if(comand==2)
			fprintf(flog,",\"Delete\"");
		else if(comand==3)
			fprintf(flog,",\"Change\"");
		else if(comand==4)
			fprintf(flog,",\"Information\"");
		else if(comand==5)
			fprintf(flog,",\"Print all\"");
		else if(comand==0)
			fprintf(flog,",\"Exit\"");
		else break;
		fclose(flog);
	}

	write_student_csv(students, line);
	free(students);

}
int main()
{
	mainstudent();
	
	return 0;
}	
