#ifndef SPMS_H
#define SMPS_H

#include "TPS55288.h"



class SMPS {
  public:
    void OutputEnable();
    void OutputDisable();
}

#endif
