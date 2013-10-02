#include <QtGui>
#include <math.h>

#include "glwidget.h"
#include "mainwindow.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    fig=0;
    xRot=-45; yRot=0; zRot=-45; zTra=0; nSca=1;
    scx=0;
    scy=0;
    wi=1000;
    he=1000;
    alpha=1;
    com_alpha=1;
}

void GLWidget::initializeGL(){


   glClearColor(0,0,0,1);/*цвет области рисования */
   GLfloat light_col[] = {1,1,1};
   qglClearColor(Qt::white);
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_FLAT);
   glEnable(GL_CULL_FACE);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_col);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_COLOR_MATERIAL);
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);


}
void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(nSca, nSca, nSca);
    glTranslatef(0.0f, zTra, 0.0f);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot, 0.0f, 0.0f, 1.0f);
    drawAxis();

    glEnable(GL_ALPHA_TEST);
    glEnable(GL_SCISSOR_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glScissor(scx,scy,wi,he);

    glAlphaFunc(GL_GREATER,alpha);
    switch (fig)
    {
        case 0:
        break;
        case 1:
        drawPolygon();
        break;
        case 2:
        drawQuadStrip();
        break;
        case 3:
        drawQuad();
        break;
        case 4:
        drawTrFan();
        break;
        case 5:
        drawTrStrip();
        break;
        case 6:
        drawTr();
        break;
        case 7:
        drawLineLoop();
        break;
        case 8:
        drawLineStrip();
        break;
        case 9:
        drawLine();
        break;
        case 10:
        drawPoint();
        break;
    }
    glDisable(GL_BLEND);
  glDisable(GL_SCISSOR_TEST);//запрещаю рисовать
  glDisable(GL_ALPHA_TEST);
}
void GLWidget::resizeGL(int nWidth, int nHeight)
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   GLfloat ratio=(GLfloat)nHeight/(GLfloat)nWidth;

   if (nWidth>=nHeight)
      glOrtho(-1.0/ratio, 1.0/ratio, -1.0, 1.0, -10.0, 1.0);
   else
      glOrtho(-1.0, 1.0, -1.0*ratio, 1.0*ratio, -10.0, 1.0);

   glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
}


void GLWidget::setFigure(int input)
{
    fig = input;

}

void GLWidget::mousePressEvent(QMouseEvent* pe)
{
   ptrMousePosition = pe->pos();
}

void GLWidget::mouseReleaseEvent(QMouseEvent* pe)
{

}

void GLWidget::mouseMoveEvent(QMouseEvent* pe)
{
   xRot += 180/nSca*(GLfloat)(pe->y()-ptrMousePosition.y())/height();
   zRot += 180/nSca*(GLfloat)(pe->x()-ptrMousePosition.x())/width();

   ptrMousePosition = pe->pos();

   updateGL();
}

void GLWidget::drawAxis()
{
   glLineWidth(3.0f);

   glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
   glBegin(GL_LINES);
      glVertex3d( 1.0f,  0.0f,  0.0f);
      glVertex3d(-1.0f,  0.0f,  0.0f);
   glEnd();

   QColor halfGreen(0, 128, 0, 255);
   qglColor(halfGreen);
   glBegin(GL_LINES);
      glVertex3d( 0.0f,  1.0f,  0.0f);
      glVertex3d( 0.0f, -1.0f,  0.0f);

      glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
      glVertex3d( 0.0f,  0.0f,  1.0f);
      glVertex3d( 0.0f,  0.0f, -1.0f);
   glEnd();
}

void GLWidget::drawPoint()
{
    glBegin(GL_POINTS);//рисуем точку
    glColor4f(1,0,0,com_alpha);
    glVertex3d(-0.05,-0.05,0);
    glEnd();
}

void GLWidget::drawLine()
{
    glBegin(GL_LINES);//рисуем прямую
    glColor4f(1,1,0,com_alpha);
    glVertex3d(-0.05,-0.05,0);
    glVertex3d(+0.05,-0.05,0);

    glEnd();
}

void GLWidget::drawLineStrip()
{
    glBegin(GL_LINE_STRIP);//рисуем последовательные прямые
    glColor4f(1.0, 0.0, 1.0,com_alpha);
    glVertex3d(-0.05,-0.05,0);
    glVertex3d(+0.05,-0.05,0);
    glVertex3d(+0.05,+0.05,0);

    glEnd();
}

