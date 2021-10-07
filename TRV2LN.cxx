#include "TRV2LN.h"
#include "TRadCor.h"
#include "THapradConfig.h"
#include "TKinematicalVariables.h"
#include "TLorentzInvariants.h"
#include "THadronKinematics.h"
#include "TPODINL.h"
#include "TThetaMatrix.h"
#include "haprad_constants.h"
#include "square_power.h"
#include "TMath.h"
#include "Math/GSLIntegrator.h"
#include <iostream>


TRV2LN::TRV2LN(const TRadCor* rc, double phi_k)
  : fH(rc), fPhiK(phi_k)
{
    fRC     = rc;
    fConfig = rc->GetConfig();
    fKin    = rc->GetKinematicalVariables();
    fInv    = rc->GetLorentzInvariants();
    fHadKin = rc->GetHadronKinematics();

    fH.Evaluate(0.,0.,0.);
}



TRV2LN::~TRV2LN()
{

}



ROOT::Math::IBaseFunctionOneDim* TRV2LN::Clone() const
{
    return 0;
}



double TRV2LN::DoEval(double tauln) const
{
    const Double_t& M = kMassProton;
    Double_t tau, mu, factor;

    tau = TMath::Exp(tauln) - fInv->Q2() / fInv->Sx();

    Double_t costk, sintk;
    costk = (fInv->Sx() - 2 * SQ(M) * tau) / fInv->SqrtLq();

    if (TMath::Abs(costk) <= 1) {
        sintk = TMath::Sqrt(1. - costk * costk);
    } else {
        std::cout << "     rv2ln: costk > 1 " << costk << std::endl;
        sintk = 0;
    }

    mu = (fHadKin->Eh() - fHadKin->Pl() * costk -
            fHadKin->Pt() * sintk * TMath::Cos(fPhiK - fKin->PhiH())) / M;
    factor = 1. + tau - mu;

    TThetaMatrix theta(fRC);
    theta.Evaluate(tau, mu, 1, fPhiK);

    ROOT::Math::GSLIntegrator ig(ROOT::Math::IntegrationOneDim::kNONADAPTIVE);

    TPODINL podinl(fRC, tau, mu, fH, theta);
    ig.SetFunction(podinl);
    ig.SetRelTolerance(fConfig->EpsRR());
    ig.SetAbsTolerance(1E-18);

    Double_t rmin = 1E-8;
    Double_t rmax = (fHadKin->Px2() - kMassC2) / factor;
    double res = ig.Integral(rmin, rmax);

    return res * (fInv->Q2() / fInv->Sx() + tau);
}
