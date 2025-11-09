#ifndef   __Complete_Task_Command__
# define  __Complete_Task_Command__

# include "cmd.h"  // Base class

# include <QString>  // for QString

class CompleteTaskCmd final : public Cmd
{
public:
    explicit CompleteTaskCmd(QString);
    ~CompleteTaskCmd() override = default;

    bool execute() const override;

private:
    QString m_taskName;
};

#endif // __Complete_Task_Command__