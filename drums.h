#pragma once

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QtGamepad/QGamepadManager>
#include <QtGamepad/QGamepadInputState>

#include "sound.h"

class Drums : public QWidget
{
Q_OBJECT
public:
    Drums();
    virtual ~Drums();

public slots:
    void printStatus();

private:
    QPushButton *b1;
    QPushButton *b2;
    QPushButton *b3;
    QPushButton *b4;
    QPushButton *b5;
    QHBoxLayout lay;
    Sound snd;
    QSignalMapper *mapper;

    QGamepadManager *m_manager;
    QGamepadInputState *m_inputState;
};
