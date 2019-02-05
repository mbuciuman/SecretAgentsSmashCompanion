#ifndef GCTRAIN_ESCAPEOPTION_MASHJUMP_H_
#define GCTRAIN_ESCAPEOPTION_MASHJUMP_H_

#include <Nintendo.h>
#include "EscapeOption.hpp"

class MashJump : public EscapeOption
{
    private:
        bool executingJump;
    public:
        void inputEscapeOption(Gamecube_Data_t* dataToModify);
};

#endif // GCTRAIN_ESCAPEOPTION_MASHJUMP_H_