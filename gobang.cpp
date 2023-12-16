#include<winsock.h>		/*引入winsock头文件*/
#pragma comment(lib,"ws2_32.lib")
#include<stdio.h> 
#include <graphics.h>
#include<string.h>
#include<bits/stdc++.h>

using namespace std;

#define MAXN 1000

FILE *fp;

struct Node
{
	char name[100];

	int mark;

}three[3];

void choose();

void explation();

void scoring(int n);

void select(); //选择人人模式 

int visb[MAXN][MAXN];//记录黑棋

int visw[MAXN][MAXN];//记录白棋

int bwin;//标记黑棋获胜

int wwin;//标记白棋子获胜

int step;  //记录步数 

int steppc;  //记录人机步数

int flag;   //判断进行人机或人人对战 

int flag2;//退出模式

int px, py;

int player;

static int MAN = 1;

static int COM = -1;

int CD=0; 

char IP[100];

mouse_msg msg = { 0 };

int zqy[2];

struct point

{

	int x;

	int y;

};



int board[MAXN][MAXN];//1是黑棋，-1是白棋，0，表示没有



void CreateMenus()//主菜单

{




	wwin = 0;

	bwin = 0;

	memset(visb, 0, sizeof(visb));

	memset(visw, 0, sizeof(visw));

	flag = 0;

	flag2 = 0;//退出模式



	initgraph(1000, 600, 0);

	//	setcolor(EGERGB(0x0, 0xFF, 0x0));//文字颜色

	  //  setbkmode(TRANSPARENT);//文字填充透明化

	//	setfont(100, 60, "楷体");

	//	outtextxy(200, 0, "五子棋游戏");

	setcolor(EGERGB(228, 228, 228));

	setfont(60, 30, "楷体");

	outtextxy(420, 150, "人机对战");

	setcolor(EGERGB(228, 228, 228));

	setfont(60, 30, "楷体");

	outtextxy(420, 240, "人人对战");

	setcolor(EGERGB(228, 228, 228));

	setfont(60, 30, "楷体");

	outtextxy(420, 330, "游戏排行");

	setcolor(EGERGB(228, 228, 228));

	setfont(60, 30, "楷体");

	outtextxy(420, 420, "退出游戏");

	setcolor(EGERGB(228, 228, 228));

	setbkmode(TRANSPARENT);

	setfont(35, 14, "楷体");

	//  outtextxy(710,500,"Author: Farmer Three");




}





int jud()//人人判断

{

	for (int i = 60; i <= 480; i++)

	{

		for (int j = 60; j <= 480; j++)

		{

			//判断黑棋

			if (visb[i][j] && visb[i + 30][j] && visb[i + 60][j] && visb[i - 30][j] && visb[i - 60][j]) return 1;//横向获胜

			else if (visb[i][j] && visb[i][j + 30] && visb[i][j + 60] && visb[i][j - 30] && visb[i][j - 60]) return 1;//纵向获胜

			else if (visb[i][j] && visb[i + 30][j + 30] && visb[i + 60][j + 60] && visb[i - 30][j - 30] && visb[i - 60][j - 60]) return 1;//斜率为1

			else if (visb[i][j] && visb[i - 30][j + 30] && visb[i - 60][j + 60] && visb[i + 30][j - 30] && visb[i + 60][j - 60]) return 1;//斜率为-1

			//判断白棋

			if (visw[i][j] && visw[i + 30][j] && visw[i + 60][j] && visw[i - 30][j] && visw[i - 60][j]) return 2;//横向获胜

			else if (visw[i][j] && visw[i][j + 30] && visw[i][j + 60] && visw[i][j - 30] && visw[i][j - 60]) return 2;//纵向获胜

			else if (visw[i][j] && visw[i + 30][j + 30] && visw[i + 60][j + 60] && visw[i - 30][j - 30] && visw[i - 60][j - 60]) return 2;//斜率为1

			else if (visw[i][j] && visw[i - 30][j + 30] && visw[i - 60][j + 60] && visw[i + 30][j - 30] && visw[i + 60][j - 60]) return 2;//斜率为-1

		}

	}

}



int judpc()//人机判断

{

	for (int i = 60; i <= 480; i += 30)

	{

		for (int j = 60; j <= 480; j += 30)

		{

			//判断黑棋

			if (board[i][j] == 1 && board[i + 30][j] == 1 && board[i + 60][j] == 1 && board[i - 30][j] == 1 && board[i - 60][j] == 1) return 1;//横向获胜

			else if (board[i][j] == 1 && board[i][j + 30] == 1 && board[i][j + 60] == 1 && board[i][j - 30] == 1 && board[i][j - 60] == 1) return 1;//纵向获胜

			else if (board[i][j] == 1 && board[i + 30][j + 30] == 1 && board[i + 60][j + 60] == 1 && board[i - 30][j - 30] == 1 && board[i - 60][j - 60] == 1) return 1;//斜率为1

			else if (board[i][j] == 1 && board[i - 30][j + 30] == 1 && board[i - 60][j + 60] == 1 && board[i + 30][j - 30] == 1 && board[i + 60][j - 60] == 1) return 1;//斜率为-1

			//判断白棋子

			if (board[i][j] == -1 && board[i + 30][j] == -1 && board[i + 60][j] == -1 && board[i - 30][j] == -1 && board[i - 60][j] == -1) return 2;//横向获胜

			else if (board[i][j] == -1 && board[i][j + 30] == -1 && board[i][j + 60] == -1 && board[i][j - 30] == -1 && board[i][j - 60] == -1) return 2;//纵向获胜

			else if (board[i][j] == -1 && board[i + 30][j + 30] == -1 && board[i + 60][j + 60] == -1 && board[i - 30][j - 30] == -1 && board[i - 60][j - 60] == -1) return 2;//斜率为1

			else if (board[i][j] == -1 && board[i - 30][j + 30] == -1 && board[i - 60][j + 60] == -1 && board[i + 30][j - 30] == -1 && board[i + 60][j - 60] == -1) return 2;//斜率为-1

		}

	}

}



void CreatePCBoard()//人机棋盘

{

	setbkcolor(EGERGB(173, 92, 45));//设置背景颜色

	setcolor(BLACK);

	for (int i = 60; i < 510; i += 30)

	{

		line(i, 60, i, 480);

	}

	for (int j = 60; j < 510; j += 30)

	{

		line(60, j, 480, j);

	}

	setcolor(EGERGB(0xFF, 0x0, 0x0));

	setbkmode(TRANSPARENT);

	setfont(40, 15, "楷体");

	outtextxy(750, 100, "PVP");

	setfillcolor(EGERGB(0xFF, 0x0, 0x0));

	setcolor(EGERGB(0xFF, 0xFF, 0x0));

	xyprintf(650, 40, "当前共计下了0棋");

	//P1信息

	setcolor(EGERGB(255, 255, 255));

	setfont(40, 15, "楷体");

	xyprintf(700, 150, "PC(白):0");

	//P2信息

	setcolor(EGERGB(0, 0, 0));

	setfont(40, 15, "楷体");

	xyprintf(700, 200, "Player(黑):0");



	setfillcolor(EGERGB(0xFF, 0x0, 0x0));

	bar(700, 400, 850, 450);

	setcolor(EGERGB(0x0, 0xFF, 0x0));

	outtextxy(750, 400, "退出");

}



