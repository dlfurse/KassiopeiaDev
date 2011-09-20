#include "KScatterBasicElasticCalculatorFerenc.h"
#include "KSRandom.h"
#include "KSConst.h"


using namespace std;
namespace Kassiopeia{
KScatterBasicElasticCalculatorFerenc::KScatterBasicElasticCalculatorFerenc()
{}

KScatterBasicElasticCalculatorFerenc::~KScatterBasicElasticCalculatorFerenc(){
	//not needed
}

Double_t KScatterBasicElasticCalculatorFerenc::sigmael(Double_t anE){

	const Double_t e[14]={0.,1.5,5.,7.,10.,15.,20.,30.,60.,100.,150.,200.,300.,400.};
	const Double_t s[14]={9.6,13.,15.,12.,10.,7.,5.6,3.3,1.1,0.9,0.5,0.36,0.23,0.15};
	//const Double_t emass=18780.; //????
	//const Double_t a02 = 28.e-22; //?????
	const Double_t emass= 1./(KSConst::Alpha() * KSConst::Alpha());
	const Double_t a02 = KSConst::BohrRadiusSquared();

	Double_t gam,T;
	Double_t sigma = 0.0;
	T=anE/27.2;
	if(anE>=400.)
	{
		gam=( emass+T) / emass;
		sigma = gam * gam * KSConst::Pi()/(2.* T) * (4.2106 - 1./T) * a02;
	}
	else
		for( Int_t i=0;i<= 12; i++){
			if(anE>=e[i] && anE<e[i+1]) sigma=1.e-20*(s[i]+(s[i+1]-s[i])*(anE-e[i])/(e[i+1]-e[i]));
		}

	return sigma;

}

void KScatterBasicElasticCalculatorFerenc::randomel(Double_t anE,Double_t& Eloss,Double_t& Theta){ //ToDO: vernuenftige einheiten, constanten woanderst definieren.

    //std::cout<<"In randomel, calculating an elastic scattering event"<<std::endl;

	Double_t emass= 1./ (KSConst::Alpha() * KSConst::Alpha());  // electron mass energy anE = m c^2 in atomic unit
	Double_t clight= 1./KSConst::Alpha() ;  // velocity of light in atomic units is 1/ alpha

	Double_t H2molmass=69.e6;

	Double_t T,c,b,u[3],G,a,gam,K2,Gmax;
	//Int_t i;
	if(anE >= 250.)
		Gmax = 1.e-19;
	else if(anE < 250. && anE >= 150.)
		Gmax = 2.5e-19;
	else
		Gmax = 1.e-18;
	T = anE/27.2;
	gam = 1.+T/(clight*clight);   // relativistic correction factor
	b = 2./(1.+gam)/T;
	for(Int_t i=1; i<5000; i++)
	{
		KSRandom::GetInstance()->RndmArray(3, u );
		//subrn(u,2);
		c  = 1.+ b - b * (2.+b)/(b+2.*u[1]);
		K2 = 2.* T * (1.+gam) * fabs(1.-c); // momentum transfer squared
		a  = ( 4. + K2) * (4.+K2) / (gam*gam);
		G  = a *  DiffXSecEl(anE,c);
		if(G > Gmax * u[2]) break;
	}
	Theta = acos(c)*180./KSConst::Pi();
	Eloss = 2.*emass / H2molmass * (1.-c) * anE;
	return;
}

Double_t KScatterBasicElasticCalculatorFerenc::DiffXSecEl(Double_t anE,Double_t cosTheta){

	//Double_t a02=28.e-22;   // Bohr radius squared
	Double_t a02 = KSConst::BohrRadiusSquared();

	Double_t clight= 1. / KSConst::Alpha();   // velocity of light in atomic units is 1/ alpha

	Double_t Cel[50]={
			-0.512,     -0.512,     -0.509,     -0.505,     -0.499,
			-0.491,     -0.476,     -0.473,     -0.462,     -0.452,
			-0.438,     -0.422,     -0.406,     -0.388,     -0.370,
			-0.352,     -0.333,     -0.314,     -0.296,     -0.277,
			-0.258,     -0.239,     -0.221,     -0.202,     -0.185,
			-0.167,     -0.151,     -0.135,     -0.120,     -0.105,
			-0.092,     -0.070,     -0.053,     -0.039,     -0.030,
			-0.024,     -0.019,     -0.016,     -0.014,     -0.013,
			-0.012,     -0.009,     -0.008,     -0.006,     -0.005,
			-0.004,     -0.003,     -0.002,     -0.002,     -0.001};
	Double_t e[10]={0.,3.,6.,12.,20.,32.,55.,85.,150.,250.};
	Double_t t[10]={0.,10.,20.,30.,40.,60.,80.,100.,140.,180.};
	Double_t D[9][10]={
			{2.9, 2.70, 2.5, 2.10, 1.80, 1.2000, 0.900, 1.0000, 1.600, 1.9},
			{4.2, 3.60, 3.1, 2.50, 1.90, 1.1000, 0.800, 0.9000, 1.300, 1.4},
			{6.0, 4.40, 3.2, 2.30, 1.80, 1.1000, 0.700, 0.5400, 0.500, 0.6},
			{6.0, 4.10, 2.8, 1.90, 1.30, 0.6000, 0.300, 0.1700, 0.160, 0.23},
			{4.9, 3.20, 2.0, 1.20, 0.80, 0.3000, 0.150, 0.0900, 0.050, 0.05},
			{5.2, 2.50, 1.2, 0.64, 0.36, 0.1300, 0.050, 0.0300, 0.016, 0.02},
			{4.0, 1.70, 0.7, 0.30, 0.16, 0.0500, 0.020, 0.0130, 0.010, 0.01},
			{2.8, 1.10, 0.4, 0.15, 0.07, 0.0200, 0.010, 0.0070, 0.004, 0.003},
			{1.2, 0.53, 0.2, 0.08, 0.03, 0.0074, 0.003, 0.0016, 0.001, 0.0008}};
	Double_t T,K2,K,d,st1,st2,DH,gam, CelK,Ki,theta;
	Double_t Delreturn = -1.0;
	Int_t i,j;
	T=anE/27.2;
	if(anE>=250.)
	{
		gam=1.+T/(clight*clight);   // relativistic correction factor
		K2=2.*T*(1.+gam)*(1.-cosTheta); if(K2<0.) K2=1.e-30;
		K=sqrt(K2); if(K<1.e-9) K=1.e-9;  // momentum transfer
		d=1.4009;              // distance of protons in H2
		st1=8.+K2; st2=4.+K2;
		// DH is the diff. cross section for elastic electron scatt.
		// on atomic hydrogen within the first Born approximation :
		DH=4.*st1*st1/(st2*st2*st2*st2)*a02;
		// CelK calculation with linear interpolation.
		// CelK is the correction of the elastic electron
		// scatt. on molecular hydrogen compared to the independent atom
		// model.
		if(K<3.)
		{
			i=(Int_t)(K/0.1); //WOLF Int_t->Double_t->Int_t
			Ki=i*0.1;
			CelK=Cel[i]+(K-Ki)/0.1*(Cel[i+1]-Cel[i]);
		}
		else if(K>=3. && K < 5.)
		{
			i=(Int_t)(30+(K-3.)/0.2); //WOLF: Int_t->Double_t
			Ki=3.+(i-30)*0.2;//WOLF: Int_t->Double_t
			CelK=Cel[i]+(K-Ki)/0.2*(Cel[i+1]-Cel[i]);
		}
		else if(K>=5. && K < 9.49)
		{
			i=(Int_t)(40+(K-5.)/0.5); //WOLF: Int_t->Double_t
			Ki=5.+(i-40)*0.5;//WOLF: Int_t->Double_t
			CelK=Cel[i]+(K-Ki)/0.5*(Cel[i+1]-Cel[i]);
		}
		else CelK=0.;

		Delreturn=2.*gam*gam*DH*(1.+sin(K*d)/(K*d))*(1.+CelK);
	}//end if anE>=250
	else
	{
		theta = acos(cosTheta) * 180. / KSConst::Pi();
		for(i = 0; i <= 8; i++)
			if(anE>= e[i] && anE< e[i+1])
				for(j = 0; j <= 8; j++)
					if(theta >= t[j] && theta < t[j+1])
						Delreturn = 1.e-20*(D[i][j]+(D[i][j+1]-D[i][j])*
								(theta-t[j])/(t[j+1]-t[j]));
	}
	return Delreturn;

}//end DiffXSecEl
}
