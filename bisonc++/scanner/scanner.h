#ifndef _INCLUDED_SCANNER_
#define _INCLUDED_SCANNER_

#include <string>
#include <fstream>
#include <utility>
#include <vector>

#if ! defined(_SKIP_YYFLEXLEXER_) && ! defined(_SYSINC_FLEXLEXER_H_)
#include <FlexLexer.h>
#define _SYSINC_FLEXLEXER_H_
#endif

#include "../block/block.h"

class Scanner: public yyFlexLexer
{
    public:
        // When modifying this enum, also adapt nameOf[] in lex.cc
        enum Token
        {
            UNAVAILABLE             = 256,      // for d_lastToken  22
            BASECLASS_HEADER,
            BASECLASS_PREINCLUDE,
            CLASS_HEADER,
            CLASS_NAME,
            DEBUGFLAG,
            ENDFILE,
            ERROR_VERBOSE,
            EXPECT,
            FILENAMES,
            IDENTIFIER,
            ILLEGAL,
            IMPLEMENTATION_HEADER,
            LEFT,
            LINES,
            LOCATIONSTRUCT,
            LSP_NEEDED,
            LTYPE,
            NAMESPACE,
            NONASSOC,
            NUMBER,
            PARSEFUN_SOURCE,
            PREC,
            QUOTE,
            RIGHT,
            RULE,
            SCANNER_INCLUDE,
            START,
            STRING,
            STYPE,
            TOKEN,
            TWO_PERCENTS,
            TYPE,
            TYPENAME,
            UNION,
            WS,
        };

    private:
        std::ifstream       d_in;
        unsigned            d_retWS;
        unsigned            d_number;   // only valid after tokens NUMBER and
                                        // after escape(), octal() and 
                                        // hexadecimal() 
        std::string         d_ungotText;
        unsigned            d_ungotToken;    
        unsigned            d_ungotNumber;
        std::string         d_text;
        unsigned            d_token;
        int                 d_commentChar;  // set to ' ' in `lexer' when C
                                            // comment without \n is matched,
                                            // otherwise set to \n. See
                                            // `lexer' for details

        std::string         d_canonicalQuote;   // canonical quoted ident.

    public:
        Scanner(std::string const &fname);

        void cutColon();
    
        std::string const &text() const     // same as YYText(), but now 
        {                                   // a std::string
            return d_text;
        }
        std::string const &trimmedText();   // same as text(), but surrounding
                                            // ws removed.

        std::string const &canonicalQuote();
        int token() const                   // return the current token    
        {
            return d_token;
        }
        unsigned number() const             // only after token NUMBER
        {
            return d_number;
        }

        int lex();
        bool block(Block *block);           // returns true if a block was
                                            // read

        char const *nextString();           // series non-blank/comment chars
        void ignoreUntilEndl();
        void unexpectedEOF();
        void unget();
        int miniBrace(std::string *dest);   // returns '{' or '}'
    private:
        int yylex();                        // generated by flex, used by 
                                            // lex().

        void multiLineString();
        void octal();
        void hexadecimal();
        void escape();

        int setNumber();
        


        bool identChar(int c) const;
        Token identifier(int c);
        Token quotedText();
        Token parsePercentToken();

        int nextChar();                     // eat blanks and comment
        void skipComment();
        void skip_C_comment();
        int stringChar();                   // next non-ws/comment/etc char
};

#endif


