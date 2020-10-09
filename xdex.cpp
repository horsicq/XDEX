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
#include "xdex.h"

XDEX::XDEX(QIODevice *__pDevice): XBinary(__pDevice)
{

}

bool XDEX::isValid()
{
    bool bIsValid=false;

    bIsValid=compareSignature("'dex\n'......00");

    return bIsValid;
}

quint32 XDEX::_getVersion()
{
    quint32 nVersion=0;

    QString sVersion=read_ansiString(4);

    nVersion=sVersion.toUInt();

    return nVersion;
}

bool XDEX::isBigEndian()
{
    quint32 nEndian=read_uint32(offsetof(XDEX_DEF::HEADER,endian_tag));

    return (nEndian!=0x12345678);
}

quint32 XDEX::getHeader_magic()
{
    return read_uint32(offsetof(XDEX_DEF::HEADER,magic),false);
}

quint32 XDEX::getHeader_version()
{
    return read_uint32(offsetof(XDEX_DEF::HEADER,version),false);
}

quint32 XDEX::getHeader_checksum()
{
    return read_uint32(offsetof(XDEX_DEF::HEADER,checksum),isBigEndian());
}

QByteArray XDEX::getHeader_signature()
{
    return read_array(offsetof(XDEX_DEF::HEADER,signature),20);
}

quint32 XDEX::getHeader_file_size()
{
    return read_uint32(offsetof(XDEX_DEF::HEADER,file_size),isBigEndian());
}

quint32 XDEX::getHeader_header_size()
{
    return read_uint32(offsetof(XDEX_DEF::HEADER,header_size),isBigEndian());
}

quint32 XDEX::getHeader_endian_tag()
{
    return read_uint32(offsetof(XDEX_DEF::HEADER,endian_tag));
}

quint32 XDEX::getHeader_link_size()
{
    return read_uint32(offsetof(XDEX_DEF::HEADER,link_size),isBigEndian());
}

quint32 XDEX::getHeader_link_off()
{
    return read_uint32(offsetof(XDEX_DEF::HEADER,link_off),isBigEndian());
}

quint32 XDEX::getHeader_map_off()
{
    return read_uint32(offsetof(XDEX_DEF::HEADER,map_off),isBigEndian());
}

quint32 XDEX::getHeader_string_ids_size()
{
    return read_uint32(offsetof(XDEX_DEF::HEADER,string_ids_size),isBigEndian());
}

quint32 XDEX::getHeader_string_ids_off()
{
    return read_uint32(offsetof(XDEX_DEF::HEADER,string_ids_off),isBigEndian());
}

quint32 XDEX::getHeader_type_ids_size()
{
    return read_uint32(offsetof(XDEX_DEF::HEADER,type_ids_size),isBigEndian());
}

quint32 XDEX::getHeader_type_ids_off()
{
    return read_uint32(offsetof(XDEX_DEF::HEADER,type_ids_off),isBigEndian());
}

quint32 XDEX::getHeader_proto_ids_size()
{
    return read_uint32(offsetof(XDEX_DEF::HEADER,proto_ids_size),isBigEndian());
}

quint32 XDEX::getHeader_proto_ids_off()
{
    return read_uint32(offsetof(XDEX_DEF::HEADER,proto_ids_off),isBigEndian());
}

quint32 XDEX::getHeader_field_ids_size()
{
    return read_uint32(offsetof(XDEX_DEF::HEADER,field_ids_size),isBigEndian());
}

quint32 XDEX::getHeader_field_ids_off()
{
    return read_uint32(offsetof(XDEX_DEF::HEADER,field_ids_off),isBigEndian());
}

quint32 XDEX::getHeader_method_ids_size()
{
    return read_uint32(offsetof(XDEX_DEF::HEADER,method_ids_size),isBigEndian());
}

quint32 XDEX::getHeader_method_ids_off()
{
    return read_uint32(offsetof(XDEX_DEF::HEADER,method_ids_off),isBigEndian());
}

