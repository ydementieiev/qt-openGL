#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QOpenGLFunctions>
#include <QWindow>

QT_FORWARD_DECLARE_CLASS(QPainter)
QT_FORWARD_DECLARE_CLASS(QOpenGLContext)
QT_FORWARD_DECLARE_CLASS(QOpenGLPaintDevice)

class OpenGLWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT

  public:
    explicit OpenGLWindow(QWindow* parent = nullptr);
    ~OpenGLWindow();

    virtual void render(QPainter* painter);
    virtual void render();

    virtual void initialize();

    void setAnimating(bool animating);

  public Q_SLOTS:
    void renderLater();
    void renderNow();

  protected:
    bool event(QEvent* event) override;

    void exposeEvent(QExposeEvent* event) override;

  private:
    bool m_animating = false;

    QOpenGLContext* m_context = nullptr;
    QOpenGLPaintDevice* m_device = nullptr;
};

#endif // OPENGLWINDOW_H