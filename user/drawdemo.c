#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

#define W 40
#define H 15
#define SIZE 4

char frame[W * H];

void delay(int ticks) {
    for (volatile int i = 0; i < ticks * 100000; i++);
}

// vẽ hình vuông 4x4 tại (x0, y0)
void draw_square(int x0, int y0) {
    // clear frame
    for (int i = 0; i < W * H; i++)
        frame[i] = '.';

    for (int y = y0; y < y0 + SIZE; y++) {
        for (int x = x0; x < x0 + SIZE; x++) {
            if (x >= 0 && x < W && y >= 0 && y < H)
                frame[y * W + x] = '#';
        }
    }
}

void show_frame() {
    printf("\033[2J\033[H");
    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            printf("%c", frame[y * W + x]);
        }
        printf("\n");
    }
}

int
main(void)
{
    int fd = open("/dev/fb", O_RDWR);
    if (fd < 0) {
        printf("Cannot open /dev/fb\n");
        exit(1);
    }

    int x = 15;   // vị trí ban đầu
    int y = 5;
    char c;

    while (1) {
        // đọc phím (PHẢI bấm ENTER)
        if (read(0, &c, 1) > 0) {
            if (c == 'a') {           // trái
                x--;
                if (x < 0) x = 0;
            }
            else if (c == 'd') {      // phải
                x++;
                if (x > W - SIZE) x = W - SIZE;
            }
            else if (c == 'w') {      // lên
                y--;
                if (y < 0) y = 0;
            }
            else if (c == 's') {      // xuống
                y++;
                if (y > H - SIZE) y = H - SIZE;
            }
            else if (c == 'q') {      // thoát
                break;
            }
        }

        draw_square(x, y);

        // ghi framebuffer xuống kernel
        write(fd, frame, W * H);

        // hiển thị
        show_frame();

        delay(20);
    }

    exit(0);
}
