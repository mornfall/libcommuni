/*
* Copyright (C) 2008-2013 The Communi Project
*
* This library is free software; you can redistribute it and/or modify it
* under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation; either version 2 of the License, or (at your
* option) any later version.
*
* This library is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
* License for more details.
*/

#ifndef IRCNETWORK_H
#define IRCNETWORK_H

#include <IrcGlobal>
#include <QtCore/qobject.h>
#include <QtCore/qstringlist.h>
#include <QtCore/qscopedpointer.h>

IRC_BEGIN_NAMESPACE

class IrcConnection;
class IrcNetworkPrivate;

class IRC_CORE_EXPORT IrcNetwork : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QStringList modes READ modes NOTIFY modesChanged)
    Q_PROPERTY(QStringList prefixes READ prefixes NOTIFY prefixesChanged)
    Q_PROPERTY(QStringList channelTypes READ channelTypes NOTIFY channelTypesChanged)
    Q_PROPERTY(QStringList availableCapabilities READ availableCapabilities NOTIFY availableCapabilitiesChanged)
    Q_PROPERTY(QStringList activeCapabilities READ activeCapabilities NOTIFY activeCapabilitiesChanged)

public:
    explicit IrcNetwork(IrcConnection* connection);
    virtual ~IrcNetwork();

    bool isValid() const;

    QString name() const;

    QStringList modes() const;
    QStringList prefixes() const;

    Q_INVOKABLE QString modeToPrefix(const QString& mode) const;
    Q_INVOKABLE QString prefixToMode(const QString& prefix) const;

    QStringList channelTypes() const;

    enum ModeType {
        TypeA    = 0x1,
        TypeB    = 0x2,
        TypeC    = 0x4,
        TypeD    = 0x8,
        AllTypes = 0xf
    };
    Q_DECLARE_FLAGS(ModeTypes, ModeType)

    QStringList channelModes(ModeTypes types) const;

    enum Limit {
        NickLength,
        ChannelLength,
        TopicLength,
        MessageLength,
        KickReasonLength,
        AwayReasonLength,
        ModeCount
    };

    int numericLimit(Limit limit) const;

    int modeLimit(const QString& mode = QString()) const;
    int channelLimit(const QString& type = QString()) const;
    int targetLimit(const QString& command = QString()) const;

    QStringList availableCapabilities() const;
    QStringList activeCapabilities() const;

Q_SIGNALS:
    void nameChanged(const QString& name);
    void modesChanged(const QStringList& modes);
    void prefixesChanged(const QStringList& prefixes);
    void channelTypesChanged(const QStringList& types);
    void availableCapabilitiesChanged(const QStringList& capabilities);
    void activeCapabilitiesChanged(const QStringList& capabilities);

private:
    QScopedPointer<IrcNetworkPrivate> d_ptr;
    Q_DECLARE_PRIVATE(IrcNetwork)
    Q_DISABLE_COPY(IrcNetwork)
};

Q_DECLARE_OPERATORS_FOR_FLAGS(IrcNetwork::ModeTypes)

IRC_END_NAMESPACE

#endif // IRCNETWORK_H