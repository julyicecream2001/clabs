#include<stdio.h>
#include<string.h>
#define LEN 100
char *s_gets(char *s, int n);
void reverse(char *s, int n);
int main(void)
{
	char s[LEN];
	int n;
	printf("Please enter a string:\n");
	s_gets(s, LEN);
	n = strlen(s);
	reverse(s, n);
	printf("Reversed string:\n%s\n",s);
	return 0;
}
char *s_gets(char *s, int n)
{
	char *ret, *find;
	ret = fgets(s, n, stdin);
	if (ret) {
		find = strchr(s, '\n');
		if (find)
			*find = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret;
}
void swap(char *s1, char *s2)
{
	char t;
	t = *s1;
	*s1 = *s2;
	*s2 = t;
}
void reverse(char *s, int n)
{
	static int i = 0;
	if (i < n-1) {
		swap(&s[i++], &s[n-1]);
		reverse(s, n-1);
	}
}