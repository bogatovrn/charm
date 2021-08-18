#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#include <math.h>


#include "charmlib.h"

int main()
{
	cursor_off();
	const int N = 28, M = 99;
	char* scr = create_screen(M + 1, N, ' ');
	setcurrentscreen(scr, M + 1);
	setmaxxy(M - 1, N - 1);

	char c = 'Ы';
	int x = 20, y = 10, z = 10, thickness = 1, shiftup = 10, shiftleft = 0;
	int mode = 0;
	goto Skip1;

	for (;;) {
		setmaxxy(M - 1, N - 1);
		clear_canvas();
		//printfxy(8, N - 4, "z = %d, (minxz = %d, maxz = %d)", z, shiftleft, shiftup);

		setdepth3d(shiftleft, shiftup);
		drawline3d(M / 2, N / 2, 0, M / 2 + x, N / 2 - y, z);

		//setmaxxy(M - 1, (mode + 1) * N - 1);
		//mode ? drawline_2(M / 2, 2 * N / 2, M / 2 + x, 2 * N / 2 + y, c) :
		//	drawline(M / 2, N / 2, M / 2 + x, N / 2 + y, c);

		printfxy(8, N - 4, "z = %d, (minxz = %d, maxz = %d)", z, shiftleft, shiftup);

		print_current_screen();

		while (!_kbhit());
		while (_kbhit())
		{
			char k = _getch();
			switch (k) {
			case -32: break;
			case 75: /*if (x > 0)*/ x--; break;
			case 77: x++; break;
			case 80: /*if (y > 0)*/ y--; break;
			case 72: y++; break;
			case '+': z++; break;
			case '-': z--; break;
			case 'a': shiftleft++; break;
			case 'd': shiftleft--; break;
			case 'w': shiftup++; break;
			case 's': shiftup--; break;
			case 'm': mode = !mode; break;
			case 27: goto Cont;
			default: c = k;  break;
			}
		}
	}
	Skip1:
	while (_kbhit()) _getch();
	for (int i = 0; i < 40; i++)
	{
		//drawfilledrectangle(0, 0, M - 1, N - 1, 'A'+i);

		double x = 3*(4 + i / 3.0) * cos(2 * 3.14 / 15 * i);
		double y = (4 + i / 3.0) * sin(2 * 3.14 / 15 * i);
		//drawrectangle_2(M/2, 2*N/2, M/2+(int)x, 2*N/2-(int)y);
		//printfxy(scr, M + 1, M / 2 + (int)x, N / 2 - (int)y, "%d", i);

		setdepth3d(shiftleft, shiftup);
		//drawline(M / 2, N / 2, M / 2 + x, N / 2 - y);
		drawline3d(M / 2, N / 2, 0, M / 2 + x, N / 2 - y, z);

		print_current_screen();
		sleep(50);
		//_getch();
	}
	_getch();

	for (;;) {
		//pixel2_cb(scr, M + 1, x-1, y, M - 1, 2 * N - 1, false);
		//pixel2_cb(scr, M + 1, x+1, y, M - 1, 2 * N - 1, false);
		//pixel2_cb(scr, M + 1, x, y-1, M - 1, 2 * N - 1, false);
		//pixel2_cb(scr, M + 1, x, y+1, M - 1, 2 * N - 1, false);

		//pixel2_cb(scr, M + 1, x, y, M - 1, 2 * N - 1);

		drawfilledrectangle(0, 0, M - 1, N - 1, '+');
		drawtext8x10_2_shifted(
			"Hello, World! Как жизнь?", x, y, 
			CHR_GRAY75, 0, thickness, shiftleft, shiftup);
		//drawtext8x10(scr, M + 1,
		//	"Hello, World! Как жизнь?", x, y, M - 1, N - 1,
		//	CHR_GRAY75, 0, thickness);
		print_current_screen();
		while (!_kbhit());
		while (_kbhit())
		{
			char k = _getch();
			switch (k) {
				case -32: break;
				case 75: /*if (x > 0)*/ x--; break;
				case 77: x++; break;
				case 72: /*if (y > 0)*/ y--; break;
				case 80: y++; break;
				case '+': thickness++; break;
				case '-': if (thickness > 1) thickness--; break;
				case 'a': shiftleft++; break;
				case 'd': shiftleft--; break;
				case 'w': shiftup++; break;
				case 's': shiftup--; break;
				case 27: goto Cont;
				default: c = k;  break;
			}
		}
	}

	Cont:
	
	const char text[] = "A painting that hung for some 60 years in a Brussels town hall has been authenticated as the oldest known version of one of Flemish master Jacques Jordaens' most famous works. The discovery of the Holy Family painting was made during a 2019 inventory of cultural works in Saint - Gilles town hall. It was thought to have been a copy. The work dates to 1617 or 1618, said the Royal Institute for Cultural Heritage, which helped make the find.";
	//const char text[] = "Новые правила противопожарного режима в РФ приняты в рамках \"регуляторной гильотины\". Они будут действовать до 2026 года, после чего будут подлежать пересмотру в соответствии с требованиями времени.";
	//const char text[] = "1НовыеA 2правилаB 3противопожарногоC 4режимаD 5вE 6РФF 7принятыG 8вH 9рамкахI 10\"регуляторнойJ 11гильотины\".K 12Они будут действовать до 2026 года, после чего будут подлежать пересмотру в соответствии с требованиями времени.";
	//const char text[] = "A painting that hung for some 60 years in a Brussels town hall has been authenticated as the oldest known version of one of Flemish master Jacques Jordaens";
	int time = clock();
	c = ' ';
	x = 0;
	thickness = 2;
	int delay = 20;
	for (int offset = 0; text[offset / (8*thickness)] != 0; offset++)
	{
		drawfilledrectangle(0, 0, M - 1, N - 1, c);
		drawtext8x8_2_shifted(text + offset / (8 * thickness),
			x, y, 
			CHR_GRAY75, 0, thickness,
			offset % (8*thickness), 0);
		//drawtext8x8(scr, M + 1, text + offset / (8 * thickness),
		//	x - (offset % (8 * thickness)), y, M - 1, N - 1,
		//	CHR_GRAY75, 0, thickness);
		print_current_screen();
		sleep(delay);
		while (_kbhit())
		{
			char k = _getch();
			switch (k) {
				case -32: break;
				case 75: /*if (x > 0)*/ x--; break;
				case 77: x++; break;
				case 72: /*if (y > 0)*/ y--; break;
				case 80: y++; break;
				case '+': thickness++; break;
				case '-': if (thickness>1) thickness--; break;
				case 'w': delay++; break;
				case 's': if (delay > 0) delay--; break;
				case 'p': _getch(); break;
				case 27: goto Cont2;
				default: c = k;  break;
			}
		}
	}

Cont2:
	
	printf("\n%d milliseconds", clock() - time);
	_getch();

Exit:
	
	delete_screen(scr);
}