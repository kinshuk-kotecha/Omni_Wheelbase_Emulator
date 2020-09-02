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
    const QString helperFunctions = R"~(

     float getWheelbasePos_X() {
         float wb_pos_x = 0;
         cout << "getWheelbasePos_X()" << endl;
         cin >> wb_pos_x;
         return wb_pos_x;
     }

     float getWheelbasePos_Y() {
         float wb_pos_y = 0;
         cout << "getWheelbasePos_Y()" << endl;
         cin >> wb_pos_y;
         return wb_pos_y;
     }

     float getWheelbaseVel_X() {
         float wb_vel_x = 0;
         cout << "getWheelbaseVel_X()" << endl;
         cin >> wb_vel_x;
         return wb_vel_x;
     }

     float getWheelbaseVel_Y() {
         float wb_vel_y = 0;
         cout << "getWheelbaseVel_Y()" << endl;
         cin >> wb_vel_y;
         return wb_vel_y;
     }

     void setWheelbaseVel(float x, float y) {
         cout << "setWheelbaseVel()" << '\n';
         cout << x << '\n';
         cout << y << endl;
     }
                             )~";
};

#endif // MAINWINDOW_H
