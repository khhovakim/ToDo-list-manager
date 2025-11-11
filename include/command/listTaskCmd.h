#ifndef   __List_Task_Command__
# define  __List_Task_Command__

# include "cmd.h"  // Base class

class ListTaskCmd final : public Cmd
{
public:
    explicit  ListTaskCmd(const QString& name = QString()) {  Q_UNUSED(name); }
    ~ListTaskCmd() override = default;

    bool execute() const override;
};

#endif // __List_Task_Command__
