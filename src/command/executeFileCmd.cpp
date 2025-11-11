#include "command/executeFileCmd.h"

#include <QString>      // for QString
#include <QFile>        // for QFile
#include <QTextStream>  // for QTextStream

#include <cstddef>  // for std::size_t
#include <utility>  // for std::move

#include "command/cmd.h"     // for Cmd::Ptr
#include "parser/parser.h"   // for CmdParser::createCmd
#include "log/logType.h"     // for LogType
#include "log/logManager.h"  // for LogManager

ExecuteFileCmd::ExecuteFileCmd(QString filePath)
    : m_filePath( std::move(filePath ) )
{   }

bool ExecuteFileCmd::execute() const
{
    QFile file( m_filePath );
    QString outMsg;
    LogManager* lm = LogManager::instance();
    if ( !file.exists() ) {
        outMsg = QString( "Error: file \"%1\" does not exist." ).arg( m_filePath );
        lm->log( outMsg, LogType::Error );
        return false;
    }

    if ( !file.open( QFile::ReadOnly | QFile::Text ) ) {
        outMsg = QString( "Error: cannot open file \"%1\" for reading." ).arg( m_filePath );
        lm->log( outMsg, LogType::Error );
        return false;
    }

    std::size_t line { 0 };
    QTextStream stream( &file );
    while ( stream.atEnd() ) {
        QString lineStr { stream.readLine().trimmed() };
        ++line;

        if ( lineStr.isEmpty() || lineStr.startsWith('#') ) {
            continue; // allow comments / blank lines
        }

        const Cmd::Ptr cmd = Parser::createCmd( lineStr );
        if ( !cmd ) {
            outMsg = QString( "Error: invalid command in file \"%1\" (line %2): %3" )
                            .arg( m_filePath )
                            .arg( line )
                            .arg( lineStr );
            lm->log( outMsg, LogType::Error );
            return false;
        }

        if ( !cmd->execute() ) {
            return false;
        }
    }
    return true;
}
