#ifndef   __Add_Task_Command__
# define  __Add_Task_Command__

# include "cmd.h"  // Base class

# include <QString>  // for QString

class AddTaskCmd final : public Cmd
{
public:
    explicit AddTaskCmd(QString);
    ~AddTaskCmd() override = default;

    bool execute() const override;
private:
    QString m_taskName;
};

#endif // __Add_Task_Command__
