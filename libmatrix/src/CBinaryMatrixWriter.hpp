#ifndef CBINARYMATRIXWRITER_HPP
#define CBINARYMATRIXWRITER_HPP

#include <QFile>
#include <QDataStream>

#include "IMatrixWriter.hpp"

class CBinaryMatrixWriter : public IMatrixWriter
{
public:
    CBinaryMatrixWriter();

    // IMatrixWriter interface
public:
    virtual bool openFile(const std::string &fileName);
    virtual void closeFile();
    virtual void writeFileHeader(quint64 rows, quint64 cols, bool isTransposed);
    virtual void writeElement(double element);
    virtual bool hasError();

private:
    QFile m_file;
    QDataStream m_stream;
    bool m_isError;
};

#endif // CBINARYMATRIXWRITER_HPP
