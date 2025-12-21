#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

#define W 40
#define H 15

char frame[W * H];

void delay(int ticks) {
    for (volatile int i = 0; i < ticks * 100000; i++);
}

void draw_square(int x0) {
    // clear frame → fill with '.'
    for (int i = 0; i < W*H; i++)
        frame[i] = '.';

    // draw 4×4 square
    for (int y = 5; y < 9; y++) {
        for (int x = x0; x < x0 + 4; x++) {
            frame[y * W + x] = '#';
        }
    }
}

void show_frame() {
    // clear screen
    printf("\033[2J\033[H");

    for (int y = 0; y < H; y++) {
        for (int x = 0; x < W; x++) {
            printf("%c", frame[y*W + x]);
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

    int x = 15;
    int direction = 1;

    while (1) {
        draw_square(x);

        // write frame to kernel
        write(fd, frame, W * H);

        // optional: read back if muốn kiểm tra
        // read(fd, frame, W * H);

        show_frame();

        // move square
        x += direction;
        if (x <= 0 || x >= W - 4)
            direction = -direction;

        delay(50);
    }

    exit(0);
}
