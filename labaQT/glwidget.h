#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class GLWidget : public QGLWidget
{
    Q_OBJECT
private:
    int fig;
    GLfloat xRot;
    GLfloat yRot;
    GLfloat zRot;
    GLfloat zTra;
    GLfloat nSca;

    int scx,scy,he,wi;
    float alpha;
    QPoint ptrMousePosition;
public:

    explicit GLWidget(QWidget *parent = 0);
    void drawAxis();
    void initializeGL();
    void paintGL();
    void resizeGL(int nWidth, int nHeight);
    void mousePressEvent(QMouseEvent* pe);
    void mouseMoveEvent(QMouseEvent* pe);
    void mouseReleaseEvent(QMouseEvent* pe);
    void setFigure(int input);

    void drawPolygon();
    void drawQuadStrip();
    void drawQuad();
    void drawTrFan();
    void drawTrStrip();
    void drawTr();
    void drawLineLoop();
    void drawLineStrip();
    void drawLine();
    void drawPoint();
    void setSci(int x,int y,int h,int w);
    void setAlpha(float input);
};

#endif // GLWIDGET_H
