#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
int getch(void);
void ungetch(int);
int getfloat(double *pn);
int main(void)
{
	double n;
	if (getfloat(&n) == 1)
		printf("n = %.8g\n", n);
	else
		puts("Not a number");
	return 0;
}
//getch() ungetch()
#define BUFSIZE 40
int bufp = 0;
char buf[BUFSIZE];
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("Error: too many characters.\n");
	else
		buf[bufp++] = c;
}
// getfloat()
int getfloat(double *pn)
{
	int sign, sign_e;
	int hasint = 0; //判断小数点前是否有数字
	int hassign = 0;//判断是否有符号
	double intpart = 0.0;//小数的整数部分
	double decpart = 0.0;//小数的小数部分
	int exp = 0;//指数部分
	int decdigit = 1;//小数的小数点后数字位置
	int c, c1, c2;
	while (isspace(c = getch()))
		;
	if (!isdigit(c) && c != '-' &&  c != '+' && c != '.' && c != EOF) {
		ungetch(c);
		return 0;
	}
//	if (c == EOF)
//		return c;
	sign = (c == '-') ? -1 : 1;
	if (c == '-' || c == '+') {
		c1 = getch();
		if (!isdigit(c1) && c1 != '.' && c1 != EOF){
			ungetch(c);
			ungetch(c1);
			return 0;
		}
		c = c1;
		hassign = 1;
	} // c 只能是数字或点号, EOF
	//如果 c 是数字，计算小数的整数部分
	for (intpart = 0.0; isdigit(c); c = getch()) {
		intpart = 10 * intpart + c - '0';
		hasint = 1;	
	}
	// c 可能是非法字符，科学计数符 e 或 E， 小数点， EOF
	//如果是非法字符，那已经扫描到数字
	if (c != '.' && c != 'e' && c != 'E' && c != EOF) {
		ungetch(c);
		*pn = sign * intpart;
		return 1;
	}
	//如果是小数点
	if (c == '.') {
		c1 = getch();
		//如果小数点前面没数字，后面也没数字，则非法
		if (hasint == 0 && !isdigit(c1)) {
			if (hassign == 1) {
				c2 = (sign == -1) ? '-' : '+';
				ungetch(c2);
			}
			ungetch(c);
			ungetch(c1);
			return 0;
		}
		//小数点前有数字，后面非法
		else if (hasint == 1 && !isdigit(c1) && c1 != 'e' && c1 != 'E') {
			if (c1 != EOF)
				ungetch(c1);
			*pn =  sign * intpart;
			return 1;
		}
		//小数点后数字或者e（小数点前有数字）
		//计算小数部分
		for (decpart = 0.0; isdigit(c1); c1 = getch())
			decpart = (c1 - '0') / pow(10, decdigit++);
		c = c1;
	}
	//小数部分计算完成
	//如果扫描到 e
	hassign = 0;
	if (c == 'e' || c == 'E') {
		if ((c1 = getch()) == '-' || c1 == '+') 
			hassign = 1;
			sign_e = (c == '-') ? -1 : 1;
			c2 = getch();
			if (!isdigit(c2)) {
				if (hassign == 1) {
					ungetch(c);
					ungetch((sign_e == -1) ? '-' : '+');
				}
				if (c2 != EOF)
					ungetch(c2);
				*pn = sign * (intpart + decpart);
				return 1;
			}
			c = c2;
	}
	// 计算指数部分
	for (exp = 0; isdigit(c); c = getch())
		exp = exp * 10 + c - '0';
	if (c != EOF)
		ungetch(c);
	exp = sign_e * exp;
	*pn = sign * (intpart + decpart) * pow(10, exp);
	return 1;
}