quint32 XDEX::getHeader_class_defs_size()
{
    return read_uint32(offsetof(XDEX_DEF::HEADER,class_defs_size),isBigEndian());
}

quint32 XDEX::getHeader_class_defs_off()
{
    return read_uint32(offsetof(XDEX_DEF::HEADER,class_defs_off),isBigEndian());
}

quint32 XDEX::getHeader_data_size()
{
    return read_uint32(offsetof(XDEX_DEF::HEADER,data_size),isBigEndian());
}

quint32 XDEX::getHeader_data_off()
{
    return read_uint32(offsetof(XDEX_DEF::HEADER,data_off),isBigEndian());
}

XDEX_DEF::HEADER XDEX::getHeader()
{
    XDEX_DEF::HEADER result={};

    bool bIsBigEndian=isBigEndian();

    result.magic=read_uint32(offsetof(XDEX_DEF::HEADER,magic),false);
    result.version=read_uint32(offsetof(XDEX_DEF::HEADER,version),false);
    result.checksum=read_uint32(offsetof(XDEX_DEF::HEADER,checksum),bIsBigEndian);
//    result.signature=getHeader_signature();
    result.file_size=read_uint32(offsetof(XDEX_DEF::HEADER,file_size),bIsBigEndian);
    result.header_size=read_uint32(offsetof(XDEX_DEF::HEADER,header_size),bIsBigEndian);
    result.endian_tag=read_uint32(offsetof(XDEX_DEF::HEADER,endian_tag),bIsBigEndian);
    result.link_size=read_uint32(offsetof(XDEX_DEF::HEADER,link_size),bIsBigEndian);
    result.link_off=read_uint32(offsetof(XDEX_DEF::HEADER,link_off),bIsBigEndian);
    result.map_off=read_uint32(offsetof(XDEX_DEF::HEADER,map_off),bIsBigEndian);
    result.string_ids_size=read_uint32(offsetof(XDEX_DEF::HEADER,string_ids_size),bIsBigEndian);
    result.string_ids_off=read_uint32(offsetof(XDEX_DEF::HEADER,string_ids_off),bIsBigEndian);
    result.type_ids_size=read_uint32(offsetof(XDEX_DEF::HEADER,type_ids_size),bIsBigEndian);
    result.type_ids_off=read_uint32(offsetof(XDEX_DEF::HEADER,type_ids_off),bIsBigEndian);
    result.proto_ids_size=read_uint32(offsetof(XDEX_DEF::HEADER,proto_ids_size),bIsBigEndian);
    result.proto_ids_off=read_uint32(offsetof(XDEX_DEF::HEADER,proto_ids_off),bIsBigEndian);
    result.field_ids_size=read_uint32(offsetof(XDEX_DEF::HEADER,field_ids_size),bIsBigEndian);
    result.field_ids_off=read_uint32(offsetof(XDEX_DEF::HEADER,field_ids_off),bIsBigEndian);
    result.method_ids_size=read_uint32(offsetof(XDEX_DEF::HEADER,method_ids_size),bIsBigEndian);
    result.method_ids_off=read_uint32(offsetof(XDEX_DEF::HEADER,method_ids_off),bIsBigEndian);
    result.class_defs_size=read_uint32(offsetof(XDEX_DEF::HEADER,class_defs_size),bIsBigEndian);
    result.class_defs_off=read_uint32(offsetof(XDEX_DEF::HEADER,class_defs_off),bIsBigEndian);
    result.data_size=read_uint32(offsetof(XDEX_DEF::HEADER,data_size),bIsBigEndian);
    result.data_off=read_uint32(offsetof(XDEX_DEF::HEADER,data_off),bIsBigEndian);

    return result;
}

quint32 XDEX::getHeaderSize()
{
    return sizeof(XDEX_DEF::HEADER);
}

