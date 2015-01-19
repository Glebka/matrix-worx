#ifndef IMATRIXWRITER_HPP
#define IMATRIXWRITER_HPP

#include <QObject>
#include <string>

#include "Common.hpp"

class IMatrixWriter
{
public:
    IMatrixWriter();
    virtual ~IMatrixWriter() = 0;

    virtual bool openFile(const std::string &fileName) = 0;
    virtual void closeFile() = 0;

    virtual void writeFileHeader(quint64 rows, quint64 cols, bool isTransposed) = 0;
    virtual void writeElement(double element) = 0;

    virtual bool hasError() = 0;
};

#endif // IMATRIXWRITER_HPP
