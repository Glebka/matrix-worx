#include "CBaseMatrixReader.hpp"

CBaseMatrixReader::CBaseMatrixReader(IMatrixWriter &writer)
    : m_writer(writer)
{
}

bool CBaseMatrixReader::openFile(const std::string &fileName)
{
    m_file.setFileName(QString::fromStdString(fileName));
    return m_file.open(QIODevice::ReadOnly);
}

void CBaseMatrixReader::closeFile()
{
    m_file.close();
}

CBaseMatrixReader::~CBaseMatrixReader()
{
    m_file.close();
}
