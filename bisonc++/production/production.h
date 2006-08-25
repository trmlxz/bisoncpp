#ifndef _INCLUDED_PRODUCTION_
#define _INCLUDED_PRODUCTION_

#include <vector>
#include <string>
#include <iosfwd>

#include "../block/block.h"
#include "../symbol/symbol.h"
#include "../terminal/terminal.h"

#include <iostream>

class Production: public std::vector<Symbol *>
{
    friend std::ostream &operator<<(std::ostream &out, 
                                               Production const *production);
    static size_t/*unsigned*/ s_nr;

    Terminal const *d_precedence;
    Block           d_action;
    Symbol const *d_nonTerminal;
    size_t/*unsigned*/ d_nr;                              // production order number
                                                // over all productions,
                                                // starts at 1

    public:
        struct IAContext                    // insertActionContext
        {
            std::ostream &out;
            char const *infile;
            bool lineDirectives;
            size_t/*unsigned*/ indent;
        };

        static void insertAction(Production const *prod, IAContext &context);

        static void showElement(std::ostream &out, Symbol const *sp);

        Production(Symbol const *nonTerminal);

        Symbol const *atIdx(size_t/*unsigned*/ idx) const
        {
            return vectorIdx(idx);
        }

        Symbol const *lhs() const
        {
            return d_nonTerminal;
        }

        size_t/*unsigned*/ nr() const
        {
            return d_nr;
        }
        Block const &action() const
        {
            return d_action;
        }
        bool hasAction() const
        {
            return !d_action.empty();
        }

        bool isEmpty() const
        {
            return empty() && d_action.empty();
        }

        Terminal const *precedence() const
        {
            return d_precedence;
        }
        Symbol const &operator[](size_t/*unsigned*/ idx) const
        {
            return *vectorIdx(idx);
        }

        void setAction(Block const &block)
        {
            d_action = block;
        }
        void setPrecedence(Terminal const *terminal);
        
    private:
        Symbol *vectorIdx(size_t/*unsigned*/ idx) const;
};

    // only the rule.
std::ostream &operator<<(std::ostream &out, Production const &production);
    // the rule, preceded by its number.
std::ostream &operator<<(std::ostream &out, Production const *production);

#endif
