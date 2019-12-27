#include <stdio.h>
#include <string.h>
#define N 100
int i;
int main()
{
	int htoi(char []);
	char a[N];
	gets(a);
	if(htoi(a))
		printf("%d\n",htoi(a));
	return 0;
}

int htoi(char a[]){
	int len,t,sum=0;
	len=strlen(a);
	for(i=0;i<len;i++)
    {
		if(a[i]>='0'&&a[i]<='9'||a[i]>='a'&&a[i]<='f'||a[i]>='A'&&a[i]<='F')
        {
			if(a[i]>='0'&&a[i]<='9')
				t=a[i]-'0';
			else if(a[i]>='a'&&a[i]<='f')
				t=a[i]-'a'+10;
			else
				t=a[i]-'A'+10;
			sum=sum*16+t;
		}
		else
        {
			printf("请输入正确的十六进制数!\n");
			break;
		}
	}
	return sum;
}