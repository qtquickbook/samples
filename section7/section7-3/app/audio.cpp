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
#include "audio.h"
#include <QAudioInput>

QAudioFormat selectFormat(const QAudioDeviceInfo &audioInputDevice)
{
    QList<int> sampleRatesList;
    sampleRatesList += audioInputDevice.supportedSampleRates();
    qSort(sampleRatesList);

    QList<int> channelsList;
    channelsList += audioInputDevice.supportedChannelCounts();
    qSort(channelsList);

    QAudioFormat format;
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setCodec("audio/pcm");
    format.setSampleSize(16);
    format.setSampleType(QAudioFormat::SignedInt);
    int sampleRate, channels;
    foreach (sampleRate, sampleRatesList) {
        format.setSampleRate(sampleRate);
        foreach (channels, channelsList) {
            format.setChannelCount(channels);
            const bool inputSupport = audioInputDevice.isFormatSupported(format);
            if (inputSupport) {
                return format;
            }
        }
    }
    return QAudioFormat();
}

Audio::Audio(const QAudioDeviceInfo &info, QObject *parent)
  : QObject(parent)
  , m_level(0)
{
    m_info = info;
    m_format = selectFormat(info);
    m_audioinput = new QAudioInput(m_info, m_format, this);
    m_input = m_audioinput->start();
    connect(m_input, SIGNAL(readyRead()), this, SLOT(inputHandler()));
}

void Audio::inputHandler()
{
    QByteArray data = m_input->readAll();
    int max = 0;
    int length = data.size() / 2;
    qint16 *p = reinterpret_cast<qint16*>(data.data());
    for (int i = 0; i < length; i++) {
        int v = p[i];
        max = qMax(v, max);
    }
    m_level = (qreal)max / SHRT_MAX;
    emit levelChanged();
}

qreal Audio::level() const
{
    return m_level;
}
