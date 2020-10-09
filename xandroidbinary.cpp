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