QList<XDEX_DEF::MAP_ITEM> XDEX::getMapItems()
{
    QList<XDEX_DEF::MAP_ITEM> listResult;

    qint64 nOffset=getHeader_map_off();

    bool bIsBigEndian=isBigEndian();

    quint32 nCount=read_uint32(nOffset,bIsBigEndian);

    nOffset+=4;

    for(quint32 i=0;i<nCount;i++)
    {
        XDEX_DEF::MAP_ITEM map_item={};

        map_item.nType=read_uint16(nOffset,bIsBigEndian);
        map_item.nCount=read_uint32(nOffset+4,bIsBigEndian);
        map_item.nOffset=read_uint32(nOffset+8,bIsBigEndian);

        listResult.append(map_item);

        nOffset+=12;
    }

    return listResult;
}

bool XDEX::isMapItemPresent(quint16 nType,QList<XDEX_DEF::MAP_ITEM> *pMapItems)
{
    bool bResult=false;

    int nNumberOfItems=pMapItems->count();

    for(int i=0;i<nNumberOfItems;i++)
    {
        if(pMapItems->at(i).nType==nType)
        {
            bResult=true;

            break;
        }
    }

    return bResult;
}

QMap<quint64, QString> XDEX::getTypes()
{
    QMap<quint64, QString> mapResult;

    mapResult.insert(0x0000,"TYPE_HEADER_ITEM");
    mapResult.insert(0x0001,"TYPE_STRING_ID_ITEM");
    mapResult.insert(0x0002,"TYPE_TYPE_ID_ITEM");
    mapResult.insert(0x0003,"TYPE_PROTO_ID_ITEM");
    mapResult.insert(0x0004,"TYPE_FIELD_ID_ITEM");
    mapResult.insert(0x0005,"TYPE_METHOD_ID_ITEM");
    mapResult.insert(0x0006,"TYPE_CLASS_DEF_ITEM");
    mapResult.insert(0x0007,"TYPE_CALL_SITE_ID_ITEM");
    mapResult.insert(0x0008,"TYPE_METHOD_HANDLE_ITEM");
    mapResult.insert(0x1000,"TYPE_MAP_LIST");
    mapResult.insert(0x1001,"TYPE_TYPE_LIST");
    mapResult.insert(0x1002,"TYPE_ANNOTATION_SET_REF_LIST");
    mapResult.insert(0x1003,"TYPE_ANNOTATION_SET_ITEM");
    mapResult.insert(0x2000,"TYPE_CLASS_DATA_ITEM");
    mapResult.insert(0x2001,"TYPE_CODE_ITEM");
    mapResult.insert(0x2002,"TYPE_STRING_DATA_ITEM");
    mapResult.insert(0x2003,"TYPE_DEBUG_INFO_ITEM");
    mapResult.insert(0x2004,"TYPE_ANNOTATION_ITEM");
    mapResult.insert(0x2005,"TYPE_ENCODED_ARRAY_ITEM");
    mapResult.insert(0x2006,"TYPE_ANNOTATIONS_DIRECTORY_ITEM");

    return mapResult;
}

QMap<quint64, QString> XDEX::getTypesS()
{
    QMap<quint64, QString> mapResult;

    mapResult.insert(0x0000,"HEADER_ITEM");
    mapResult.insert(0x0001,"STRING_ID_ITEM");
    mapResult.insert(0x0002,"TYPE_ID_ITEM");
    mapResult.insert(0x0003,"PROTO_ID_ITEM");
    mapResult.insert(0x0004,"FIELD_ID_ITEM");
    mapResult.insert(0x0005,"METHOD_ID_ITEM");
    mapResult.insert(0x0006,"CLASS_DEF_ITEM");
    mapResult.insert(0x0007,"CALL_SITE_ID_ITEM");
    mapResult.insert(0x0008,"METHOD_HANDLE_ITEM");
    mapResult.insert(0x1000,"MAP_LIST");
    mapResult.insert(0x1001,"TYPE_LIST");
    mapResult.insert(0x1002,"ANNOTATION_SET_REF_LIST");
    mapResult.insert(0x1003,"ANNOTATION_SET_ITEM");
    mapResult.insert(0x2000,"CLASS_DATA_ITEM");
    mapResult.insert(0x2001,"CODE_ITEM");
    mapResult.insert(0x2002,"STRING_DATA_ITEM");
    mapResult.insert(0x2003,"DEBUG_INFO_ITEM");
    mapResult.insert(0x2004,"ANNOTATION_ITEM");
    mapResult.insert(0x2005,"ENCODED_ARRAY_ITEM");
    mapResult.insert(0x2006,"ANNOTATIONS_DIRECTORY_ITEM");

    return mapResult;
}

