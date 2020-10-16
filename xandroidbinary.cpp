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
#include "xandroidbinary.h"

XAndroidBinary::XAndroidBinary(QIODevice *__pDevice): XBinary(__pDevice)
{

}

bool XAndroidBinary::isValid()
{
    bool bIsValid=false;

    _MEMORY_MAP memoryMap=getMemoryMap();

    bIsValid=compareSignature(&memoryMap,"03000800")||compareSignature(&memoryMap,"02000C00");

    return bIsValid;
}

bool XAndroidBinary::isBigEndian()
{
    return false;
}

XANDROIDBINARY_DEF::HEADER XAndroidBinary::readHeader(qint64 nOffset)
{
    XANDROIDBINARY_DEF::HEADER result={};

    result.type=read_uint32(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER,type));
    result.header_size=read_uint32(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER,header_size));
    result.data_size=read_uint32(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER,data_size));

    return result;
}

XANDROIDBINARY_DEF::HEADER_STRING_POOL XAndroidBinary::readHeaderStringPool(qint64 nOffset)
{
    XANDROIDBINARY_DEF::HEADER_STRING_POOL result={};

    result.header=readHeader(nOffset);
    result.stringCount=read_uint32(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_STRING_POOL,stringCount));
    result.styleCount=read_uint32(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_STRING_POOL,styleCount));
    result.flags=read_uint32(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_STRING_POOL,flags));
    result.stringsStart=read_uint32(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_STRING_POOL,stringsStart));
    result.stylesStart=read_uint32(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_STRING_POOL,stylesStart));

    return result;
}

XANDROIDBINARY_DEF::HEADER_NAMESPACE XAndroidBinary::readHeaderNamespace(qint64 nOffset)
{
    XANDROIDBINARY_DEF::HEADER_NAMESPACE result={};

    result.header=readHeader(nOffset);
    result.lineNumber=read_uint32(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_NAMESPACE,lineNumber));
    result.comment=read_uint32(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_NAMESPACE,comment));
    result.prefix=read_uint32(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_NAMESPACE,prefix));
    result.uri=read_uint32(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_NAMESPACE,uri));

    return result;
}

XANDROIDBINARY_DEF::HEADER_XML_START XAndroidBinary::readHeaderXmlStart(qint64 nOffset)
{
    XANDROIDBINARY_DEF::HEADER_XML_START result={};

    result.header=readHeader(nOffset);
    result.lineNumber=read_uint32(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_XML_START,lineNumber));
    result.comment=read_uint32(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_XML_START,comment));
    result.ns=read_uint32(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_XML_START,ns));
    result.name=read_uint32(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_XML_START,name));
    result.attributeStart=read_uint16(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_XML_START,attributeStart));
    result.attributeSize=read_uint16(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_XML_START,attributeSize));
    result.attributeCount=read_uint16(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_XML_START,attributeCount));
    result.idIndex=read_uint16(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_XML_START,idIndex));
    result.classIndex=read_uint16(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_XML_START,classIndex));
    result.styleIndex=read_uint16(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_XML_START,styleIndex));

    return result;
}

XANDROIDBINARY_DEF::HEADER_XML_ATTRIBUTE XAndroidBinary::readHeaderXmlAttribute(qint64 nOffset)
{
    XANDROIDBINARY_DEF::HEADER_XML_ATTRIBUTE result={};

    result.ns=read_uint32(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_XML_ATTRIBUTE,ns));
    result.name=read_uint32(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_XML_ATTRIBUTE,name));
    result.rawValue=read_uint32(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_XML_ATTRIBUTE,rawValue));
    result.size=read_uint16(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_XML_ATTRIBUTE,size));
    result.reserved=read_uint8(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_XML_ATTRIBUTE,reserved));
    result.dataType=read_uint8(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_XML_ATTRIBUTE,dataType));
    result.data=read_uint32(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_XML_ATTRIBUTE,data));

    return result;
}

XANDROIDBINARY_DEF::HEADER_XML_END XAndroidBinary::readHeaderXmlEnd(qint64 nOffset)
{
    XANDROIDBINARY_DEF::HEADER_XML_END result={};

    result.header=readHeader(nOffset);
    result.lineNumber=read_uint32(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_XML_END,lineNumber));
    result.comment=read_uint32(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_XML_END,comment));
    result.ns=read_uint32(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_XML_END,ns));
    result.name=read_uint32(nOffset+offsetof(XANDROIDBINARY_DEF::HEADER_XML_END,name));

    return result;
}

QList<XANDROIDBINARY_DEF::HEADER> XAndroidBinary::getHeaders()
{
    QList<XANDROIDBINARY_DEF::HEADER> listHeaders;

    qint64 nTotalSize=getSize();
    qint64 nCurrentOffset=0;

    while(nCurrentOffset<nTotalSize)
    {
        XANDROIDBINARY_DEF::HEADER record=readHeader(nCurrentOffset);
        listHeaders.append(record);

        nCurrentOffset+=record.data_size;
    }

    return listHeaders;
}

XAndroidBinary::RECORD XAndroidBinary::getRecord(qint64 nOffset)
{
    RECORD result={};

    result.header=readHeader(nOffset);
    result.nOffset=nOffset;

    if( (result.header.type==XANDROIDBINARY_DEF::RES_XML_TYPE)||
        (result.header.type==XANDROIDBINARY_DEF::RES_TABLE_TYPE)||
        (result.header.type==XANDROIDBINARY_DEF::RES_TABLE_PACKAGE_TYPE))
    {
        qint64 nCurrentOffset=nOffset+result.header.header_size;

        while(nCurrentOffset<result.header.data_size)
        {
            RECORD record=getRecord(nCurrentOffset);

            result.listChildren.append(record);

            nCurrentOffset+=record.header.data_size;
        }
    }

    return result;
}

