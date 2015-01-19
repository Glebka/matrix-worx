#ifndef IMATRIXREADER_HPP
#define IMATRIXREADER_HPP

#include <QFile>
#include <string>
#include "IMatrixWriter.hpp"

class CBaseMatrixReader
{
public:
    CBaseMatrixReader(IMatrixWriter &writer);
    virtual ~CBaseMatrixReader() = 0;

    virtual bool openFile(const std::string &fileName);
    virtual void closeFile();
    virtual void readAndProcess() = 0;

protected:
    IMatrixWriter & m_writer;
    QFile m_file;
};

#endif // IMATRIXREADER_HPP
