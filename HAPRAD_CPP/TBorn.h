#ifndef TBORN_H
#define TBORN_H

#include "TStructFunctionArray.h"

class TRadCor;
class TKinematicalVariables;
class TLorentzInvariants;
class THadronKinematics;


class TBorn {
public:
    TBorn(const TRadCor* rc);
    ~TBorn();

    Double_t        Evaluate(void);

private:
    const TKinematicalVariables*    fKin;
    const TLorentzInvariants*       fInv;
    const THadronKinematics*        fHadKin;

    TStructFunctionArray fH;

    Double_t    fThetaB[4];
};

#endif
