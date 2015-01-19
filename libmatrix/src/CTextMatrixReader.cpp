#include "CTextMatrixReader.hpp"

CTextMatrixReader::CTextMatrixReader(IMatrixWriter &writer)
    : CBaseMatrixReader(writer)
{
}


void CTextMatrixReader::readAndProcess()
{
    QStringList splittedLine = m_stream.readLine().split(',', QString::SkipEmptyParts);
    quint64 cols = splittedLine.size();
    quint64 rows = 0;
    m_writer.writeFileHeader(0, cols, false);
    m_stream.seek(0);
    while (!m_stream.atEnd())
    {
        QStringList values = m_stream.readLine().split(',');
        foreach (QString value, values) {
            m_writer.writeElement(value.toDouble());
        }
        rows++;
    }
    m_writer.writeFileHeader(rows, cols, false);
}


bool CTextMatrixReader::openFile(const std::string &fileName)
{
    bool result = CBaseMatrixReader::openFile(fileName);
    m_stream.setDevice(&m_file);
    return result;
}
