#include "parser.ih"

Parser::Parser(Rules &rules)
:
    d_arg(Arg::getInstance()),
    d_rules(rules),
    d_scanner(d_arg[0]),
    d_debugFlag(d_arg.option(0, "debug")),
    d_errorVerbose(false),
    d_generateBaseclass(!d_arg.option(0, "dont-rewrite-baseclass-header")),
    d_lines(false),
    d_lspNeeded(false)
{
    d_arg.option(&d_nameSpace, 'n');
    d_arg.option(&d_parsefunSource, 'p');

    predefine(Rules::defaultTerminal());
    predefine(Rules::errorTerminal());
    predefine(Rules::eofTerminal());
//    d_symtab.add("$illegal.");
}






