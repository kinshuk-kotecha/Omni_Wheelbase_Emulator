#include "UserProcess.h"
#include <QDebug>

UserProcess::UserProcess() {
    setReadChannel(QProcess::StandardOutput);
    start("./a.out");
}
