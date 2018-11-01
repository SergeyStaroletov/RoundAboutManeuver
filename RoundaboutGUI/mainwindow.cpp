#include "mainwindow.h"
#include <QColor>
#include <QDebug>
#include <QThread>
#include "mythread.h"
#include "ui_mainwindow.h"

#include "model.h"

static double t = 0;
static double dt = 0.01;
static unsigned delay = 200;

static double c1 = -1.5, c2 = -0.2, c3 = -10.1, c4 = 0.1, c5 = 1.5, c6 = 0.1,
              c7 = 0.1, c8 = 8;
static double om = 1, omy = 1;

static double x1 = c1, x2 = c2, y1 = c5, y2 = c6, d1 = 0.5, d2 = +0.0105,
              e1 = 0, e2 = 0;
static double x1_old, x2_old, y1_old, y2_old, d1_old, d2_old, e1_old, e2_old;

static double protectedzone = 0.1;

static bool isManeur = false;
static bool isRun = false;

static bool isStop = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  m_graphicsScene = new QGraphicsScene(this);
}

MainWindow::~MainWindow() { delete ui; }

void MyThread::run() {
  bool isFirst = true;

  while (!isManeur) {
    if (isStop) return;
    x1_old = x1;
    x2_old = x2;
    y1_old = y1;
    y2_old = y2;
    d1_old = d1;
    d2_old = d2;
    e1_old = e1;
    e2_old = e2;

    x1 = X1(t, om, c1, c3, c4);
    x2 = X2(t, om, c2, c3, c4);
    y1 = Y1(t, e1_old, c5);
    y2 = Y2(t, e2_old, c6);
    d1 = D1(t, om, c3, c4);
    d2 = D2(t, om, c3, c4);
    e1 = E1(t, omy, c7, c8);
    e2 = E2(t, omy, c7, c8);

    qDebug() << "time = " << t << " x1=" << x1 << " y1=" << y1 << " x2=" << x2
             << " y2=" << y2 << "\n";

    if (!check_safety(x1, x2, y1, y2, protectedzone)) {
      qDebug() << "violation of enter safety! \n";
    }
    if (!isFirst) {
      emit addline(x1_old, y1_old, x1, y1, Qt::blue);
      emit addline(x2_old, y2_old, x2, y2, Qt::red);
    } else
      isFirst = false;
    t += dt;
    QThread::msleep(delay);
  }

  isFirst = true;

  if (check_safety(x1, x2, y1, y2, protectedzone)) {
    double cc1 = 0.1;
    double cc2 = 0.2;

    // fix some positions
    d1 = ((-(om)) * ((x2) - (cc2)));
    d2 = ((om) * ((x1) - (cc1)));
    e1 = ((-(om)) * ((y2) - (cc2)));
    e2 = ((om) * ((y1) - (cc1)));

    printf("fix! \n");

    // go to maneur
    while (!isStop) {
      x1_old = x1;
      x2_old = x2;
      y1_old = y1;
      y2_old = y2;
      d1_old = d1;
      d2_old = d2;
      e1_old = e1;
      e2_old = e2;

      x1 = X1(t, om, c1, c3, c4);
      x2 = X2(t, om, c2, c3, c4);
      y1 = Y1(t, e1_old, c5);
      y2 = Y2(t, e2_old, c6);
      d1 = D1(t, om, c3, c4);
      d2 = D2(t, om, c3, c4);
      e1 = E1(t, omy, c7, c8);
      e2 = E2(t, omy, c7, c8);

      qDebug() << "f time = " << t << " x1=" << x1 << " y1=" << y1
               << " x2=" << x2 << " y2=" << y2 << "\n";

      if (!check_safety(x1, x2, y1, y2, protectedzone)) {
        qDebug() << "violation of enter safety\n";
      }

      if (!isFirst) {
        emit addline(x1_old, y1_old, x1, y1, Qt::black);
        emit addline(x2_old, y2_old, x2, y2, Qt::green);
      } else
        isFirst = false;

      t += dt;
      QThread::msleep(delay);
    }
  }
}

void MainWindow::onaddline(double x0, double y0, double x, double y,
                           QColor color) {
  int k = 10;
  QPen colorPen;
  colorPen.setColor(color);

  this->m_graphicsScene->addLine(x0 * k, y0 * k, x * k, y * k, colorPen);
}

void MainWindow::on_pushButtonStart_clicked() {
  if (isRun) {
    isStop = true;
    isRun = false;
    return;
  }

  isStop = false;
  isRun = true;

  ui->graphicsView->setScene(m_graphicsScene);

  MyThread *thread = new MyThread(m_graphicsScene);

  connect(thread, SIGNAL(addline(double, double, double, double, QColor)), this,
          SLOT(onaddline(double, double, double, double, QColor)));
  thread->start();
}

void MainWindow::on_pushButtonManeur_clicked() { isManeur = true; }