void CreatePVPboard()//人人棋盘

{

	setbkcolor(EGERGB(173, 92, 45));//设置背景颜色

	setcolor(BLACK);







	for (int i = 60; i < 510; i += 30)

	{

		line(i, 60, i, 480);

	}

	for (int j = 60; j < 510; j += 30)

	{

		line(60, j, 480, j);

	}
















	setcolor(EGERGB(0xFF, 0x0, 0x0));

	setbkmode(TRANSPARENT);

	setfont(40, 15, "楷体");

	outtextxy(750, 100, "PVP");

	setfillcolor(EGERGB(0xFF, 0x0, 0x0));

	setcolor(EGERGB(0xFF, 0xFF, 0x0));

	xyprintf(650, 40, "当前共计下了0棋");

	//P1信息

	setcolor(EGERGB(255, 255, 255));

	setfont(40, 15, "楷体");

	xyprintf(700, 150, "P1(白):0");

	//P2信息

	setcolor(EGERGB(0, 0, 0));

	setfont(40, 15, "楷体");

	xyprintf(700, 200, "P2(黑):0");



	setfillcolor(EGERGB(0xFF, 0x0, 0x0));

	bar(700, 400, 850, 450);

	setcolor(EGERGB(0x0, 0xFF, 0x0));

	outtextxy(750, 400, "退出");

}



void PVPshow()//显示当前棋盘状况

{

	setbkcolor(EGERGB(173, 92, 45));//设置背景颜色

	setcolor(BLACK);



	PIMAGE img[2];

	img[0] = newimage();
	img[1] = newimage();
	getimage(img[0], "drawing\\hei.png");
	getimage(img[1], "drawing\\bai.png");





	for (int i = 60; i < 510; i += 30)

	{

		line(i, 60, i, 480);

	}

	for (int j = 60; j < 510; j += 30)

	{

		line(60, j, 480, j);

	}



	for (int i = 60; i <= 480; i += 30)

	{

		for (int j = 60; j <= 480; j += 30)

		{

			if (visw[i][j])

			{
				putimage(i - 15, j - 15, img[1]);
			}

			if (visb[i][j])

			{
				putimage(i - 15, j - 15, img[0]);
			}

		}

	}

	setcolor(EGERGB(0xFF, 0xFF, 0x0));



	setbkmode(TRANSPARENT);

	setfont(40, 15, "楷体");

	xyprintf(650, 40, "当前共计下了%d棋", step - 1);



	setcolor(EGERGB(0xFF, 0x0, 0x0));

	setbkmode(TRANSPARENT);

	setfont(40, 15, "楷体");

	outtextxy(750, 100, "PVP");



	//p1:

	setcolor(EGERGB(255, 255, 255));

	setfont(40, 15, "楷体");

	xyprintf(700, 150, "P1(黑):%d", (step - 1) / 2 + (step - 1) % 2);


	//p2

	setcolor(EGERGB(0, 0, 0));

	setfont(40, 15, "楷体");

	xyprintf(700, 200, "P2(白):%d", (step - 1) / 2);



	setfillcolor(EGERGB(0xFF, 0x0, 0x0));

	bar(700, 400, 850, 450);

	setcolor(EGERGB(0x0, 0xFF, 0x0));

	outtextxy(750, 400, "退出");

	if (bwin)

	{

		setcolor(EGERGB(0, 0, 0));

		setbkmode(TRANSPARENT);

		setfont(20, 10, "楷体");

		outtextxy(630, 350, "黑棋获胜，点击下方回到主菜单");

	}

	else if (wwin)

	{

		setcolor(EGERGB(255, 255, 255));

		setbkmode(TRANSPARENT);

		setfont(20, 10, "楷体");

		outtextxy(650, 350, "白棋获胜,点击下方退出键回到主菜单");

	}

}

void PVEshow()//显示当前人机棋盘状况

{

	PIMAGE img[2];

	img[0] = newimage();
	img[1] = newimage();
	getimage(img[0], "drawing\\hei.png");
	getimage(img[1], "drawing\\bai.png");



	setbkcolor(EGERGB(173, 92, 45));//设置背景颜色

	setcolor(BLACK);

	for (int i = 60; i < 510; i += 30)

	{

		line(i, 60, i, 480);

	}

	for (int j = 60; j < 510; j += 30)

	{

		line(60, j, 480, j);

	}



	for (int i = 60; i <= 480; i++)

	{

		for (int j = 60; j <= 480; j++)

		{

			if (board[i][j] == -1)

			{


				putimage(i - 15, j - 15, img[1]);
			}

			if (board[i][j] == 1)

			{

				putimage(i - 15, j - 15, img[0]);
			}

		}

	}

	setcolor(EGERGB(0xFF, 0xFF, 0x0));



	setbkmode(TRANSPARENT);

	setfont(40, 15, "楷体");

	xyprintf(650, 40, "当前共计下了%d棋", step + steppc);



	setcolor(EGERGB(0xFF, 0x0, 0x0));

	setbkmode(TRANSPARENT);

	setfont(40, 15, "楷体");

	outtextxy(750, 100, "PVP");



	//p1:

	setcolor(EGERGB(255, 255, 255));

	setfont(40, 15, "楷体");

	xyprintf(700, 150, "PC(白):%d", steppc);



	//p2

	setcolor(EGERGB(0, 0, 0));

	setfont(40, 15, "楷体");

	xyprintf(700, 200, "Player(黑):%d", step);



	setfillcolor(EGERGB(0xFF, 0x0, 0x0));

	bar(700, 400, 850, 450);

	setcolor(EGERGB(0x0, 0xFF, 0x0));

	outtextxy(750, 400, "退出");







	setfillcolor(EGERGB(0xFF, 0x0, 0x0));

	bar(700, 280, 850, 330);

	setcolor(EGERGB(0x0, 0xFF, 0x0));

	outtextxy(715, 280, "悔棋一步");










	if (bwin)

	{

		setcolor(EGERGB(0, 0, 0));

		setbkmode(TRANSPARENT);

		setfont(20, 10, "楷体");

		outtextxy(630, 350, "玩家(黑)获胜，点击下方回到主菜单");

		if (CD)
		{

			setfillcolor(EGERGB(0xFF, 0x0, 0x0));

			bar(700, 500, 850, 550);

			setfont(40, 15, "楷体");

			setcolor(EGERGB(0x0, 0xFF, 0x0));

			outtextxy(710, 500, "记录排行");

		}

	}

	else if (wwin)

	{

		setcolor(EGERGB(255, 255, 255));

		setbkmode(TRANSPARENT);

		setfont(20, 10, "楷体");

		outtextxy(650, 350, "电脑(白)获胜,点击下方退出键回到主菜单");

	}

}

