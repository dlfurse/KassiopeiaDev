/*!
 * @file KSBuilder.h
 * @brief contains class definition for KSBuilder
 *
 * @details
 * <b>Revision History:</b>
 * @verbatim
 * Date         Name          Brief description
 * -----------------------------------------------
 * 13 Jul 2010  D. Furse      first version
 * @endverbatim
 *
 */

#ifndef KSBUILDER_H_
#define KSBUILDER_H_

#include "KSReceiver.h"

#include "KSTokenizer.h"

/*!
 * @class Kassiopeia::KSBuilder
 * @author Dan Furse
 *
 * @brief base class for all builders
 *
 * @details
 * <b>Detailed Description:</b><br>
 *
 */
namespace Kassiopeia
{

    class KSBuilder :
        public KSReceiver
    {
        public:
            KSBuilder();
            virtual ~KSBuilder();

            void SetTokenizer( KSTokenizer* tokenizer );

            void DropBuilder( KSBuilder* newbuild );
            void LiftBuilder( KSBuilder* const oldbuild );

            virtual const string& GetTypeName() const = 0;

            virtual void ReceiveToken( const KSErrorToken* token );
            virtual void ReceiveToken( const KSTokenBeginParsing* token );
            virtual void ReceiveToken( const KSEndParsingToken* token );
            virtual void ReceiveToken( const KSTokenBeginFile* token );
            virtual void ReceiveToken( const KSTokenEndFile* token );

            virtual void ReceiveToken( const KSTokenStartElement* token );
            virtual void ReceiveToken( const KSTokenAttribute* token );
            virtual void ReceiveToken( const KSTokenEndElement* token );
            virtual void ReceiveToken( const KSDataToken* token );
            virtual void ReceiveToken( const KSTokenError* token );

            virtual const KSBuilder* GetParent() const;
            virtual const KSBuilder* GetChild() const;

        protected:
            virtual Bool_t ProcessToken( const KSErrorToken* token );
            virtual Bool_t ProcessToken( const KSTokenBeginParsing* token );
            virtual Bool_t ProcessToken( const KSEndParsingToken* token );
            virtual Bool_t ProcessToken( const KSTokenBeginFile* token );
            virtual Bool_t ProcessToken( const KSTokenEndFile* token );

            virtual Bool_t ProcessToken( const KSPseudoBeginToken* token );
            virtual Bool_t ProcessToken( const KSPseudoParameterToken* token );
            virtual Bool_t ProcessToken( const KSPseudoEndToken* token );
            virtual Bool_t ProcessToken( const KSPseudoKeywordToken* token );
            virtual Bool_t ProcessToken( const KSPseudoErrorToken* token );

            virtual Bool_t ProcessToken( const KSStartElementToken* token );
            virtual Bool_t ProcessToken( const KSTokenAttribute* token );
            virtual Bool_t ProcessToken( const KSTokenEndElement* token );
            virtual Bool_t ProcessToken( const KSDataToken* token );
            virtual Bool_t ProcessToken( const KSTokenError* token );

            virtual Bool_t ProcessBuilder( const KSBuilder* token );

            void SetParent( KSBuilder* const prev );
            void SetChild( KSBuilder* const next );

            virtual Bool_t ProcessSystemAttributes( const KSPseudoParameterToken* token );
            virtual Bool_t ProcessSystemAttributes( const KSTokenAttribute* token );

            KSTokenizer* fTokenizer;
            KSBuilder* fParent;
            KSBuilder* fChild;
    };

} // end namespace Kassiopeia

#endif // end ifndef KSPseudoXMLBuilder_h
