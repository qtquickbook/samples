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
#include <QPainter>
#include <QAudioInput>
#include <QDateTime>
#include <QPixmap>

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
  , m_interval(0)
{
    m_info = info;
    m_format = selectFormat(info);
    m_audioinput = new QAudioInput(m_info, m_format);
    m_spectrumBufferLength = SpectrumLengthSamples * (m_format.sampleSize() / 8) * m_format.channelCount();
    m_spectrumAnalyser = new SpectrumAnalyser(this);
    qRegisterMetaType<FrequencySpectrum>("FrequencySpectrum");
    connect(m_spectrumAnalyser, SIGNAL(spectrumChanged(FrequencySpectrum)), this, SLOT(addLine(FrequencySpectrum)));
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

    m_buffer.append(data);
    int interval = (m_format.sampleRate() / 2) * (m_format.sampleSize() / 8) * m_format.channelCount();
    int maxLen = qMax(interval , m_spectrumBufferLength);
    if (m_buffer.size() - m_interval >= interval && m_buffer.size() >= m_spectrumBufferLength && m_spectrumAnalyser->isReady()) {
        m_spectrumAnalyser->calculate(m_buffer.left(m_spectrumBufferLength), m_format);
        m_interval = interval;
        int willRemove = m_buffer.size() - maxLen;
        if (willRemove > 0) {
            m_buffer = m_buffer.right(maxLen);
            m_interval -= willRemove;
        }
    }
}

void Audio::addLine(FrequencySpectrum spectrum)
{
    int i = 0;
    FrequencySpectrum::const_iterator it = spectrum.begin();
    const FrequencySpectrum::const_iterator end = spectrum.end();
    QImage image(SpectrumLengthSamples / 2, 1, QImage::Format_ARGB32_Premultiplied);
    for ( ; it != end && i < image.width(); it++, i++) {
        const FrequencySpectrum::Element &e = *it;
        int v = e.amplitude * 256.0;
        image.setPixel(it - spectrum.begin(), 0, qRgb(v,v,v));
    }
    m_graph.append(QPixmap::fromImage(std::move(image)));
    if (m_graph.size() > SpectrumLengthSamples / 2) {
        m_graph.takeFirst();
    }
    m_sequence = QString::number(QDateTime::currentMSecsSinceEpoch());
    emit sequenceChanged();
}

bool Audio::active() const
{
    return m_audioinput->state() == QAudio::ActiveState ? true :
           m_audioinput->state() == QAudio::IdleState   ? true : false;
}

void Audio::setActive(bool act) {
    if (act) {
        if (m_audioinput->state() != QAudio::ActiveState && m_audioinput->state() != QAudio::IdleState) {
            start();
        }
    } else {
        if (m_audioinput->state() != QAudio::StoppedState) {
            stop();
        }
    }
}

void Audio::start() {
    m_input = m_audioinput->start();
    connect(m_input, SIGNAL(readyRead()), this, SLOT(inputHandler()));
}

void Audio::stop() {
    m_audioinput->stop();
    m_input->disconnect(this);
}

qreal Audio::level() const
{
    return m_level;
}

QString Audio::sequence() const
{
    return m_sequence;
}

qreal Audio::sampleRate() const
{
    return m_format.sampleRate();
}
