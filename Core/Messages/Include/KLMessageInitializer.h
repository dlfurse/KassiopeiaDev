#ifndef KLMessageInitializer_h
#define KLMessageInitializer_h

/**
 @file
 @brief contains KLMessageInitializer

 @details
 KLMessageInitializer is responsible for ensuring that klmsg (global instance of KLMessageInterface) is initialized before
 its first usage.  It does this using the nifty-counter (Schwarz counter) idiom.  See below for an explanation of how it works.

 See KLMessage.h for other classes related to the KLMessage system.

 This file should be included at the top of ALL message system header files (e.g. KSMessage.h) to ensure that
 KLMessage is in place before any other message system.

 <b>Revision History:</b>
 \verbatim
 Date         Name          Brief description
 -----------------------------------------------
 15/03/2011   N. Oblath     First version
 29/04/2011   N. Oblath     KLMessageInitializer moved to separate header file
 \endverbatim

 */

namespace Kassiopeia
{

    /*!
     @class Kassiopeia::KLMessageInitializer
     @author N. Oblath

     @brief Initializer class to guarantee that the KLMessage system is ready before it's first used.

     @details
     This initializer class uses the nifty-counter (Schwarz counter) idiom to ensure that the klmsg instance is fully initialized
     before its first use.  Therefore it can be used even in objects being statically intialized, as it will make sure
     that klmsg is initialized first.

     There is a static instance of the initializer defined here in this header.  Every time its constructor is called (i.e. every
     time KLMessage.h is included somewhere and not excluded by #ifndef blocks) it increments a counter.  The first time it's called
     it initializes all of the static parts of the KLMessage system.  This results in KLMessage being created, which results in
     KLMessageManager being created.  Therefore, by using this system, the entire messaging system is automatically created without
     user intervention.

     When the destructor is called the counter is decremented.  When the counter reaches zero, all of the objects created are
     destroyed.  KLMessage removes itself from KLMessageManager, and if it was the last message system present, then
     the KLMessageManager instance is destroyed, as well.
     */

    class KLMessageInitializer
    {
        public:
            KLMessageInitializer();
            ~KLMessageInitializer();
    };

    static KLMessageInitializer sKLMInitializer;

} // end Kassiopeia namespace

#endif // KLMessageInitializer_h
