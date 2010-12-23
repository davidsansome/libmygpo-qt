/***************************************************************************
* This file is part of libmygpo-qt                                         *
* Copyright (c) 2010 Stefan Derkits <stefan@derkits.at>                    *
* Copyright (c) 2010 Christian Wagner <christian.wagner86@gmx.at>          *
* Copyright (c) 2010 Felix Winter <ixos01@gmail.com>                       *
*                                                                          *
* This library is free software; you can redistribute it and/or            *
* modify it under the terms of the GNU Lesser General Public               *
* License as published by the Free Software Foundation; either             *
* version 2.1 of the License, or (at your option) any later version.       *
*                                                                          *
* This library is distributed in the hope that it will be useful,          *
* but WITHOUT ANY WARRANTY; without even the implied warranty of           *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU        *
* Lesser General Public License for more details.                          *
*                                                                          *
* You should have received a copy of the GNU Lesser General Public         *
* License along with this library; if not, write to the Free Software      *
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 *
* USA                                                                      *
***************************************************************************/

#ifndef EPISODEACTIONLIST_H_
#define EPISODEACTIONLIST_H_

#include <QNetworkReply>
#include <QList>
#include <QObject>
#include <QVariant>
#include "EpisodeAction.h"
#include "mygpo_export.h"

namespace mygpo {

class EpisodeActionListPrivate;

class MYGPO_EXPORT EpisodeActionList : public QObject {
	Q_OBJECT
	Q_PROPERTY(QVariant episodeActions READ episodeActions CONSTANT)
	Q_PROPERTY(qulonglong timestamp READ timestamp CONSTANT)
public:
	EpisodeActionList(QNetworkReply* reply, QObject* parent = 0);
	virtual ~EpisodeActionList();

	QList<EpisodeActionPtr> list() const;
	QVariant episodeActions() const;

	qulonglong timestamp() const;

private:
  EpisodeActionListPrivate* const d;
  friend class EpisodeActionListPrivate;
signals:
    /**Gets emitted when the data is ready to read*/
    void finished();
    /**Gets emitted when an parse error ocurred*/
    void parseError();
    /**Gets emitted when an request error ocurred*/
    void requestError(QNetworkReply::NetworkError error);

};

typedef QSharedPointer<EpisodeActionList> EpisodeActionListPtr;

}

Q_DECLARE_METATYPE(mygpo::EpisodeActionListPtr);

#endif /* EPISODEACTIONLIST_H_ */