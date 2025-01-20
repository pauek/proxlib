// main.c
#include <iostream>
#include "fenster.h"

const int W = 1024;
const int H = 768;

inline void rect(struct fenster *f, int x, int y, int w, int h, int color) {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			fenster_pixel(f, x + j, y + i) = color;
		}
	}
}

int main() {
	uint32_t	   buf[W * H] = {0};
	struct fenster f = {.title = "hello", .width = W, .height = H, .buf = buf};
	fenster_open(&f);
	int last_time = fenster_time();
	while (fenster_loop(&f) == 0) {
		if (f.keys[27]) {
			break;
		}
		if (f.mouse == 1) {
			int color = 0x00ffffff;
			if (f.mod & 0x1) {
				color = 0x00ff0000;
			}
			fenster_pixel(&f, f.x, f.y) = color;
		}
		rect(&f, 0, 0, 10, 10, !(f.mod & 0x1) ? 0xff0000 : 0x0);
		rect(&f, 10, 0, 10, 10, !(f.mod & 0x2) ? 0x00ff00 : 0x0);
		rect(&f, 20, 0, 10, 10, !(f.mod & 0x4) ? 0x0000ff : 0x0);

		int wait = 16 - (fenster_time() - last_time);
		if (wait > 0) {
			fenster_sleep(wait);
		}
		int time = fenster_time();
		// std::cout << "FPS: " << 1000.0 / double(time - last_time) << std::endl;
		last_time = time;
	}
	fenster_close(&f);
	return 0;
}