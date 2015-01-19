#include "CBinaryMatrixReader.hpp"

CBinaryMatrixReader::CBinaryMatrixReader(IMatrixWriter &writer)
    : CBaseMatrixReader(writer)
{
}


bool CBinaryMatrixReader::openFile(const std::string &fileName)
{
    bool result = CBaseMatrixReader::openFile(fileName);
    m_stream.setDevice(&m_file);
    return result;
}

void CBinaryMatrixReader::readAndProcess()
{
    quint64 rows = 0;
    quint64 cols = 0;
    bool isTransposed  = false;
    m_stream >> rows >> cols >> isTransposed;
    m_writer.writeFileHeader(rows, cols, isTransposed);
    while (!m_stream.atEnd())
    {
        double el;
        m_stream >> el;
        m_writer.writeElement(el);
    }
}
