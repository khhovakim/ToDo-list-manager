#include "command/completeTaskCmd.h"

#include <QString>  // for QString

#include <utility>  // for std::move

#include "task/taskManager.h"  // for TaskManager

CompleteTaskCmd::CompleteTaskCmd(QString taskName)
    : m_taskName( std::move( taskName ) )
{   }

bool CompleteTaskCmd::execute() const
{
    TaskManager* tm = TaskManager::instance();
    return tm->completeTask( m_taskName );
}


