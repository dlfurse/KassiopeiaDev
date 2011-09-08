/*
 * KSStepContainer.cxx
 *
 * created on: Mar 6, 2011
 * author: dlfurse
 */

#include "KSStepContainer.h"

namespace Kassiopeia
{

    KSStepContainer::KSStepContainer() :
        fCenter(0.,0.,0.),
        fDirection(0.,0.,0.),
        fLength(0.),
        fStart(0.,0.,0.),
        fEnd(0.,0.,0.),
        fRadius(0.),
        fDiagonal(0.)
    {
    }

    KSStepContainer::~KSStepContainer()
    {
    }

}
