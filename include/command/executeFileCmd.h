#ifndef   __Execute_File_Batch_Command__
# define  __Execute_File_Batch_Command__

# include "cmd.h"  // Base class

# include <QString>  // for QString

class ExecuteFileCmd final : public Cmd
{
public:
    explicit ExecuteFileCmd(QString filePath);
    ~ExecuteFileCmd() override = default;

    bool execute() const override;

private:
    QString m_filePath;
};

#endif // __Execute_File_Batch_Command__