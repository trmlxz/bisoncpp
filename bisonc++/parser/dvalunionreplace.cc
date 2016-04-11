#include "parser.ih"

bool Parser::dvalUnionReplace(bool midRule, Block &block, AtDollar const &atd, 
                                                        char const *suffix)
{
    string tag = warnAutoTag(midRule, atd, "field"); // get the element's tag

    if (string("->") == suffix and tag.empty())
        errNoUnionPtr(atd);
    else        
        block.replace(atd.pos(), atd.length(), 
                s_semanticValue + (tag.empty() ? ""s : "." + tag) + suffix);

    return block.assignment();
}
