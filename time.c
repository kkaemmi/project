#include <stdio.h>
#include <windows.h> //system��ɾ ����ϱ� ���� 
#include <time.h> //_strtime_s�� ����Ұ��� 

FILE *read,*write;
//���� �ð��� ���� 
struct timewrite
{
	char *sf; 
	int y,mon,day;
	int h,m,s;
}
userlist[2];
//���νð��� ���� 
struct studytime
{
	int h,m,s;
	int stop; 
}
timelist[1];
//�ð��� ���� ����ü 
struct tm* now;
time_t now_t;
//�������� 
int result;
int sp=0;//1�϶� start 
int i=0;
int num=0;
int start=0;
char filename[30];
//�Լ� ���� 
void load(char *name);//������ ������ �ҷ���. 
void save();//������ 
void exitcatch(void);//������ 
void starttime();
void log();
void stop();
void totalstudy();
void timeshow();
//�����Լ� 
int main()
{
	//HWND time;
	
	//SetWindowPos(time, HWND_TOPMOST, 0, 0, 600, 300, SWP_NOMOVE);
	//WS_EX_TOPMOST;
	HWND time=FindWindow("ConsoleWindowClass", NULL);
	SetWindowPos(time, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	char command[20];
	char user[20];
	char study[10];//�Է¹��� ���� 
	timelist[0].stop=0;	
	system("mode con: cols=60 lines=13");//���̴� ȭ�� ũ�⸦ �����Ѵ�.
	printf("username(�����̸�)�� �Է����ּ���.\n"); 
	scanf("%s",user);
	sprintf(filename,"%s.txt",user);
//  load(&user);
	printf("command ���: \n+---------------------+\n| start | stop | show |\n+---------------------+\n");
	
	while(1)
	{
		scanf("%s",command);
		//gets(command);
		if(GetKeyState(VK_F2)<0||strstr(command,"start")){
			
			if(sp==0){
				atexit(exitcatch);//����ڰ� �����ϸ� ���� ���¸� �����Ѵ�.
				sp++;
			}
			system("cls");
			starttime();
			start++;
		}
		
		else if(GetKeyState(VK_F1)<0||strstr(command,"show")){
			if(start!=0){
				//system("cls");
				timeshow();
			}
		}
		
		else if(GetKeyState(VK_F10)<0||strstr(command,"stop")){
			if(start!=0){
				system("cls");
				timeshow();
				stop();
			}
		}
		else if(strstr(command,"hardstudy")){
			if(start!=0){	
				char text[100];
				if(num==0){
					printf("hard ���θ���Դϴ�.\n������ �ð� �̻� �������� ������ ��ǻ�Ͱ� �����ϴ�. ");
					printf("\n������ �ð��� �Է��ϼ���.(�ʴ����� �Է�EX:300)= ");
					scanf("%d",&num); 
					sprintf(text,"shutdown -s -t %d -c \"%s\"",219999999,"���ݺ��� �� ��ǻ�ʹ� �ʱ����� �����ߴ�");
					//printf("%s",text);
					system(text);
				}
			}	
		}
		if(num!=0&&num<result){
			num=0;
			system("shutdown -a");
		}
		
	}
	return 0;
}
//Ÿ�̸Ӱ��� �Լ��� ���� 
void starttime()
{
	//printf("user num = %d\n",user);
	
	time(&now_t);
	now=localtime(&now_t);
	userlist[i].sf="start";
	userlist[i].y=now->tm_year+1900;
	userlist[i].mon=now->tm_mon+1;
	userlist[i].day=now->tm_mday;
	userlist[i].h=now->tm_hour;
	userlist[i].m=now->tm_min;
	userlist[i].s=now->tm_sec;
		
	printf("%d�� ",userlist[0].y);
	printf("%d�� ",userlist[0].mon);	
	printf("%d��\n",userlist[0].day);	
	printf("%d�� ",userlist[0].h);
	printf("%d�� ",userlist[0].m);
	printf("%d�ʿ� ���θ� �����մϴ�.\n",userlist[0].s);
	printf("-->");
	
}
/*
//����� �ʿ������� �ϴ� ���� 
void load(char *name)
{
	printf("�ҷ����� ");
	sprintf(filename,"%s.txt",name);
	printf("%s\n",filename); 
	read=fopen(filename,"r+");
	fscanf(read,"%s",&userlist[1].sf);//
	fscanf(read,"%d",&userlist[1].y);//year
	fscanf(read,"%d",&userlist[1].mon);//mon
	fscanf(read,"%d",&userlist[1].day);//day
	fscanf(read,"%d",&userlist[1].h);//h
	fscanf(read,"%d",&userlist[1].m);//m
	fscanf(read,"%d",&userlist[1].s);//s
	fclose(read);
	//return 0;
}
*/
//���� �ð� ���¸� �����ϴ� save�Լ��� ���� 
void save()
{
	//if(save==1){
		log();
		write=fopen(filename,"a+");
		
		fprintf(write,"%s ",userlist[i].sf);//start
		fprintf(write,"%d ",userlist[i].y);//year
		fprintf(write,"%d ",userlist[i].mon);//mon
		fprintf(write,"%d ",userlist[i].day);//day
		fprintf(write,"%d ",userlist[i].h);//h
		fprintf(write,"%d ",userlist[i].m);//m
		fprintf(write,"%d\n",userlist[i].s);//s
		
		fprintf(write,"%s ",userlist[1].sf);//finish
		fprintf(write,"%d ",userlist[1].y);//year
		fprintf(write,"%d ",userlist[1].mon);//mon
		fprintf(write,"%d ",userlist[1].day);//day
		fprintf(write,"%d ",userlist[1].h);//h
		fprintf(write,"%d ",userlist[1].m);//m	
		fprintf(write,"%d\n",userlist[1].s);//s
		fclose(write);
		if(num!=0){
			if(num<result){//�׳� ������������ ���
				system("shutdown -a"); 
				return 0;}
			system("shutdown -a");
			system("shutdown -s -t 1");
		}
}
//���νð��� �����ϴ� �Լ� 
void log() //���νð��� ������. 
{
	totalstudy();
	write = fopen("studytime.txt", "a+");
	fprintf(write, "%d��%d��%d�� ~ ", userlist[i].y, userlist[i].mon, userlist[i].day);
	fprintf(write, "%d��%d��%d�� = ", userlist[1].y, userlist[1].mon, userlist[1].day);
	fprintf(write, "��%d�ð� %d�� %d�ʸ� �����ϼ̽��ϴ�.\n", timelist[0].h, timelist[0].m, timelist[0].s);//h
	fclose(write);
}
//�ð��� �����ִ� �Լ� 
void timeshow() //������ �ð��� ������. 
{
	totalstudy();
	printf("%d�ð� %d�� %d�ʰ����߽��ϴ�.\n-->", timelist[0].h, timelist[0].m, timelist[0].s);
}
//�ð��� ���ߴ� �Լ� 
void stop()
{
	//save=1;
	totalstudy();
	timelist[0].stop=result;
	save();
	printf("�Ͻ� �������Դϴ�.\n�ƹ�Ű�� �Է��ϼ���\n");
	printf("----------------------\n");
	getch();
	starttime(); 
} 
//�� ���νð��� ����ϴ� �Լ� 
void totalstudy()
{
	time(&now_t);
	now = localtime(&now_t);
	userlist[1].sf = "finish";
	userlist[1].y = now->tm_year + 1900;
	userlist[1].mon = now->tm_mon + 1;
	userlist[1].day = now->tm_mday;
	userlist[1].h = now->tm_hour;
	userlist[1].m = now->tm_min;
	userlist[1].s = now->tm_sec;
	//���ݽð�-ó���ð��ϸ� -�ð��� ��µǹǷ� �����ϰ� ���� ������Ѵ�.
	int time1 = userlist[1].h * 3600 + userlist[1].m * 60 + userlist[1].s;
	int time2 = userlist[i].h * 3600 + userlist[i].m * 60 + userlist[i].s;
	result = time1 - time2 + timelist[0].stop;
	int temp = result % 3600;
	timelist[i].h = result / 3600;//0�� ó���ð� 
	timelist[i].m = temp / 60;
	timelist[i].s = result % 60;
}
//�����ϸ� �ڵ����� ����Ǵ� �Լ�. 
void exitcatch(void)
{
	//save=1;
	save();
}