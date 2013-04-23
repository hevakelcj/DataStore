#include "datastore.h"
#include <memory.h>

#define ASSERT(condition)

DataStore::DataStore(int pageSize, int buffSize)
{
    ASSERT(pageSize > 0);
    ASSERT(buffSize > 0);

    m_nPageSize = pageSize;
    m_nPageMaxNum = buffSize / pageSize;
    buffSize = m_nPageSize * m_nPageMaxNum;

    m_pDataBuffer = new char [buffSize];
    ASSERT(m_pDataBuffer != NULL);

    clear();
}

DataStore::~DataStore()
{
    delete [] m_pDataBuffer;
}

void DataStore::clear()
{
    m_nReadPos = m_nWritePos = 0;
    m_bIsFull = false;
}

int DataStore::getNum() const
{
    int distance = m_nWritePos - m_nReadPos;
    if ((distance < 0) || ((distance==0) && m_bIsFull))
        distance += m_nPageMaxNum;

    return distance;
}

void DataStore::putIn(const void *pData, int wSize)
{
    ASSERT(wSize <= m_nPageSize);
    char *pWrite = getAddress(getWritePos());

    if (pWrite)
        memcpy(pWrite, pData, wSize);
}

void DataStore::fetch(void *pData, int rSize)
{
    ASSERT(rSize >= m_nPageSize);
    char *pRead = getAddress(getReadPos());

    if (pRead)
        memcpy(pData, pRead, rSize);
}

void DataStore::readAt(void *pData, int rSize, int index)
{
    ASSERT(rSize >= m_nPageSize);
    char *pRead = getAddress(getReadPosAt(index));

    if (pRead)
        memcpy(pData, pRead, rSize);
}

char* DataStore::getAddress(int pos) const
{
    if (pos >= m_nPageMaxNum || pos < 0)
        return NULL;

    return m_pDataBuffer + pos * m_nPageSize;
}

int DataStore::getReadPosAt(int index) const
{
    if (index >= getNum() || index < -1) {
        return -1;
    } else if (index == -1) {
        return lastPos(m_nWritePos);
    } else {
        return (m_nReadPos+index) % m_nPageMaxNum;
    }
}

int DataStore::getReadPos()
{
    if (getNum() == 0)
        return -1;

    int readPos = m_nReadPos;
    m_nReadPos = nextPos(m_nReadPos);
    m_bIsFull = false;

    return readPos;
}

int DataStore::getWritePos()
{
    if (nextPos(m_nWritePos) == m_nReadPos) {
        m_bIsFull = true;
    } else if (m_nWritePos == m_nReadPos && m_bIsFull) {
        m_nReadPos = nextPos(m_nReadPos);
    } else {}

    int writePos = m_nWritePos;
    m_nWritePos = nextPos(m_nWritePos);

    return writePos;
}

int DataStore::nextPos(int pos) const
{
    return (pos+1) % m_nPageMaxNum;
}

int DataStore::lastPos(int pos) const
{
    return (pos==0) ? (m_nPageMaxNum-1) : (pos-1);
}
