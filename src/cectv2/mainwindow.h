#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "tausta.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void haeKonffi();


private slots:
    void kello();
    void on_listWidget_activated(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Tausta tausta;
};

#endif // MAINWINDOW_H
