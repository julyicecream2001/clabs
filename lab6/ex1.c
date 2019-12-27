#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#define NUMBER 'N'
#define FUNC 'F'
int getop(char *s);
void push(double f);
double pop(void);
void mathfunc(char *s);
int main(int argc, char *argv[])
{
	if (argc == 1) {
		printf("Usage: expression\n");
		return 0;
	}
	int i, op;
	double op2, sum;
	for (i = 1; i < argc; i++) {
		op = getop(argv[i]);
		switch (op) {
			case NUMBER:
					push(atof(argv[i]));
					break;
			case '+':
					push(pop() + pop());
					break;
			case '*':
					push(pop() * pop());
					break;
			case '-':
					op2 = pop();
					push(pop() - op2);
					break;
			case '/':
					op2 = pop();
					if (op2 != 0.0)
						push(pop() / op2);
					else
						printf("Zero divisor\n");
					break;
			case '%':
					op2 = pop();
					if (op2 != 0.0)
						push(fmod(pop(),op2));
					else
						printf("Zero divisor\n");
					break;
			case FUNC:
					mathfunc(argv[i]);
					break;
			default:
					printf("Error: unknown command %s\n",argv[i]);
					break;
		}
	}
	sum = pop();
	printf("%.8g\n",sum);
	return 0;
}
//push() pop()
#define MAXVAL 100
int sp = 0;
double val[MAXVAL];
void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("Error: stack full, can't push %g\n",f);
}
double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("Error: stack empty\n");
		return 0.0;
	}
}
//math function
void mathfunc(char *s)
{
	double op2;
		if (strcmp(s, "sin") == 0) 
			push(sin(pop()));
		else if (strcmp(s, "cos") == 0) 
			push(cos(pop()));
		else if (strcmp(s, "tan") == 0)
			push(tan(pop()));
		else if (strcmp(s, "pow") == 0) {
			op2 = pop();
			push(pow(pop(), op2));
		}			
		else if (strcmp(s, "exp") == 0) 
			push(exp(pop()));
}
//getop()
int getop(char *s)
{
	int i;
	int isnum = 0;
	if (!isdigit(s[0]) && s[0] != '.' && s[0] != '-') {
		if (strcmp(s,"sin") == 0 || strcmp(s,"cos") == 0\
		|| strcmp(s,"tan") == 0 || strcmp(s,"pow") == 0 \
		|| strcmp(s, "exp") == 0)
		return FUNC;
	else if (strcmp(s, "+") == 0)
		return '+';
	else if (strcmp(s, "*") == 0)
		return '*';
	else if (strcmp(s, "/") == 0)
		return '/';
	else if (strcmp(s, "%") == 0)
		return '%';
	else
		return -1;
	}
	if (strcmp(s, "-") == 0)
		return '-';
	i = 0;
	if (s[0] == '-')
		while (isdigit(s[++i]))
			isnum = 1;
	if (isdigit(s[i])) {
		isnum = 1;
		while (isdigit(s[++i]))
			isnum = 1;
	}
	if (s[i] == '.')
		while (isdigit(s[++i]))
			isnum = 1;
	if (isnum == 0 || s[i] != '\0')
		return -1;
	else
		return NUMBER;
}