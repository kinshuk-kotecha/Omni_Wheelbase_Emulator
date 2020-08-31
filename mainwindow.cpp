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
    ui->textBrowser->setText(QString("Welcome to the Omni Wheelbase Emulator\n1. Type some code and try to move the wheelbase"));
    ui->pushButton->connect(ui->pushButton, SIGNAL (clicked()),this, SLOT (response_submitted()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete emulator;
    delete process;
}

void MainWindow::response_submitted() {
    QString data = ui->textEdit->toPlainText();
    TextToFile(data);
    compile();
    process = new UserProcess();
    process->connect(process,SIGNAL(readyReadStandardOutput()),this,SLOT(handle_user_output()));
    process->connect(process, QOverload<int>::of(&QProcess::finished), [this](){ process->kill(); process->deleteLater(); process = nullptr; } );
}

bool MainWindow::TextToFile(QString text) {
    QFile file("main.cpp");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        ui->textBrowser->append(QString("\n\nOpen Failed"));
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
        ui->textBrowser->append(QString("\n\nCompilation Failed"));
        return false;
    }
    ui->textBrowser->append(QString("\n\nCompilation Successful"));
    return true;
}

void MainWindow::handle_user_output() {
    QStringList output = QString(process->readAllStandardOutput()).split(QRegExp("[\n]"),QString::SkipEmptyParts);
    if (output[0] == "GetWheelbasePos_X()") {
        process->write(QString().setNum(emulator->wheelbase->get_pos().x).toUtf8());
        process->write(QString("\n").toUtf8());
    }
    else if (output[0] == "GetWheelbasePos_Y()") {
        process->write(QString().setNum(emulator->wheelbase->get_pos().y).toUtf8());
        process->write(QString("\n").toUtf8());
    }
    else if (output[0] == "GetWheelbaseVel_X()") {
        process->write(QString().setNum(emulator->wheelbase->get_real_velocity().x).toUtf8());
        process->write(QString("\n").toUtf8());
    }
    else if (output[0] == "GetWheelbaseVel_Y()") {
        process->write(QString().setNum(emulator->wheelbase->get_real_velocity().y).toUtf8());
        process->write(QString("\n").toUtf8());
    }
    else if (output[0] == "SetWheelbaseVel()") {
        if (output.length() != 3) {
            ui->textBrowser->append(QString("Proper Use of SetWheelbaseVel():\ncout << SetWheelbaseVel() << float(x vel) << float(y vel) << endl;").toUtf8());
            return;
        }
        emulator->wheelbase->set_opt_vel(XYTheta{.x = output[1].toFloat(),.y = output[2].toFloat(),.theta = 0});
    }
    else {
        ui->textBrowser->append(output[0]);
    }
}

