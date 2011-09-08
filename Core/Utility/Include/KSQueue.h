// $Id$

#ifndef KSQUEUE_H
#define KSQUEUE_H
/**
 @file
 @brief contains KSQueue
 @details
 <b>Revision History:</b>
 \verbatim
 Date         Name          Brief description
 -----------------------------------------------
 01/04/2010   N. Oblath     First version
 28/04/2010   N. Oblath     Added queue merging (AddQueue)
 \endverbatim

 */

/*!
 \class Kassiopeia::KSQueue
 @author N. Oblath

 @brief Queue class for any class

 @details
 <b>Detailed Description:</b><br>
 This Queue class provides a standardized method for queueing any type of object.

 The queue is a first-in, first-out (FIFO) container.  It was implemented using a std::queue.

 While in the queue, objects are owned by the queue.
 When GetItem is called ownership is transferred to the user.
 Queues can be merged by calling AddQueue, as long as the type of object queued is the same.
 */

#include <queue>

#include "Rtypes.h"

namespace Kassiopeia
{

    template< class XType >
    class KSQueue
    {

        protected:
            //typedef boost::ptr_deque<T> KSQueueDeque;
            typedef std::queue< XType > KSQueueDeque;

        public:
            //! Default constructor
            KSQueue();
            virtual ~KSQueue();

            //! Check whether there's anything in the queue
            virtual Bool_t HasItems() const;

            //! Returns the number of items waiting in the queue
            virtual UInt_t Size() const;

            //! Deletes all items in the queue
            virtual void ClearQueue();

            //! Add an item to the back of the queue
            //! Item is now owned by the queue
            virtual void AddItem( XType );

            //! Add a queue of items to the back of this queue
            //! All items are now owned by this queue
            virtual void AddQueue( KSQueue< XType >* );

            //! Get an item from the front of the queue
            //! Item is now owned by the user
            virtual XType GetItem();

        protected:

            KSQueueDeque fQueue;

    };

    //*********************
    // Member definitions
    //*********************

    template< class XType >
    KSQueue< XType >::KSQueue() :
        fQueue()
    {
    }
    template< class XType >
    KSQueue< XType >::~KSQueue()
    {
        ClearQueue();
    }

    //**************

    template< class XType >
    Bool_t KSQueue< XType >::HasItems() const
    {
        if( fQueue.empty() )
            return kFALSE;
        else
            return kTRUE;
    }

    template< class XType >
    UInt_t KSQueue< XType >::Size() const
    {
        return (UInt_t) fQueue.size();
    }

    //**************

    template< class XType >
    void KSQueue< XType >::ClearQueue()
    {
        //fQueue.clear();
        while( !fQueue.empty() )
        {
            delete GetItem();
        }
        return;
    }

    template< class XType >
    void KSQueue< XType >::AddItem( XType aItem )
    {
        //fQueue.push_back(aItem);
        fQueue.push( aItem );
    }

    template< class XType >
    void KSQueue< XType >::AddQueue( KSQueue< XType >* aQueue )
    {
        while( aQueue->HasItems() )
        {
            AddItem( aQueue->GetItem() );
        }
    }

    template< class XType >
    XType KSQueue< XType >::GetItem()
    {
        if( HasItems() )
        {
            //typename KSQueueDeque::auto_type tIntermediate = fQueue.release(fQueue.begin());
            //T *theReturn = tIntermediate.release();
            XType theReturn = fQueue.front();
            fQueue.pop();
            return theReturn;
        }
        else
        {
            return NULL;
        }
    }

} // end Kassiopeia namespace

#endif // KSQUEUE_H
