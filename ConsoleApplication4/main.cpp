#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX 50
#define AlterMax 10
struct Student {
	char id[15];
	char name[20];
	float English;
	float Math;
	float Physics;
	float C;
};
typedef struct Student Student;
void menu(void);
void record(void);
void query(void);
void alter(void);
void save(void);
void average(void);
void sort(void);
void read(void);
float avg(Student student);
float sum(Student student);
Student student[MAX];
int N, len = 0;
int main()
{
	menu();
	return 0;
}

//主菜单
void menu(void)
{
	int option = 0;
	read();
	N = len;
	while (1)
	{
		printf("\n                   学生成绩管理系统\n\n");
		printf("**********************主菜单*********************\n");
		printf("-------------------------------------------------\n");
		printf("                  1.录入学生成绩\n");
		printf("                  2.查询学生成绩\n");
		printf("                  3.修改学生成绩\n");
		printf("                  4.计算总成绩和平均分\n");
		printf("                  5.按总成绩降序排序\n");
		printf("                  6.保存修改\n");
		printf("                  7.退出\n");
		printf("-------------------------------------------------\n");
		printf("请选择功能选项对应编号:");
		scanf_s("%d", &option);
		switch (option)
		{
		case 1:record(); break;
		case 2:query(); break;
		case 3:alter(); break;
		case 4:average(); break;
		case 5:sort(); break;
		case 6:save(); break;
		case 7:save(); return;
		}
	}
}

//录入学生成绩
void record()
{
	int i;
	printf("请输入学生数：");
	scanf_s("%d", &N);
	for (i = len; i < len + N; i++)
	{
		printf("学生%d学号：", i + 1 - len); scanf_s("%s", student[i].id, 15);
		printf("学生%d姓名：", i + 1 - len); scanf_s("%s", student[i].name, 15);
		printf("学生%d大学英语成绩：", i + 1 - len); scanf_s("%f", &student[i].English, 15);
		printf("学生%d高等数学成绩：", i + 1 - len); scanf_s("%f", &student[i].Math, 15);
		printf("学生%d大学物理成绩：", i + 1 - len); scanf_s("%f", &student[i].Physics, 15);
		printf("学生%dC语言成绩：", i + 1 - len); scanf_s("%f", &student[i].C, 15);
	}
	len += N;
	N = len;
}

//查询学生成绩
void query()
{
	char id[30];
	int i;
	printf("请输入学生学号："); scanf_s("%s", id, 20);
	printf("\n%-15s%-20s%-10s%-10s%-10s%-10s\n", "ID", "Name", "English", "Math", "Physics", "C");
	for (i = 0; i<N; i++)
	{
		if(!strcmp(id, student[i].id))
			printf("%-15s%-20s%-10.2f%-10.2f%-10.2f%-10.2f\n", student[i].id, student[i].name, student[i].English, student[i].Math, student[i].Physics, student[i].C);
	}
	putchar('\n');
}

//修改学生成绩
void alter()
{
	int i;
	char id[30], subject[20];
	float score;
	printf("请输入要修改学生的学号："); scanf_s("%s", id, 30);
	printf("请输入要修改的科目(English,Math,Physics或C)："); scanf_s("%s", subject, 20);
	printf("请输入学生成绩："); scanf_s("%f", &score, 10);
	printf("修改成功！\n修改后的学生成绩如下：\n");
	for (i = 0; i < N; i++)
	{
		if (!strcmp(id, student[i].id))
		{
			if (!strcmp(subject, "English")) student[i].English = score;
			if (!strcmp(subject, "Math")) student[i].Math = score;
			if (!strcmp(subject, "Physics")) student[i].Physics = score;
			if (!strcmp(subject, "C")) student[i].C = score;
		}
	}
	printf("%-15s%-20s%-10s%-10s%-10s%-10s\n", "ID", "Name", "English", "Math", "Physics", "C");
	for (i = 0; i < N; i++)
	{
		printf("%-15s%-20s%-10.2f%-10.2f%-10.2f%-10.2f\n", student[i].id, student[i].name, student[i].English, student[i].Math, student[i].Physics, student[i].C);
	}
	putchar('\n');
}

//计算平均分
void average()
{
	int i;
	printf("%-15s%-20s%-10s%-10s\n", "ID", "Name", "SUM", "AVG");
	for (i = 0; i<N; i++)
	{
		printf("%-15s%-20s%-10.2f%-10.2f\n", student[i].id, student[i].name, sum(student[i]), avg(student[i]));
	}
	putchar('\n');
}

//排序
void sort()
{
	Student m;
	int i, j;
	for (i = N - 1; i>0; i--)
	{
		for (j = 0; j<i; j++)
			if (avg(student[j])>avg(student[j + 1]))
			{
				m = student[j];
				student[j] = student[j + 1];
				student[j + 1] = m;
			}
	}
	printf("%-15s%-20s%-10s\n", "ID", "Name", "SUM");
	for (i = 0; i<N; i++)
	{
		printf("%-15s%-20s%-10.2f\n", student[i].id, student[i].name, sum(student[i]));
	}
	putchar('\n');
}

//保存
void save()
{
	FILE *fp;
	errno_t err = fopen_s(&fp, "学生成绩管理系统数据库.txt", "w");
	int i;
	for(i=0;i < N;i++)
	{
		fprintf(fp, "%-15s%-20s%-10.2f%-10.2f%-10.2f%-10.2f\n", student[i].id, student[i].name, student[i].English, student[i].Math, student[i].Physics, student[i].C);
	}
	fclose(fp);
	printf("保存成功!\n");
	return;
}

//读取数据
void read()
{
	FILE *fp;
	errno_t err = fopen_s(&fp, "学生成绩管理系统数据库.txt", "r");
	if (err != 0)
	{
		printf("数据文件不存在或载入数据失败！");
		return;
	}
	if (!fp) return;
	int i = 0;
	while (!feof(fp))
	{
		fscanf_s(fp, "%s%s%f%f%f%f\n", student[i].id, 15, student[i].name, 20, &student[i].English, &student[i].Math, &student[i].Physics, &student[i].C);
		i++;
	}
	len = i;
	fclose(fp);
	return;
}


float sum(Student student)
{
	float sum = student.English + student.Math + student.Physics + student.C;
	return sum;
}
float avg(Student student)
{
	return sum(student) / 4;
}
