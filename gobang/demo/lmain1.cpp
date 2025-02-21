#include <graphics.h>

#include <iostream>

int lmain1()
{
	initgraph(1280, 720);
	int M_X = 300;
	int M_Y = 300;

	BeginBatchDraw();

	while (true)
	{
		ExMessage msg;
		while (peekmessage(&msg))
		{
			if (msg.message == WM_MOUSEMOVE)
			{
				//此处处理鼠标移动的逻辑
				M_X = msg.x;
				M_Y = msg.y;
			}
		}
		cleardevice();
		solidcircle(M_X, M_Y, 200);
		FlushBatchDraw();

	}
	EndBatchDraw();
	return 0;
}