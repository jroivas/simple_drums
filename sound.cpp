#include <QDebug>
#include <QAudioDeviceInfo>
#include <QIODevice>
#include <QSound>
#include <QAudioDecoder>
#include <QMediaPlayer>
#include <QUrl>
#include "sound.h"

Sound::Sound()
{
    format.setSampleRate(22050);
    format.setChannelCount(2);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);
    if (!format.isValid()) {
        qWarning() << "Invalid format";
        return;
    }

    qDebug() << "Devices:";
    foreach (const QAudioDeviceInfo &deviceInfo, QAudioDeviceInfo::availableDevices(QAudio::AudioOutput))
        qDebug() << "Device name: " << deviceInfo.deviceName();
    qDebug() << "---";
    foreach (const QAudioDeviceInfo &deviceInfo, QAudioDeviceInfo::availableDevices(QAudio::AudioInput))
        qDebug() << "Device name: " << deviceInfo.deviceName();
    qDebug() << "---";
    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format)) {
        format = info.nearestFormat(format);
    }
    qDebug() << format.sampleRate();
    qDebug() << format.channelCount();
    qDebug() << format.sampleSize();
    qDebug() << format.codec();
    qDebug() << format.byteOrder();
    qDebug() << format.sampleType();

    if (!info.isFormatSupported(format)) {
        qWarning() << "Raw audio format not supported by backend, cannot play audio.";
        return;
    }

    std::vector <std::string> waves = {
        "bass.wav", "crash.wav", "snare.wav",
        "hihat.wav", "kick.wav"
    };
    for (auto item : waves) {
        QFile tmp(("sound/" + item).c_str());
        tmp.open(QIODevice::ReadOnly);
        sounds.push_back(tmp.readAll());
    }

    for (auto _ : sounds) {
        (void)_;
        QAudioOutput *tmp_audio = new QAudioOutput(format, this);
        audio.push_back(tmp_audio);
        connect(
            tmp_audio, SIGNAL(stateChanged(QAudio::State)),
            this, SLOT(handleStateChanged(QAudio::State)));
    }

}

Sound::~Sound()
{
}

bool Sound::play(int num)
{
    if (num < 0)
        return false;
    if ((unsigned int)num > sounds.size()) {
        return false;
    }

    qDebug() << "Play: "<< num;
    QBuffer *tmp = new QBuffer(&sounds[num]);
    tmp->open(QIODevice::ReadOnly);

    stack.push_back(tmp);
    QAudioOutput *tmp_audio = new QAudioOutput(format, this);
    connect(
        tmp_audio, SIGNAL(stateChanged(QAudio::State)),
        this, SLOT(handleStateChanged(QAudio::State)));
    tmp_audio->start(tmp);

    return true;
}

bool Sound::play(QString ff)
{
    qDebug() << "Play: "<< ff;
    QSound::play(ff);
    return true;
}

void Sound::handleStateChanged(QAudio::State newState)
{
    switch (newState) {
        case QAudio::IdleState:
            {
                QAudioOutput *tmp = qobject_cast<QAudioOutput*>(sender());
                if (tmp != nullptr) {
                    tmp->stop();
                    tmp->deleteLater();
                }
                while (stack.size() > 0) {
                    if (stack[0]->pos() >= stack[0]->size())
                        stack.erase(stack.begin());
                    else
                        break;
                }
            }
            break;

        case QAudio::StoppedState:
            break;

        default:
            break;
    }
}
