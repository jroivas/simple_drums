#pragma once

#include <QAudioOutput>
#include <QAudioFormat>
#include <QFile>
#include <QObject>
#include <QBuffer>
#include <vector>
#include <QAudioRecorder>
#include <QMediaRecorder>

class Sound : public QObject
{
Q_OBJECT
public:
    Sound();
    virtual ~Sound();

public slots:
    void handleStateChanged(QAudio::State newState);
    bool play(int num);
    bool play(QString ff);

private:
    QAudioFormat format;
    std::vector<QAudioOutput *> audio;
    std::vector<QByteArray> sounds;
    std::vector<QBuffer*> stack;
    QAudioRecorder *record;
};
