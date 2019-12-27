#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<stdlib.h>
#define MAXOP 100
#define NUMBER '0'
#define NAME 'N'
int getop(char *s);
void push(double f);
double pop(void);
int getch(void);
void ungetch(int c);
void mathfunc(char *s);
double top(void);
void duplicate(void);
void swap(void);
void clear(void);
int main(void)
{
	int type;
	double op2;
	char s[MAXOP];
	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				 push(atof(s));
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
				 	printf("error: zero divisor\n");
				break;
			case '%':
				 op2 = pop();
				 if (op2 != 0.0)
				 	push(fmod(pop(), op2));
				 else
				 	printf("error: zero divisor\n");
				 break;
			case '?':
			     printf("\t%.8g\n",top());
				 break;
			case 'd':
				 duplicate();
				 break;
			case 'c':
				 clear();
				 break;
			case 's':
				 swap();
				 break;
			case NAME:
				 mathfunc(s);
				 break;
			case '\n':
				 printf("\t%.8g\n", pop());
				 break;
			default:
				 printf("error: unknown command %s\n", s);
				 break;
		}
	}
	return 0;
}
//pop() push() 
#define MAXVAL 100
int sp = 0;
double val[MAXVAL];
void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n",f);
}
double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else
		printf("error: stack empty\n");
	return 0.0;
}
//top() duplicate() swap() clear()
double top(void)
{
	if (sp > 0)
		return val[sp-1];
	else
		printf("error: stack empty\n");
	return 0.0;
}
void duplicate(void)
{
	push(top());
}
void swap(void)
{
	double elem1 = pop();
	double elem2 = pop();
	push(elem1);
	push(elem2);
}
void clear(void)
{
	sp = 0;
}
//getch() ungetch()
#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
//void mathfunc()
void mathfunc(char *s)
{
	double op2;
	if (strcmp(s, "sin") == 0)
		push(sin(pop()));
	else if (strcmp(s, "cos") == 0)
		push(cos(pop()));
	else if (strcmp(s, "tan") == 0)
		push(tan(pop()));
	else if (strcmp(s, "exp") == 0)
		push(exp(pop()));
	else if (strcmp(s, "pow") == 0) {
		op2 = pop();
		push(pow(pop(), op2));
	}
	else
		printf("error: unknow command %s\n", s);
}
//getop()
int getop(char *s)
{
	int i, c, c1;
	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	i = 0;
	if (islower(c)) {
		while (islower(s[++i] = c1 = getch()))
			;
		s[i] = '\0';
		if (c1 != EOF)
			ungetch(c1);
		if (strlen(s) > 1)
			return NAME;
		return c;
	}
	if (!isdigit(c) && c != '.' && c != '-')
		return c;
	if (c == '-')
		if (isdigit(c = getch()) || c == '.')
			s[++i] = c;
		else {
			if (c != EOF)
				ungetch(c);
			return '-';
		}
	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}