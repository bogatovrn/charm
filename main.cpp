#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#include "charmlib.h"

int main()
{
	cursor_off();
	const int N = 28, M = 99;
	char* scr = create_screen(M + 1, N, ' ');
	
	char c = 'Ы';
	int x = 0, y = 0, thickness = 1, shiftup = 0, shiftleft = 0;
	
	//goto Cont;
	for (;;) {
		//pixel2_cb(scr, M + 1, x-1, y, M - 1, 2 * N - 1, false);
		//pixel2_cb(scr, M + 1, x+1, y, M - 1, 2 * N - 1, false);
		//pixel2_cb(scr, M + 1, x, y-1, M - 1, 2 * N - 1, false);
		//pixel2_cb(scr, M + 1, x, y+1, M - 1, 2 * N - 1, false);

		//pixel2_cb(scr, M + 1, x, y, M - 1, 2 * N - 1);

		drawfilledrectangle(scr, M + 1, 0, 0, M - 1, N - 1, ' ');
		//drawtext8x8_shifted(scr, M + 1,
		//	"Hello, World! Как жизнь?", x, y, M - 1, N - 1,
		//	CHR_GRAY75, 0, thickness, shiftleft, shiftup);
		drawtext8x8(scr, M + 1,
			"Hello, World! Как жизнь?", x, y, M - 1, N - 1,
			CHR_GRAY75, 0, thickness);
		print_screen(scr);
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
	//const char text[] = "A painting that hung for some 60 years in a Brussels town hall has been authenticated as the oldest known version of one of Flemish master Jacques Jordaens";
	int time = clock();
	c = ' ';
	x = 0;
	thickness = 2;
	int delay = 20;
	for (int offset = 0; text[offset / (8*thickness)] != 0; offset++)
	{
		drawfilledrectangle(scr, M + 1, 0, 0, M - 1, N - 1, c);
		drawtext8x8_shifted(scr, M + 1, text + offset / (8 * thickness),
			x, y, M-1, N-1,
			CHR_GRAY75, 0, thickness,
			offset % (8*thickness), 0);
		//drawtext8x8(scr, M + 1, text + offset / (8 * thickness),
		//	x - (offset % (8 * thickness)), y, M - 1, N - 1,
		//	CHR_GRAY75, 0, thickness);
		print_screen(scr);
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