XDEX_DEF::MAP_ITEM XDEX::getMapItem(quint16 nType, QList<XDEX_DEF::MAP_ITEM> *pMapItems)
{
    XDEX_DEF::MAP_ITEM result={};

    int nCount=pMapItems->count();

    for(int i=0;i<nCount;i++)
    {
        if(pMapItems->at(i).nType==nType)
        {
            result=pMapItems->at(i);

            break;
        }
    }

    return result;
}

QList<XDEX_DEF::STRING_ITEM_ID> XDEX::getList_STRING_ITEM_ID()
{
    QList<XDEX_DEF::STRING_ITEM_ID> listResult;

    QList<XDEX_DEF::MAP_ITEM> listMapItems=getMapItems();
    bool bIsBigEndian=isBigEndian();

    XDEX_DEF::MAP_ITEM mapItem=getMapItem(XDEX_DEF::TYPE_STRING_ID_ITEM,&listMapItems);

    for(quint32 i=0;i<mapItem.nCount;i++)
    {
        qint64 nOffset=mapItem.nOffset+sizeof(XDEX_DEF::STRING_ITEM_ID)*i;

        XDEX_DEF::STRING_ITEM_ID record={};

        record.string_data_off=read_int32(nOffset+offsetof(XDEX_DEF::STRING_ITEM_ID,string_data_off),bIsBigEndian);

        listResult.append(record);
    }

    return listResult;
}

QList<XDEX_DEF::TYPE_ITEM_ID> XDEX::getList_TYPE_ITEM_ID()
{
    QList<XDEX_DEF::MAP_ITEM> listMapItems=getMapItems();

    return getList_TYPE_ITEM_ID(&listMapItems);
}

QList<XDEX_DEF::TYPE_ITEM_ID> XDEX::getList_TYPE_ITEM_ID(QList<XDEX_DEF::MAP_ITEM> *pListMapItems)
{
    QList<XDEX_DEF::TYPE_ITEM_ID> listResult;

    XDEX_DEF::MAP_ITEM mapItem=getMapItem(XDEX_DEF::TYPE_TYPE_ID_ITEM,pListMapItems);
    bool bIsBigEndian=isBigEndian();

    for(quint32 i=0;i<mapItem.nCount;i++)
    {
        qint64 nOffset=mapItem.nOffset+sizeof(XDEX_DEF::TYPE_ITEM_ID)*i;

        XDEX_DEF::TYPE_ITEM_ID record={};

        record.descriptor_idx=read_int32(nOffset+offsetof(XDEX_DEF::TYPE_ITEM_ID,descriptor_idx),bIsBigEndian);

        listResult.append(record);
    }

    return listResult;
}

