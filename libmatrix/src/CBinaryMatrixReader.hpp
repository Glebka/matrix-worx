#ifndef CBINARYMATRIXREADER_HPP
#define CBINARYMATRIXREADER_HPP

#include <QDataStream>
#include "CBaseMatrixReader.hpp"

class CBinaryMatrixReader : public CBaseMatrixReader
{
public:
    CBinaryMatrixReader(IMatrixWriter &writer);

    // CBaseMatrixReader interface
public:
    virtual bool openFile(const std::string &fileName);
    virtual void readAndProcess();

private:
    QDataStream m_stream;
};

#endif // CBINARYMATRIXREADER_HPP
