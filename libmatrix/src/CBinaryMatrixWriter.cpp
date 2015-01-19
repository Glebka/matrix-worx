#include "CBinaryMatrixWriter.hpp"

CBinaryMatrixWriter::CBinaryMatrixWriter()
    : m_isError(false)
{
}


bool CBinaryMatrixWriter::openFile(const std::string &fileName)
{
    m_file.setFileName(QString::fromStdString(fileName));
    bool result = m_file.open(QIODevice::WriteOnly);
    m_stream.setDevice(&m_file);
    return result;
}

void CBinaryMatrixWriter::closeFile()
{
    m_file.close();
}

void CBinaryMatrixWriter::writeFileHeader(quint64 rows, quint64 cols, bool isTransposed)
{
    m_file.seek(0);
    m_stream << rows << cols << isTransposed;
    m_isError = (m_stream.status() != QDataStream::Ok);
}

void CBinaryMatrixWriter::writeElement(double element)
{
    m_stream << element;
}

bool CBinaryMatrixWriter::hasError()
{
    return m_isError;
}
