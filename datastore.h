#ifndef DATASTORE_H
#define DATASTORE_H

class DataStore
{
public:
    DataStore(int pageSize, int buffSize);
    ~DataStore();

    void putIn(const void *pData, int wSize);
    void fetch(void *pData, int rSize);
    void readAt(void *pData, int rSize, int index);
    void clear();

    int  getNum() const ;
    int  getMaxNum() const { return m_nPageMaxNum; }
    bool isFull() const { return m_bIsFull; }

protected:
    char* getAddress(int pos) const;

    int getReadPosAt(int index) const;
    int getReadPos();
    int getWritePos();

    int nextPos(int pos) const;
    int lastPos(int pos) const;

private:
    char *m_pDataBuffer;

    int m_nPageSize;
    int m_nPageMaxNum;

    int m_nReadPos;
    int m_nWritePos;
    bool m_bIsFull;
};

#endif // DATASTORE_H
