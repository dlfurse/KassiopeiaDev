/*
 * KSCommand.h
 *
 * created on: Mar 24, 2011
 * author: dlfurse
 */

#ifndef KSCOMMAND_H_
#define KSCOMMAND_H_

/*!
 @file KSCommand.h
 @author Susanne Mertens, Dan Furse

 @brief This file contains classes that are templates of commands.

 @details
 <b>Detailed Description:</b><br>
 The command class can call SOME function x of SOME class y with SOME parameter z  that returns SOME w return parameter.
 All SOMES (x,y,z,w) are set when a command is created (i.e. during initialization).
 To let the command know on which specific object of the type (with which it is initialized)
 it has to act there is a function SetTarget(Receiving object).
 To find out to which class the command belongs it has the function GetTypeName(),
 which actually returns the type name of the class the command is supposed to act on.
 For this purpose the command is a friend of the corresponding class and has therefore access to its typename.



 <b>Revision History:</b>
 @verbatim
 Date       Name          Brief description
 -----------------------------------------------
 13.05.2010   dan       First version
 28.06.2010   susanne   Little adjusting for KASSIOPEIA purposes (comments)
 26.03.2011   dan       Removed boost::any to improve safety
 @endverbatim

 */

#include "KLMessage.h"

#include <string>
using std::string;

namespace Kassiopeia
{

    /*!
     * @class Kassiopeia::KSCommand
     *
     * @brief This class represents a prepared command which may be executed at any time.
     *
     */
    class KSCommand
    {
        public:
            inline KSCommand()
            {
            }
            inline virtual ~KSCommand()
            {
            }

            virtual void Execute() = 0;
        
            virtual void Print() = 0;
    };

    /*!
     * @class Kassiopeia::KSCommandPrototype
     *
     * @brief This class is a command templated with the type of the target on which the command will be executed.
     * @details
     * When a command of this type is created, the type of the object that is supposed to receive the command is given as an argument.
     * To define the actual object on which the command has to be executed the class has the function SetTarget(object of receiver type).
     */
    template<class XTargetType>
    class KSCommandPrototype:
        public KSCommand
    {
        public:
            inline KSCommandPrototype() :
                fTarget(0)
            {
            }
            inline virtual ~KSCommandPrototype()
            {
            }

            inline void SetTarget(XTargetType* const target)
            {
                fTarget = target;
            }

        protected:
            XTargetType* fTarget;
    };

    /*!
     * @class Kassiopeia::KSCommandOneParameter
     *
     * @brief this command class is specific to commands with one input parameter and a return parameter.
     * @details
     * This command inherits from the KSCommand. Only this has the actual information about the details of the command.
     * When creating a command of this type, the receiver type, return type, and input parameter type have to be specified.
     * In the constructor the command itself (i.e.  the function of the receiving class, that should be called) has to be given
     * as well as the input parameter for this function.
     */
    template<class XTargetType, class XReturnType, class XFirstParameterType>
    class KSCommandOneParameter:
        public KSCommandPrototype<XTargetType>
    {
        public:
            inline KSCommandOneParameter(XReturnType(XTargetType::* member)(XFirstParameterType), XFirstParameterType firstParameter) :
                fMemberPointer(member), fFirstParameter(firstParameter)
            {
            }
            inline virtual ~KSCommandOneParameter()
            {
            }

            inline virtual void Execute()
            {
                (KSCommandPrototype<XTargetType>::fTarget->*fMemberPointer)(fFirstParameter);
                return;
            }
        
            inline virtual void Print()
            {
                klmsg < "KSCommandOneParameter::Print";
                klmsg(KLMessage::eMessage1) << "First parameter: " << fFirstParameter << eom;
                return;
            }

        protected:
            XReturnType (XTargetType::* fMemberPointer)(XFirstParameterType);
            XFirstParameterType fFirstParameter;
    };

    /*!
     * @brief This is a template specification of KSCommandOneParameter, for the case when the first parameter type is a reference.
     * @details
     * This allows an actual copy of the first argument to be stored in the command, allowing the
     * class that prepared the command to go out of scope with the referent remaining intact.
     */
    template<class XTargetType, class XReturnType, class XFirstParameterType>
    class KSCommandOneParameter<XTargetType, XReturnType, XFirstParameterType&> :
        public KSCommandPrototype<XTargetType>
    {
        public:
            inline KSCommandOneParameter(XReturnType(XTargetType::* member)(XFirstParameterType&), XFirstParameterType& firstParameter) :
                fMemberPointer(member), fFirstParameter(firstParameter)
            {
            }
            inline virtual ~KSCommandOneParameter()
            {
            }

            inline virtual void Execute()
            {
                (KSCommandPrototype<XTargetType>::fTarget->*fMemberPointer)(fFirstParameter);
                return;
            }

            inline virtual void Print()
            {
                klmsg < "KSCommandOneParameter::Print";
                klmsg(KLMessage::eMessage1) << "First parameter: " << fFirstParameter << eom;
                return;
            }
    protected:
            XReturnType (XTargetType::* fMemberPointer)(XFirstParameterType&);
            XFirstParameterType fFirstParameter;
    };

