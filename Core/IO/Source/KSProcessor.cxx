#include "KSProcessor.h"

#include <iostream>
using std::cout;
using std::endl;

namespace Kassiopeia
{

    KSTokenizer* KSProcessor::fTokenizer = NULL;

    KSProcessor::KSProcessor() :
        fParent( NULL ),
        fChild( NULL )
    {
    }
    KSProcessor::~KSProcessor()
    {
    }

    void KSProcessor::DropProcessor( KSProcessor* aNewProcessor )
    {
        if( fChild == NULL )
        {
            fChild = aNewProcessor;
            fChild->fParent = this;
            return;
        }
        fChild->DropProcessor( aNewProcessor );
        return;
    }
    void KSProcessor::LiftProcessor( KSProcessor* const anOldProcessor )
    {
        if( anOldProcessor == this )
        {
            KSProcessor* OldParent = fParent;

            fParent->fChild = NULL;
            this->fParent = NULL;

            OldParent->LiftProcessor( this );

            return;
        }

        if( fParent == NULL )
        {
            delete anOldProcessor;
            return;
        }
        fParent->LiftProcessor( anOldProcessor );
        return;
    }

    void KSProcessor::ProcessToken( KSTokenBeginParsing* aToken )
    {
        if( fChild == NULL )
        {
            return;
        }
        else
        {
            fChild->ProcessToken( aToken );
            return;
        }
    }
    void KSProcessor::ProcessToken( KSTokenEndParsing* aToken )
    {
        if( fChild == NULL )
        {
            return;
        }
        else
        {
            fChild->ProcessToken( aToken );
            return;
        }
    }
    void KSProcessor::ProcessToken( KSTokenBeginFile* aToken )
    {
        if( fChild == NULL )
        {
            return;
        }
        else
        {
            fChild->ProcessToken( aToken );
            return;
        }
    }
    void KSProcessor::ProcessToken( KSTokenEndFile* aToken )
    {
        if( fChild == NULL )
        {
            return;
        }
        else
        {
            fChild->ProcessToken( aToken );
            return;
        }
    }
    void KSProcessor::ProcessToken( KSTokenBeginElement* aToken )
    {
        if( fChild == NULL )
        {
            return;
        }
        else
        {
            fChild->ProcessToken( aToken );
            return;
        }
    }
    void KSProcessor::ProcessToken( KSTokenEndElement* aToken )
    {
        if( fChild == NULL )
        {
            return;
        }
        else
        {
            fChild->ProcessToken( aToken );
            return;
        }
    }
    void KSProcessor::ProcessToken( KSTokenAttribute* aToken )
    {
        if( fChild == NULL )
        {
            return;
        }
        else
        {
            fChild->ProcessToken( aToken );
            return;
        }
    }
    void KSProcessor::ProcessToken( KSTokenData* aToken )
    {
        if( fChild == NULL )
        {
            return;
        }
        else
        {
            fChild->ProcessToken( aToken );
            return;
        }
    }
    void KSProcessor::ProcessToken( KSTokenError* aToken )
    {
        if( fChild == NULL )
        {
            return;
        }
        else
        {
            fChild->ProcessToken( aToken );
            return;
        }
    }

} /* namespace Kassiopeia */
