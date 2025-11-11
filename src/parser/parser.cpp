#include "parser/parser.h"

#include <QHash>               // for QHash
#include <QString>             // for QString
#include <QStringList>         // for QStringList
#include <QRegularExpression>  // for QRegularExpression

#include <functional>   // for std::function
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
    args.pop_front();
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
    if ( args.size() < 2 ) {
        outMsg =  "Error: Invalid arguments count.";
        lm->log(outMsg, LogType::Error);
        return "";
    }

    if (const QString key = args.first(); key != "-name" || key != "-file_path" ) {
        outMsg =  "Error: Missing required argument.";
        lm->log(outMsg, LogType::Error);
        return "";
    }

    // substring from key to end
    const QString value = args.mid(1).join(' ');
    if ( !value.startsWith( '{' ) && !value.endsWith( '}' ) ) {
        outMsg = "Error: Invalid syntax. Value must be enclosed in '{' and '}'.";
        lm->log(outMsg, LogType::Error);
        return "";
    }

    return value.mid(1, value.size() - 2).trimmed();
}
