Space Evaders
=============

The brain child and virginity shattering creation of Grizzly Studios

## Lines of Code
The develop branch has 1085 lines of code at 13/10/2013.

On a unix system you can count the lines of code by running:

expr $(find src/main/ -iname '*.h' | xargs cat | sed '/^\s*#/d;/^\s*$/d' | wc -l)\
 + $(find src/main/ -iname '*.hpp' | xargs cat | sed '/^\s*#/d;/^\s*$/d' | wc -l)\
 + $(find src/main/ -iname '*.cpp' | xargs cat | sed '/^\s*#/d;/^\s*$/d' | wc -l)
