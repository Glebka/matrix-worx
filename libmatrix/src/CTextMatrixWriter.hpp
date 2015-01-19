#ifndef CTEXTMATRIXWRITER_HPP
#define CTEXTMATRIXWRITER_HPP

#include <QFile>
#include <QTextStream>

#include "IMatrixWriter.hpp"

class CTextMatrixWriter : public IMatrixWriter
{
public:
    CTextMatrixWriter();

    // IMatrixWriter interface
public:
    virtual bool openFile(const std::string &fileName);
    virtual void closeFile();
    virtual void writeFileHeader(quint64 rows, quint64 cols, bool isTransposed);
    virtual void writeElement(double element);
    virtual bool hasError();

private:
    quint64 m_cols;
    quint64 m_currentCols;
    bool m_isError;
    QFile m_file;
    QTextStream m_stream;
};

#endif // CTEXTMATRIXWRITER_HPP
