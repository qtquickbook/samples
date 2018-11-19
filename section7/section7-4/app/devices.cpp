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
#include "devices.h"
#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <QPainter>

Devices::Devices(QObject *parent)
    : QAbstractListModel(parent)
{
    QList<QAudioDeviceInfo> list = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    QAudioDeviceInfo defaultInfo = QAudioDeviceInfo::defaultInputDevice();
    for (int i = 0; i < list.size(); i++) {
        const QAudioDeviceInfo &info = list.at(i);
        Audio *audio = new Audio(info, this);
        m_list.append(audio);
        connect(audio, &Audio::levelChanged, [=] {
            emit dataChanged(index(i), index(i), QVector<int>() << Devices::Level);
        });
        connect(audio, &Audio::activeChanged, [=] {
            emit dataChanged(index(i), index(i), QVector<int>() << Devices::Active);
        });
        if (i == 0) {
            audio->setActive(true);
        }
    }
}

int	Devices::rowCount(const QModelIndex& parent) const
{
    return m_list.size();
}

QVariant Devices::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    switch(role) {
    case Devices::Name:
        return QVariant(m_list.at(index.row())->name());
    case Devices::Level:
        return m_list.at(index.row())->level();
    case Devices::Active:
        return m_list.at(index.row())->active();
    case Devices::Disconnected:
        return QVariant(false);
    default:
        ;
    }
    return QVariant();
}

bool Devices::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }
    if (!value.isValid()) {
        return false;
    }
    switch (role) {
    case Devices::Active:
        m_list.at(index.row())->setActive(value.toBool());
        break;
    default:
        return false;
    }
    return true;
}

QHash<int, QByteArray> Devices::roleNames() const
{
    QHash<int, QByteArray> ret;
    ret.insert(Devices::Name, "name");
    ret.insert(Devices::Level, "inputlevel");
    ret.insert(Devices::Active, "active");
    ret.insert(Devices::Disconnected, "disconnected");
    return ret;
}
