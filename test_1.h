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

	printf("1.�ð� ���� 2. ���� : >>");
	scanf_s("%d", &sel);
	t = localtime(&base);
	switch (sel)
	{
	case 1:
		printf("%d�� %d�� %d�� \n", y = t->tm_year + 1900, mon = t->tm_mon + 1, day = t->tm_mday);
		printf("�� �ð� �� �� �� �ʿ� �˶��� �︮�� �ϰԽ��ϱ�?");
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