void inter1()//创建人人对战

{

	int k = 0;

	int b1, b2, b3, i, j;

	int a[10];

	int net[2];

	net[0] = 0;

	net[1] = 0;

	bwin = 0;

	wwin = 0;

	CreatePVPboard();

	step = 1;//步数初始化

	/*-----------------------------------------*/
	/*------------定义变量---------------------*/
	/*-----------------------------------------*/
	char Sendbuf[100];		/*发送数据的缓冲区*/
	char Sendbuf1[100];		/*发送数据的缓冲区*/
	char Receivebuf[100];	/*接受数据的缓冲区*/
	int SendLen;			/*发送数据的长度*/
	int	ReceiveLen;			/*接收数据的长度*/
	int Length;				/*表示SOCKADDR的大小*/

	SOCKET socket_server;	/*定义服务器套接字*/
	SOCKET socket_receive;  /*定义用于连接套接字*/

	SOCKADDR_IN Server_add;	/*服务器地址信息结构*/
	SOCKADDR_IN Client_add;	/*客户端地址信息结构*/

	WORD wVersionRequested;	/*字（word）：unsigned short*/
	WSADATA wsaData;		/*库版本信息结构*/
	int error;				/*表示错误*/

	/*-----------------------------------------*/
	/*------------初始化套接字库---------------*/
	/*-----------------------------------------*/
	/*定义版本类型。将两个字节组合成一个字，前面是第字节，后面是高字节*/
	wVersionRequested = MAKEWORD(2, 2);
	/*加载套接字库，初始化Ws2_32.dll动态链接库*/
	error = WSAStartup(wVersionRequested, &wsaData);
	if (error != 0)
	{
		outtextxy(500, 400, "加载套接字失败！");
		//	return 0;	/*程序结束*/
	}
	/*判断请求加载的版本号是否符合要求*/
	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();	/*不符合，关闭套接字库*/
	//	return 0;		/*程序结束*/
	}

	/*-----------------------------------------*/
	/*------------设置连接地址-----------------*/
	/*-----------------------------------------*/
	Server_add.sin_family = AF_INET;/*地址家族，对于必须是AF_INET，注意只有它不是网络网络字节顺序*/
	Server_add.sin_addr.S_un.S_addr = htonl(INADDR_ANY);/*主机地址*/
	Server_add.sin_port = htons(8888);/*端口号*/

	/*------------创建套接字-------------------*/
	/*AF_INET表示指定地址族，SOCK_STREAM表示流式套接字TCP，特定的地址家族相关的协议。*/
	socket_server = socket(AF_INET, SOCK_STREAM, 0);

	/*-----------------------------------------*/
	/*---绑定套接字到本地的某个地址和端口上----*/
	/*-----------------------------------------*/
			/*socket_server为套接字，(SOCKADDR*)&Server_add为服务器地址*/
	if (bind(socket_server, (SOCKADDR*)&Server_add, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		outtextxy(500, 400, "绑定失败\n");
	}

	/*-----------------------------------------*/
	/*------------设置套接字为监听状态---------*/
	/*-----------------------------------------*/
		/*监听状态，为连接做准备，最大等待的数目为5*/
	if (listen(socket_server, 5) < 0)
	{
		outtextxy(500, 400, "监听失败\n");
	}

	/*-----------------------------------------*/
	/*------------接受连接---------------------*/
	/*-----------------------------------------*/
	Length = sizeof(SOCKADDR);
	/*接受客户端的发送请求,等待客户端发送connect请求*/
	socket_receive = accept(socket_server, (SOCKADDR*)&Client_add, &Length);
	if (socket_receive == SOCKET_ERROR)
	{
		outtextxy(500, 400, "接受连接失败");
	}

	/*-----------------------------------------*/
	/*--------------进行聊天-------------------*/
	/*-----------------------------------------*/



	int Flag = 0;

	int jb = 0;













	for (; is_run(); )

	{





		msg = getmouse();

		//边界条件
		if (jb > 0 && (int)msg.is_left() && (int)msg.x >= ((int)msg.x - (int)msg.x % 30) - 14 && (int)msg.x <= ((int)msg.x - (int)msg.x % 30) + 14 && (int)msg.y >= ((int)msg.y - (int)msg.y % 30) - 14 && (int)msg.y <= ((int)msg.y - (int)msg.y % 30) + 14 && visw[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] == 0 && visb[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] == 0 && msg.x >= 50 && msg.x <= 485 && msg.y >= 55 && msg.y <= 485)
		{

			step++;//每走一步，步数+1

			k++;

			Flag = 1;


			visw[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] = 1;//偶数下白棋;


			if (jud() == 1) bwin = 1;

			else if (jud() == 2) wwin = 1;


			cleardevice();

			PVPshow();

			//   if(bwin||wwin) break;



		}


		if (jb == 0 || (k % 2 == 0 && k != 0 && Flag == 1))
		{

			jb++;

			if (k % 2 == 0 && k != 0 && Flag == 1)
			{


				Flag = 0;

				net[0] = (int)msg.x - (int)msg.x % 30;

				net[1] = (int)msg.y - (int)msg.y % 30;

				memset(Sendbuf, 0x00, sizeof(char) * 100);
				memset(Sendbuf1, 0x00, sizeof(char) * 100);



				sprintf(Sendbuf, "%d", net[0]);
				sprintf(Sendbuf1, "%d", net[1]);
				strcat(Sendbuf, ",");
				strcat(Sendbuf, Sendbuf1);


				SendLen = send(socket_receive, Sendbuf, 100, 0);
				//发送数据
				if (SendLen < 0)
				{
			//		outtextxy(600, 400, "发送失败!\n");
				}
			}
			if (bwin || wwin)
			{
				closesocket(socket_receive);	/*释放客户端的套接字资源*/
				closesocket(socket_server);/*释放套接字资源*/
				WSACleanup();/*关闭动态链接库*/
				break;
			}

			//--------------接收数据过程---------------
			ReceiveLen = recv(socket_receive, Receivebuf, 100, 0);	//接受数据
			if (ReceiveLen < 0)
			{
				outtextxy(600, 400, "对方已退出");
				closesocket(socket_receive);	/*释放客户端的套接字资源*/
				closesocket(socket_server);/*释放套接字资源*/
				WSACleanup();/*关闭动态链接库*/
				break;
			}
			else
			{
				step++;
				for (i = 0; i < 10; i++)
				{
					a[i] = 5;

					//cleardevice();
					  //PVPshow();
				}

				for (i = 0; Receivebuf[i] != ','; i++)
				{

					a[i] = Receivebuf[i] - 48;

				}
				b3 = a[2]; b2 = a[1]; b1 = a[0];
				if (b3 != 5)
					net[0] = b1 * 100 + b2 * 10 + b3;
				else
					net[0] = b1 * 10 + b2;

				for (j = i + 1; Receivebuf[j] != '\0'; j++)
					a[j - 1] = Receivebuf[j] - 48;
				b3 = a[i + 2];
				b2 = a[i + 1];
				b1 = a[i];
				if (b3 != 5)
					net[1] = b1 * 100 + b2 * 10 + b3;
				else
					net[1] = b1 * 10 + b2;

				visb[net[0]][net[1]] = 1;



				if (jud() == 1) bwin = 1;

				else if (jud() == 2) wwin = 1;


				cleardevice();
				PVPshow();

				if (bwin || wwin)
				{
					closesocket(socket_receive);	/*释放客户端的套接字资源*/
					closesocket(socket_server);/*释放套接字资源*/
					WSACleanup();/*关闭动态链接库*/
					break;
				}

			}

		}

		if (k % 2 != 0 && k != 0)
			k++;






		if ((bwin || wwin) && (int)msg.is_down() && (int)msg.x >= 700 && msg.x <= 850 && msg.y >= 400 && msg.y <= 450)

		{

			cleardevice();

			CreateMenus();

			choose();

		}




	}

}



