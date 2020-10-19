#include <gl/glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>

// 라이브러리 추가
#pragma comment (lib,"glut32.lib")
#pragma comment (lib,"glu32.lib")
#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"winmm.lib") 

#define WINDOW_WIDTH 500.0
#define WINDOW_HEIGHT 500.0

int StartX = 18, StartY = 70, Width = 16, Height = 8, Bcol, Brow;
GLfloat BlackX, BlackY;

// 퍼즐 색상표
float Color[25][3] = 
{ 
    {0,0,1},{1,0,0},{0.5,0,1},{0.5,0.5,0.5},{0.5,0.5,1}, 
    {0.5,0.5,0},{1,0.9,0.3},{1,0.5,1},{0.7,0.2,1},{0.2,0.5,0.1},
    {0.8,1,1},{0,1,0.5},{0,0,0},{0,1,0},{0.7,0.5,0.3},
    {0.2,0.2,0.6},{0.1,0.8,1},{0.2,0.4,1},{1,0.4,0.4},{0.8,0,0.4}, 
    {1,1,0},{1,1,0.7},{1,0.2,0.8},{0.7,0.7,0.7},{0.2,1,1}
};

void Dis_rect(float CX, float CY, float Width, float Height, float *Colorz) // 사각형 그리기 함수
{
    glColor3f(Colorz[0], Colorz[1], Colorz[2]);
    glBegin(GL_POLYGON);
    glVertex3f(CX - Width / 2, CY - Height / 2, 0.0);
    glVertex3f(CX + Width / 2, CY - Height / 2, 0.0);
    glVertex3f(CX + Width / 2, CY + Height / 2, 0.0);
    glVertex3f(CX - Width / 2, CY + Height / 2, 0.0);
    glEnd();
}

void Mydisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    int X, Y = StartY;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            X = StartX + j * Width;
            Dis_rect(X, Y, Width, Height, Color[i * 5 + j]);
            if (Color[i * 5 + j][0] == 0 && Color[i * 5 + j][1] == 0 && Color[i * 5 + j][2] == 0)
            {
                BlackX = X; BlackY = Y; Brow = i; Bcol = j;
            }
        }
        Y = StartY - (1 + i) * Height;
    }
    glFlush();
}

short is_Collison(GLfloat X, GLfloat Y, GLfloat* Ary) // 충돌 판정
{
    if (Ary[0] - 8 < X && X < Ary[0] + 8 && Ary[1] - 4 < Y && Y < Ary[1] + 4)
        return 1;
    return 0;
}

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) // 마우스는 윈도우 기준 좌표라 왼쪽, 위가 (0, 0)이다.
{
    GLfloat Up[2], Down[2], Left[2], Right[2], m_X, m_Y;
    Up[0] = BlackX; Up[1] = BlackY + 8;
    Down[0] = BlackX; Down[1] = BlackY - 8;
    Left[0] = BlackX - 16; Left[1] = BlackY;
    Right[0] = BlackX + 16; Right[1] = BlackY;
    m_X = X * (100.0 / WINDOW_WIDTH); m_Y = (WINDOW_HEIGHT - Y) * (100.0 / WINDOW_HEIGHT);
    if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN 
        && 12 < m_X && m_X < 92 && 36 < m_Y && m_Y < 76)
    {
        if (is_Collison(m_X, m_Y, Up))
        {
            Color[Brow * 5 + Bcol][0] = Color[(Brow - 1) * 5 + Bcol][0];
            Color[Brow * 5 + Bcol][1] = Color[(Brow - 1) * 5 + Bcol][1];
            Color[Brow * 5 + Bcol][2] = Color[(Brow - 1) * 5 + Bcol][2];
            Color[(Brow - 1) * 5 + Bcol][0] = Color[(Brow - 1) * 5 + Bcol][1] = Color[(Brow - 1) * 5 + Bcol][2] = 0;       
        }
        else if (is_Collison(m_X, m_Y, Down))
        {
            Color[Brow * 5 + Bcol][0] = Color[(Brow + 1) * 5 + Bcol][0];
            Color[Brow * 5 + Bcol][1] = Color[(Brow + 1) * 5 + Bcol][1];
            Color[Brow * 5 + Bcol][2] = Color[(Brow + 1) * 5 + Bcol][2];
            Color[(Brow + 1) * 5 + Bcol][0] = Color[(Brow + 1) * 5 + Bcol][1] = Color[(Brow + 1) * 5 + Bcol][2] = 0;
        }
        else if (is_Collison(m_X, m_Y, Left))
        {
            Color[Brow * 5 + Bcol][0] = Color[Brow * 5 + Bcol - 1][0];
            Color[Brow * 5 + Bcol][1] = Color[Brow * 5 + Bcol - 1][1];
            Color[Brow * 5 + Bcol][2] = Color[Brow * 5 + Bcol - 1][2];
            Color[Brow * 5 + Bcol - 1][0] = Color[Brow * 5 + Bcol - 1][1] = Color[Brow * 5 + Bcol - 1][2] = 0;
        }
        else if (is_Collison(m_X, m_Y, Right))
        {
            Color[Brow * 5 + Bcol][0] = Color[Brow * 5 + Bcol + 1][0];
            Color[Brow * 5 + Bcol][1] = Color[Brow * 5 + Bcol + 1][1];
            Color[Brow * 5 + Bcol][2] = Color[Brow * 5 + Bcol + 1][2];
            Color[Brow * 5 + Bcol + 1][0] = Color[Brow * 5 + Bcol + 1][1] = Color[Brow * 5 + Bcol + 1][2] = 0;
        }
    }
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    srand((unsigned int)time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(500, 100);
    glutCreateWindow("201663021 이경준");

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);

    glutDisplayFunc(Mydisplay);
    glutMouseFunc(MyMouseClick);

    glutMainLoop();
    return 0;
}