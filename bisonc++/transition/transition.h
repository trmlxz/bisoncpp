#ifndef _INCLUDED_TRANSITION_
#define _INCLUDED_TRANSITION_

#include <vector>
#include <set>

#include "../lookaheadset/lookaheadset.h"
#include "../item/item.h"

class Symbol;

class Transition
{
    LookaheadSet d_la;                  // this key or state's LA set
    size_t/*unsigned*/ d_next;                    // state to go to when the
                                        // transitionmap's key was
                                        // observed 
    bool d_productionsEntered;          // All production rules of a
                                        // symbol were entered

    std::vector<Item> d_kernel;         // next's kernel items
    typedef std::vector<Item>::const_iterator KernelConstIterator;

    std::set<Symbol const *> d_depSym;  // Inspect these Transition 
                                        // entries if this symbol's 
                                        // LAset changes.
    typedef std::set<Symbol const *>::const_iterator InfluenceConstIterator;

    public:
        Transition()
        :
            d_next(UINT_MAX),
            d_productionsEntered(false)
        {}

        KernelConstIterator kernelBegin()
        {
            return d_kernel.begin();
        }
        KernelConstIterator kernelEnd()
        {
            return d_kernel.end();
        }

        std::vector<Item> const &kernel() const
        {
            return d_kernel;
        }
        void rmEOF()
        {
            d_la.rmEOF();
        }
        LookaheadSet const &lookaheadSet() const
        {
            return d_la;
        }
        LookaheadSet &lookaheadSet()
        {
            return d_la;
        }
        void shutOff()
        {
            d_next = UINT_MAX;
        }        
        size_t/*unsigned*/ next() const
        {
            return d_next;
        }
        void setNext(size_t/*unsigned*/ next)
        {
            d_next = next;
        }
        bool hasDestination() const
        {
            return d_next != UINT_MAX;
        }
        bool productionsEntered() const
        {
            return d_productionsEntered;
        }
        bool emptyKernel() const
        {
            return d_kernel.empty();
        }
        
        void enteredProductions()
        {
            d_productionsEntered = true;
        }
        void addShow(Item const &item);
        void influences(Symbol const *symbol)
        {
            d_depSym.insert(symbol);
        }        
        size_t/*unsigned*/ influenceSize() const
        {
            return d_depSym.size();
        }        
        InfluenceConstIterator influenceBegin() const
        {
            return d_depSym.begin();
        }
        InfluenceConstIterator influenceEnd() const
        {
            return d_depSym.end();
        }

            
    private:
};

        
#endif




