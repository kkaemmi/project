#include <stdio.h>
#include <time.h>
#include <Windows.h>

int alarm(int sec)
{
	Sleep(sec * 1000);
	printf("\a");
}
int test_1()
{
	struct tm* t;
	time_t base = time(NULL);
	int y, mon, day;
	int h, m, s;
	int sel;

	printf("1.시간 설정 2. 종료 : >>");
	scanf_s("%d", &sel);
	t = localtime(&base);
	switch (sel)
	{
	case 1:
		printf("%d년 %d월 %d일 \n", y = t->tm_year + 1900, mon = t->tm_mon + 1, day = t->tm_mday);
		printf("몇 시간 몇 분 몇 초에 알람을 울리게 하게습니까?");
		scanf_s("%d %d %d", &h, &m, &s);
		h *= 3600;
		m *= 60;
		alarm(h);
		alarm(m);
		alarm(s);
		break;
	}
	return 0;
}
