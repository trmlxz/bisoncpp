/*
                              bisonc++.cc
*/

#include "bisonc++.h"

using namespace std;
using namespace FBB;

namespace 
{
    Arg::LongOption longOptions[] = 
    {
        Arg::LongOption("baseclass-preinclude", 'H'),
        Arg::LongOption("baseclass-skeleton", 'B'),
        Arg::LongOption("class-skeleton", 'C'),
        Arg::LongOption("implementation-skeleton", 'I'),
        Arg::LongOption("parsefun-skeleton", 'P'),

        Arg::LongOption("baseclass-header", 'b'),
        Arg::LongOption("class-header", 'c'),
        Arg::LongOption("implementation-header", 'i'),
        Arg::LongOption("parsefun-source", 'p'),

        Arg::LongOption("filenames", 'f'),

        Arg::LongOption("construction"),
        Arg::LongOption("debug"),

        Arg::LongOption("force-implementation-header"),
        Arg::LongOption("force-class-header"),

        Arg::LongOption("help", 'h'),

        Arg::LongOption("namespace", 'n'),

        Arg::LongOption("no-baseclass-header"),
        Arg::LongOption("no-parse-member"),

        Arg::LongOption("lines", 'l'),
        Arg::LongOption("no-lines"),
        Arg::LongOption("scanner", 's'),
        Arg::LongOption("show-filenames"),
        Arg::LongOption("version", 'v'),
        Arg::LongOption("verbose", 'V'),
    };

    Arg::LongOption const *const longEnd = longOptions + 
                                sizeof(longOptions) / sizeof(Arg::LongOption); 
}

int main(int argc, char **argv)
try
{
    Arg &arg = Arg::initialize("B:b:C:c:f:H:hI:i:ln:p:P:s:Vv", 
                    longOptions, longEnd, argc, argv);

    arg.versionHelp(usage, version, 1);

    if (arg.option(0, "construction"))
        Msg::setDisplay(true);

    Rules rules;

    Parser parser(rules);   // parses the input, fills the data in the Rules

    parser.parse();         // read the grammar file, build required data
                            // structures. 

    parser.showFilenames();

    rules.showTerminals();

    rules.determineFirst();
    rules.showFirst();

    rules.determineFollow();
    rules.showFollow();

    ItemSets itemSets;
    itemSets.define(rules.startProduction());

    rules.assignNonTerminalNumbers();

    rules.setVerbose(parser.verboseSource());

    State::showConflicts();

    itemSets.showConflicts();

    rules.showUnusedTerminals();
    rules.showUnusedNonTerminals();

    rules.showRules();

    Generator generator(rules, parser, itemSets);

    generator.baseclassHeader();
    generator.classHeader();
    generator.implementationHeader();

    generator.parseFunction();

    itemSets.showParsingTables();   // Note that the generator may change a
                                    // state, which will then affect the shown
                                    // parsing tables. This is done in
                                    // Generator::srtables, calling
                                    // State::writeStateArray(). This latter
                                    // function may set a State's
                                    // d_defaultReduction field. Consider
                                    // removing this modification from
                                    // writeStateArray(), moving it to a
                                    // separate State member, so that
                                    // Generator merely produces the generated
                                    // parser.

    itemSets.deriveSentence();

    return 0;
}
catch(Errno const &err)
{
    cerr << err.what() << endl;
    return err.which();
}
catch(int x)
{
    return x;
}