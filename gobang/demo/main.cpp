#include <graphics.h>

char board_date[3][3] = { '-','-','-','-','-','-', '-','-','-' };

char current_piece = 'o';

//检测指定棋子的玩家是否获胜
bool CheckWin(char c)
{
	for (int i = 0; i < 3; i++)
	{
		if (board_date[i][0] == c && board_date[i][1] == c && board_date[i][2] == c)
		{
			return true;
		}
		if (board_date[0][i] == c && board_date[1][i] == c && board_date[2][i] == c)
		{
			return true;
		}
	}
	if (board_date[0][0] == c && board_date[1][1] == c && board_date[2][2] == c)
	{
		return true;
	}if (board_date[0][2] == c && board_date[1][1] == c && board_date[2][0] == c)
	{
		return true;
	}
	return false;

}
//检查是否平局
bool CheckDraw()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board_date[i][j] == '-') 
			{
				return false;
			}
		}
	}
	return true;
}

//绘制棋盘网格
void DrawBoard()
{
	line(0, 200, 600, 200);
	line(0, 400, 600, 400);
	line(200, 0, 200, 600);
	line(400, 0, 400, 600);
}

//绘制棋子
void DrawPiece()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			switch (board_date[i][j])
			{
			case 'o':
				circle(200 * j + 100, 200 * i + 100, 100);
				break;
			case 'x':
				line(200 * j, 200 * i, 200 * (j + 1), 200 * (i + 1));
				line(200 * (j + 1), 200 * i, 200 * j, 200 * (i + 1));
				break;
			case '-':
				break;
			}
		}
	}
}

//绘制提示信息
void DrawTip()
{
	static TCHAR str[64];
	_stprintf_s(str, _T("当前棋子类型:%c"), current_piece);

	settextcolor(RGB(225, 175, 45));
	outtextxy(0, 0, str);
}


int main()
{
	//初始渲染画布
	initgraph(600, 600);

	bool running = true;

	ExMessage msg;

	BeginBatchDraw();


	while (running)
	{
		DWORD start_time = GetTickCount();
		//逻辑判断
		while (peekmessage(&msg))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				//计算点击的位置
				int x = msg.x;
				int y = msg.y;

				int index_x = x / 200;
				int index_y = y / 200;

				//落子
				if (board_date[index_y][index_x] == '-')
				{
					board_date[index_y][index_x] = current_piece;

					//切换棋子类型
					if (current_piece == 'o')
					{
						current_piece = 'x';
					}
					else
					{
						current_piece = 'o';
					}
				}
			}
		}


		cleardevice();


		DrawBoard();
		DrawPiece();
		DrawTip();


		FlushBatchDraw();


		if (CheckWin('x'))
		{
			MessageBox(GetHWnd(), _T("x 玩家获胜"), _T("游戏结束"), MB_OK); // 注意这里的引号
			running = false;
		}
		else if (CheckWin('o'))
		{
			MessageBox(GetHWnd(), _T("o 玩家获胜"), _T("游戏结束"), MB_OK); // 注意这里的引号
			running = false;
		}
		else if (CheckDraw())
		{
			MessageBox(GetHWnd(), _T("平局"), _T("游戏结束"), MB_OK); // 注意这里的引号
			running = false;
		}
		
		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / 60)
		{
			Sleep(1000 / 60 - delta_time);
		}
	}
	EndBatchDraw();
	return 0;

}
