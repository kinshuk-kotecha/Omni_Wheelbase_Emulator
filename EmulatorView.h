#ifndef EMULATORVIEW_H
#define EMULATORVIEW_H

#include <QGraphicsView>

class EmulatorView : public QGraphicsView {
public:
    EmulatorView(QWidget* parent = nullptr);
    void initialise(QGraphicsScene* scene);
};

#endif // EMULATORVIEW_H
