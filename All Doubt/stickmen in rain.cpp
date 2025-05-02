#include <graphics.h>
#include <cstdlib> // Required for rand() and srand()
#include <ctime>   // Required for time()

void initialize_graphics() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
}

void stickman_open(int a) {
    for (int i = 0; i < 3; i++) {
        circle(50 + a, 320, 30 + i);
        line(50 + i + a, 350, 50 + i + a, 400);
        line(50 + i + a, 400, 30 + i + a, 450);
        line(50 + i + a, 400, 70 + i + a, 450);
        line(50 + a + i, 360, 20 + a + i, 400);
        line(50 + a, 360 + i, 80 + a, 380 + i);
        line(80 + i + a, 380, 100 + i + a, 360);
        line(100 + i + a, 360, 100 + i + a, 270);
        line(50 + a, 270 + i, 150 + a, 270 + i);
        arc(100 + a, 270, 0, 180, 50 + i);
    }
}

void stickman_close(int a) {
    for (int i = 0; i < 3; i++) {
        circle(50 + a, 320, 30 + i);
        line(50 + i + a, 350, 50 + i + a, 400);
        line(50 - i + a, 400, 50 - i + a, 450);
        line(50 + i + a, 400, 50 + i + a, 450);
        line(50 + a + i, 360, 45 + a + i, 400);
        line(50 + a, 360 + i, 80 + a, 380 + i);
        line(80 + i + a, 380, 100 + i + a, 360);
        line(100 + i + a, 360, 100 + i + a, 270);
        line(50 + a, 270 + i, 150 + a, 270 + i);
        arc(100 + a, 270, 0, 180, 50 + i);
    }
}

void rain() {
    for (int i = 0; i < 60; i++) {
        outtextxy(rand() % 600, rand() % 445, "| ");
    }
}

void road() {
    for (int i = 0; i < 3; i++) {
        line(0, 450 + i, 600, 450 + i);
    }
}

int main() {
    initialize_graphics();
    int s = 0;
    int page = 0;
    int n = 0;

    srand(time(0));

    while (n <= 150) {
        setactivepage(page);
        setvisualpage(1 - page);
        cleardevice();

        road();
        rain();

        if (n % 2 == 0)
            stickman_open(s);
        else
            stickman_close(s);

        page = 1 - page;
        delay(150);
        s += 4;
        n++;
    }
    getch();
    closegraph();
    return 0;
}

