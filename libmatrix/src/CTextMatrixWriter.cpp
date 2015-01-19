#include "CTextMatrixWriter.hpp"

CTextMatrixWriter::CTextMatrixWriter()
    : m_cols(0)
    , m_currentCols(0)
    , m_isError(false)

{
}


bool CTextMatrixWriter::openFile(const std::string &fileName)
{
    m_file.setFileName(QString::fromStdString(fileName));
    bool result = m_file.open(QIODevice::WriteOnly);
    m_stream.setDevice(&m_file);
    return result;
}

void CTextMatrixWriter::closeFile()
{
     m_file.close();
}

void CTextMatrixWriter::writeFileHeader(quint64 rows, quint64 cols, bool isTransposed)
{
    m_cols = cols;
}

void CTextMatrixWriter::writeElement(double element)
{
    if (m_currentCols == m_cols)
    {
        m_currentCols = 0;
        m_stream << endl;
    }
    m_stream << element << ',';
    m_isError = (m_stream.status() != 0);
    m_currentCols++;
}

bool CTextMatrixWriter::hasError()
{
    return m_isError;
}