QList<XDEX_DEF::PROTO_ITEM_ID> XDEX::getList_PROTO_ITEM_ID(QList<XDEX_DEF::MAP_ITEM> *pListMapItems)
{
    QList<XDEX_DEF::PROTO_ITEM_ID> listResult;

    XDEX_DEF::MAP_ITEM mapItem=getMapItem(XDEX_DEF::TYPE_PROTO_ID_ITEM,pListMapItems);
    bool bIsBigEndian=isBigEndian();

    for(quint32 i=0;i<mapItem.nCount;i++)
    {
        qint64 nOffset=mapItem.nOffset+sizeof(XDEX_DEF::PROTO_ITEM_ID)*i;

        XDEX_DEF::PROTO_ITEM_ID record={};

        record.shorty_idx=read_int32(nOffset+offsetof(XDEX_DEF::PROTO_ITEM_ID,shorty_idx),bIsBigEndian);
        record.return_type_idx=read_int32(nOffset+offsetof(XDEX_DEF::PROTO_ITEM_ID,return_type_idx),bIsBigEndian);
        record.parameters_off=read_int32(nOffset+offsetof(XDEX_DEF::PROTO_ITEM_ID,parameters_off),bIsBigEndian);

        listResult.append(record);
    }

    return listResult;
}

QList<XDEX_DEF::FIELD_ITEM_ID> XDEX::getList_FIELD_ITEM_ID(QList<XDEX_DEF::MAP_ITEM> *pListMapItems)
{
    QList<XDEX_DEF::FIELD_ITEM_ID> listResult;

    XDEX_DEF::MAP_ITEM mapItem=getMapItem(XDEX_DEF::TYPE_FIELD_ID_ITEM,pListMapItems);
    bool bIsBigEndian=isBigEndian();

    for(quint32 i=0;i<mapItem.nCount;i++)
    {
        qint64 nOffset=mapItem.nOffset+sizeof(XDEX_DEF::FIELD_ITEM_ID)*i;

        XDEX_DEF::FIELD_ITEM_ID record={};

        record.class_idx=read_int16(nOffset+offsetof(XDEX_DEF::FIELD_ITEM_ID,class_idx),bIsBigEndian);
        record.type_idx=read_int16(nOffset+offsetof(XDEX_DEF::FIELD_ITEM_ID,type_idx),bIsBigEndian);
        record.name_idx=read_int32(nOffset+offsetof(XDEX_DEF::FIELD_ITEM_ID,name_idx),bIsBigEndian);

        listResult.append(record);
    }

    return listResult;
}

QList<XDEX_DEF::METHOD_ITEM_ID> XDEX::getList_METHOD_ITEM_ID(QList<XDEX_DEF::MAP_ITEM> *pListMapItems)
{
    QList<XDEX_DEF::METHOD_ITEM_ID> listResult;

    XDEX_DEF::MAP_ITEM mapItem=getMapItem(XDEX_DEF::TYPE_METHOD_ID_ITEM,pListMapItems);
    bool bIsBigEndian=isBigEndian();

    for(quint32 i=0;i<mapItem.nCount;i++)
    {
        qint64 nOffset=mapItem.nOffset+sizeof(XDEX_DEF::METHOD_ITEM_ID)*i;

        XDEX_DEF::METHOD_ITEM_ID record={};

        record.class_idx=read_int16(nOffset+offsetof(XDEX_DEF::METHOD_ITEM_ID,class_idx),bIsBigEndian);
        record.proto_idx=read_int16(nOffset+offsetof(XDEX_DEF::METHOD_ITEM_ID,proto_idx),bIsBigEndian);
        record.name_idx=read_int32(nOffset+offsetof(XDEX_DEF::METHOD_ITEM_ID,name_idx),bIsBigEndian);

        listResult.append(record);
    }

    return listResult;
}

