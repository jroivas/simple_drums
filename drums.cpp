#include "drums.h"

Drums::Drums()
    : QWidget(0)
{
    b1 = new QPushButton("bass");
    b2 = new QPushButton("crash");
    b3 = new QPushButton("snare");
    b4 = new QPushButton("hihat");
    b5 = new QPushButton("kick");

    lay.addWidget(b1);
    lay.addWidget(b2);
    lay.addWidget(b3);
    lay.addWidget(b4);
    lay.addWidget(b5);
    setLayout(&lay);

    mapper = new QSignalMapper(this);
    connect(
        b1, SIGNAL(clicked()),
        mapper, SLOT(map()));
    connect(
        b2, SIGNAL(clicked()),
        mapper, SLOT(map()));
    connect(
        b3, SIGNAL(clicked()),
        mapper, SLOT(map()));
    connect(
        b4, SIGNAL(clicked()),
        mapper, SLOT(map()));
    connect(
        b5, SIGNAL(clicked()),
        mapper, SLOT(map()));

    mapper->setMapping(b1, 0);
    mapper->setMapping(b2, 1);
    mapper->setMapping(b3, 2);
    mapper->setMapping(b4, 3);
    mapper->setMapping(b5, 4);

    connect(
        mapper, SIGNAL(mapped(int)),
        &snd, SLOT(play(int)));

    m_manager = new QGamepadManager(this);
    m_inputState = new QGamepadInputState(this);

    connect(
        m_manager, SIGNAL(gamepadEvent(QGamepadInfo*,quint64,int,int,int)),
        m_inputState, SLOT(processGamepadEvent(QGamepadInfo*,quint64,int,int,int)));

    connect(
        m_inputState, SIGNAL(stateUpdated()),
        this, SLOT(printStatus()));
}

Drums::~Drums()
{
}

void Drums::printStatus()
{
    // Red
    if (m_inputState->queryGamepadButton((QGamepadInputState::Buttons)306))
        snd.play(2); //snare
    // Yellow
    if (m_inputState->queryGamepadButton((QGamepadInputState::Buttons)307))
        snd.play(3); //hihat
    // Blue
    if (m_inputState->queryGamepadButton((QGamepadInputState::Buttons)304))
        snd.play(0); //bass
    // Green
    if (m_inputState->queryGamepadButton((QGamepadInputState::Buttons)305))
        snd.play(1); //crash
    // Pedal
    if (m_inputState->queryGamepadButton((QGamepadInputState::Buttons)308))
        snd.play(4); //kick
}
