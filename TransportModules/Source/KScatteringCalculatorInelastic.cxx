#include "KScatteringCalculatorInelastic.h"
#include "KSIOToolbox.h"
#include "KSTextFile.h"

#include <fstream>
using std::fstream;

#include "TMath.h"
#include "KMath.h"
#include "KSRandom.h"
#include "KSConst.h"

using namespace std;
namespace Kassiopeia{
KScatteringCalculatorInelastic::KScatteringCalculatorInelastic() :
                fDataFile(),
                fIonizationEnergy(0),
                fMoleculeType(""),
				fMinimum(-1)
{
    fDataFile.SetKey("InelasticScatteringData");
    KSIOToolbox::GetInstance()->AddDataTextFile(&fDataFile);
}

KScatteringCalculatorInelastic::~KScatteringCalculatorInelastic()
{
	//not needed
}

void KScatteringCalculatorInelastic::setmolecule(const std::string& aMolecule)
{
    
    //E < "KScatterBasicInelasticCalculatorFerenc::setmolecule";
    fMoleculeType = aMolecule;
    fDataFile.AddToBases(fMoleculeType + string(".txt"));
    //cout << "Molecule " << fMoleculeType << endl;
    if( ReadData() == kFALSE )
    {
        //cout << "unknown ERROR reading file. quit.";

    }
    return;
}
Double_t KScatteringCalculatorInelastic::GetIonizationEnergy()
{
	return fIonizationEnergy;
}


Double_t KScatteringCalculatorInelastic::sigmaexc(Double_t anE){
	//TODO: move constants somewhere. precision?

	const Double_t a02 = KSConst::BohrRadiusSquared();
	// Double_t a02= 28.e-22; //used several times

	const Double_t R = 13.6; //hydrogen inoisation? precision?

	Double_t sigma;
	if(anE<9.8)
		sigma = 1.e-40;
	else if(anE>=9.8 && anE<=250.)
		sigma = sigmaBC(anE) + sigmadiss10(anE) + sigmadiss15(anE);
	else
		sigma = 4.*KSConst::Pi() * a02 * R/anE * (0.80*log(anE/R)+0.28);
	//    sigma=sigmainel(anE)-sigmaion(anE);
	return sigma;


}

void KScatteringCalculatorInelastic::randomexc(Double_t anE,Double_t& Eloss,Double_t& Theta) //Todo: move static stuff to constructor. constants and precision?
{

	static Int_t iff=0;
	static Double_t sum[1001];
	static Double_t fmax;

	Double_t Ecen=12.6/27.21;



	Double_t T,c,u[3],K,xmin,ymin,ymax,x,y,fy,dy,pmax;
	Double_t D,Dmax;
	Int_t i,j,n,N,v;
	// Energy values of the excited electronic states:
	//  (from Mol. Phys. 41 (1980) 1501, in Hartree atomic units)
	Double_t En[7]={12.73/27.2,13.2/27.2,14.77/27.2,15.3/27.2,
			14.93/27.2,15.4/27.2,13.06/27.2};
	// Probability numbers of the electronic states:
	//  (from testelectron7.c calculation )
	Double_t p[7]={35.86, 40.05, 6.58, 2.26, 9.61, 4.08, 1.54};
	// Energy values of the B vibrational states:
	//   (from: Phys. Rev. A51 (1995) 3745 , in Hartree atomic units)
	Double_t EB[28]={0.411, 0.417, 0.423, 0.428, 0.434, 0.439, 0.444,0.449,
			0.454, 0.459, 0.464, 0.468, 0.473, 0.477, 0.481,0.485,
			0.489, 0.493, 0.496, 0.500, 0.503, 0.507, 0.510,0.513,
			0.516, 0.519, 0.521, 0.524};
	// Energy values of the C vibrational states:
	//   (from: Phys. Rev. A51 (1995) 3745 , in Hartree atomic units)
	Double_t EC[14]={0.452,0.462,0.472,0.481,0.490,0.498,0.506,0.513,
			0.519,0.525,0.530,0.534,0.537,0.539};
	// Franck-Condon factors of the B vibrational states:
	//   (from: Phys. Rev. A51 (1995) 3745 )
	Double_t pB[28]={4.2e-3,1.5e-2,3.0e-2,4.7e-2,6.3e-2,7.3e-2,7.9e-2,
			8.0e-2,7.8e-2,7.3e-2,6.6e-2,5.8e-2,5.1e-2,4.4e-2,
			3.7e-2,3.1e-2,2.6e-2,2.2e-2,1.8e-2,1.5e-2,1.3e-2,
			1.1e-2,8.9e-3,7.4e-3,6.2e-3,5.2e-3,4.3e-3,3.6e-3};
	// Franck-Condon factors of the C vibrational states:
	//   (from: Phys. Rev. A51 (1995) 3745 )
	Double_t pC[14]={1.2e-1,1.9e-1,1.9e-1,1.5e-1,1.1e-1,7.5e-2,5.0e-2,
			3.3e-2,2.2e-2,1.4e-2,9.3e-3,6.0e-3,3.7e-3,1.8e-3};

	T=20000./27.2;
	//
	xmin=Ecen*Ecen/(2.*T);
	ymin=log(xmin);
	ymax=log(8.*T+xmin);
	dy=(ymax-ymin)/1000.;

	// Initialization of the sum[] vector, and fmax calculation://TODO move to constructor
	if(iff==0)
	{
		fmax=0;
		for(i=0;i<=1000;i++)
		{ y=ymin+dy*i;
		K=exp(y/2.);
		sum[i]=sumexc(K);
		if(sum[i]>fmax) fmax=sum[i];
		}
		fmax=1.05*fmax;
		iff=1;
	}
	//
	//  Scattering angle Theta generation:
	//
	T=anE/27.2;
	if(anE>=100.)
	{
		xmin=Ecen*Ecen/(2.*T);
		ymin=log(xmin);
		ymax=log(8.*T+xmin);
		dy=(ymax-ymin)/1000.;
		// Generation of y values with the Neumann acceptance-rejection method:
		for(j=1;j<5000;j++)
		{
			//subrn(u,2);
			KSRandom::GetInstance()->RndmArray(3, u );
			y=ymin+(ymax-ymin)*u[1];
			K=exp(y/2.);
			fy=sumexc(K);
			if(fmax*u[2]<fy) break;
		}
		// Calculation of c=cos(Theta) and Theta:
		x=exp(y);
		c=1.-(x-xmin)/(4.*T);
		Theta=acos(c)*180./KSConst::Pi();
	}
	else
	{
		if(anE<=25.)
			Dmax=60.;
		else if(anE>25. && anE<=35.)
			Dmax=95.;
		else if(anE>35. && anE<=50.)
			Dmax=150.;
		else
			Dmax=400.;
		for(j=1;j<5000;j++)
		{
			//subrn(u,2);
			KSRandom::GetInstance()->RndmArray(3, u );
			c=-1.+2.*u[1];
			D =  DiffXSecExc(anE,c) * 1.e22;
			if(Dmax*u[2]<D) break;
		}
		Theta=acos(c)*180./KSConst::Pi();
	}
	// Energy loss Eloss generation:

	// First we generate the electronic state, using the Neumann
	// acceptance-rejection method for discrete distribution:
	N=7;            // the number of electronic states in our calculation
	pmax=p[1];      // the maximum of the p[] values
	for(j=1;j<5000;j++)
	{
		KSRandom::GetInstance()->RndmArray(3, u );
		//subrn(u,2);
		n = (Int_t)(N*u[1]); //WOLF: conversion Int_t-> Double_t -> Int_t
		if(u[2]*pmax<p[n]) break;
	}
	if(n<0) n=0;
	else if(n>6) n=6;

	if(n>1)          // Bp, Bpp, D, Dp, EF states
	{
		Eloss=En[n]*27.2;
		return;
	}
	if(n==0)       // B state; we generate now a vibrational state,
		// using the Frank-Condon factors
	{
		N=28;        // the number of B vibrational states in our calculation
		pmax=pB[7];  // maximum of the pB[] values
		for(j=1;j<5000;j++)
		{
			KSRandom::GetInstance()->RndmArray(3, u );
			//subrn(u,2); //WOLF: conversion Int_t->Double_t
			v=(Int_t)(N*u[1]);
			if(u[2]*pmax<pB[v]) break;
		}
		if(v<0) v=0; if(v>27) v=27;
		Eloss=EB[v]*27.2;

	}
	if(n==1)       // C state; we generate now a vibrational state,
		// using the Franck-Condon factors
	{
		N=14;        // the number of C vibrational states in our calculation
		pmax=pC[1];  // maximum of the pC[] values
		for(j=1; j<5000; j++){
			KSRandom::GetInstance()->RndmArray(3, u );
			//subrn(u,2);
			v=(Int_t)(N*u[1]); //WOLF> conversion Int_t->Double_t
			if(u[2]*pmax<pC[v]) break;
		}
		if(v<0) v=0;
		else if(v>13) v=13;
		Eloss=EC[v]*27.2;
	}
	return;

}//end randomexc

//old version (HYDROGEN ONLY!)
/*
Double_t KScatterBasicInelasticCalculatorFerenc::sigmaion(Double_t anE){ //TODO: move atomic units somewhere
	Double_t B=15.43,U=15.98,R=13.6;
	//const Double_t a02=0.28e-20;
	const Double_t a02 = KaConst::BohrRadiusSquared();
	Double_t sigma,t,u,S,r,lnt;
	if(anE<16.)
		sigma=1.e-40;
	else if(anE>=16. && anE<=250.)
	{
		t=anE/B;
		u=U/B;
		r=R/B;
		S=4.*KaConst::Pi()*a02*2.*r*r;
		lnt=log(t);
		sigma=S/(t+u+1.)*(lnt/2.*(1.-1./(t*t))+1.-1./t-lnt/(t+1.));
	}
	else
		sigma=4.*KaConst::Pi()*a02*R/anE*(0.82*log(anE/R)+1.3);
	return sigma;

}
 */
Double_t KScatteringCalculatorInelastic::sigmaion(Double_t anE)
{
    //KSException Except;
    //Except < "KScatterBasicInelasticCalculatorFerenc::sigmaion";
    
	Double_t sigma = 0.0;

	std::vector <Double_t> CrossSections;
	Double_t TotalCrossSection = 0.0;

	if (fBindingEnergy.size() == 0 )
	{
//        Except = KSException::eFatalError;
//		Except<<"using unitialized calculator. quitting";
//		CatchException(Except);
	}
	const Double_t a02 = KSConst::BohrRadiusSquared();
	const Double_t ERyd = KSConst::ERyd_eV(); //this does exist!

	//in old code:
	//const Double_t ERyd =13.6;//Rydberg constant from EH2SCAT
	//or nancys value:
	//const Double_t R=13.6057;//Rydberg constant


	if (anE > fOrbitalEnergy[fMinimum]){
	//if (anE > 16.){//EH2scat sucks

		//for (std::vector<Double_t>::iterator orbitalIt = fOrbitalEnergy.begin();
		//		orbitalIt != fOrbitalEnergy.end(); orbitalIt++){

		for (UInt_t io=0; io<fOrbitalEnergy.size(); io++){
			Int_t i = 0; //numbers the possible shells

			if ( anE > fOrbitalEnergy[io]){

				//???special case for hydrogen and anE>250 EV ????
				//is this an approximation, or is this acually more correct?
				if (fMoleculeType == "Hydrogen" && anE > 250.)
				{

					sigma = 4.*KSConst::Pi()*a02 * ERyd / anE* (0.82 * log(anE/ERyd)+1.3);
					CrossSections.push_back(4.*KSConst::Pi()*a02 * ERyd / anE* (0.82 * log(anE/ERyd)+1.3));

					TotalCrossSection = CrossSections.at(i);
				}
				else
				{
					Double_t t = anE / fBindingEnergy.at(io);
					Double_t u = fOrbitalEnergy.at(io) / fBindingEnergy.at(io);
					Double_t r = ERyd / fBindingEnergy.at(io);
					Double_t S = 4.*KSConst::Pi()*a02 * fNOccupation.at(io) * r * r;
					Double_t lnt = TMath::Log(t);

					CrossSections.push_back(S/ (t + u + 1.) * (lnt /2.* ( 1. - 1. / (t * t))+1. - 1. / t - lnt / (t+1.)));
					TotalCrossSection += CrossSections.at(i);

					sigma += S/ (t + u + 1.) * (lnt /2.* ( 1. - 1. / (t * t))+1. - 1. / t - lnt / (t+1.));
				}
				i++;
			}
			else sigma=1E-40; //for eh2scat comparison!
		}

		//Determination of ionization energy
		//Random number
		Double_t IonizationDice = KSRandom::GetInstance()->Rndm();
		//Decide from which shell the secondary electron is kicked out
		for( UInt_t i=0; i<CrossSections.size(); i++)
		{
			IonizationDice -= CrossSections.at(i)/TotalCrossSection;
			if( IonizationDice < 0 )
			{
				fIonizationEnergy = fBindingEnergy.at(i);
				/*
				#ifdef DEBUG_VERBOSE
				
				E = KSException::eKTrackDebug;
				E < "KSScatterBasicInelastic::sigmaion";
				E << "ionization energy: " << CrossSections.at(i);
				CatchException(E);
				#endif
				*/
				break;
			}
		}



	}

	else sigma = 1E-40; //why not 0?
	return sigma;

}

Bool_t KScatteringCalculatorInelastic::ReadData(){
	//TODO replace path with the one specified in the core manager
    
    
    //E < "KScatterBasicInelasticCalculatorFerenc::ReadData";

    //KSDataFile* aDataFile = KSIOToolbox::GetInstance()->DemandConfigFile("");
    //todo: implemend the line above to avoid multiple instances of one datafile

	if( fDataFile.Open( KSFile::eRead ) == kTRUE )
	{

	    fstream& inputfile = *(fDataFile.File());
		Double_t aTemp, anotherTemp;
		Int_t aTempInt;
		
		fBindingEnergy.clear();
		fOrbitalEnergy.clear();
		fNOccupation.clear();
		
		while ( ! inputfile.eof() ){

			//does this remove comments? should work.
			Char_t c = inputfile.peek();
			if ( c >= '0' && c < '9') {
				inputfile >> aTemp >> anotherTemp >> aTempInt;
                #ifdef DEBUG_VERBOSE
                //E = KSException::eScatteringDebug
				//std::cout << aTemp << " "<<anotherTemp <<" "<< aTempInt<<std::endl;
                //CatchException(E);
                #endif
				fBindingEnergy.push_back(aTemp);
				fOrbitalEnergy.push_back(anotherTemp);
				fNOccupation.push_back(aTempInt);
			}
			else {
				Char_t dump[200];
				inputfile.getline(dump, 200);
                #ifdef DEBUG_VERBOSE
                //E = KSException::eScatteringDebug
				//E <<"dumping "<< dump<< " because " << c <<" is not a number";
                //CatchException(E);
                #endif
				continue;
			}
		}
	}
	else {
//        E = KSException::eFatalError;
//		E<< "FATAL ERROR reading scattering data: inputfile " << filename<<" not found or molecule type not supported. ";
//		CatchException(E);
	}

	return FindMinimum();
}

Bool_t KScatteringCalculatorInelastic::FindMinimum() {
	Double_t aMinimum = 999999.99;
	for (UInt_t io = 0; io < fOrbitalEnergy.size(); io++){
		if (aMinimum > fOrbitalEnergy[io]) fMinimum = (Int_t) io;
	}
	if (fMinimum >= 0) return true;
	else return false;
}

void KScatteringCalculatorInelastic::randomion(Double_t anE,Double_t& Eloss,Double_t& Theta){
	// << "Eloss Computation" << endl;

  	//Double_t Ei=15.45/27.21;
	Double_t IonizationEnergy_eV = GetIonizationEnergy();		//ionization energy in eV
	Double_t IonizationEnergy_au = IonizationEnergy_eV/27.21;	//ionization energy in atomic units
	Double_t c,b,u[3],K,xmin,ymin,ymax,x,y,T,G,W,Gmax;
	Double_t q,h,F,Fmin,Fmax,Gp,Elmin,Elmax,qmin,qmax,El,wmax;
	Double_t WcE,Jstarq,WcstarE,w,D2ion;
	//Int_t j;
	Double_t K2,KK,fE,kej,ki,kf,Rex,arg,arctg;
	//Int_t i;
	Double_t st1,st2;
	//
	// I. Generation of Theta
	// -----------------------
	Gmax=1.e-20;
	if(anE<200.)
		Gmax=2.e-20;
	T=anE/27.21;
	xmin=IonizationEnergy_au*IonizationEnergy_au/(2.*T);
	b=xmin/(4.*T);
	ymin=log(xmin);
	ymax=log(8.*T+xmin);
	// Generation of y values with the Neumann acceptance-rejection method:
	for(Int_t j=1;j<5000;j++)
	{
		//subrn(u,2);
		KSRandom::GetInstance()->RndmArray(3, u );
		y=ymin+(ymax-ymin) * u[1];
		K=exp(y/2.);
		c=1.+b-K*K/(4.*T);
		G=K*K*( DiffXSecInel(anE,c)- DiffXSecExc(anE,c));
		if(Gmax*u[2]<G) break;
	}
	// y --> x --> c --> Theta
	x=exp(y);
	c=1.-(x-xmin)/(4.*T);
	Theta=acos(c)*180./KSConst::Pi();

	//
	// II. Generation of Eloss, for fixed Theta
	// ----------------------------------------
	//
	// For anE<=200 eV we use subr. gensecelen
	//   (in this case no correlation between Theta and Eloss)
	if(anE<=200.)
	{
		gensecelen(anE, W);
		Eloss=IonizationEnergy_eV+W;
        return;
	}
	// For Theta>=20 the free electron model is used
	//   (with full correlation between Theta and Eloss)
	if(Theta>=20.)
	{
		Eloss=anE*(1.-c*c);
		if(Eloss<IonizationEnergy_eV+0.05)
			Eloss=IonizationEnergy_eV+0.05;
        return;
	}
	// For anE>200 eV and Theta<20: analytical first Born approximation
	//   formula of Bethe for H atom (with modification for H2)
	//
	// Calc. of wmax:
	if(Theta>=0.7)
		wmax=1.1;
	else if(Theta<=0.7 && Theta>0.2)
		wmax=2.;
	else if(Theta<=0.2 && Theta>0.05)
		wmax=4.;
	else
		wmax=8.;
	// We generate the q value according to the Jstarq pdf. We have to
	// define the qmin and qmax limits for this generation:
	K=sqrt(4.*T*(1.-IonizationEnergy_au/(2.*T)-sqrt(1.-IonizationEnergy_au/T)*c));
	Elmin=IonizationEnergy_au;
	Elmax=(anE+IonizationEnergy_eV)/2./27.2;
	qmin=Elmin/K-K/2.;
	qmax=Elmax/K-K/2.;
	//
	q=qmax;
	Fmax=1./2.+1./KSConst::Pi()*(q/(1.+q*q)+atan(q));
	q=qmin;
	Fmin=1./2.+1./KSConst::Pi()*(q/(1.+q*q)+atan(q));
	h=Fmax-Fmin;
	// Generation of Eloss with the Neumann acceptance-rejection method:
	for(Int_t j=1;j<5000;j++)
	{
		// Generation of q with inverse transform method
		// (we use the Newton-Raphson method in order to solve the nonlinear eq.
		// for the inversion) :
		KSRandom::GetInstance()->RndmArray(3, u );
		//subrn(u,2);
		F=Fmin+h*u[1];
		y=0.;
		for(Int_t i=1;i<=30;i++)
		{
			G=1./2.+(y+sin(2.*y)/2.)/KSConst::Pi();
			Gp=(1.+cos(2.*y))/KSConst::Pi();
			y=y-(G-F)/Gp;
			if(fabs(G-F)<1.e-8) break;
		}
		q=tan(y);
		// We have the q value, so we can define El, and calculate the weight:
		El=q*K+K*K/2.;
		// First Born approximation formula of Bethe for e-H ionization:
		KK=K;
		ki=sqrt(2.*T);
		kf=sqrt(2.*(T-El));
		K2=4.*T*(1.-El/(2.*T)-sqrt(1.-El/T)*c); if(K2<1.e-9) K2=1.e-9;
		K=sqrt(K2);               // momentum transfer
		Rex=1.-K*K/(kf*kf)+K2*K2/(kf*kf*kf*kf);
		kej=sqrt(2.*fabs(El-IonizationEnergy_au)+1.e-8);
		st1=K2-2.*El+2.; if(fabs(st1)<1.e-9) st1=1.e-9;
		arg=2.*kej/st1;
		if(arg>=0.)
			arctg=atan(arg);
		else
			arctg=atan(arg)+KSConst::Pi();
		st1=(K+kej)*(K+kej)+1.;
		st2=(K-kej)*(K-kej)+1.;
		fE=1024.*El*(K2+2./3.*El)/(st1*st1*st1*st2*st2*st2)*
				exp(-2./kej*arctg)/(1.-exp(-2.*KSConst::Pi()/kej));
		D2ion=2.*kf/ki*Rex/(El*K2)*fE;
		K=KK;
		//
		WcE=D2ion;
		Jstarq=16./(3.*KSConst::Pi()*(1.+q*q)*(1.+q*q));
		WcstarE=4./(K*K*K*K*K)*Jstarq;
		w=WcE/WcstarE;
		if(wmax*u[2]<w) break;
	}
	//
	Eloss=El*27.21;
	if(Eloss<IonizationEnergy_eV+0.05)
		Eloss=IonizationEnergy_eV+0.05;
	//
	// << "Eloss " << Eloss << endl;

	return;

}//end randomion


Double_t KScatteringCalculatorInelastic::DiffXSecExc(Double_t anE,Double_t cosTheta){
	Double_t K2,K,T,theta;
	Double_t sigma = 0.;
	//Double_t a02=28.e-22;   // Bohr radius squared
	Double_t a02 = KSConst::BohrRadiusSquared();

	Double_t EE=12.6/27.21;
	Double_t e[5]={0.,25.,35.,50.,100.};
	Double_t t[9]={0.,10.,20.,30.,40.,60.,80.,100.,180.};
	Double_t D[4][9]={
			{60.,43.,27.,18.,13.,8.,6.,6.,6.},
			{95.,70.,21.,9.,6.,3.,2.,2.,2.,},
			{150.,120.,32.,8.,3.7,1.9,1.2,0.8,0.8},
			{400.,200.,12.,2.,1.4,0.7,0.3,0.2,0.2}};
	Int_t i,j;
	//
	T=anE/27.21;
	if(anE>=100.)
	{
		K2=4.*T*(1.-EE/(2.*T)-sqrt(1.-EE/T)*cosTheta); if(K2<1.e-9) K2=1.e-9;
		K=sqrt(K2);               // momentum transfer
		sigma=2./K2 * sumexc(K)*a02;
	}
	else if(anE<=10.)
		sigma=0.;
	else
	{
		theta=acos(cosTheta)*180./KSConst::Pi();
		for(i=0;i<=3;i++)
			if(anE>=e[i] && anE<e[i+1])
				for(j=0;j<=7;j++)
					if(theta>=t[j] && theta<t[j+1])
						sigma=1.e-22*(D[i][j]+(D[i][j+1]-D[i][j])*
								(theta-t[j])/(t[j+1]-t[j]));
	}
	return sigma;

}//end DiffXSecExc


Double_t KScatteringCalculatorInelastic::DiffXSecInel(Double_t anE,Double_t cosTheta){

	//Double_t a02=28.e-22;   // Bohr radius squared
	Double_t a02 = KSConst::BohrRadiusSquared();

	Double_t Cinel[50]={
			-0.246,     -0.244,     -0.239,     -0.234,     -0.227,
			-0.219,     -0.211,     -0.201,     -0.190,     -0.179,
			-0.167,     -0.155,     -0.142,     -0.130,     -0.118,
			-0.107,     -0.096,     -0.085,     -0.076,     -0.067,
			-0.059,     -0.051,     -0.045,     -0.039,     -0.034,
			-0.029,     -0.025,     -0.022,     -0.019,     -0.016,
			-0.014,     -0.010,     -0.008,     -0.006,     -0.004,
			-0.003,     -0.003,     -0.002,     -0.002,     -0.001,
			-0.001,     -0.001,      0.000,      0.000,      0.000,
			0.000,      0.000,      0.000,      0.000,      0.000};
	//Double_t Ei=0.568;
	Double_t IonizationEnergy_eV = GetIonizationEnergy();		//ionization energy in eV
	Double_t IonizationEnergy_au = IonizationEnergy_eV/27.21;	//ionization energy in atomic units
	Double_t T,K2,K,st1,F,DH,Dinelreturn,CinelK,Ki;
	Int_t i;
	if(anE<IonizationEnergy_eV)//Achtung! 16.
		return DiffXSecExc(anE, cosTheta);
	T=anE/27.21;
	K2=4.*T*(1.-IonizationEnergy_au/(2.*T)-sqrt(1.-IonizationEnergy_au/T)*cosTheta); if(K2<1.e-9) K2=1.e-9;//Achtung!!
	K=sqrt(K2);        // momentum transfer
	st1=1.+K2/4.;
	F=1./(st1*st1);  // scatt. formfactor of hydrogen atom
	// DH is the diff. cross section for inelastic electron scatt.
	// on atomic hydrogen within the first Born approximation :
	DH=4./(K2*K2)*(1.-F*F)*a02;
	// CinelK calculation with linear interpolation.
	// CinelK is the correction of the inelastic electron
	// scatt. on molecular hydrogen compared to the independent atom
	// model.
	if(K<3.)
	{
		i=(Int_t)(K/0.1);  //WOLF: Double_t->Int_t
		Ki=i*0.1; //WOLF: Double_t->Int_t
		CinelK=Cinel[i]+(K-Ki)/0.1*(Cinel[i+1]-Cinel[i]);}
	else if(K>=3. && K < 5.)
	{
		i=(Int_t)(30+(K-3.)/ 0.2); //WOLF: Double->Int_t
		Ki=3.+(i-30)* 0.2;//WOLF Double_t->Int_t
		CinelK=Cinel[i]+(K-Ki)/0.2*(Cinel[i+1]-Cinel[i]);}
	else if(K>=5. && K < 9.49)
	{
		i=(Int_t)(40+(K-5.)/0.5); //WOLF: Double_t ->Int_t
		Ki=5.+(i-40)*0.5; //WOLF: Double_t->Int
		CinelK=Cinel[i]+(K-Ki)/0.5*(Cinel[i+1]-Cinel[i]);}
	else
		CinelK=0.;
	Dinelreturn=2.*DH*(1.+CinelK);
	return Dinelreturn;

}



void KScatteringCalculatorInelastic::gensecelen(Double_t anE,Double_t& W){ //TODO

	Double_t IonizationEnergy_eV = GetIonizationEnergy();		//ionization energy in eV
	Double_t /*Ei=15.45,*/eps2=14.3,b=6.25;
	Double_t B;
	Double_t C,A,eps,a,u,epsmax;

	B=atan((IonizationEnergy_eV-eps2)/b);
	epsmax=(anE+IonizationEnergy_eV)/2.;
	A=atan((epsmax-eps2)/b);
	C=b/(A-B);
	u=KSRandom::GetInstance()->Rndm();
	a=b/C*(u+C/b*B);
	eps=eps2+b*tan(a);
	W=eps-IonizationEnergy_eV;
	return;

}


Double_t KScatteringCalculatorInelastic::sigmainel(Double_t anE){

	if ( anE < 250.){
        
//        E < "KScatterBasicInelasticCalculatorFerenc::sigmainel";
//        E = KSException::eError;
//		E <<"cross section not valid. return 0.";
//        CatchException(E);
		return 0.0;
	}

	Double_t IonizationEnergy_eV = GetIonizationEnergy();
	Double_t IonizationEnergy_au = IonizationEnergy_eV/27.21;	//ionization energy in atomic units
	//Double_t Ei=0.568;  // ionization energy of molecular
	// hydrogen in Hartree atomic units
	//  (15.45 eV)
	Double_t a02 = KSConst::BohrRadiusSquared();

	Double_t sigma,gamtot,T;
	T=anE/27.21;
	gamtot=2.*(-7./4.+log(IonizationEnergy_au/(2.*T)));
	sigma=2.*KSConst::Pi()/T*(1.5487*log(2.*T)+2.4036+gamtot/(2.*T));
	sigma=sigma*a02;
	return sigma;

}

/////////////////////////////////////////////////////////////
//private helper methods

Double_t KScatteringCalculatorInelastic::sumexc(Double_t K)
{
	Double_t Kvec[15]={0.,0.1,0.2,0.4,0.6,0.8,1.,1.2,1.5,1.8,2.,2.5,3.,4.,5.};
	Double_t fvec[7][15]=
	{{2.907e-1,2.845e-1,2.665e-1,2.072e-1,1.389e-1,  // B
			8.238e-2,4.454e-2,2.269e-2,7.789e-3,2.619e-3,
			1.273e-3,2.218e-4,4.372e-5,2.889e-6,4.247e-7},
			{3.492e-1,3.367e-1,3.124e-1,2.351e-1,1.507e-1,  // C
					8.406e-2,4.214e-2,1.966e-2,5.799e-3,1.632e-3,
					6.929e-4,8.082e-5,9.574e-6,1.526e-7,7.058e-9},
					{6.112e-2,5.945e-2,5.830e-2,5.072e-2,3.821e-2,  // Bp
							2.579e-2,1.567e-2,8.737e-3,3.305e-3,1.191e-3,
							6.011e-4,1.132e-4,2.362e-5,1.603e-6,2.215e-7},
							{2.066e-2,2.127e-2,2.137e-2,1.928e-2,1.552e-2,  // Bpp
									1.108e-2,7.058e-3,4.069e-3,1.590e-3,5.900e-4,
									3.046e-4,6.142e-5,1.369e-5,9.650e-7,1.244e-7},
									{9.405e-2,9.049e-2,8.613e-2,7.301e-2,5.144e-2,  // D
											3.201e-2,1.775e-2,8.952e-3,2.855e-3,8.429e-4,
											3.655e-4,4.389e-5,5.252e-6,9.010e-8,7.130e-9},
											{4.273e-2,3.862e-2,3.985e-2,3.362e-2,2.486e-2,  // Dp
													1.612e-2,9.309e-3,4.856e-3,1.602e-3,4.811e-4,
													2.096e-4,2.498e-5,2.905e-6,5.077e-8,6.583e-9},
													{0.000e-3,2.042e-3,7.439e-3,2.200e-2,3.164e-2,  // EF
															3.161e-2,2.486e-2,1.664e-2,7.562e-3,3.044e-3,
															1.608e-3,3.225e-4,7.120e-5,6.290e-6,1.066e-6}};
	Double_t EeV[7]={12.73,13.20,14.77,15.3,14.93,15.4,13.06};
	Int_t jmin = 0;
	Int_t nnmax = 6;
	Double_t En,f[7],x4[4],f4[4],sum;
	//
	sum=0.;

	for( Int_t n=0;n<=nnmax;n++)
	{ En=EeV[n]/27.21;  // En is the excitation energy in Hartree atomic units
	if(K>=5.)
		f[n]=0.;
	else if(K>=3. && K<=4.)
		f[n]=fvec[n][12]+(K-3.)*(fvec[n][13]-fvec[n][12]);
	else if(K>=4. && K<=5.)
		f[n]=fvec[n][13]+(K-4.)*(fvec[n][14]-fvec[n][13]);
	else
	{ for(Int_t j=0;j<14;j++)
	{ if(K>=Kvec[j] && K<=Kvec[j+1]) jmin=j-1 ;}
	if(jmin<0) jmin=0; if(jmin>11) jmin=11;

	for( Int_t j=0;j<=3;j++)
	{ x4[j]=Kvec[jmin+j];
	f4[j]=fvec[n][jmin+j];}
	f[n]=KMath::Lagrange(4,x4,f4,K);
	}
	sum+=f[n]/En;
	}
	return sum;
}//end sumexc


Double_t KScatteringCalculatorInelastic::sigmadiss10(Double_t anE)
{

	Double_t a[9]={-2.297914361e5,5.303988579e5,-5.316636672e5,
			3.022690779e5,-1.066224144e5,2.389841369e4,
			-3.324526406e3,2.624761592e2,-9.006246604};
	Double_t lnsigma,lnE,lnEn,Emin,sigma;
	Int_t n;
	//  anE is in eV
	sigma=0.;
	Emin=9.8;
	lnE=log(anE);
	lnEn=1.;
	lnsigma=0.;
	if(anE<Emin)
		sigma=0.;
	else
	{
		for(n=0;n<=8;n++)
		{
			lnsigma+=a[n]*lnEn;
			lnEn=lnEn*lnE;
		}
		sigma=exp(lnsigma);
	}
	return sigma*1.e-4;
}


Double_t KScatteringCalculatorInelastic::sigmadiss15(Double_t anE)
{

	Double_t a[9]={ -1.157041752e3,1.501936271e3,-8.6119387e2,
			2.754926257e2,-5.380465012e1,6.573972423,
			-4.912318139e-1,2.054926773e-2,-3.689035889e-4};
	Double_t lnsigma,lnE,lnEn,Emin,sigma;
	Int_t n;
	//  anE is in eV
	sigma=0.;
	Emin=16.5;
	lnE=log(anE);
	lnEn=1.;
	lnsigma=0.;
	if(anE<Emin)
		sigma=0.;
	else
	{
		for(n=0;n<=8;n++)
		{
			lnsigma+=a[n]*lnEn;
			lnEn=lnEn*lnE;
		}
		sigma=exp(lnsigma);
	}
	return sigma*1.e-4;
}

Double_t KScatteringCalculatorInelastic::sigmaBC(Double_t anE)
{

	Double_t aB[9]={-4.2935194e2, 5.1122109e2, -2.8481279e2,
			8.8310338e1, -1.6659591e1, 1.9579609,
			-1.4012824e-1, 5.5911348e-3, -9.5370103e-5};
	Double_t aC[9]={-8.1942684e2, 9.8705099e2, -5.3095543e2,
			1.5917023e2, -2.9121036e1,3.3321027,
			-2.3305961e-1, 9.1191781e-3,-1.5298950e-4};
	Double_t lnsigma,lnE,lnEn,sigmaB,Emin,sigma,sigmaC;
	Int_t n;
	sigma=0.;
	Emin=12.5;
	lnE=log(anE);
	lnEn=1.;
	lnsigma=0.;
	if(anE<Emin)
		sigmaB=0.;
	else
	{
		for(n=0;n<=8;n++)
		{
			lnsigma+=aB[n]*lnEn;
			lnEn=lnEn*lnE;
		}
		sigmaB=exp(lnsigma);
	}
	sigma+=sigmaB;
	//  sigma=0.;
	// C state:
	Emin=15.8;
	lnE=log(anE);
	lnEn=1.;
	lnsigma=0.;
	if(anE<Emin)
		sigmaC=0.;
	else
	{
		for(n=0;n<=8;n++)
		{
			lnsigma+=aC[n]*lnEn;
			lnEn=lnEn*lnE;
		}
		sigmaC=exp(lnsigma);
	}
	sigma+=sigmaC;
	return sigma*1.e-4;
}
}
