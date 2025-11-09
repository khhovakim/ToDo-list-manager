#include "command/rmTaskCmd.h"

#include <QString>  // for QString

#include <utility>  // for std::move

#include "task/taskManager.h"  // for TaskManager

RmTaskCmd::RmTaskCmd(QString taskName)
    : m_taskName( std::move( taskName ) )
{   }

bool RmTaskCmd::execute() const
{
    TaskManager* tm = TaskManager::instance();
    return tm->removeTask( m_taskName );
}