int inter2()//加入人人对战

{
	int jb = 1;

	int k = 0;

	int b1, b2, b3, i, j;

	int a[10];

	int net[2];

	net[0] = 0;

	net[1] = 0;

	bwin = 0;

	wwin = 0;

	CreatePVPboard();

	/*-----------------------------------------*/
/*------------定义变量---------------------*/
/*-----------------------------------------*/
	char Sendbuf[100];				/*发送数据的缓冲区*/
	char Receivebuf[100];			/*接受数据的缓冲区*/
	int	SendLen;					/*发送数据的长度*/
	int	ReceiveLen;					/*接收数据的长度*/
	char Receivebuf1[100];			/*接受数据的缓冲区*/
	char Sendbuf1[100];				/*发送数据的缓冲区*/

	SOCKET socket_send;				/*定义套接字*/

	SOCKADDR_IN Server_add;			/*服务器地址信息结构*/

	WORD wVersionRequested;			/*字（word）：unsigned short*/
	WSADATA wsaData;				/*库版本信息结构*/
	int error;						/*表示错误*/

	/*-----------------------------------------*/
	/*------------初始化套接字库---------------*/
	/*-----------------------------------------*/
				/*定义版本类型。将两个字节组合成一个字，前面是第字节，后面是高字节*/
	wVersionRequested = MAKEWORD(2, 2);
	/*加载套接字库，初始化Ws2_32.dll动态链接库*/
	error = WSAStartup(wVersionRequested, &wsaData);
	if (error != 0)
	{
		outtextxy(500, 400, "加载套接字失败！");
		//	return 0;					/*程序结束*/
	}
	/*判断请求加载的版本号是否符合要求*/
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();				/*不符合，关闭套接字库*/
		//return 0;					/*程序结束*/
	}

	/*-----------------------------------------*/
	/*------------设置服务器地址---------------*/
	/*-----------------------------------------*/
	Server_add.sin_family = AF_INET;/*地址家族，对于必须是AF_INET，注意只有它不是网络网络字节顺序*/
	/*服务器的地址，将一个点分十进制表示为IP地址，inet_ntoa是将地址转成字符串*/
	Server_add.sin_addr.S_un.S_addr = inet_addr(IP);
	Server_add.sin_port = htons(8888);/*端口号*/

	/*-----------------------------------------*/
	/*-------------进行连接服务器--------------*/
	/*-----------------------------------------*/
	/*客户端创建套接字，但是不需要绑定的，只需要和服务器建立起连接就可以了，*/
	/*socket_sendr表示的是套接字，Server_add服务器的地址结构*/
	socket_send = socket(AF_INET, SOCK_STREAM, 0);

	/*-----------------------------------------*/
	/*-------------创建用于连接的套接字--------*/
	/*-----------------------------------------*/
	/*AF_INET表示指定地址族，SOCK_STREAM表示流式套接字TCP，特定的地址家族相关的协议。*/
	if (connect(socket_send, (SOCKADDR*)&Server_add, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		jb = 0;

		outtextxy(500, 400, "连接失败!");
	}
	else
	{
		outtextxy(500, 400, "连接成功!");
	}


	int Flag = 0;


	step = 1;//步数初始化

	for (; is_run();)

	{





		msg = getmouse();

		//边界条件
		if ((int)msg.is_left() && (int)msg.x >= ((int)msg.x - (int)msg.x % 30) - 14 && (int)msg.x <= ((int)msg.x - (int)msg.x % 30) + 14 && (int)msg.y >= ((int)msg.y - (int)msg.y % 30) - 14 && (int)msg.y <= ((int)msg.y - (int)msg.y % 30) + 14 && visw[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] == 0 && visb[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] == 0 && msg.x >= 50 && msg.x <= 485 && msg.y >= 55 && msg.y <= 485 && jb)
		{

			step++;//每走一步，步数+1


			k++;

			Flag = 1;

			visb[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] = 1;//奇数下黑棋//取余是为了精确计算

			if (jud() == 1) bwin = 1;

			else if (jud() == 2) wwin = 1;

			cleardevice();

			PVPshow();

			//    if(bwin||wwin) break;  

		}


		if (k % 2 == 0 && k != 0 && Flag == 1)
		{


			Flag = 0;
			net[0] = (int)msg.x - (int)msg.x % 30;

			net[1] = (int)msg.y - (int)msg.y % 30;

			memset(Sendbuf, 0x00, sizeof(char) * 100);
			memset(Sendbuf1, 0x00, sizeof(char) * 100);



			sprintf(Sendbuf, "%d", net[0]);
			sprintf(Sendbuf1, "%d", net[1]);
			strcat(Sendbuf, ",");
			strcat(Sendbuf, Sendbuf1);


			SendLen = send(socket_send, Sendbuf, 100, 0);

			if (SendLen < 0)
			{
			//	outtextxy(500, 400, "发送失败!");
			}
			if (bwin || wwin) break;

			//--------------接收数据过程---------------
			ReceiveLen = recv(socket_send, Receivebuf, 100, 0);	//接受数据
			if (ReceiveLen < 0)
			{
						outtextxy(500,400,"对方已退出");
						closesocket(socket_send);/*释放套接字资源*/
						WSACleanup();/*关闭动态链接库*/
						
						break;
			}
			else
			{
				step++;
				for (i = 0; i < 10; i++)

					a[i] = 5;



				for (i = 0; Receivebuf[i] != ','; i++)
				{

					a[i] = Receivebuf[i] - 48;

				}
				b3 = a[2]; b2 = a[1]; b1 = a[0];
				if (b3 != 5)
					net[0] = b1 * 100 + b2 * 10 + b3;
				else
					net[0] = b1 * 10 + b2;

				for (j = i + 1; Receivebuf[j] != '\0'; j++)
					a[j - 1] = Receivebuf[j] - 48;
				b3 = a[i + 2];
				b2 = a[i + 1];
				b1 = a[i];
				if (b3 != 5)
					net[1] = b1 * 100 + b2 * 10 + b3;
				else
					net[1] = b1 * 10 + b2;

				visw[net[0]][net[1]] = 1;



				if (jud() == 1) bwin = 1;

				else if (jud() == 2) wwin = 1;

				cleardevice();

				PVPshow();

				if (bwin || wwin)
				{
					WSACleanup();/*关闭动态链接库*/

					break;
				}
			}

		}


		if (k % 2 != 0 && k != 0)
			k++;

		if ((bwin || wwin || jb == 0) && (int)msg.is_down() && (int)msg.x >= 700 && msg.x <= 850 && msg.y >= 400 && msg.y <= 450)

		{

			cleardevice();

			CreateMenus();

			choose();

		}






	}

}


