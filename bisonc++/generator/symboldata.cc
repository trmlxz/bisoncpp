#include "generator.ih"

void Generator::symbolData(ostream &out) const
{
    out <<  
        "    typedef std::map<int, char const *> SMap;\n"
        "    typedef SMap::value_type SMapVal;\n"
        "\n"
        "SMapVal s_symArr[] =\n"
        "{\n"
        "    SMapVal(-2, \"_UNDETERMINED_\"),\n"
        "    SMapVal(-1, \"_EOF_\"),\n"
        "    SMapVal(256, \"_error_\"),\n";


    TContext context = {out};

    for_each(d_rules.terminals().begin(), d_rules.terminals().end(),
            Wrap1c<Terminal, TContext>(&Generator::terminal, context));

    for_each(d_rules.nonTerminals().begin(), d_rules.nonTerminals().end(),
            Wrap1c<NonTerminal, TContext>
                 (&Generator::nonTerminal, context));

    out <<  "};\n"
            "\n"
            "SMap s_symbol\n"
            "(\n"
            "    s_symArr, s_symArr + sizeof(s_symArr) / sizeof(SMapVal)\n"
            ");\n"
            "\n";
}