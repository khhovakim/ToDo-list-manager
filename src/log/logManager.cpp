#include "log/logManager.h"

#include <QString>  // for QString

LogManager* LogManager::instance()
{
    static LogManager lm;
    return &lm;
}

void LogManager::log(const QString &msg, const LogType type) {
    emit logUi( msg, type );
}
