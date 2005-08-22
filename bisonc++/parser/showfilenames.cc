#include "parser.ih"

void Parser::showFilenames() const
{
    if (!d_arg.option(0, "show-filenames"))
        return;

    cerr << 
        "\n"
        "SKELETONS AND FILENAMES:\n"
        "  Base class skeleton:\n"
        "\t`" << d_baseclassSkeleton << "'\n"
        "  Class skeleton:\n"
        "\t`" << d_classSkeleton << "'\n"
        "  Implementation header skeleton:\n"
        "\t`" << d_implementationSkeleton << "'\n"
        "  Parser implementation skeleton:\n"
        "\t`" << d_parsefunSkeleton << "'\n"
        "\n"
        "  Base class header:     `" << d_baseclassHeader << "'\n"
        "  Class header:          `" << d_classHeader << "'\n"
        "  Implementation header: `" << d_implementationHeader << "'\n"
        "  Parser Implementation: `" << d_parsefunSource << "'\n"
        "  Grammar description:   `" << verbose() << "'\n" << endl;
}