void pvp()//人人对战

{

	bwin = 0;

	wwin = 0;

	CreatePVPboard();

	step = 1;//步数初始化

	for (; is_run(); )

	{





		msg = getmouse();

		//边界条件
		if ((int)msg.is_left() && (int)msg.x >= ((int)msg.x - (int)msg.x % 30) - 14 && (int)msg.x <= ((int)msg.x - (int)msg.x % 30) + 14 && (int)msg.y >= ((int)msg.y - (int)msg.y % 30) - 14 && (int)msg.y <= ((int)msg.y - (int)msg.y % 30) + 14 && visw[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] == 0 && visb[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] == 0 && msg.x >= 50 && msg.x <= 485 && msg.y >= 55 && msg.y <= 485)
		{

			step++;//每走一步，步数+1

			if ((step) & 1)

			{

				visb[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] = 1;//奇数下黑棋//取余是为了精确计算
			}

			if ((step) % 2 == 0)

			{

				visw[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] = 1;//偶数下白棋;

			}

			if (jud() == 1) bwin = 1;

			else if (jud() == 2) wwin = 1;


			cleardevice();

			PVPshow();

			if (bwin || wwin) break;





		}


		if ((int)msg.is_down() && (int)msg.x >= 700 && msg.x <= 850 && msg.y >= 400 && msg.y <= 450)

		{

			cleardevice();

			CreateMenus();

			choose();

		}






	}

}





void pcposition() //人工智障下棋点判断 

{



	for (int i = 60; i <= 480; i += 30)

	{

		for (int j = 60; j <= 480; j += 30)

		{



			if (board[i][j] == 1 && board[i + 30][j] == 1)
			{
				if (board[i - 30][j] == 0)
				{
					px = i - 30;
					py = j;
				}
				else
					if (board[i + 60][j] == 0)
					{
						px = i + 60;
						py = j;
					}
			}
			else if (board[i][j] == 1 && board[i][j + 30] == 1)
			{
				if (board[i][j - 30] == 0)
				{
					px = i;
					py = j - 30;
				}
				else if (board[i][j + 60] == 0)
				{
					px = i;
					py = j + 60;
				}
			}
			else
				if (board[i][j] == 1 && board[i + 30][j + 30] == 1)
				{
					if (board[i - 30][j - 30] == 0)
					{
						px = i - 30;
						py = j - 30;
					}
					else
						if (board[i + 60][j + 60] == 0)
						{
							px = i + 60;
							py = j + 60;
						}
				}
				else
					if (board[i][j] == 1 && board[i - 30][j + 30] == 1)
					{
						if (board[i - 60][j + 60] == 0)
						{
							px = i - 60;
							py = j + 60;
						}
						else
							if (board[i + 30][j - 30] == 0)
							{
								px = i + 30;
								py = j - 30;
							}

					}


		}
	}



	if (step == 1)
	{
		srand((int)time(NULL));

		px = rand() % 480 + 60;

		py = rand() % 480 + 60;

		while (px % 30 != 0 || py % 30 != 0 || board[px][py] == 1 || board[px][py] == -1)
		{
			px = rand() % 480 + 60;

			py = rand() % 480 + 60;

		}
	}











	int dx, dy;
	/*
		srand((int)time(NULL));

		px=rand()%480+60;

		py=rand()%480+60;

		while(board[px-px%30][py-py%30]==1||board[px-px%30][py-py%30]==-1)

		{

			px=rand()%421+60;

			py=rand()%421+60;

		}  */

}

int qiju[480][480][8][2];

int oldp[480][480];

int newp[480][480];

int a1[1000][1000];

int a2[1000][1000];

int win;







int caculate(int oldp[480][480], int qiuju[480][480][8][2])//棋局评估

{

	int k;

	int cnt;

	int tx, ty;

	int dirx[8] = { 0,30,30,30,0,-30,-30,-30 };//八个方向

	int diry[8] = { 30,30,0,-30,-30,-30,0,30 };//八个方向

	for (int i = 60; i <= 480; i += 30)

	{

		for (int j = 60; j <= 480; j += 30)

		{

			if (oldp[i][j] == 0)//此处为空

			{

				for (int k = 0; k < 8; k++)

				{

					tx = i;

					ty = j;

					cnt = 0;

					for (int t = 0; t < 5; t++)

					{

						tx += dirx[k];

						ty += diry[k];

						if (tx < 60 || tx>480 || ty < 60 || ty>480)

						{

							break;

						}

						if (oldp[tx][ty] == 1)//黑棋

						{

							cnt++;

						}

						else break;

					}

					qiju[i][j][k][0] = cnt;

					//白棋

					cnt = 0;

					tx = i;

					ty = j;

					for (int t = 0; t < 5; t++)

					{

						tx += dirx[k];

						ty += diry[k];

						if (tx < 60 || tx>480 || ty < 60 || ty>480)

						{

							break;

						}

						if (oldp[tx][ty] == -1)

						{

							cnt++;

						}

						else break;

					}

					qiju[i][j][k][1] = cnt;

				}

			}

		}

	}

}



int naiveline()

