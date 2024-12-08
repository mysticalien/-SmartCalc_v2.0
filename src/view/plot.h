#ifndef PLOT_H
#define PLOT_H

#include <QDialog>
#include <QString>
#include <QVector>
#include <string>

#include "../model/calc_model.h"

namespace Ui {
class Plot;
}

class Plot : public QDialog {
  Q_OBJECT

 public:
  explicit Plot(QWidget *parent = nullptr);
  ~Plot();
  void makePlot(const std::string &str);

 private slots:
  void on_xmin_editingFinished();
  void on_xmax_editingFinished();
  void on_ymin_editingFinished();
  void on_ymax_editingFinished();

 private:
  Ui::Plot *ui;
  std::string expr;
  double minX, maxX, minY, maxY;
  double step;
  QVector<double> vectorX, vectorY;
  int N;
  s21::Calculator calculator;
  void renderPlot();
  void addScaleLabel();
};

#endif  // PLOT_H