QString XAndroidBinary::recordToString(XAndroidBinary::RECORD *pRecord)
{
    QString sResult;

    if(pRecord->header.type==XANDROIDBINARY_DEF::RES_XML_TYPE)
    {
        int nNumberOfChildren=pRecord->listChildren.count();
        QList<QString> listStrings;
        QList<quint32> listResources;

        for(int i=0;i<nNumberOfChildren;i++)
        {
            if(pRecord->listChildren.at(i).header.type==XANDROIDBINARY_DEF::RES_STRING_POOL_TYPE)
            {
                XANDROIDBINARY_DEF::HEADER_STRING_POOL headerStringPool=readHeaderStringPool(pRecord->listChildren.at(i).nOffset);

                qint64 nCurrentOffset=pRecord->listChildren.at(i).nOffset+headerStringPool.header.header_size;
                qint64 nStringsDataOffset=pRecord->listChildren.at(i).nOffset+headerStringPool.stringsStart;

                for(quint32 j=0;j<headerStringPool.stringCount;j++)
                {
                    qint64 nStringOffset=nStringsDataOffset+read_int32(nCurrentOffset+j*sizeof(quint32));
                    qint16 nStringSize=read_uint16(nStringOffset);
                    QString sString=read_unicodeString(nStringOffset+sizeof(quint16),nStringSize);

                    listStrings.append(sString);
                }
            }
            else if(pRecord->listChildren.at(i).header.type==XANDROIDBINARY_DEF::RES_XML_RESOURCE_MAP_TYPE)
            {
                int nNumberOfResources=(pRecord->listChildren.at(i).header.data_size-sizeof(XANDROIDBINARY_DEF::HEADER))/4;

                qint64 nCurrentOffset=pRecord->listChildren.at(i).nOffset+sizeof(XANDROIDBINARY_DEF::HEADER);

                for(int j=0;j<nNumberOfResources;j++)
                {
                    quint32 nID=read_uint32(nCurrentOffset+j*sizeof(quint32));

                    listResources.append(nID);
                }
            }
            else if((pRecord->listChildren.at(i).header.type==XANDROIDBINARY_DEF::RES_XML_START_NAMESPACE_TYPE)||(pRecord->listChildren.at(i).header.type==XANDROIDBINARY_DEF::RES_XML_END_NAMESPACE_TYPE))
            {
                XANDROIDBINARY_DEF::HEADER_NAMESPACE headerNamespace=readHeaderNamespace(pRecord->listChildren.at(i).nOffset);

                qDebug("lineNumber %d",headerNamespace.lineNumber);
                qDebug("prefix %s",listStrings.at(headerNamespace.prefix).toLatin1().data());
                qDebug("uri %s",listStrings.at(headerNamespace.uri).toLatin1().data());
            }
            else if(pRecord->listChildren.at(i).header.type==XANDROIDBINARY_DEF::RES_XML_START_ELEMENT_TYPE)
            {
                XANDROIDBINARY_DEF::HEADER_XML_START headerXmlStart=readHeaderXmlStart(pRecord->listChildren.at(i).nOffset);

//                qDebug("lineNumber %d",headerXmlStart.lineNumber);

                if(headerXmlStart.ns!=0xFFFFFFFF)
                {
                    qDebug("ns %s",listStrings.at(headerXmlStart.ns).toLatin1().data());
                }

                qDebug("attributeStart %d",headerXmlStart.attributeStart);
                qDebug("attributeSize %d",headerXmlStart.attributeSize);
                qDebug("attributeCount %d",headerXmlStart.attributeCount);
                qDebug("idIndex %d",headerXmlStart.idIndex);
                qDebug("classIndex %d",headerXmlStart.classIndex);
                qDebug("styleIndex %d",headerXmlStart.styleIndex);

                QString sString=QString("<%1>").arg(listStrings.at(headerXmlStart.name));
                qDebug("%s",sString.toLatin1().data());

                qint64 nCurrentOffset=pRecord->listChildren.at(i).nOffset+headerXmlStart.attributeStart;

                for(int j=0;j<headerXmlStart.attributeCount;j++)
                {
                    XANDROIDBINARY_DEF::HEADER_XML_ATTRIBUTE headerXmlAttribute=readHeaderXmlAttribute(nCurrentOffset);

                    qDebug("NAME %s",listStrings.at(headerXmlAttribute.name).toLatin1().data());

                    nCurrentOffset+sizeof(XANDROIDBINARY_DEF::HEADER_XML_ATTRIBUTE);
                }
            }
            else if(pRecord->listChildren.at(i).header.type==XANDROIDBINARY_DEF::RES_XML_END_ELEMENT_TYPE)
            {
                XANDROIDBINARY_DEF::HEADER_XML_END headerXmlEnd=readHeaderXmlEnd(pRecord->listChildren.at(i).nOffset);

//                qDebug("lineNumber %d",headerXmlEnd.lineNumber);

                if(headerXmlEnd.ns!=0xFFFFFFFF)
                {
                    qDebug("ns %s",listStrings.at(headerXmlEnd.ns).toLatin1().data());
                }

                QString sString=QString("</%1>").arg(listStrings.at(headerXmlEnd.name));
                qDebug("%s",sString.toLatin1().data());
            }
            else
            {
                qDebug("Record %x",pRecord->listChildren.at(i).header.type);
            }
        }
    }

    return sResult;
}

