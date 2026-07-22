#include <GL/glut.h>
#include <math.h>

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 650
#define PI 3.14159265358979323846f

static void drawCircle(float cx, float cy, float r, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; i++) {
        float a = 2.0f * PI * (float)i / (float)segments;
        glVertex2f(cx + cosf(a) * r, cy + sinf(a) * r);
    }
    glEnd();
}

static void drawSkyGradient(void) {
    glBegin(GL_QUADS);
    glColor3f(0.02f, 0.05f, 0.18f);
    glVertex2f(0.0f, WINDOW_HEIGHT);
    glVertex2f((float)WINDOW_WIDTH, WINDOW_HEIGHT);
    glColor3f(0.12f, 0.20f, 0.40f);
    glVertex2f((float)WINDOW_WIDTH, 300.0f);
    glVertex2f(0.0f, 300.0f);
    glEnd();
}

static void drawStars(void) {
    static const float stars[][2] = {
        {90, 590}, {150, 560}, {230, 610}, {315, 540}, {410, 620}, {485, 560},
        {560, 600}, {645, 535}, {725, 615}, {810, 550}, {120, 510}, {280, 500},
        {370, 470}, {520, 500}, {670, 475}, {760, 505}, {845, 480}
    };

    glPointSize(3.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    for (unsigned int i = 0; i < sizeof(stars) / sizeof(stars[0]); i++) {
        glVertex2f(stars[i][0], stars[i][1]);
    }
    glEnd();

    glLineWidth(1.5f);
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(160, 620); glVertex2f(200, 600);
    glVertex2f(610, 580); glVertex2f(650, 560);
    glEnd();
}

static void drawBird(float x, float y, float s) {
    glBegin(GL_LINE_STRIP);
    glVertex2f(x - 10.0f * s, y);
    glVertex2f(x - 4.0f * s, y + 4.0f * s);
    glVertex2f(x, y);
    glVertex2f(x + 4.0f * s, y + 4.0f * s);
    glVertex2f(x + 10.0f * s, y);
    glEnd();
}

static void drawBirds(void) {
    glColor3f(0.05f, 0.05f, 0.06f);
    glLineWidth(2.0f);
    drawBird(170, 470, 1.0f);
    drawBird(350, 520, 0.9f);
    drawBird(530, 455, 1.1f);
    drawBird(730, 500, 0.95f);
}

static void drawMoonAndReflection(void) {
    glColor3f(0.95f, 0.95f, 0.95f);
    drawCircle(715.0f, 535.0f, 45.0f, 64);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.88f, 0.90f, 0.95f, 0.25f);
    drawCircle(715.0f, 130.0f, 33.0f, 64);
    glDisable(GL_BLEND);
}

static void drawTrees(void) {
    glColor3f(0.03f, 0.06f, 0.04f);
    for (int i = 0; i < WINDOW_WIDTH; i += 45) {
        float h = 30.0f + (float)((i / 45) % 3) * 15.0f;
        glBegin(GL_TRIANGLES);
        glVertex2f((float)i, 300.0f);
        glVertex2f((float)i + 22.0f, 300.0f + h);
        glVertex2f((float)i + 45.0f, 300.0f);
        glEnd();
    }
}

static void drawWindmillBody(void) {
    glColor3f(0.10f, 0.10f, 0.12f);
    glBegin(GL_QUADS);
    glVertex2f(425.0f, 300.0f);
    glVertex2f(475.0f, 300.0f);
    glVertex2f(465.0f, 430.0f);
    glVertex2f(435.0f, 430.0f);
    glEnd();

    glColor3f(0.95f, 0.75f, 0.25f);
    drawCircle(450.0f, 335.0f, 4.0f, 24);
    drawCircle(450.0f, 360.0f, 4.0f, 24);
    drawCircle(450.0f, 385.0f, 4.0f, 24);
    drawCircle(450.0f, 410.0f, 4.0f, 24);
}

static void drawBlade(float x1, float y1, float x2, float y2, float x3, float y3) {
    glColor3f(0.55f, 0.56f, 0.58f);
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();

    glColor3f(0.35f, 0.35f, 0.37f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex2f((x1 + x2) * 0.5f, (y1 + y2) * 0.5f);
    glVertex2f((x1 + x3) * 0.5f, (y1 + y3) * 0.5f);
    glVertex2f((x2 + x3) * 0.5f, (y2 + y3) * 0.5f);
    glVertex2f((x1 + x3) * 0.5f, (y1 + y3) * 0.5f);
    glEnd();
}

static void drawWindmillBlades(void) {
    drawBlade(450.0f, 430.0f, 445.0f, 530.0f, 455.0f, 530.0f);
    drawBlade(450.0f, 430.0f, 550.0f, 425.0f, 550.0f, 435.0f);
    drawBlade(450.0f, 430.0f, 445.0f, 330.0f, 455.0f, 330.0f);
    drawBlade(450.0f, 430.0f, 350.0f, 425.0f, 350.0f, 435.0f);

    glColor3f(0.20f, 0.20f, 0.22f);
    drawCircle(450.0f, 430.0f, 10.0f, 24);
}

static void drawWindmillReflection(void) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(0.18f, 0.19f, 0.22f, 0.35f);
    glBegin(GL_QUADS);
    glVertex2f(425.0f, 300.0f);
    glVertex2f(475.0f, 300.0f);
    glVertex2f(470.0f, 170.0f);
    glVertex2f(430.0f, 170.0f);
    glEnd();

    glColor4f(0.42f, 0.43f, 0.45f, 0.28f);
    glBegin(GL_TRIANGLES);
    glVertex2f(450.0f, 300.0f); glVertex2f(445.0f, 205.0f); glVertex2f(455.0f, 205.0f);
    glVertex2f(450.0f, 300.0f); glVertex2f(545.0f, 295.0f); glVertex2f(545.0f, 305.0f);
    glVertex2f(450.0f, 300.0f); glVertex2f(445.0f, 395.0f); glVertex2f(455.0f, 395.0f);
    glVertex2f(450.0f, 300.0f); glVertex2f(355.0f, 295.0f); glVertex2f(355.0f, 305.0f);
    glEnd();

    glDisable(GL_BLEND);
}

static void drawWater(void) {
    glBegin(GL_QUADS);
    glColor3f(0.03f, 0.08f, 0.16f);
    glVertex2f(0.0f, 300.0f);
    glVertex2f((float)WINDOW_WIDTH, 300.0f);
    glColor3f(0.04f, 0.11f, 0.22f);
    glVertex2f((float)WINDOW_WIDTH, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glEnd();

    glColor4f(0.75f, 0.83f, 0.95f, 0.22f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for (int y = 35; y <= 280; y += 28) {
        glBegin(GL_LINES);
        glVertex2f(30.0f, (float)y);
        glVertex2f(870.0f, (float)y + 5.0f);
        glEnd();
    }
    glDisable(GL_BLEND);
}

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    drawSkyGradient();
    drawStars();
    drawBirds();
    drawMoonAndReflection();
    drawTrees();
    drawWindmillBody();
    drawWindmillBlades();
    drawWater();
    drawWindmillReflection();

    glutSwapBuffers();
}

static void reshape(int w, int h) {
    (void)w;
    (void)h;
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void initScene(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Night Windmill Landscape");

    initScene();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
