#include "HCALStudies/TPDigi/interface/Utils.h"



int GetRBXId(HcalSubdetector subdet, const int& iphi)
{
  if( subdet == HcalBarrel || subdet == HcalEndcap || subdet == HcalForward )
  {
    return int( ( ( iphi-1+2) % 72 ) / 4. ) + 1;
  }
  
  return 99;
}
