#ifndef TLORENTZINVARIANTS_H
#define TLORENTZINVARIANTS_H

#include "TROOT.h"

class THapradConfig;
class TKinematicalVariables;
class THadronKinematics;


class TLorentzInvariants {
public:
    TLorentzInvariants(THapradConfig* config,
                       TKinematicalVariables* kin);
    ~TLorentzInvariants();

    // Getters
    Double_t    S(void)   const { return fS; };
    Double_t    X(void)   const { return fX; };
    Double_t    Sx(void)  const { return fSx; };
    Double_t    Sp(void)  const { return fSp; };
    Double_t    Q2(void)  const { return fQ2; };
    Double_t    W2(void)  const { return fW2; };

    Double_t    LambdaS(void) const { return fLambdaS; };
    Double_t    LambdaX(void) const { return fLambdaX; };
    Double_t    LambdaM(void) const { return fLambdaM; };
    Double_t    LambdaQ(void) const { return fLambdaQ; };

    Double_t    SqrtLs(void) const { return fSqrtLs; };
    Double_t    SqrtLx(void) const { return fSqrtLx; };
    Double_t    SqrtLm(void) const { return fSqrtLm; };
    Double_t    SqrtLq(void) const { return fSqrtLq; };

    // Setter
    void        Evaluate(void);

private:
    void    SetS(void);
    void    SetX(void);
    void    SetSx(void);
    void    SetSp(void);
    void    SetQ2(void);
    void    SetW2(void);
    void    SetLambdas(void);


    THapradConfig*            fConfig;
    TKinematicalVariables*    fKin;
    THadronKinematics*        fHadKin;

    Double_t    fS;
    Double_t    fX;
    Double_t    fSx;
    Double_t    fSp;
    Double_t    fQ2;
    Double_t    fW2;

    Double_t    fLambdaS;
    Double_t    fLambdaX;
    Double_t    fLambdaM;
    Double_t    fLambdaQ;

    Double_t    fSqrtLs;
    Double_t    fSqrtLx;
    Double_t    fSqrtLm;
    Double_t    fSqrtLq;
};

#endif
