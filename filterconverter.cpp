#include "filterconverter.h"

#include <QDebug>

QString FilterConverter::convert(QString input)
{
    input = input.replace(".", "\\.");
    input = input.replace("*", R"(.*)");
    qDebug() << input;
    return input;
}
