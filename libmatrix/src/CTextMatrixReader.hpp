#ifndef CTEXTMATRIXREADER_HPP
#define CTEXTMATRIXREADER_HPP

#include <QTextStream>
#include "CBaseMatrixReader.hpp"

class CTextMatrixReader : public CBaseMatrixReader
{
public:
    CTextMatrixReader(IMatrixWriter &writer);

    // CBaseMatrixReader interface
public:
    virtual bool openFile(const std::string &fileName);
    virtual void readAndProcess();

private:
    QTextStream m_stream;
};

#endif // CTEXTMATRIXREADER_HPP
