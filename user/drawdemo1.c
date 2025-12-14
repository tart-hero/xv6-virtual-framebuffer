#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

#define W 40
#define H 15

char frame[W * H];

// Fill entire frame with background char
void clear_frame(char c) {
  for (int i = 0; i < W * H; i++)
    frame[i] = c;
}

// Draw a square of size S at (x, y)
void draw_square(int x, int y, int S, char c) {
  for (int dy = 0; dy < S; dy++) {
    for (int dx = 0; dx < S; dx++) {
      int xx = x + dx;
      int yy = y + dy;
      if (xx >= 0 && xx < W && yy >= 0 && yy < H)
        frame[yy * W + xx] = c;
    }
  }
}

int main() {
  int fd = open("/dev/fb", O_RDWR);
  if (fd < 0) {
    printf("Cannot open /dev/fb\n");
    exit(1);
  }

  int x = 0;
  int dir = 1;     // 1 = right, -1 = left
  int S = 4;       // size of square

  for (int t = 0; t < 200; t++) {
    clear_frame('.');                     // background
    draw_square(x, 5, S, '#');            // moving square

    write(fd, frame, W * H);              // push to framebuffer

    x += dir;
    if (x + S >= W) dir = -1;
    if (x <= 0)     dir = 1;

    // Yield to let kernel schedule (animation delay)
    for (int i = 0; i < 1000000; i++)
      ; // simple busy-wait delay
  }

  close(fd);
  exit(0);
}
