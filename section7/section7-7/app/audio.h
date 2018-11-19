/**
 * Copyright (c) 2018 Nobumasa Murakami
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef AUDIO_H
#define AUDIO_H

#include <QObject>
#include <QAudioDeviceInfo>
#include <QPointer>
#include <QList>
#include <QPixmap>

#include "spectrumanalyser.h"

class QAudioInput;
class QIODevice;

class Audio : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal level READ level NOTIFY levelChanged)
    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(QString sequence READ sequence NOTIFY sequenceChanged)

public:
    Audio(const QAudioDeviceInfo &info, QObject *parent = 0);

    qreal level() const;
    bool  active() const;
    void  setActive(bool act);
    QString sequence() const;
    QList<QPixmap>   graph() const {
        return m_graph;
    }

    QString name() const {
        return m_info.deviceName();
    }
    qreal sampleRate() const;

signals:
    void levelChanged();
    void activeChanged();
    void sequenceChanged();

public slots:

private slots:
    void addLine(FrequencySpectrum spectrum);
    void inputHandler();

private:
    void start();
    void stop();

    QAudioDeviceInfo           m_info;
    QAudioFormat               m_format;
    QPointer<QAudioInput>      m_audioinput;
    int                        m_spectrumBufferLength;
    QPointer<SpectrumAnalyser> m_spectrumAnalyser;
    QPointer<QIODevice>        m_input;
    QByteArray                 m_buffer;
    qreal                      m_level;
    QList<QPixmap>             m_graph;
    QString                    m_sequence;
    int                        m_interval;

};

#endif // AUDIO_H
