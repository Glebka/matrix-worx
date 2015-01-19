#include <QCoreApplication>
#include <QCommandLineParser>
#include <QStringList>

#include "Common.hpp"

QCommandLineOption hostsFileOption("hosts",
                                   QCoreApplication::translate("main", "Processing hosts file"),
                                   QCoreApplication::translate("main", "file")
    );

QCommandLineOption outputFileOption(QStringList() << "o" << "out",
                                   QCoreApplication::translate("main", "Result matrix file"),
                                   QCoreApplication::translate("main", "file")
    );

QCommandLineOption isCSVOption("csv",
                         QCoreApplication::translate("main", "Write result matrix in CSV format instead of binary"));


quint32 requiredParams = Parameters::HOSTS | Parameters::MATRIX_A | Parameters::MATRIX_B | Parameters::OUTPUT_FILE;

void prepareCommandLineParser(QCommandLineParser &parser)
{
    parser.setApplicationDescription(QCoreApplication::translate("main", "Calculates matrix product using distributed algorithm"));
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addOption(hostsFileOption);
    parser.addOption(outputFileOption);

    parser.addPositionalArgument("matrixA", "First matrix in binary format");
    parser.addPositionalArgument("matrixB", "Second matrix in binary format (should be in the transposed form)");
}

bool parseCommandLineArguments(const QCommandLineParser &parser,
                               quint32 &inputParametersMask,
                               QString &hostsFile,
                               QString &outputFile,
                               QString &matrixAFile,
                               QString &matrixBFile
    )
{
    if (parser.isSet(hostsFileOption))
    {
        inputParametersMask |= Parameters::HOSTS;
        hostsFile = parser.value(hostsFileOption);
    }

    if (parser.isSet(outputFileOption))
    {
        inputParametersMask |= Parameters::OUTPUT_FILE;
        outputFile = parser.value(outputFileOption);
    }

    if (parser.isSet(isCSVOption))
        inputParametersMask |= Parameters::IS_CSV_OUTPUT;

    QStringList positionalArguments = parser.positionalArguments();
    if (positionalArguments.size() == 2)
    {
        inputParametersMask |= Parameters::MATRIX_A | Parameters::MATRIX_B;
        matrixAFile = positionalArguments.first();
        matrixBFile = positionalArguments.last();
    }

    return testFlag(inputParametersMask, requiredParams);
}

bool testFlag(int mask, int flag)
{
    return ((mask & flag) == flag);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("Distributed Matrix Product Scheduler");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    prepareCommandLineParser(parser);

    parser.process(a);

    QString hostsFile, outputFile, matrixAFile, matrixBFile;
    quint32 inputParametersMask = 0;

    bool success = parseCommandLineArguments(parser, inputParametersMask, hostsFile, outputFile, matrixAFile, matrixBFile);

    return 0;
}
