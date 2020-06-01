#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QVector>
#include <QTableWidget>
#include <QProgressBar>
#include <QHeaderView>
#include "longprocess.h"
namespace Ui {

class MainWindow;
}
typedef QPair<QThread *,LongProcess *> TPair;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void update(int n,int i);
    void deleteLater(int n);
private:

    QVector<TPair*> processes;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
