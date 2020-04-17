/* =================================================
 * This file is part of the TTK qmmp plugin project
 * Copyright (C) 2015 - 2020 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ================================================= */

#include <QtPlugin>
#include "decoderalacfactory.h"
#include "decoder_alac.h"
#include "alachelper.h"

bool DecoderAlacFactory::canDecode(QIODevice *) const
{
    return false;
}

DecoderProperties DecoderAlacFactory::properties() const
{
    DecoderProperties properties;
    properties.name = tr("Alac Plugin");
    properties.filters << "*.alac";
    properties.description = tr("Apple Lossless Audio Codec Audio Files");
    properties.shortName = "alac";
    properties.hasSettings = false;
    properties.noInput = true;
    properties.protocols << "file";
    return properties;
}

Decoder *DecoderAlacFactory::create(const QString &path, QIODevice *)
{
    return new DecoderAlac(path);
}

QList<TrackInfo *> DecoderAlacFactory::createPlayList(const QString &path, TrackInfo::Parts parts, QStringList *)
{
    TrackInfo *info = new TrackInfo(path);

    if(parts == TrackInfo::NoParts)
    {
        return QList<TrackInfo *>() << info;
    }

    AlacHelper helper(path.toUtf8().constData());
    if(!helper.initialize())
    {
        delete info;
        return QList<TrackInfo *>();
    }

    if(parts & TrackInfo::Properties)
    {
        info->setValue(Qmmp::BITRATE, helper.bitrate());
        info->setValue(Qmmp::SAMPLERATE, helper.samplerate());
        info->setValue(Qmmp::CHANNELS, helper.channels());
        info->setDuration(helper.totalTime());
    }

    return QList<TrackInfo *>() << info;
}

MetaDataModel* DecoderAlacFactory::createMetaDataModel(const QString &, bool)
{
    return nullptr;
}

Q_EXPORT_PLUGIN2(alac,DecoderAlacFactory)