{

	for (int i = 60; i <= 480; i += 30)

	{

		for (int j = 60; j <= 480; j += 30)

		{

			if (board[i][j] == 0)

			{

				int win = 0;

				for (int k = 0; k < 4; k++)

				{

					if (qiju[i][j][k][0] + qiju[i][j][k + 4][0] >= 4)

					{

						win += 10000;

					}

					else if (qiju[i][j][k][0] + qiju[i][j][k + 4][0] == 3)

					{

						win += 1000;

					}

					else if (qiju[i][j][k][0] + qiju[i][j][k + 4][0] == 2)

					{

						win += 100;

					}

					else if (qiju[i][j][k][0] + qiju[i][j][k + 4][0] == 1)

					{

						win += 10;

					}

				}

				a1[i][j] = win;//黑棋

				win = 0;

				for (int k = 0; k < 4; k++)

				{

					if (qiju[i][j][k][1] + qiju[i][j][k + 4][1] >= 4)

					{

						win += 10000;

					}

					else if (qiju[i][j][k][1] + qiju[i][j][k + 4][1] == 3)

					{

						win += 1000;

					}

					else if (qiju[i][j][k][1] + qiju[i][j][k + 4][1] == 2)

					{

						win += 100;

					}

					else if (qiju[i][j][k][1] + qiju[i][j][k + 4][1] == 1)

					{

						win += 10;

					}

				}

				a2[i][j] = win;//白棋子

			}

		}

	}

}



void AIprotect()//防守型AI

{

	int x, y;

	int k = 0;

	int x1 = 270, y1 = 270;

	int x2 = 270, y2 = 270;



	for (int i = 60; i <= 480; i += 30)

	{

		for (int j = 60; j <= 480; j += 30)

		{

			oldp[i][j] = board[i][j];

			newp[i][j] = board[i][j];

		}

	}

	memset(qiju, 0, sizeof(qiju));

	memset(a1, 0, sizeof(a1));

	memset(a2, 0, sizeof(a2));

	caculate(oldp, qiju);

	naiveline();

	for (int i = 60; i <= 480; i += 30)

	{

		for (int j = 60; j <= 480; j += 30)

		{

			if (a2[x2][y2] < a2[i][j])

			{

				x2 = i;

				y2 = j;

			}

		}

	}

	for (int i = 60; i <= 480; i += 30)

	{

		for (int j = 60; j <= 480; j += 30)

		{

			if (a1[x1][y1] < a1[i][j])

			{

				x1 = i;

				y1 = j;

			}

		}

	}

	if (a2[x2][y2] > a1[x1][y1])

	{

		px = x2;

		py = y2;

	}

	else

	{

		px = x1;

		py = y1;

	}

}







void pveeasy()//人工智障

{

	int zqy[2];

	zqy[0] = zqy[1] = 0;

	memset(board, 0, sizeof(board));//清空棋盘

	int flag3 = 0;

	int k = 0;

	bwin = 0;

	wwin = 0;

	CreatePCBoard();

	step = 0;

	steppc = 0;

	AIprotect();

	flag3 = 0;

	steppc++;

	board[px - px % 30][py - py % 30] = -1;

	cleardevice();

	PVEshow();

	for (; is_run();)

	{

		msg = getmouse();

		if ((int)msg.is_left() && (int)msg.x >= ((int)msg.x - (int)msg.x % 30) - 14 && (int)msg.x <= ((int)msg.x - (int)msg.x % 30) + 14 && (int)msg.y >= ((int)msg.y - (int)msg.y % 30) - 14 && (int)msg.y <= ((int)msg.y - (int)msg.y % 30) + 14 && board[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] == 0 && msg.x >= 50 && msg.x <= 485 && msg.y >= 55 && msg.y <= 485)
		{
			k = 1;

			flag3 = 1;

			step++;

			board[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] = 1;//奇数下黑棋//取余是为了精确计算

			zqy[0] = (int)msg.x - (int)msg.x % 30;

			zqy[1] = (int)msg.y - (int)msg.y % 30;

			cleardevice();

			PVEshow();

			if (judpc() == 1)

			{

				bwin = 1;

				break;

			}

		}


		if ((int)msg.is_down() && (int)msg.x >= 700 && msg.x <= 850 && msg.y >= 400 && msg.y <= 450)     //游戏退出 

		{

			cleardevice();

			CreateMenus();

			choose();
		}


		if (flag3)

		{

			pcposition();

			flag3 = 0;

			steppc++;

			board[px][py] = -1;

			cleardevice();

			PVEshow();

			if (judpc() == 2)

			{

				wwin = 1;

				break;

			}

		}

		if ((int)msg.is_down() && (int)msg.x >= 700 && msg.x <= 850 && msg.y >= 280 && msg.y <= 330 && step > 0 && k)     //悔棋功能 k判断是否只能悔棋一步，不允许连续悔棋两以上步 
		{
			k = 0;

			step--;         //人步数退回一步 

			steppc--;          //PC步数退回一步 

			board[px][py] = 0;      //人机相应下棋点重置 

			board[zqy[0]][zqy[1]] = 0;          //人相应下棋点重置 

			cleardevice();

			PVEshow();

		}

	}

	cleardevice();

	PVEshow();

}







void pve()//中等难度

{
	int zqy[2];

	zqy[0] = zqy[1] = 0;

	memset(board, 0, sizeof(board));//清空棋盘

	int flag3 = 0;

	int k = 0;

	bwin = 0;

	wwin = 0;

	CreatePCBoard();

	step = 0;

	steppc = 0;

	AIprotect();

	flag3 = 0;

	steppc++;

	board[px - px % 30][py - py % 30] = -1;

	cleardevice();

	PVEshow();

	for (; is_run();)

	{

		msg = getmouse();
		//出界条件以及下子位置判断 
		if ((int)msg.is_left() && (int)msg.x >= ((int)msg.x - (int)msg.x % 30) - 14 && (int)msg.x <= ((int)msg.x - (int)msg.x % 30) + 14 && (int)msg.y >= ((int)msg.y - (int)msg.y % 30) - 14 && (int)msg.y <= ((int)msg.y - (int)msg.y % 30) + 14 && board[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] == 0 && msg.x >= 50 && msg.x <= 485 && msg.y >= 55 && msg.y <= 485)
		{

			k = 1;

			flag3 = 1;

			step++;

			board[(int)msg.x - (int)msg.x % 30][(int)msg.y - (int)msg.y % 30] = 1;//奇数下黑棋//取余是为了精确计算

			zqy[0] = (int)msg.x - (int)msg.x % 30;

			zqy[1] = (int)msg.y - (int)msg.y % 30;

			cleardevice();

			PVEshow();

			if (judpc() == 1)

			{

				bwin = 1;

				if ((int)msg.is_down() && (int)msg.x >= 700 && msg.x <= 850 && msg.y >= 400 && msg.y <= 450)     //游戏退出 

				{

					cleardevice();

					CreateMenus();

					choose();

				}



			}

		}

		if ((int)msg.is_down() && (int)msg.x >= 700 && msg.x <= 850 && msg.y >= 500 && msg.y <= 550 && bwin)
		{

			cleardevice();

			scoring(step);

		}





		if ((int)msg.is_down() && (int)msg.x >= 700 && msg.x <= 850 && msg.y >= 400 && msg.y <= 450)         //游戏退出 

		{

			cleardevice();

			CreateMenus();

			choose();

		}










		if (flag3)

		{

			AIprotect();

			flag3 = 0;

			steppc++;

			board[px - px % 30][py - py % 30] = -1;

			cleardevice();

			PVEshow();

			if (judpc() == 2)

			{

				wwin = 1;

				break;

			}

		}

		if ((int)msg.is_down() && (int)msg.x >= 700 && msg.x <= 850 && msg.y >= 280 && msg.y <= 330 && step > 0 && k)     //悔棋功能 k判断是否只能悔棋一步，不允许连续悔棋两步 
		{
			k = 0;

			step--;         //人步数退回一步 

			steppc--;          //PC步数退回一步 

			board[px - px % 30][py - py % 30] = 0;      //人相应下棋点重置 

			board[zqy[0]][zqy[1]] = 0;          //人相应下棋点重置 

			cleardevice();

			PVEshow();

		}



	}



	cleardevice();

	PVEshow();

}







