#ifndef MIMEMAPPER_H
#define MIMEMAPPER_H

#include <QMap>

// Maps common mime types to the KTextEditor highlight mode.
const QMap<QString, QString> mimeMap = {
    { "", "Normal" },
    { "text/plain", "Normal" },
    { "text/css", "CSS" },
    { "text/html", "HTML" },
    { "application/json", "JSON" },
    { "text/markdown", "Markdown" },
    { "text/xml", "XML" },
    { "application/xml", "XML" },
    { "text/yaml", "YAML" },
    { "application/x-yaml", "YAML" },
    { "application/javascript", "JavaScript" },
    //    {"", "G-Code"},
    //    {"", "GLSL"},
    //    {"", "OpenSCAD"},
    //    {"", "PLY"},
    //    {"", "POV-Ray"},
    //    {"", "RenderMan RIB"},
    //    {"", "STL"},
    //    {"", "VRML"},
    //    {"", "Wavefront OBJ"},
    //    {"", "Asm6502"},
    //    {"", "AVR Assembler"},
    //    {"", "Common Intermediate Language (CIL)"},
    //    {"", "GNU Assembler"},
    //    {"", "Intel x86 (FASM)"},
    //    {"", "Intel x86 (NASM)"},
    //    {"", "MIPS Assembler"},
    //    {"", "Motorola 68k (VASM/Devpac)"},
    //    {"", "Motorola DSP56k"},
    //    {"", "PicAsm"},
    //    {"", ".desktop"},
    //    {"", "Adblock Plus"},
    //    {"", "Apache Configuration"},
    //    {"", "Cisco"},
    //    {"", "Doxyfile"},
    //    {"", "fstab"},
    //    {"", "Git Ignore"},
    //    {"", "Gitolite"},
    //    {"", "INI Files"},
    //    {"", "Kconfig"},
    //    {"", "kdesrc-buildrc"},
    //    {"", "mergetag text"},
    //    {"", "Nagios"},
    //    {"", "QDoc Configuration"},
    //    {"", "systemd unit"},
    //    {"", "TOML"},
    //    {"", "Varnish Configuration Language"},
    //    {"", "Varnish Test Case language"},
    //    {"", "WINE Config"},
    //    {"", "x.org Configuration"},
    //    {"", "4GL"},
    //    {"", "4GL-PER"},
    //    {"", "LDIF"},
    //    {"", "progress"},
    //    {"", "SQL"},
    //    {"", "SQL (MySQL)"},
    //    {"", "SQL (Oracle)"},
    //    {"", "SQL (PostgreSQL)"},
    //    {"", "AHDL"},
    //    {"", "Spice"},
    //    {"", "SystemC"},
    //    {"", "SystemVerilog"},
    //    {"", "Vera"},
    //    {"", "Verilog"},
    //    {"", "VHDL"},
    //    {"", "AppArmor Security Profile"},
    //    {"", "AsciiDoc"},
    //    {"", "ASN.1"},
    //    {"", "ASP"},
    //    {"", "BibTeX"},
    //    {"", "CartoCSS"},
    //    {"", "CleanCSS"},
    //    {"", "ColdFusion"},
    //    {"", "ConTeXt"},
    //    {"", "Cucumber Gherkin feature"},
    //    {"", "Django HTML Template"},
    //    {"", "Doxygen"},
    //    {"", "DoxygenLua"},
    //    {"", "DTD"},
    //    {"", "Fluent"},
    //    {"", "FTL"},
    //    {"", "GlossTex"},
    //    {"", "GNU Gettext"},
    //    {"", "Haml"},
    //    {"", "Hamlet"},
    //    {"", "Javadoc"},
    //    {"", "Jira"},
    //    {"", "JSP"},
    //    {"", "LaTeX"},
    //    {"", "LESSCSS"},
    //    {"", "MAB-DB"},
    //    {"", "Mako"},
    //    {"", "MediaWiki"},
    //    {"", "Metapost/Metafont"},
    //    {"", "Mustache/Handlebars (HTML)"},
    //    {"", "Pango"},
    //    {"", "PostScript"},
    //    {"", "PostScript Printer Description"},
    //    {"", "Pug"},
    //    {"", "R documentation"},
    //    {"", "R Markdown"},
    //    {"", "RELAX NG"},
    //    {"", "RelaxNG-Compact"},
    //    {"", "reStructuredText"},
    //    {"", "Rich Text Format"},
    //    {"", "Roff"},
    //    {"", "Ruby/Rails/RHTML"},
    //    {"", "SASS"},
    //    {"", "SCSS"},
    //    {"", "SGML"},
    //    {"", "SiSU"},
    //    {"", "Texinfo"},
    //    {"", "Textile"},
    //    {"", "Troff Mandoc"},
    //    {"", "TT2"},
    //    {"", "txt2tags"},
    //    {"", "vCard, vCalendar, iCalendar"},
    //    {"", "Wesnoth Markup Language"},
    //    {"", "XML (Debug)"},
    //    {"", "xslt"},
    //    {"", "XUL"},
    //    {"", "YANG"},
    //    {"", "ABC"},
    //    {"", "Alerts"},
    //    {"", "ChangeLog"},
    //    {"", "CMake"},
    //    {"", "Comments"},
    //    {"", "CSS/PHP"},
    //    {"", "CUE Sheet"},
    //    {"", "Debian Changelog"},
    //    {"", "Debian Control"},
    //    {"", "Diff"},
    //    {"", "Dockerfile"},
    //    {"", "Email"},
    //    {"", "GDB"},
    //    {"", "GDB Backtrace"},
    //    {"", "GDB Init"},
    //    {"", "Git Rebase"},
    //    {"", "GraphQL"},
    //    {"", "Hunspell Affix File"},
    //    {"", "Hunspell Dictionary File"},
    //    {"", "Hunspell Thesaurus File"},
    //    {"", "Hunspell Thesaurus Index File"},
    //    {"", "InnoSetup"},
    //    {"", "Intel HEX"},
    //    {"", "Jam"},
    //    {"", "Java Properties"},
    //    {"", "JavaScript React (JSX)/PHP"},
    //    {"", "JavaScript/PHP"},
    //    {"", "LilyPond"},
    //    {"", "Logcat"},
    //    {"", "M3U"},
    //    {"", "Makefile"},
    //    {"", "Meson"},
    //    {"", "MIB"},
    //    {"", "Modelines"},
    //    {"", "Music Publisher"},
    //    {"", "Mustache/Handlebars (HTML)/PHP"},
    //    {"", "Ninja"},
    //    {"", "Overpass QL"},
    //    {"", "PGN"},
    //    {"", "QMake"},
    //    {"", "RPM Spec"},
    //    {"", "SELinux File Contexts"},
    //    {"", "Snort/Suricata"},
    //    {"", "SPDX-Comments"},
    //    {"", "SubRip Subtitles"},
    //    {"", "Tiger"},
    //    {"", "Todo.txt"},
    //    {"", "TypeScript/PHP"},
    //    {"", "Valgrind Suppression"},
    //    {"", "Wayland Trace"},
    //    {"", "YARA"},
    //    {"", "Ansys"},
    //    {"", "B-Method"},
    //    {"", "dot"},
    //    {"", "FASTQ"},
    //    {"", "GAP"},
    //    {"", "GDL"},
    //    {"", "Gnuplot"},
    //    {"", "Magma"},
    //    {"", "Mathematica"},
    //    {"", "Matlab"},
    //    {"", "Maxima"},
    //    {"", "Metamath"},
    //    {"", "Octave"},
    //    {"", "R Script"},
    //    {"", "Replicode"},
    //    {"", "scilab"},
    //    {"", "Stan"},
    //    {"", "Stata"},
    //    {"", "TI Basic"},
    //    {"", "yacas"},
    //    {"", "4DOS BatchToMemory"},
    //    {"", "AMPLE"},
    //    {"", "AutoHotKey"},
    //    {"", "AWK"},
    //    {"", "Bash"},
    //    {"", "BrightScript"},
    //    {"", "CLIST"},
    //    {"", "CoffeeScript"},
    //    {"", "CubeScript"},
    //    {"", "Erlang"},
    //    {"", "Euphoria"},
    //    {"", "ferite"},
    //    {"", "Fish"},
    //    {"", "GNU Linker Script"},
    //    {"", "Godot"},
    //    {"", "J"},
    //    {"", "JavaScript React (JSX)"},
    //    {"", "JCL"},
    //    {"", "k"},
    //    {"", "LSL"},
    //    {"", "Lua"},
    //    {"", "Mason"},
    //    {"", "MEL"},
    //    {"", "MS-DOS Batch"},
    //    {"", "NSIS"},
    //    {"", "Perl"},
    //    {"", "PHP (HTML)"},
    //    {"", "PHP/PHP"},
    //    {"", "Pig"},
    //    {"", "Pike"},
    //    {"", "PowerShell"},
    //    {"", "Praat"},
    //    {"", "Puppet"},
    //    {"", "Python"},
    //    {"", "q"},
    //    {"", "QML"},
    //    {"", "Quake Script"},
    //    {"", "Raku"},
    //    {"", "REXX"},
    //    {"", "Ruby"},
    //    {"", "Scheme"},
    //    {"", "sed"},
    //    {"", "Sieve"},
    //    {"", "TaskJuggler"},
    //    {"", "Tcl/Tk"},
    //    {"", "Tcsh"},
    //    {"", "TypeScript"},
    //    {"", "TypeScript React (TSX)"},
    //    {"", "UnrealScript"},
    //    {"", "Velocity"},
    //    {"", "Xonotic Script"},
    //    {"", "Zsh"},
    //    {"", "ABAP"},
    //    {"", "ActionScript 2.0"},
    //    {"", "Ada"},
    //    {"", "Agda"},
    //    {"", "ANS-Forth94"},
    //    {"", "ANSI C89"},
    //    {"", "ATS"},
    //    {"", "Bitbake"},
    //    {"", "Boo"},
    //    {"", "C"},
    //    {"", "C#"},
    //    {"", "C++"},
    //    {"", "Cg"},
    //    {"", "CGiS"},
    //    {"", "Clipper"},
    //    {"", "Clojure"},
    //    {"", "Common Lisp"},
    //    {"", "Component-Pascal"},
    //    {"", "Crack"},
    //    {"", "Curry"},
    //    {"", "D"},
    //    {"", "E Language"},
    //    {"", "Eiffel"},
    //    {"", "Elixir"},
    //    {"", "Elm"},
    //    {"", "FlatBuffers"},
    //    {"", "Fortran (Fixed Format)"},
    //    {"", "Fortran (Free Format)"},
    //    {"", "FreeBASIC"},
    //    {"", "FSharp"},
    //    {"", "GCCExtensions"},
    //    {"", "GNU M4"},
    //    {"", "Go"},
    //    {"", "Groovy"},
    //    {"", "Haskell"},
    //    {"", "Haxe"},
    //    {"", "IDL"},
    //    {"", "Idris"},
    //    {"", "ILERPG"},
    //    {"", "Inform"},
    //    {"", "ISO C++"},
    //    {"", "Java"},
    //    {"", "Julia"},
    //    {"", "KBasic"},
    //    {"", "KDev-PG[-Qt] Grammar"},
    //    {"", "Kotlin"},
    //    {"", "Lex/Flex"},
    //    {"", "Literate Curry"},
    //    {"", "Literate Haskell"},
    //    {"", "LLVM"},
    //    {"", "Logtalk"},
    //    {"", "LPC"},
    //    {"", "Modelica"},
    //    {"", "Modula-2"},
    //    {"", "Modula-2 (ISO only)"},
    //    {"", "Modula-2 (PIM only)"},
    //    {"", "Modula-2 (R10 only)"},
    //    {"", "Modula-3"},
    //    {"", "MonoBasic"},
    //    {"", "Nemerle"},
    //    {"", "nesC"},
    //    {"", "Nim"},
    //    {"", "noweb"},
    //    {"", "Objective Caml"},
    //    {"", "Objective Caml Ocamllex"},
    //    {"", "Objective Caml Ocamlyacc"},
    //    {"", "Objective-C"},
    //    {"", "Objective-C++"},
    //    {"", "OORS"},
    //    {"", "OPAL"},
    //    {"", "OpenCL"},
    //    {"", "Pascal"},
    //    {"", "PL/I"},
    //    {"", "Pony"},
    //    {"", "Prolog"},
    //    {"", "Protobuf"},
    //    {"", "Pure"},
    //    {"", "PureBasic"},
    //    {"", "PureScript"},
    //    {"", "RapidQ"},
    //    {"", "RenPy"},
    //    {"", "RSI IDL"},
    //    {"", "Rust"},
    //    {"", "Sather"},
    //    {"", "Scala"},
    //    {"", "SELinux CIL Policy"},
    //    {"", "SELinux Policy"},
    //    {"", "Smali"},
    //    {"", "SML"},
    //    {"", "Solidity"},
    //    {"", "TADS 3"},
    //    {"", "Vala"},
    //    {"", "Varnish module spec file"},
    //    {"", "xHarbour"},
    //    {"", "Yacc/Bison"},
    //    {"", "Zonnon"},
};

class MimeMapper {
public:
    static QString mapMime(QString mimeType)
    {
        return mimeMap.value(mimeType, "Normal");
    }
};

#endif // MIMEMAPPER_H
