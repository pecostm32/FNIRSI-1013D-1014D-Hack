//----------------------------------------------------------------------------------------------------------------------------------

#ifndef FNIRSI_1013D_SCOPE_H
#define FNIRSI_1013D_SCOPE_H

//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct tagScopeSettings       SCOPESETTINGS,      *PSCOPESETTINGS;
typedef struct tagChannelSettings     CHANNELSETTINGS,    *PCHANNELSETTINGS;

//----------------------------------------------------------------------------------------------------------------------------------

struct tagChannelSettings
{
  uint8 enable;
  uint8 coupling;
  uint8 magnification;
  uint8 voltperdiv;
};

struct tagScopeSettings
{
  CHANNELSETTINGS channel1;
  CHANNELSETTINGS channel2;
};

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* FNIRSI_1013D_SCOPE_H */

