#include <stdio.h>
#include <windows.h> //system명령어를 사용하기 위함 
#include <time.h> //_strtime_s를 사용할거임 

FILE *read,*write;
//현재 시간을 저장 
struct timewrite
{
	char *sf; 
	int y,mon,day;
	int h,m,s;
}
userlist[2];
//공부시간을 저장 
struct studytime
{
	int h,m,s;
	int stop; 
}
timelist[1];
//시간을 위한 구조체 
struct tm* now;
time_t now_t;
//전역변수 
int result;
int sp=0;//1일때 start 
int i=0;
int num=0;
int start=0;
char filename[30];
//함수 선언 
void load(char *name);//저장한 내용을 불러옴. 
void save();//저장함 
void exitcatch(void);//저장함 
void starttime();
void log();
void stop();
void totalstudy();
void timeshow();
//메인함수 
int main()
{
	//HWND time;
	
	//SetWindowPos(time, HWND_TOPMOST, 0, 0, 600, 300, SWP_NOMOVE);
	//WS_EX_TOPMOST;
	HWND time=FindWindow("ConsoleWindowClass", NULL);
	SetWindowPos(time, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	char command[20];
	char user[20];
	char study[10];//입력받을 문자 
	timelist[0].stop=0;	
	system("mode con: cols=60 lines=13");//보이는 화면 크기를 제한한다.
	printf("username(파일이름)을 입력해주세요.\n"); 
	scanf("%s",user);
	sprintf(filename,"%s.txt",user);
//  load(&user);
	printf("command 목록: \n+---------------------+\n| start | stop | show |\n+---------------------+\n");
	
	while(1)
	{
		scanf("%s",command);
		//gets(command);
		if(GetKeyState(VK_F2)<0||strstr(command,"start")){
			
			if(sp==0){
				atexit(exitcatch);//사용자가 종료하면 현재 상태를 저장한다.
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
					printf("hard 공부모드입니다.\n설정한 시간 이상 공부하지 않으면 컴퓨터가 꺼집니다. ");
					printf("\n공부할 시간을 입력하세요.(초단위로 입력EX:300)= ");
					scanf("%d",&num); 
					sprintf(text,"shutdown -s -t %d -c \"%s\"",219999999,"지금부터 이 컴퓨터는 너굴단이 접수했다");
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
//타이머관련 함수를 정의 
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
		
	printf("%d년 ",userlist[0].y);
	printf("%d월 ",userlist[0].mon);	
	printf("%d일\n",userlist[0].day);	
	printf("%d시 ",userlist[0].h);
	printf("%d분 ",userlist[0].m);
	printf("%d초에 공부를 시작합니다.\n",userlist[0].s);
	printf("-->");
	
}
/*
//만들다 필요없어보여서 일단 보류 
void load(char *name)
{
	printf("불러왔음 ");
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
//현재 시간 상태를 저장하는 save함수를 정의 
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
			if(num<result){//그냥 종료했을때를 대비
				system("shutdown -a"); 
				return 0;}
			system("shutdown -a");
			system("shutdown -s -t 1");
		}
}
//공부시간을 저장하는 함수 
void log() //공부시간을 저장함. 
{
	totalstudy();
	write = fopen("studytime.txt", "a+");
	fprintf(write, "%d년%d월%d일 ~ ", userlist[i].y, userlist[i].mon, userlist[i].day);
	fprintf(write, "%d년%d월%d일 = ", userlist[1].y, userlist[1].mon, userlist[1].day);
	fprintf(write, "총%d시간 %d분 %d초를 공부하셨습니다.\n", timelist[0].h, timelist[0].m, timelist[0].s);//h
	fclose(write);
}
//시간을 보여주는 함수 
void timeshow() //공부한 시간을 보여줌. 
{
	totalstudy();
	printf("%d시간 %d분 %d초공부했습니다.\n-->", timelist[0].h, timelist[0].m, timelist[0].s);
}
//시간을 멈추는 함수 
void stop()
{
	//save=1;
	totalstudy();
	timelist[0].stop=result;
	save();
	printf("일시 정지중입니다.\n아무키나 입력하세요\n");
	printf("----------------------\n");
	getch();
	starttime(); 
} 
//총 공부시간을 계산하는 함수 
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
	//지금시간-처음시간하면 -시간이 출력되므로 간단하게 뭔가 해줘야한다.
	int time1 = userlist[1].h * 3600 + userlist[1].m * 60 + userlist[1].s;
	int time2 = userlist[i].h * 3600 + userlist[i].m * 60 + userlist[i].s;
	result = time1 - time2 + timelist[0].stop;
	int temp = result % 3600;
	timelist[i].h = result / 3600;//0이 처음시간 
	timelist[i].m = temp / 60;
	timelist[i].s = result % 60;
}
//종료하면 자동으로 실행되는 함수. 
void exitcatch(void)
{
	//save=1;
	save();
}