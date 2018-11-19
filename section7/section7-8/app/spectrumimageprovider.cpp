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
#include "spectrumimageprovider.h"
#include <QPainter>
#include <QDebug>
#include <QMap>
#include "devices.h"

SpectrumImageProvider::SpectrumImageProvider(Devices *spectrumImage)
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
    , m_spectrumImage(spectrumImage)
{
    for (int i = 0; i < m_spectrumImage->rowCount(); i++) {
        QPixmap pix(SpectrumLengthSamples / 2, SpectrumLengthSamples / 2);
        pix.fill(QColor(Qt::black));
        m_images.append(pix);
    }
}

QPixmap SpectrumImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    QPixmap p;
    int sep = id.indexOf("/");
    if (sep > 0) {
        bool ok;
        int idx = id.left(sep).toInt(&ok);
        p = createPixmap(idx);
    }
    *size = p.size();
    return p;
}

QPixmap SpectrumImageProvider::createPixmap(int device)
{
    QPixmap &pix = m_images[device];
    pix.fill(QColor(Qt::black));
    QPainter p(&pix);
    const QList<QPixmap> &graph = m_spectrumImage->m_list.at(device)->graph();
    for (int i = 0; i < graph.size(); i++) {
        p.drawPixmap(0, graph.size() - i, graph.at(i));
    }
    p.end(); // for enable Implicit Sharing.
    return pix;
}

