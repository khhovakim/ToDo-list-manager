#ifndef   __Command__
# define  __Command__

# include <QString>  // for QString

# include <memory>  // for std::unique_ptr

class Cmd
{
public:
    using Ptr = std::unique_ptr<Cmd>;

    Cmd() = default;
    virtual ~Cmd() = default;

    virtual bool execute() const = 0;
};

#endif // __Command__
