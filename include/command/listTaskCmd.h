#ifndef   __List_Task_Command__
# define  __List_Task_Command__

# include "cmd.h"  // Base class

class ListTaskCmd final : public Cmd
{
public:
    ListTaskCmd() = default;
    ~ListTaskCmd() override = default;

    bool execute() const override;
};

#endif // __List_Task_Command__
