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

public slots:
    void response_submitted();
    void handle_user_output();
    void nextLevel();

private:
    Ui::MainWindow *ui;
    Emulator *emulator;
    UserProcess* process = nullptr;
    bool TextToFile(QString text);
    bool compile();
};

#endif // MAINWINDOW_H