    /*!
     * @brief This is a template specification of KSCommandOneParameter, for the case when the first parameter type is void.
     */
    template<class XTargetType, class XReturnType>
    class KSCommandOneParameter<XTargetType, XReturnType, void> :
        public KSCommandPrototype<XTargetType>
    {
        public:
            KSCommandOneParameter(XReturnType(XTargetType::* member)()) :
                fMemberPointer(member)
            {
            }
            inline virtual ~KSCommandOneParameter()
            {
            }

            inline virtual void Execute()
            {
                (KSCommandPrototype<XTargetType>::fTarget->*fMemberPointer)();
                return;
            }

            inline virtual void Print()
            {
                klmsg < "KSCommandOneParameter::Print";
                klmsg(KLMessage::eMessage1) << "No parameters" << eom;
                return;
            }
    protected:
            XReturnType (XTargetType::* fMemberPointer)();

    };

    /*!
     * @class Kassiopeia::KSCommandTwoParameters
     * @brief This command class is analogous to the KSCommandOneParameter but it takes two input parameters.
     * @details
     * So far, KASSIOPEIA has no commands of this kind.
     */
    template<class XTargetType, class XReturnType, class XFirstParameterType, class XSecondParameterType>
    class KSCommandTwoParameters :
        public KSCommandPrototype<XTargetType>
    {
        public:
            KSCommandTwoParameters(XReturnType(XTargetType::*member)(XFirstParameterType, XSecondParameterType), XFirstParameterType firstParameter, XSecondParameterType secondParameter) :
                fMemberPointer(member), fFirstParameter(firstParameter), fSecondParameter(secondParameter)
            {
            }
            inline virtual ~KSCommandTwoParameters()
            {
            }

            inline virtual void Execute()
            {
                (KSCommandPrototype<XTargetType>::fTarget->*fMemberPointer)(fFirstParameter, fSecondParameter);
                return;
            }

            inline virtual void Print()
            {
                klmsg < "KSCommandTwoParameters::Print";
                klmsg(KLMessage::eMessage1) << "First parameter (addr: " << &fFirstParameter << "): " << fFirstParameter << newline;
                klmsg << "Second parameter (addr: " << &fSecondParameter << "): " << fSecondParameter << eom;
                return;
            }
    protected:
            XReturnType (XTargetType::*fMemberPointer)(XFirstParameterType, XSecondParameterType);
            XFirstParameterType fFirstParameter;
            XSecondParameterType fSecondParameter;
    };

    /*!
     * @class Kassiopeia::KSCommandTwoParameters
     * @brief Template specialization of KSCommandTwoParameters for the case where the first parameter is a reference.
     * @details
     */
    template<class XTargetType, class XReturnType, class XFirstParameterType, class XSecondParameterType>
    class KSCommandTwoParameters<XTargetType, XReturnType, XFirstParameterType&, XSecondParameterType> :
    public KSCommandPrototype<XTargetType>
    {
    public:
        KSCommandTwoParameters(XReturnType(XTargetType::*member)(XFirstParameterType&, XSecondParameterType), XFirstParameterType& firstParameter, XSecondParameterType secondParameter) :
        fMemberPointer(member), fFirstParameter(firstParameter), fSecondParameter(secondParameter)
        {
        }
        inline virtual ~KSCommandTwoParameters()
        {
        }
        
        inline virtual void Execute()
        {
            (KSCommandPrototype<XTargetType>::fTarget->*fMemberPointer)(fFirstParameter, fSecondParameter);
            return;
        }
        
        inline virtual void Print()
        {
            klmsg < "KSCommandTwoParameters::Print";
            klmsg(KLMessage::eMessage1) << "First parameter (addr: " << &fFirstParameter << "): " << fFirstParameter << newline;
            klmsg << "Second parameter (addr: " << &fSecondParameter << "): " << fSecondParameter << eom;
            return;
        }
    protected:
        XReturnType (XTargetType::*fMemberPointer)(XFirstParameterType&, XSecondParameterType);
        XFirstParameterType fFirstParameter;
        XSecondParameterType fSecondParameter;
    };
    
//Here is an example of how a command is created:
//KSCommand* TestTagKSCommand = new KSCommandOneParameter< StepSizeCyclotron, void, Double_t >(&StepSizeCyclotron::SetCyclotronFraction,32);

} // end namespace Kassiopeia

#endif /* KSCOMMAND_H_ */
