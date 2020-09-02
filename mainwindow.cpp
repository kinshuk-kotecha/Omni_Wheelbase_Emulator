#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QFile>
#include <QDebug>
#include "EmulatorView.h"
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene(this);
    QTimer *timer = new QTimer();
    Wheelbase *wheelbase = new Wheelbase();
    emulator = new Emulator(timer, scene, wheelbase);
    ui->emulatorView->initialise(scene);
    ui->codeEditor->setHighlighter(&highlighter);
    ui->enterButton->connect(ui->enterButton, SIGNAL (clicked()),this, SLOT (response_submitted()));
    ui->nextButton->connect(ui->nextButton, SIGNAL (clicked()), this, SLOT (nextLevel()));
    nextLevel();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete emulator;
    delete process;
}

void MainWindow::response_submitted() {
    QString data = ui->codeEditor->toPlainText();
    data += helperFunctions;
    TextToFile(data);
    if (!compile())
        return;
    process = new UserProcess();
    process->connect(process,SIGNAL(readyReadStandardOutput()),this,SLOT(handle_user_output()));
    process->connect(process, QOverload<int>::of(&QProcess::finished), [this](){ process->kill(); process->deleteLater(); process = nullptr; } );
}

bool MainWindow::TextToFile(QString text) {
    QFile file("main.cpp");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        ui->textBrowser->append(QString("\nOpen Failed"));
        return false;
    }

    file.write(text.toUtf8());
    return true;
}

bool MainWindow::compile() {
    QProcess p;
    QStringList arguments = {"main.cpp"};
    p.start("g++",arguments);
    p.waitForFinished();
    if(p.exitCode() != 0) {
        ui->textBrowser->append(QString("\nCompilation Failed"));
        return false;
    }
    ui->textBrowser->append(QString("\nCompilation Successful"));
    return true;
}

void MainWindow::handle_user_output() {
    QStringList output = QString(process->readAllStandardOutput()).split(QRegExp("[\n]"),QString::SkipEmptyParts);
    for (int i = 0; i < output.length(); i++) {
        if (output[i] == "getWheelbasePos_X()") {
            process->write(QString().setNum(emulator->wheelbase->get_pos().x).toUtf8());
            process->write(QString("\n").toUtf8());
        }
        else if (output[i] == "getWheelbasePos_Y()") {
            process->write(QString().setNum(emulator->wheelbase->get_pos().y).toUtf8());
            process->write(QString("\n").toUtf8());
        }
        else if (output[i] == "getWheelbaseVel_X()") {
            process->write(QString().setNum(emulator->wheelbase ->get_real_velocity().x).toUtf8());
            process->write(QString("\n").toUtf8());
        }
        else if (output[i] == "getWheelbaseVel_Y()") {
            process->write(QString().setNum(emulator->wheelbase->get_real_velocity().y).toUtf8());
            process->write(QString("\n").toUtf8());
        }
        else if (output[i] == "setWheelbaseVel()") {
            if (output.length() < i+3) {
                ui->textBrowser->append(QString("Proper Use ofSetWheelbaseVel():\ncout << SetWheelbaseVel() << endl;\ncout << float(x vel) << endl;\ncout << float(y vel) << endl;").toUtf8());
                return;
            }
            emulator->set_user_vel(XYTheta{.x = output[i+1].toFloat(),.y = output[i+2].toFloat(),.theta = 0});
            i = i+2;
        }
        else {
            ui->textBrowser->append(output[i]);
        }
    }
}

void MainWindow::nextLevel() {
    switch(emulator->level) {
        case BEGINNER:
            ui->codeEditor->setText(QString(R"~(
#include <iostream>
using namespace std;

/* Helper Functions */

float getWheelbasePos_X();
float getWheelbasePos_Y();
float getWheelbaseVel_X();
float getWheelbaseVel_Y();
void setWheelbaseVel(float x, float y);

int main() {

}
                                        )~"));
            ui->textBrowser->setText(QString("Welcome to the Omni Wheelbase Emulator\nUse the functions and try to reach the target\n"));
            ui->textBrowser->append(QString("You can look up the available functions in the documentation"));
            break;
        case INTRO_TRAPEZOID:
            ui->textBrowser->setText(QString(""));
            break;
        case INTRO_PID:
            break;
        case END:
            break;
    }
    emulator->level = static_cast<LEVEL>(static_cast<int>(emulator->level)+1);
}

