// copyright (c) 2019-2020 hors<horsicq@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#ifndef XDEX_H
#define XDEX_H

#include "xdex_def.h"
#include "xbinary.h"

class XDEX: public XBinary
{
    Q_OBJECT
public:

    XDEX(QIODevice *__pDevice);
    virtual bool isValid();
    quint32 _getVersion();
    virtual QString getVersion();

    virtual bool isBigEndian();

    quint32 getHeader_magic();
    quint32 getHeader_version();
    quint32 getHeader_checksum();
    QByteArray getHeader_signature();
    quint32 getHeader_file_size();
    quint32 getHeader_header_size();
    quint32 getHeader_endian_tag();
    quint32 getHeader_link_size();
    quint32 getHeader_link_off();
    quint32 getHeader_map_off();
    quint32 getHeader_string_ids_size();
    quint32 getHeader_string_ids_off();
    quint32 getHeader_type_ids_size();
    quint32 getHeader_type_ids_off();
    quint32 getHeader_proto_ids_size();
    quint32 getHeader_proto_ids_off();
    quint32 getHeader_field_ids_size();
    quint32 getHeader_field_ids_off();
    quint32 getHeader_method_ids_size();
    quint32 getHeader_method_ids_off();
    quint32 getHeader_class_defs_size();
    quint32 getHeader_class_defs_off();
    quint32 getHeader_data_size();
    quint32 getHeader_data_off();

    void setHeader_magic(quint32 value);
    void setHeader_version(quint32 value);
    void setHeader_checksum(quint32 value);

    XDEX_DEF::HEADER getHeader();
    quint32 getHeaderSize();

    QList<XDEX_DEF::MAP_ITEM> getMapItems();

    static bool isMapItemPresent(quint16 nType,QList<XDEX_DEF::MAP_ITEM> *pMapItems);

    static QMap<quint64, QString> getTypes();
    static QMap<quint64, QString> getTypesS();

    static XDEX_DEF::MAP_ITEM getMapItem(quint16 nType,QList<XDEX_DEF::MAP_ITEM> *pMapItems);

    QList<XDEX_DEF::STRING_ITEM_ID> getList_STRING_ITEM_ID();
    QList<XDEX_DEF::TYPE_ITEM_ID> getList_TYPE_ITEM_ID();
    QList<XDEX_DEF::TYPE_ITEM_ID> getList_TYPE_ITEM_ID(QList<XDEX_DEF::MAP_ITEM> *pListMapItems);
    QList<XDEX_DEF::PROTO_ITEM_ID> getList_PROTO_ITEM_ID(QList<XDEX_DEF::MAP_ITEM> *pListMapItems);
    QList<XDEX_DEF::FIELD_ITEM_ID> getList_FIELD_ITEM_ID(QList<XDEX_DEF::MAP_ITEM> *pListMapItems);
    QList<XDEX_DEF::METHOD_ITEM_ID> getList_METHOD_ITEM_ID(QList<XDEX_DEF::MAP_ITEM> *pListMapItems);
    QList<XDEX_DEF::CLASS_ITEM_DEF> getList_CLASS_ITEM_DEF(QList<XDEX_DEF::MAP_ITEM> *pListMapItems);

    QList<QString> getStrings(QList<XDEX_DEF::MAP_ITEM> *pMapItems);
    QString _getString(XDEX_DEF::MAP_ITEM map_stringIdItem, quint32 nIndex, bool bIsBigEndian);
    QString _geTypeItemtString(XDEX_DEF::MAP_ITEM map_stringIdItem,XDEX_DEF::MAP_ITEM map_typeItemId, quint32 nIndex, bool bIsBigEndian);
    QList<quint32> _getTypeList(qint64 nOffset, bool bIsBigEndian);

    QList<QString> getTypeItemStrings(QList<XDEX_DEF::MAP_ITEM> *pMapItems,QList<QString> *pListStrings);
    void getProtoIdItems(QList<XDEX_DEF::MAP_ITEM> *pMapItems);

    QString getStringItemIdString(XDEX_DEF::STRING_ITEM_ID stringItemId);
    QString getTypeItemIdString(XDEX_DEF::TYPE_ITEM_ID typeItemId,XDEX_DEF::MAP_ITEM *pMapItemStrings);
    QString getProtoItemIdString(XDEX_DEF::PROTO_ITEM_ID protoItemId,XDEX_DEF::MAP_ITEM *pMapItemStrings);
};

#endif // XDEX_H
