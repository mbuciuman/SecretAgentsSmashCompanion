#ifndef GCTRAIN_ESCAPEOPTION_NOESCAPEOPTION_H_
#define GCTRAIN_ESCAPEOPTION_NOESCAPEOPTION_H_

#include <Nintendo.h>
#include "EscapeOption.hpp"

class NoEscapeOption : public EscapeOption
{
    public:
        void inputEscapeOption(Gamecube_Data_t* dataToModify);
};

#endif // GCTRAIN_ESCAPEOPTION_NOESCAPEOPTION_H_