void createPC2()        //人机大战 

{

	PIMAGE img;
	img = newimage();
	getimage(img, "drawing\\three1.jpg");
	putimage(0, 0, img);



	int flag = 0;



	for (; is_run(); delay_fps(600))//鼠标操作

	{

		setbkmode(TRANSPARENT);//文字填充透明化

		if (msg.x >= 30 && msg.x <= 250 && msg.y >= 110 && msg.y <= 200)
		{
			setcolor(EGERGB(255, 255, 0));

			setfont(60, 30, "黑体");

			outtextxy(35, 125, "人工智障");

		}
		else
		{

			setcolor(EGERGB(42, 234, 207));

			setfont(60, 30, "黑体");

			outtextxy(35, 125, "人工智障");

		}
		if (msg.x >= 30 && msg.x <= 250 && msg.y >= 270 && msg.y <= 360)
		{

			setcolor(EGERGB(255, 255, 0));

			setfont(60, 30, "黑体");

			outtextxy(35, 285, "人工智能");
		}
		else
		{
			setcolor(EGERGB(42, 234, 207));

			setfont(60, 30, "黑体");

			outtextxy(35, 285, "人工智能");


		}


		//获取鼠标消息，这个函数会等待，等待到有消息为止

		//类似地，有和kbhit功能相近的函数MouseHit，用于检测有没有鼠标消息

		while (mousemsg())

		{

			msg = getmouse();

		}



		//格式化输出为字符串，用于后面输出

		//msg和flag常数请参考文档或者mouse_msg_e, mouse_flag_e的声明

		if (msg.is_left() && msg.x >= 30 && msg.x <= 250 && msg.y >= 110 && msg.y <= 200)

		{

			cleardevice();

			flag = 1;

			break;

		}

		if (msg.is_left() && msg.x >= 30 && msg.x <= 250 && msg.y >= 270 && msg.y <= 360)

		{

			cleardevice();

			flag = 2;
			
			CD=1;

			break;

		}

	}

	if (flag == 1)

	{

		pveeasy();

	}

	else if (flag == 2)

	{

		pve();

	}



}





void choose()      //根据鼠标操作，以此选择游戏模式 

{
	PIMAGE img;
	img = newimage();
	getimage(img, "drawing\\three2.jpg");
	putimage(0, 0, img);




	for (; is_run(); delay_fps(600))//鼠标操作

	{

		//获取鼠标消息，这个函数会等待，等待到有消息为止

		//类似地，有和kbhit功能相近的函数MouseHit，用于检测有没有鼠标消息

		while (mousemsg())

		{

			msg = getmouse();

		}


		//	setcolor(EGERGB(0x0, 0xFF, 0x0));//文字颜色

		//   setbkmode(TRANSPARENT);//文字填充透明化

		//	setfont(100, 60, "楷体");

		//	outtextxy(200, 0, "五子棋游戏");



		if (msg.x >= 400 && msg.x <= 660 && msg.y >= 150 && msg.y <= 220)
		{



			setcolor(EGERGB(255, 255, 0));

			setfont(60, 30, "楷体");

			outtextxy(420, 150, "人机对战");
		}
		else
		{
			setcolor(EGERGB(228, 228, 228));

			setfont(60, 30, "楷体");

			outtextxy(420, 150, "人机对战");

		}


		if (msg.x >= 400 && msg.x <= 660 && msg.y >= 240 && msg.y <= 310)
		{
			setcolor(EGERGB(255, 255, 0));

			setfont(60, 30, "楷体");

			outtextxy(420, 240, "人人对战");
		}
		else
		{
			setcolor(EGERGB(228, 228, 228));

			setfont(60, 30, "楷体");

			outtextxy(420, 240, "人人对战");
		}

		if (msg.x >= 400 && msg.x <= 660 && msg.y >= 330 && msg.y <= 400)
		{
			setcolor(EGERGB(255, 255, 0));

			setfont(60, 30, "楷体");

			outtextxy(420, 330, "游戏排行");
		}
		else
		{
			setcolor(EGERGB(228, 228, 228));

			setfont(60, 30, "楷体");

			outtextxy(420, 330, "游戏排行");
		}

		if (msg.x >= 400 && msg.x <= 660 && msg.y >= 420 && msg.y <= 490)
		{
			setcolor(EGERGB(255, 255, 0));

			setfont(60, 30, "楷体");

			outtextxy(420, 420, "退出游戏");
		}
		else
		{
			setcolor(EGERGB(228, 228, 228));

			setfont(60, 30, "楷体");

			outtextxy(420, 420, "退出游戏");
		}



		//Author

		setcolor(EGERGB(32, 229, 170));

		setbkmode(TRANSPARENT);

		setfont(35, 14, "楷体");

		// outtextxy(710,550,"Author: Farmer Three");








			 //格式化输出为字符串，用于后面输出

			 //msg和flag常数请参考文档或者mouse_msg_e, mouse_flag_e的声明

		if (msg.is_left() && msg.x >= 400 && msg.x <= 660 && msg.y <= 220 && msg.y >= 150)

		{

			cleardevice();  //清除屏幕和图形缓冲区 

			flag = 1;

			break;

		}

		if (msg.is_left() && msg.x >= 400 && msg.x <= 660 && msg.y >= 240 && msg.y <= 310)

		{

			cleardevice();    //清除屏幕和图形缓冲区 

			flag = 2;

			break;

		}

		if (msg.is_left() && msg.x >= 400 && msg.x <= 660 && msg.y >= 330 && msg.y <= 400)
		{
			cleardevice();    //清除屏幕和图形缓冲区 

			explation();


		}

		if (msg.is_left() && msg.x >= 400 && msg.x <= 660 && msg.y >= 420 && msg.y <= 490)
		{

			closegraph();

		}



	}

	if (flag == 1)//进行人机大战

	{

		cleardevice();         //清除屏幕和图形缓冲区 

		createPC2();



	}

	//人人对抗

	else if (flag == 2)

	{

		select();

	}

}

void exitt()//退出到主菜单

