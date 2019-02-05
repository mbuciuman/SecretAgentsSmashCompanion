#ifndef GCTRAIN_ESCAPEOPTION_ESCAPEOPTION_H
#define GCTRAIN_ESCAPEOPTION_ESCAPEOPTION_H

#include <Nintendo.h>

class EscapeOption
{
public:
    EscapeOption() = default;
    virtual void inputEscapeOption(Gamecube_Data_t* dataToModify) = 0;
};
#endif // GCTRAIN_ESCAPEOPTION_ESCAPEOPTION_H