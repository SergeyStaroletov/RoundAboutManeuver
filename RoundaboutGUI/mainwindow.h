#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButtonStart_clicked();

  void on_pushButtonManeur_clicked();
 public slots:

  void onaddline(double x0, double y0, double x, double y, QColor color);

 private:
  Ui::MainWindow *ui;
  QGraphicsScene *m_graphicsScene;
};

#endif  // MAINWINDOW_H