void GLWidget::drawLineLoop()
{

    glBegin(GL_LINE_LOOP);//рисует замкнтые кривые линии
    glColor4f(1.0,0.5f,0.0f,com_alpha);
    glVertex3d(-1,-0.35,0);
    glVertex3d(+0.35,-1,0);
    glVertex3d(+0.35,+0.35,0);


    glEnd();
}

void GLWidget::drawTr()
{

    glBegin(GL_TRIANGLES);//сует треугольник
    glColor4f(0.35,0.12,0.457,com_alpha);
    glVertex3d(-0.35,-0.35,0);
    glVertex3d(+0.35,-0.35,0);
    glVertex3d(+0.35,+0.35,0);

    glEnd();
}

void GLWidget::drawTrStrip()
{
    glBegin(GL_TRIANGLE_STRIP);//рисуем много связанных треугольников
    glColor4f(0.6,0.1,0.5,com_alpha);
    glVertex3f( 0.5f, 0.5f, 0.0f ); //vertex 4
    glVertex3f( 0.0f, 0.5f, 0.0f ); //vertex 2
    glVertex3f( 0.5f, 0.0f, 0.0f ); //vertex 3
    glVertex3f( 0.0f, 0.0f, 0.0f ); //vertex 1

    glEnd();
}


void GLWidget::drawPolygon()
{
    glBegin(GL_POLYGON);
      glColor4f(0.7,0.05,0.1,com_alpha);
      glVertex3f(-0.2f,0.5f,-0.5f);
      glVertex3f(-0.5f,0.2f,-0.5f);
      glVertex3f(-0.5f,-0.2f,-0.5f);
      glVertex3f(-0.2f,-0.5f,-0.5f);
      glVertex3f(0.2f,-0.5f,-0.5f);
      glVertex3f( 0.5f,-0.2f,-0.5f);
      glVertex3f(0.5f,0.2f,  -0.5f);
      glVertex3f( 0.2f, 0.5f,-0.5f);




    glEnd();
}

void GLWidget::drawQuadStrip()
{
    glBegin(GL_QUAD_STRIP);
     glColor4f(0.46,0.21,0.15,com_alpha);
    glVertex3f( 0.5f, 0.5f, 0.0f ); //vertex 4
    glVertex3f( 0.0f, 0.5f, 0.0f ); //vertex 2
    glVertex3f( 0.5f, 0.0f, 0.0f ); //vertex 3
    glVertex3f( 0.0f, 0.0f, 0.0f ); //vertex 1

    glVertex3f( 0.5f, 0.5f, 0.0f ); //vertex 2
    glVertex3f( 0.5f, 0.0f, 0.0f ); //vertex 3
    glVertex3f( 0.8f, 0.8f, 0.0f ); //vertex 1
    glVertex3f( 1.0f, 0.5f, 0.0f ); //vertex 1

    glEnd();
}

void GLWidget::drawQuad()
{
    glBegin(GL_QUADS);
     glColor4f(0.46,0.0,0.95,com_alpha);
    glVertex3d(+0.25,-0.55,0);//1
    glVertex3d(+0.35,-0.35,0);//2
    glVertex3d(+0.35,+0.35,0);//3
    glVertex3d(-0.35,-0.35,0);//4




    glEnd();
}

void GLWidget::drawTrFan()
{
    glBegin(GL_TRIANGLE_FAN);
    glColor4f(0.46,0.0,0.95,com_alpha);
    glVertex3f( 0.5f, 0.5f, 0.0f ); //vertex 4
    glVertex3f( 0.0f, 0.5f, 0.0f ); //vertex 2
    glVertex3f( 0.5f, 0.0f, 0.0f ); //vertex 3

    glVertex3f( 0.5f, 0.5f, 0.0f ); //vertex 2
    glVertex3f( 0.5f, 0.0f, 0.0f ); //vertex 3
    glVertex3f( 0.8f, 0.8f, 0.0f ); //vertex 1


    glEnd();
}


void GLWidget::setSci(int x,int y,int h,int w)
{
    scx=x;
    scy=y;
    he=h;
    wi=w;
}

void GLWidget::setAlpha(float input)
{
    alpha=input;
}


void GLWidget::setCom_Alpha(float input)
{
    com_alpha=input;
}