{

	for (; is_run(); )

	{

		msg = getmouse();

		if ((int)msg.is_down() && (int)msg.x >= 700 && msg.x <= 850 && msg.y >= 400 && msg.y <= 450)

		{

			cleardevice();

			CreateMenus();

			choose();

		}

	}

}

void explation()
{

	PIMAGE img;
	img = newimage();
	getimage(img, "drawing\\three4.jpg");
	putimage(0, 0, img);

	outtextxy(0, 50, "1st");
	xyprintf(700, 50, "%10d", three[0].mark);
	outtextxy(300, 50, three[0].name);
	outtextxy(0, 150, "2nd");
	xyprintf(700, 150, "%10d", three[1].mark);
	outtextxy(300, 150, three[1].name);
	outtextxy(0, 250, "3rd");
	xyprintf(700, 250, "%10d", three[2].mark);
	outtextxy(300, 250, three[2].name);

	setfont(40, 15, "楷体");

	setcolor(EGERGB(0x0, 0xFF, 0x0));

	outtextxy(750, 400, "退出");


	for (; is_run(); )

	{


		msg = getmouse();




		if ((int)msg.is_down() && (int)msg.x >= 700 && msg.x <= 850 && msg.y >= 400 && msg.y <= 450)

		{

			cleardevice();

			CreateMenus();

			choose();

		}






	}


}


void scoring(int n)   //当用户赢得人工智能，则可以记录排行榜 
{

	int score;

	char farmer[100];

	score = 12544 - n * n;

	PIMAGE img;

	img = newimage();

	getimage(img, "drawing\\three3.jpeg");

	putimage(0, 0, img);

	setcolor(EGERGB(25, 224, 114));

	setfont(40, 20, "楷体");




	// outtextxy(20,20,"请输入一个昵称");

	inputbox_getline("请输入", "你爱输入什么就输入什么（回车确认）", farmer, 100);   //建立一个对话框 
	int i, j;
	for (i = 0; i <= 2; i++)
	{
		if (score > three[i].mark)
		{
			for (j = 2; j >= i; j--)
			{
				if (i == j)
				{
					strcpy(three[i].name, farmer);
					three[i].mark = score;
					break;
				}
				else
				{
					strcpy(three[j].name, three[j - 1].name);
					three[j].mark = three[j - 1].mark;
				}
			}
			if (i == j)
				break;
		}

	}
	fp = fopen("rank.txt", "w+");

	for (i = 0; i < 3; i++)
	{
		if (three[i].mark != 0)
		{
			if (i != 0)
				fprintf(fp, "\n");
			fputs(three[i].name, fp);
			fprintf(fp, "\t");
			fprintf(fp, "%d", three[i].mark);
		}

	}

	fclose(fp);

	outtextxy(0, 50, "1st");
	xyprintf(700, 50, "%10d", three[0].mark);
	outtextxy(300, 50, three[0].name);
	outtextxy(0, 150, "2nd");
	xyprintf(700, 150, "%10d", three[1].mark);
	outtextxy(300, 150, three[1].name);
	outtextxy(0, 250, "3rd");
	xyprintf(700, 250, "%10d", three[2].mark);
	outtextxy(300, 250, three[2].name);












	setfont(80, 30, "楷体");

	setcolor(EGERGB(0x0, 0xFF, 0x0));

	outtextxy(750, 400, "退出");


	for (; is_run(); )

	{


		msg = getmouse();




		if ((int)msg.is_down() && (int)msg.x >= 700 && msg.x <= 850 && msg.y >= 400 && msg.y <= 450)

		{

			cleardevice();

			CreateMenus();

			choose();

		}



	}

}


void select()
{
	strcpy(IP, "0");

	char farmer[100];

	PIMAGE img;
	img = newimage();
	getimage(img, "drawing\\three5.jpg");
	putimage(0, 0, img);
	int h = 0;



	for (; is_run(); delay_fps(600))//鼠标操作

	{

		setbkmode(TRANSPARENT);//文字填充透明化

		if (msg.x >= 30 && msg.x <= 250 && msg.y >= 110 && msg.y <= 200)
		{
			setcolor(EGERGB(255, 255, 0));

			setfont(60, 30, "黑体");

			outtextxy(35, 125, "本地对战");

		}
		else
		{

			setcolor(EGERGB(42, 234, 207));

			setfont(60, 30, "黑体");

			outtextxy(35, 125, "本地对战");

		}
		if (msg.x >= 30 && msg.x <= 250 && msg.y >= 270 && msg.y <= 360)
		{

			setcolor(EGERGB(255, 255, 0));

			setfont(60, 30, "黑体");

			outtextxy(35, 285, "创建游戏");
		}
		else
		{
			setcolor(EGERGB(42, 234, 207));

			setfont(60, 30, "黑体");

			outtextxy(35, 285, "创建游戏");
		}
		if (msg.x >= 30 && msg.x <= 250 && msg.y >= 430 && msg.y <= 520)
		{
			setcolor(EGERGB(255, 255, 0));

			setfont(60, 30, "黑体");

			outtextxy(35, 445, "加入游戏");
		}
		else
		{
			setcolor(EGERGB(42, 234, 207));

			setfont(60, 30, "黑体");

			outtextxy(35, 445, "加入游戏");
		}





		//获取鼠标消息，这个函数会等待，等待到有消息为止

		//类似地，有和kbhit功能相近的函数MouseHit，用于检测有没有鼠标消息

		while (mousemsg())

		{

			msg = getmouse();

		}



		//格式化输出为字符串，用于后面输出

		//msg和flag常数请参考文档或者mouse_msg_e, mouse_flag_e的声明

		if (msg.is_left() && msg.x >= 30 && msg.x <= 250 && msg.y >= 110 && msg.y <= 200)

		{

			cleardevice();

			h = 1;

			break;

		}

		if (msg.is_left() && msg.x >= 30 && msg.x <= 250 && msg.y >= 270 && msg.y <= 360)

		{

			cleardevice();

			h = 2;

			break;

		}
		if (msg.is_left() && msg.x >= 30 && msg.x <= 250 && msg.y >= 430 && msg.y <= 520)
		{
			cleardevice();
			h = 3;
			break;
		}

	}

	if (h == 1)
		pvp();
	else if (h == 2)
		inter1();
	else if (h == 3)
	{
		putimage(0, 0, img);

		inputbox_getline("请输入", "ip地址（回车确认）", farmer, 100);   //建立一个对话框 

		strcpy(IP, farmer);

		cleardevice();

		inter2();

	}



}



int main()

{
	int i = 0;
	fp = fopen("rank.txt", "a+");
	while (!feof(fp))
	{
		fscanf(fp, "%s%d", three[i].name, &three[i].mark);
		i++;
	}
	fclose(fp);
	CreateMenus();//主菜单

	choose();//菜单栏选择

	exitt();

	getch();

	return 0;

}

