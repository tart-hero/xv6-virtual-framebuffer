#include "kernel/types.h"
#include "user/user.h"

#define W 40
#define H 15

char buf[W*H];

void clear(char c){
  for(int i=0;i<W*H;i++) buf[i]=c;
}

void draw_square(int x, int y, int s){
  for(int dy=0;dy<s;dy++){
    for(int dx=0;dx<s;dx++){
      int xx = x + dx;
      int yy = y + dy;
      if(xx>=0 && xx<W && yy>=0 && yy<H)
        buf[yy*W + xx] = '#';
    }
  }
}

void render(){
  // CLEAR SCREEN + move cursor to top-left
  printf("\033[H\033[2J");

  for(int y=0;y<H;y++){
    for(int x=0;x<W;x++){
      printf("%c", buf[y*W+x]);
    }
    printf("\n");
  }
}

int main(){
  int x = 0, dir = 1;

  while(1){
    clear('.');

    draw_square(x, 5, 4);
    render();

    x += dir;
    if (x <= 0) dir = 1;
    if (x+4 >= W) dir = -1;

    // delay
    for(volatile int i=0;i<500000;i++);
  }

  exit(0);
}
