#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QGraphicsScene>
#include <QThread>

class MyThread : public QThread {
  Q_OBJECT
 private:
  QGraphicsScene *m_graphicsScene;

 public:
  MyThread(QGraphicsScene *graphicsScene) {
    this->m_graphicsScene = graphicsScene;
  }
  virtual void run();
 signals:
  void addline(double x1, double y1, double x2, double y2, QColor color);
};
#endif  // MYTHREAD_H
