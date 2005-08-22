#include "parser.ih"

// copy the union declaration into ostringstream `union_decl' as the
// definition of LSTYPE.

void Parser::setUnionDecl()
{
    if (d_stackDecl.size())
        lineMsg() << "%union or %stype multiply declared" << err;

    d_stackDecl = "struct STYPE\n";

    if (!d_scanner.block(&d_block))
        lineMsg() << "`%union { ... }' expected" << err;
    else
        (d_stackDecl += d_block) += ";\n";

    if (d_scanner.lex() != ';')                     // trailing ; is ok
        d_scanner.unget();                          // but none is ok too.
}