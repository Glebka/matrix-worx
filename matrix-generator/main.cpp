#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDataStream>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Common.hpp"
#include "IMatrixWriter.hpp"
#include "CBinaryMatrixWriter.hpp"
#include "CTextMatrixWriter.hpp"
#include "CTextMatrixReader.hpp"
#include "CBinaryMatrixReader.hpp"

using namespace std;



quint32 generateRandomMatrix = Parameters::MATRIX_ROWS | Parameters::MATRIX_COLUMNS | Parameters::FILL_RANDOM | Parameters::OUTPUT_FILE;
quint32 generateMatrixFromFile = Parameters::INPUT_FILE | Parameters::OUTPUT_FILE;

QCommandLineOption fillRandomOption(QStringList() << "r" << "random",
                              QCoreApplication::translate("main", "Fill the matrix with random values"));

QCommandLineOption matrixRowsOption(QStringList() << "m" << "rows",
                               QCoreApplication::translate("main", "Matrix row count"),
                               QCoreApplication::translate("main", "rows"));

QCommandLineOption matrixColumnsOption(QStringList() << "n" << "cols",
                               QCoreApplication::translate("main", "Matrix column count"),
                               QCoreApplication::translate("main", "cols"));

QCommandLineOption isMatrixTransposedOption(QStringList() << "t" << "transpose",
                                      QCoreApplication::translate("main", "Transpose matrix on write"));

QCommandLineOption inputTextFileOption(QStringList() << "i" << "input",
                                 QCoreApplication::translate("main", "Input CSV (coma separated) file path"),
                                 QCoreApplication::translate("main", "path"));

QCommandLineOption outputFileOption(QStringList() << "o" << "output",
                              QCoreApplication::translate("main", "Output file path"),
                              QCoreApplication::translate("main", "path"));

QCommandLineOption isCSVOption("csv",
                         QCoreApplication::translate("main", "Write matrix in CSV format instead of binary"));

QCommandLineOption isBinaryInputOption("binary-input",
                         QCoreApplication::translate("main", "Read input file in binary matrix format"));

void prepareCommandLineParser(QCommandLineParser &parser)
{
    parser.setApplicationDescription(QCoreApplication::translate("main", "Matrix Generator"));
    parser.addHelpOption();
    parser.addVersionOption();


    parser.addOption(fillRandomOption);


    parser.addOption(matrixRowsOption);


    parser.addOption(matrixColumnsOption);


    parser.addOption(isMatrixTransposedOption);


    parser.addOption(inputTextFileOption);


    parser.addOption(outputFileOption);


    parser.addOption(isCSVOption);

    parser.addOption(isBinaryInputOption);

}

bool parseCommandLineArguments(const QCommandLineParser &parser, quint32 &inputParametersMask, QString &inputFile, QString &outputFile, quint64 &rows, quint64 &cols)
{

    if (parser.isSet(fillRandomOption))
        inputParametersMask |= Parameters::FILL_RANDOM;

    if (parser.isSet(matrixRowsOption))
    {
        rows = parser.value(matrixRowsOption).toULongLong();
        inputParametersMask |= Parameters::MATRIX_ROWS;
    }

    if (parser.isSet(matrixColumnsOption))
    {
        cols = parser.value(matrixColumnsOption).toULongLong();
        inputParametersMask |= Parameters::MATRIX_COLUMNS;
    }

    if (parser.isSet(isMatrixTransposedOption))
        inputParametersMask |= Parameters::MATRIX_TRANSPOSE;

    if (parser.isSet(inputTextFileOption))
    {
        inputFile.append(parser.value(inputTextFileOption));
        inputParametersMask |= Parameters::INPUT_FILE;
    }

    if (parser.isSet(outputFileOption))
    {
        outputFile.append(parser.value(outputFileOption));
        inputParametersMask |= Parameters::OUTPUT_FILE;
    }

    if (parser.isSet(isCSVOption))
        inputParametersMask |= Parameters::IS_CSV_OUTPUT;

    if (parser.isSet(isBinaryInputOption))
        inputParametersMask |= Parameters::IS_BINARY_INPUT;


    bool result = false;
    result |= ((generateRandomMatrix & inputParametersMask) == generateRandomMatrix);
    result |= ((generateMatrixFromFile & inputParametersMask) == generateMatrixFromFile);

    return result;
}

bool writeRandomMatrix(IMatrixWriter &writer, quint64 rows, quint64 cols, bool isTransponed)
{
    writer.writeFileHeader(rows, cols, isTransponed);
    srand(time(NULL));
    for (quint64 i = 0; i < rows * cols; i++)
    {
        writer.writeElement(rand());
    }
    return !writer.hasError();
}

bool testFlag(int mask, int flag)
{
    return ((mask & flag) == flag);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("Matrix Generator");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    prepareCommandLineParser(parser);

    parser.process(a);

    QString inputFile, outputFile;
    quint64 rows = 0, cols = 0;
    quint32 inputParametersMask = 0;

    bool success = parseCommandLineArguments(parser, inputParametersMask, inputFile, outputFile, rows, cols);

    if (success)
    {
        IMatrixWriter *binaryWriter = new CBinaryMatrixWriter();
        IMatrixWriter *textWriter = new CTextMatrixWriter();
        IMatrixWriter *writer = 0;
        CBaseMatrixReader *reader = 0;


        if (testFlag(inputParametersMask, Parameters::IS_CSV_OUTPUT))
        {
            writer = textWriter;
        }
        else
        {
            writer = binaryWriter;
        }

        if (testFlag(inputParametersMask, generateRandomMatrix))
        {
            writer->openFile(outputFile.toStdString());
            writeRandomMatrix(*writer, rows, cols, testFlag(inputParametersMask, Parameters::MATRIX_TRANSPOSE));
            writer->closeFile();
        }

        if (testFlag(inputParametersMask, generateMatrixFromFile))
        {
            if (testFlag(inputParametersMask, Parameters::IS_BINARY_INPUT))
            {
                reader = new CBinaryMatrixReader(*writer);
            }
            else
            {
                reader = new CTextMatrixReader(*writer);
            }

            writer->openFile(outputFile.toStdString());
            reader->openFile(inputFile.toStdString());
            reader->readAndProcess();
            reader->closeFile();
            writer->closeFile();
        }
        delete binaryWriter;
        delete textWriter;
        delete reader;
    }
    return 0;
}
