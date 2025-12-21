int fbwrite(int user_src, uint64 src, int n) {
  int max = FB_WIDTH * FB_HEIGHT;
  if (n > max) n = max;

  char buf[max];
  if (either_copyin(buf, user_src, src, n) < 0)
    return -1;

  for (int i = 0; i < n; i++) {
    int y = i / FB_WIDTH;
    int x = i % FB_WIDTH;
    framebuffer[y][x] = buf[i];
  }

  // clear screen
  printf("\033[2J\033[H");

  // print framebuffer
  for (int y = 0; y < FB_HEIGHT; y++) {
    for (int x = 0; x < FB_WIDTH; x++) {
      printf("%c", framebuffer[y][x]);
    }
    printf("\n");
  }

  return n;
}
