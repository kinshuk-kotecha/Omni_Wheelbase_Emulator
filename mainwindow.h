#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCodeEditor>
#include "Emulator.h"
#include "UserProcess.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void get_input();

public slots:
    void response_submitted();

private:
    Ui::MainWindow *ui;
    Emulator *emulator;
    UserProcess* process;
};

#endif // MAINWINDOW_H
