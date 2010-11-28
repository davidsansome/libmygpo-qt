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

#include <parser.h>

#include "TagList.h"

using namespace mygpo;

TagList::TagList ( QNetworkReply* reply, QObject* parent ) : QObject ( parent ), m_reply ( reply )
{
    QObject::connect ( m_reply,SIGNAL ( finished() ), this, SLOT ( parseData() ) );
    QObject::connect ( m_reply,SIGNAL ( error ( QNetworkReply::NetworkError ) ),this,SLOT ( error ( QNetworkReply::NetworkError ) ) );
}

TagList::TagList ( const TagList& other ) : QObject ( other.parent() ), m_reply ( other.m_reply ), m_tags ( other.m_tags )
{
    QObject::connect ( m_reply,SIGNAL ( finished() ), this, SLOT ( parseData() ) );
    QObject::connect ( m_reply,SIGNAL ( error ( QNetworkReply::NetworkError ) ),this,SLOT ( error ( QNetworkReply::NetworkError ) ) );
}

TagList::~TagList()
{
}

QList<Tag> TagList::list() const
{
    QList<Tag> list;
    QVariantList varList = m_tags.toList();
    foreach ( QVariant var,varList )
    {
        list.append ( var.value<mygpo::Tag>() );
    }
    return list;
}

QVariant TagList::tags() const
{
    return m_tags;
}

bool TagList::parse(const QVariant& data)
{
    if (!data.canConvert(QVariant::List))
        return false;
    QVariantList varList = data.toList();
    QVariantList tagList;
    foreach (QVariant var,varList)
    {
        QVariant v;
        v.setValue<mygpo::Tag>(Tag(var));
        tagList.append(v);
    }
    m_tags = QVariant( tagList);
    return true;
}

bool TagList::parse(const QByteArray& data)
{
    QJson::Parser parser;
    bool ok;
    QVariant variant = parser.parse( data, &ok );
    if( ok ) {
      ok = (parse( variant ));
    }
    return ok;
}


void TagList::parseData()
{
    QJson::Parser parser;
    if (parse( m_reply->readAll() ) ) { 
      emit finished();
    } else {
      emit parseError();
    }
}

void TagList::error(QNetworkReply::NetworkError error)
{
    this->m_error = error;
    emit requestError(error);
}
