#ifndef   __Remove_Task_Command__
# define  __Remove_Task_Command__

# include "cmd.h"  // Base class

# include <QString>  // for QString

class RmTaskCmd final : public Cmd
{
public:
    explicit RmTaskCmd(QString);
    ~RmTaskCmd() override = default;

    bool execute() const override;

private:
    QString m_taskName;
};


#endif // __Remove_Task_Command__