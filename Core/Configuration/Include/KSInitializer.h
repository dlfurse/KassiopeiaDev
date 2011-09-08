/*
 * KSInitializer.h
 *
 * created on: Apr 11, 2011
 * author: dlfurse
 */

#ifndef KSINITIALIZER_H_
#define KSINITIALIZER_H_

#include "KSBuilder.h"

#include "KSBuilderFactoryTable.h"

/*!
 * @class Kassiopeia::Initializer
 * @author Dan Furse
 *
 * @brief this class is a special builder that sits at one end of the linked list, managing the initialization and operation of the other builders.
 *
 */
namespace Kassiopeia
{

    class KSInitializer :
        public KSBuilder
    {
        public:
            KSInitializer();
            virtual ~KSInitializer();

            void Read( const string& filename );

            virtual void ReceiveToken( const KSPseudoBeginToken* token );
            virtual void ReceiveToken( const KSTokenBeginElement* token );

        protected:
            virtual Bool_t ProcessBuilder( const KSBuilder* builder );

        private:
            const KSBuilderFactoryTable::BuilderMap* fMap;
            KSBuilderFactoryTable::BuilderMap::const_iterator fMapIt;
    };

}

#endif /* KSINITIALIZER_H_ */