QList<XDEX_DEF::CLASS_ITEM_DEF> XDEX::getList_CLASS_ITEM_DEF(QList<XDEX_DEF::MAP_ITEM> *pListMapItems)
{
    QList<XDEX_DEF::CLASS_ITEM_DEF> listResult;

    XDEX_DEF::MAP_ITEM mapItem=getMapItem(XDEX_DEF::TYPE_METHOD_ID_ITEM,pListMapItems);
    bool bIsBigEndian=isBigEndian();

    for(quint32 i=0;i<mapItem.nCount;i++)
    {
        qint64 nOffset=mapItem.nOffset+sizeof(XDEX_DEF::METHOD_ITEM_ID)*i;

        XDEX_DEF::CLASS_ITEM_DEF record={};

        record.class_idx=read_int32(nOffset+offsetof(XDEX_DEF::CLASS_ITEM_DEF,class_idx),bIsBigEndian);
        record.access_flags=read_int32(nOffset+offsetof(XDEX_DEF::CLASS_ITEM_DEF,access_flags),bIsBigEndian);
        record.superclass_idx=read_int32(nOffset+offsetof(XDEX_DEF::CLASS_ITEM_DEF,superclass_idx),bIsBigEndian);
        record.interfaces_off=read_int32(nOffset+offsetof(XDEX_DEF::CLASS_ITEM_DEF,interfaces_off),bIsBigEndian);
        record.source_file_idx=read_int32(nOffset+offsetof(XDEX_DEF::CLASS_ITEM_DEF,source_file_idx),bIsBigEndian);
        record.annotations_off=read_int32(nOffset+offsetof(XDEX_DEF::CLASS_ITEM_DEF,annotations_off),bIsBigEndian);
        record.class_data_off=read_int32(nOffset+offsetof(XDEX_DEF::CLASS_ITEM_DEF,class_data_off),bIsBigEndian);
        record.static_values_off=read_int32(nOffset+offsetof(XDEX_DEF::CLASS_ITEM_DEF,static_values_off),bIsBigEndian);

        listResult.append(record);
    }

    return listResult;
}

QList<QString> XDEX::getStrings(QList<XDEX_DEF::MAP_ITEM> *pMapItems)
{
    QList<QString> listResult;

    bool bIsBigEndian=isBigEndian();

    XDEX_DEF::MAP_ITEM map_strings=getMapItem(XDEX_DEF::TYPE_STRING_ID_ITEM,pMapItems);

    for(quint32 i=0;i<map_strings.nCount;i++)
    {
        QString sString=_getString(map_strings,i,bIsBigEndian);

        listResult.append(sString);
    }

    return listResult;
}

QString XDEX::_getString(XDEX_DEF::MAP_ITEM map_stringIdItem, quint32 nIndex, bool bIsBigEndian)
{
    QString sResult;

    if(nIndex<map_stringIdItem.nCount)
    {
        qint64 nOffset=map_stringIdItem.nOffset+sizeof(quint32)*nIndex;

        quint32 nStringsOffset=read_uint32(nOffset,bIsBigEndian);

        sResult=XBinary::_read_utf8String(nStringsOffset);
    }

    return sResult;
}

QString XDEX::_geTypeItemtString(XDEX_DEF::MAP_ITEM map_stringIdItem, XDEX_DEF::MAP_ITEM map_typeItemId, quint32 nIndex, bool bIsBigEndian)
{
    QString sResult;

    if(nIndex<map_typeItemId.nCount)
    {
        quint32 nID=read_uint32(map_typeItemId.nOffset+sizeof(quint32)*nIndex,bIsBigEndian);

        sResult=_getString(map_stringIdItem,nID,bIsBigEndian);
    }

    return sResult;
}

QList<quint32> XDEX::_getTypeList(qint64 nOffset, bool bIsBigEndian)
{
    QList<quint32> listResult;

    if(nOffset)
    {
        quint32 nCount=read_uint32(nOffset,bIsBigEndian);

        for(quint32 i=0;i<nCount;i++)
        {
            quint32 nType=read_uint32(nOffset+sizeof(quint32)*(1+i),bIsBigEndian);
            listResult.append(nType);
        }
    }

    return listResult;
}

