#ifndef \@$Base_h_included
#define \@$Base_h_included

#include <iostream>
#include <exception>
#include <vector>
#include <stack>
#include <tuple>
$insert polyincludes
$insert preincludes
$insert debugincludes

namespace // anonymous
{
    struct PI__;
    struct SR__;
}

$insert namespace-open

$insert polymorphic

class \@Base
{
    public:
        enum DebugMode__
        {
            OFF           = 0,
            ON            = 1 << 0,
            ACTIONCASES   = 1 << 1
        };

$insert tokens
$insert LTYPE
$insert STYPE

    private:
                        // state   msgidx  orgidx  semval
        typedef std::tuple<size_t, size_t, size_t, STYPE__> StateTuple;
        typedef std::pair<int, std::string> TokenPair;

        int d_stackIdx;
        std::vector<StateTuple> d_stateStack;
        StateTuple *d_vsp;              // points to the topmost value stack
                                        // element

        std::stack<TokenPair> d_tokenStack;
        std::string d_matched;
        TokenPair   d_tp;

        size_t      d_state;

$insert LTYPEstack

    protected:
        enum Return__
        {
            PARSE_ACCEPT__ = 0,   // values used as parse()'s return values
            PARSE_ABORT__  = 1
        };
        enum ErrorRecovery__
        {
            UNEXPECTED_TOKEN__,
        };

        size_t const *d_s_nErrors__;            // saves Meta__::s_nErrors__
        bool        d_actionCases__ = false;
        bool        d_debug__ = true;
        size_t      d_nErrors__;
        size_t      d_requiredTokens__;
        size_t      d_acceptedTokens__;
        STYPE__     d_val__;
$insert LTYPEdata

    public:
        void setDebug(bool mode);
        void setDebug(DebugMode__ mode);

    protected:
        \@Base();

$insert debugdecl
        void ABORT() const;
        void ACCEPT() const;
        void ERROR() const;
        bool debug() const;

        bool pendingTokens__();
        int token__() const;

        STYPE__ &vs__(size_t idx);      // value stack element idx 
                                        // counting back fm the current 
                                        // element in the production rule
        std::string const &matched__() const;

        void lex__(int token, std::string const &matchedText);
        void nextMatched__();



        SR__ const *findToken__() const;
        size_t msgIdx__() const;
        void done__();
        void errorVerbose__();
        void msgIdx__(size_t idx);
        void pop__(size_t count = 1);
        void print__();
        void pushToken__(bool error = false);
        void push__(size_t nextState);
        void reduce__(PI__ const &pi);
        void reset__();
        size_t stackSize__() const;

        template<int>                   // elements fm the stateStack:
        auto top__(size_t shift = 0) const;

        template<int>   
        auto &top__();

    private:
        void checkStackSize();

        StateTuple &top();
}; 

template<int idx>
inline auto ParserBase::top__(size_t shift) const
{
    return std::get<idx>(d_stateStack[ d_stackIdx - shift ]);
}

template<int idx>
inline auto &ParserBase::top__()
{
    return std::get<idx>(d_stateStack[ d_stackIdx ]);
}

inline int \@Base::token__() const
{
    return d_tp.first;
}

inline std::string const &\@Base::matched__() const
{
    return d_matched;
}

inline size_t \@Base::stackSize__() const
{
    return d_stackIdx + 1;
}

inline \@Base::STYPE__ &\@Base::vs__(size_t idx) 
{
    return std::get<3>(*(d_vsp - idx));
}

inline ParserBase::StateTuple &ParserBase::top()
{
    return d_stateStack[d_stackIdx];
}

inline \@Base::DebugMode__ operator|(\@Base::DebugMode__ lhs, 
                                     \@Base::DebugMode__ rhs)
{
    return static_cast<\@Base::DebugMode__>(static_cast<int>(lhs) | rhs);
};

inline size_t \@Base::msgIdx__() const
{
    return top__<1>();
}

inline void \@Base::msgIdx__(size_t idx)
{
    top__<1>() = idx;
}

inline bool \@Base::debug() const
{
    return d_debug__;
}

inline void \@Base::ABORT() const
{
$insert 4 debug "ABORT(): Parsing unsuccessful"
    throw PARSE_ABORT__;
}

inline void \@Base::ACCEPT() const
{
$insert 4 debug "ACCEPT(): Parsing successful"
    throw PARSE_ACCEPT__;
}

inline void \@Base::ERROR() const
{
$insert 4 debug "ERROR(): Forced error condition"
    throw UNEXPECTED_TOKEN__;
}

inline \@Base::DebugMode__ operator&(\@Base::DebugMode__ lhs,
                                     \@Base::DebugMode__ rhs)
{
    return static_cast<\@Base::DebugMode__>(
            static_cast<int>(lhs) & rhs);
}

// For convenience, when including ParserBase.h its symbols are available as
// symbols in the class Parser, too.
#define \@ \@Base

$insert namespace-close

#endif
