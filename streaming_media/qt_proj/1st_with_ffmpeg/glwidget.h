
#pragma once

#include <QOpenGLWidget>
//#include <QOpenGLFunctions>
#include <QOpenGLFunctions_3_3_Core>
#include <qopenglshaderprogram.h>
#include <QOpenGLTexture>
#include <qopenglpixeltransferoptions.h>

struct AVFrame;

// public QOpenGLFunctions
class GLWidget : public QOpenGLWidget, public QOpenGLFunctions_3_3_Core
{
  Q_OBJECT
public:
  explicit GLWidget(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
  ~GLWidget() override;

public slots:
  void repaint(AVFrame* frame); // 设置需要绘制的图像帧

public:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

signals:
  void signal_on_avframe(AVFrame *frame);

private:
  // YUV420图像数据更新
  void repaintTexYUV420P(AVFrame* frame);
  void initTexYUV420P(AVFrame* frame);
  void freeTexYUV420P();
  // NV12图像数据更新
  void repaintTexNV12(AVFrame* frame);
  void initTexNV12(AVFrame* frame);
  void freeTexNV12();

private:
  QOpenGLShaderProgram* m_program = nullptr;
  QOpenGLTexture* m_texY = nullptr;
  QOpenGLTexture* m_texU = nullptr;
  QOpenGLTexture* m_texV = nullptr;
  QOpenGLTexture* m_texUV = nullptr;
  QOpenGLPixelTransferOptions m_options;

  GLuint VBO = 0;       // 顶点缓冲对象,负责将数据从内存放到缓存，一个VBO可以用于多个VAO
  GLuint VAO = 0;       // 顶点数组对象,任何随后的顶点属性调用都会储存在这个VAO中，一个VAO可以有多个VBO
  GLuint EBO = 0;       // 元素缓冲对象,它存储 OpenGL 用来决定要绘制哪些顶点的索引
  QSize  m_size;
  QSizeF  m_zoomSize;
  QPointF m_pos;
  int m_format;         // 像素格式
};