QList<QString> XDEX::getTypeItemStrings(QList<XDEX_DEF::MAP_ITEM> *pMapItems, QList<QString> *pListStrings)
{
    QList<QString> listResult;

    bool bIsBigEndian=isBigEndian();

    int nStringsCount=pListStrings->count();

    XDEX_DEF::MAP_ITEM map_items=getMapItem(XDEX_DEF::TYPE_TYPE_ID_ITEM,pMapItems);

    for(quint32 i=0;i<map_items.nCount;i++)
    {
        quint32 nOffset=map_items.nOffset+sizeof(quint32)*i;

        quint32 nItem=read_uint32(nOffset,bIsBigEndian);

        if((qint32)nItem<nStringsCount)
        {
            QString sString=pListStrings->at(nItem);

            listResult.append(sString);
        }
//        else
//        {
//            qDebug("Error");
//        }
    }

    return listResult;
}

void XDEX::getProtoIdItems(QList<XDEX_DEF::MAP_ITEM> *pMapItems)
{
    bool bIsBigEndian=isBigEndian();

    XDEX_DEF::MAP_ITEM map_protoIdItem=getMapItem(XDEX_DEF::TYPE_PROTO_ID_ITEM,pMapItems);
    XDEX_DEF::MAP_ITEM map_typeIdItem=getMapItem(XDEX_DEF::TYPE_TYPE_ID_ITEM,pMapItems);
    XDEX_DEF::MAP_ITEM map_stringIdItem=getMapItem(XDEX_DEF::TYPE_STRING_ID_ITEM,pMapItems);

    for(quint32 i=0;i<map_protoIdItem.nCount;i++)
    {
        quint32 nOffset=map_protoIdItem.nOffset+sizeof(XDEX_DEF::PROTO_ITEM_ID)*i;

        XDEX_DEF::PROTO_ITEM_ID record={};

        record.shorty_idx=read_uint32(nOffset+offsetof(XDEX_DEF::PROTO_ITEM_ID,shorty_idx),bIsBigEndian);
        record.return_type_idx=read_uint32(nOffset+offsetof(XDEX_DEF::PROTO_ITEM_ID,return_type_idx),bIsBigEndian);
        record.parameters_off=read_uint32(nOffset+offsetof(XDEX_DEF::PROTO_ITEM_ID,parameters_off),bIsBigEndian);

        QString sProto=_getString(map_stringIdItem,record.shorty_idx,bIsBigEndian);
        QString sRet=_geTypeItemtString(map_stringIdItem,map_typeIdItem,record.return_type_idx,bIsBigEndian);

        QList<quint32> listParams=_getTypeList(record.parameters_off,bIsBigEndian);

        QString sDebugString=QString("%1 %2").arg(sRet).arg(sProto);

        qDebug(sDebugString.toLatin1().data());
    }
}

QString XDEX::getStringItemIdString(XDEX_DEF::STRING_ITEM_ID stringItemId)
{
    QString sResult;

    sResult=_read_utf8String(stringItemId.string_data_off);

    return sResult;
}

QString XDEX::getTypeItemIdString(XDEX_DEF::TYPE_ITEM_ID typeItemId, XDEX_DEF::MAP_ITEM *pMapItemStrings)
{
    QString sResult;

    bool bIsBigEndian=isBigEndian();

    sResult=_read_utf8String(read_uint32(pMapItemStrings->nOffset+sizeof(quint32)*typeItemId.descriptor_idx,bIsBigEndian));

    return sResult;
}

QString XDEX::getProtoItemIdString(XDEX_DEF::PROTO_ITEM_ID protoItemId, XDEX_DEF::MAP_ITEM *pMapItemStrings)
{
    QString sResult;

    bool bIsBigEndian=isBigEndian();

    QString sPrototype=_read_utf8String(read_uint32(pMapItemStrings->nOffset+sizeof(quint32)*protoItemId.shorty_idx,bIsBigEndian));
    QString sReturn=_read_utf8String(read_uint32(pMapItemStrings->nOffset+sizeof(quint32)*protoItemId.return_type_idx,bIsBigEndian));
    sResult=QString("%1 %2()").arg(sReturn).arg(sPrototype);

    return sResult;
}
