#ifndef MUSICLRCMANAGERFORDESKTOP_H
#define MUSICLRCMANAGERFORDESKTOP_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (c) 2014 - 2016 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musiclrcmanager.h"

class MUSIC_LRC_EXPORT MusicLRCManagerForDesktop : public MusicLRCManager
{
    Q_OBJECT
public:
    explicit MusicLRCManagerForDesktop(QWidget *parent = 0);
    virtual ~MusicLRCManagerForDesktop();

    void setSelfGeometry(const QPoint &point);
    void setSelfGeometry(int x, int y);
    int x() const;
    void resetOrigin();
    void setLrcFontSize(int size);
    inline int getFirstFontSize() const { return m_font.pointSize(); }

protected:
    virtual void paintEvent(QPaintEvent *event) override;

};

#endif // MUSICLRCMANAGERFORDESKTOP_H