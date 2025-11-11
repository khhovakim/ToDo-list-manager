#include "parser/parser.h"

#include <QHash>               // for QHash
#include <QString>             // for QString
#include <QStringList>         // for QStringList
#include <QRegularExpression>  // for QRegularExpression

#include <functional>   // for std::function
#include <iostream>
#include <ostream>
#include <utility>      // for std::make_unique
#include <type_traits>  // for std::is_same_v

#include "log/logType.h"              // for LogType
#include "log/logManager.h"           // for LogManager
#include "command/cmd.h"              // for Cmd::PTR
#include "command/addTaskCmd.h"       // for AddTaskCmd
#include "command/rmTaskCmd.h"        // for RmTaskCmd
#include "command/listTaskCmd.h"      // for ListTaskCmd
#include "command/completeTaskCmd.h"  // for CompleteTaskCmd
#include "command/executeFileCmd.h"   // for ExecuteFileCmd

namespace {
    const char* const NameFlag = "-name";
    const char* const FilePathFlag = "-file_path";
    const char* const BatchCmd = "execute_file";

    using functionMap = QHash<QString, std::function<Cmd::Ptr(const QStringList&)>>;
}

Cmd::Ptr Parser::createCmd(const QString& cmdLine)
{
    QStringList args = cmdLine.split(
            QRegularExpression("\\s+"),
            Qt::SkipEmptyParts
            );
    if ( args.isEmpty() ) return nullptr;

    const QString cmdName = args[0].toLower();
    static const functionMap function_map = {
        { "add_task"     , &createTemplateCmd<AddTaskCmd>      },
        { "remove_task"  , &createTemplateCmd<RmTaskCmd>       },
        { "list_tasks"   , &createTemplateCmd<ListTaskCmd>     },
        { "complete_task", &createTemplateCmd<CompleteTaskCmd> },
        { "execute_file" , &createTemplateCmd<ExecuteFileCmd>  }
    };
    // unknown command
    if ( function_map.find( cmdName ) == function_map.end() ) return nullptr;

    return function_map[cmdName]( args );
}

template<typename T>
Cmd::Ptr Parser::createTemplateCmd(const QStringList& args)
{
    if constexpr ( std::is_same_v<T, ListTaskCmd> ) return std::make_unique<T>();

    const QString value = extractArgValue(args);
    if ( value.isEmpty() ) return nullptr;

    return std::make_unique<T>(value);
}

QString Parser::extractArgValue(const QStringList& args)
{
    QString outMsg;
    LogManager* lm = LogManager::instance();

    if ( args.size() < 3 ) {
        outMsg = "Error: Invalid arguments count.";
        lm->log( outMsg, LogType::Error );
        return "";
    }

    const QString cmdName = args[0].toLower();
    const QString key = cmdName == BatchCmd ? FilePathFlag : NameFlag;
    const int keyIndex = args.indexOf(key);

    if ( keyIndex == -1 || keyIndex != 1 ) {
        outMsg = QString( "Error: Command '%1' expects a key (%2) as the second argument." )
             .arg( cmdName )
             .arg( key );
        lm->log( outMsg, LogType::Error );
        return "";
    }

    // substring from key to end
    const QString value = args.mid( keyIndex + 1 ).join(' ');

    // Ensure value is enclosed in '{' and '}'
    if ( !value.startsWith('{')  ) {
        outMsg = QString( "Error: Invalid syntax for key '%1'. Value must start with '{'." ).arg( key );
        lm->log( outMsg, LogType::Error );
        return "";
    }

    const int idx = value.indexOf('}');
    if ( idx == -1 ) {
        outMsg = QString( "Error: Invalid syntax for key '%1'. Value must end with '}'." ).arg( key );
        lm->log( outMsg, LogType::Error );
        return "";
    }

    if ( idx < value.size() - 1 ) {
        outMsg = "Error: Invalid arguments count.";
        lm->log( outMsg, LogType::Error );
        return "";
    }

    return value.mid( 1, idx - 1 ).trimmed();
}
