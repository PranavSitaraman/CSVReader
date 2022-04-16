#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include<assert.h>
#include<stdarg.h>
#define rownum 1000
#define columnnum 255
#define cellsize 255
char* getfield(char* line, int num)
{
	char* tok;
	for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n"))
	{
		if (!--num)
		{
			return tok;
		}
	}
	return NULL;
}
bool isDate(char* string)
{
	char* endptr;
	int base = 10;
	bool works = true;
	int year, month, day;
	month = strtol(string, &endptr, base);
	if (month < 1 || month > 12)
	{
		works = false;
	}
	if (endptr[0] == '/')
	{
		day = strtol(endptr + 1, &endptr, base);
		if (day < 1 || day > 31)
		{
			works = false;
		}
	}
	else
	{
		works = false;
	}
	if (endptr[0] == '/')
	{
		year = strtol(endptr + 1, &endptr, base);
		if (year < 1 || year > 9999)
		{
			works = false;
		}
	}
	else
	{
		works = false;
	}
	return works;
}
typedef struct
{
	int month;
	int day;
	int year;
} date;
typedef struct
{
	date thedate;
	int theint;
	char thechar[cellsize];
} cell;
char line[columnnum * cellsize];
char find[cellsize];
cell table[rownum][columnnum];
int locsort;
int compareIntA(const void* p, const void* q)
{
	cell* n1 = (cell*)p;
	cell* n2 = (cell*)q;
	int m1 = n1[locsort].theint;
	int m2 = n2[locsort].theint;
	if (m1 < m2)
	{
		return -1;
	}
	if (m1 > m2)
	{
		return 1;
	}
	return 0;
}
int compareIntD(const void* p, const void* q)
{
	cell* n1 = (cell*)p;
	cell* n2 = (cell*)q;
	int m1 = n1[locsort].theint;
	int m2 = n2[locsort].theint;
	if (m1 < m2)
	{
		return 1;
	}
	if (m1 > m2)
	{
		return -1;
	}
	return 0;
}
int compareStringA(const void* p, const void* q)
{
	cell* n1 = (cell*)p;
	cell* n2 = (cell*)q;
	char* m1 = n1[locsort].thechar;
	char* m2 = n2[locsort].thechar;
	if (strcmp(m1, m2) == -1)
	{
		return -1;
	}
	if (strcmp(m1, m2) == 1)
	{
		return 1;
	}
	return 0;
}
int compareStringD(const void* p, const void* q)
{
	cell* n1 = (cell*)p;
	cell* n2 = (cell*)q;
	char* m1 = n1[locsort].thechar;
	char* m2 = n2[locsort].thechar;
	if (strcmp(m1, m2) == -1)
	{
		return 1;
	}
	if (strcmp(m1, m2) == 1)
	{
		return -1;
	}
	return 0;
}
int compareDateA(const void* p, const void* q)
{
	cell* n1 = (cell*)p;
	cell* n2 = (cell*)q;
	date m1 = n1[locsort].thedate;
	date m2 = n2[locsort].thedate;
	int val1 = m1.month * 12 + m1.day + m1.year * 365;
	int val2 = m2.month * 12 + m2.day + m2.year * 365;
	if (val1 < val2)
	{
		return -1;
	}
	if (val1 > val2)
	{
		return 1;
	}
	return 0;
}
int compareDateD(const void* p, const void* q)
{
	cell* n1 = (cell*)p;
	cell* n2 = (cell*)q;
	date m1 = n1[locsort].thedate;
	date m2 = n2[locsort].thedate;
	int val1 = m1.month * 12 + m1.day + m1.year * 365;
	int val2 = m2.month * 12 + m2.day + m2.year * 365;
	if (val1 < val2)
	{
		return 1;
	}
	if (val1 > val2)
	{
		return -1;
	}
	return 0;
}
int main()
{
	for (int i = 0; i < rownum; i++)
	{
		for (int j = 0; j < columnnum; j++)
		{
			strcpy(table[i][j].thechar, "NULL");
			table[i][j].theint = INT_MIN;
			table[i][j].thedate.day = INT_MIN;
			table[i][j].thedate.year = INT_MIN;
			table[i][j].thedate.month = INT_MIN;
		}
	}
	FILE* file = fopen("Level 3\\Test Project\\test.csv", "r");
	char sortorder;
	char sorttype;
	printf("Run command: ");
	scanf("parseThis %s %c %c", &find, &sortorder, &sorttype);
	int counter = 0;
	while (fgets(line, columnnum * cellsize, file))
	{
		int num = 1;
		for (int i = 0; i < int(strlen(line)); i++)
		{
			if (line[i] == ',')
			{
				num++;
			}
		}
		for (int i = 0; i < num; i++)
		{
			char* tmp = strdup(line);
			char* val = getfield(tmp, i + 1);
			if (counter == 0 && strcmp(val, find) == 0)
			{
				locsort = i;
			}
			if (isDate(val) == true)
			{
				strcpy(table[counter][i].thechar, "NULL");
				table[counter][i].theint = INT_MIN;
				char* endptr;
				int base = 10;
				table[counter][i].thedate.month = strtol(val, &endptr, base);
				table[counter][i].thedate.day = strtol(endptr + 1, &endptr, base);
				table[counter][i].thedate.year = strtol(endptr + 1, &endptr, base);
			}
			else if (val == "0" || atoi(val) != 0 && val != NULL)
			{
				strcpy(table[counter][i].thechar, "NULL");
				table[counter][i].thedate.day = INT_MIN;
				table[counter][i].thedate.month = INT_MIN;
				table[counter][i].thedate.year = INT_MIN;
				table[counter][i].theint = atoi(val);
			}
			else if (val != NULL)
			{
				table[counter][i].thedate.day = INT_MIN;
				table[counter][i].thedate.month = INT_MIN;
				table[counter][i].thedate.year = INT_MIN;
				table[counter][i].theint = INT_MIN;
				strcpy(table[counter][i].thechar, val);
			}
			free(tmp);
		}
		counter++;
	}
	fclose(file);
	if (sorttype == 'N' && sortorder == 'A')
	{
		qsort(table[1], sizeof(table) / sizeof(table[0]) - 1, sizeof(table[0]), compareIntA);
	}
	else if (sorttype == 'N' && sortorder == 'D')
	{
		qsort(table[1], sizeof(table) / sizeof(table[0]) - 1, sizeof(table[0]), compareIntD);
	}
	else if (sorttype == 'S' && sortorder == 'A')
	{
		qsort(table[1], sizeof(table) / sizeof(table[0]) - 1, sizeof(table[0]), compareStringA);
	}
	else if (sorttype == 'S' && sortorder == 'D')
	{
		qsort(table[1], sizeof(table) / sizeof(table[0]) - 1, sizeof(table[0]), compareStringD);
	}
	else if (sorttype == 'D' && sortorder == 'A')
	{
		qsort(table[1], sizeof(table) / sizeof(table[0]) - 1, sizeof(table[0]), compareDateA);
	}
	else if (sorttype == 'D' && sortorder == 'D')
	{
		qsort(table[1], sizeof(table) / sizeof(table[0]) - 1, sizeof(table[0]), compareDateD);
	}
	file = fopen("test.csv", "w");
	bool newline = false;
	for (int i = 0; i < rownum; i++)
	{
		if (newline == true)
		{
			fprintf(file, "\n");
		}
		newline = false;
		for (int j = 0; j < columnnum; j++)
		{
			if (table[i][j].theint != INT_MIN)
			{
				if (j != 0)
				{
					fprintf(file, ",");
				}
				fprintf(file, "%d", table[i][j].theint);
				newline = true;
			}
			if (table[i][j].thedate.day != INT_MIN && table[i][j].thedate.month != INT_MIN && table[i][j].thedate.year != INT_MIN)
			{
				if (j != 0)
				{
					fprintf(file, ",");
				}
				fprintf(file, "%02d/%02d/%04d", table[i][j].thedate.month, table[i][j].thedate.day, table[i][j].thedate.year);
				newline = true;
			}
			if (strcmp(table[i][j].thechar, "NULL") != 0)
			{
				if (j != 0)
				{
					fprintf(file, ",");
				}
				fprintf(file, "%s", table[i][j].thechar);
				newline = true;
			}
		}
	}
	fclose(file);
}
