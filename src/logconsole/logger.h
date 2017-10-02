/****************************************************************************
**
** Copyright (C) 2016 Pelagicore AG
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QmlLive tool.
**
** $QT_BEGIN_LICENSE:GPL-QTAS$
** Commercial License Usage
** Licensees holding valid commercial Qt Automotive Suite licenses may use
** this file in accordance with the commercial license agreement provided
** with the Software or, alternatively, in accordance with the terms
** contained in a written agreement between you and The Qt Company.  For
** licensing terms and conditions see https://www.qt.io/terms-conditions.
** For further information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
** SPDX-License-Identifier: GPL-3.0
**
****************************************************************************/

#pragma once

#include <QObject>
#include <QMutex>
#include <QUrl>

#include "qmllive_global.h"

class QMLLIVESHARED_EXPORT Logger : public QObject
{
    Q_OBJECT
public:
    virtual ~Logger();
    static Logger *instance(){
        if (!s_instance){
            s_instance = new Logger();
        }
        return s_instance;
    }

public Q_SLOTS:
    static void setIgnoreMessages(bool ignoreMessages);

Q_SIGNALS:
    void message(int type, const QString &msg, const QUrl &url = QUrl(), int line = -1, int column = -1);

private:
    static Logger *s_instance;
    static bool s_ignoreMesssages;
    static QMutex m_mutex;
    explicit Logger(QObject *parent = 0);
    static void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);
};
