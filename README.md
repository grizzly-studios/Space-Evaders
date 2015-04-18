Space Evaders  [![Build Status](https://travis-ci.org/grizzly-studios/Space-Evaders.svg?branch=develop)](https://travis-ci.org/grizzly-studios/Space-Evaders)
=============

The brain child and virginity shattering creation of Grizzly Studios

## Lines of Code
| # of Lines | Date       |
| ---------- | ---------- |
| 1085       | 13/10/2013 |
| 2483       | 09/10/2014 |
| 2850       | 13/10/2014 |
| 3008       | 02/04/2015 |
| 4281       | 15/04/2015 |

On a unix system you can count the lines of code by running:

```bash
expr $(find src/main/ -iname '*.h' | xargs cat | sed '/^\s*#/d;/^\s*$/d' | wc -l)\
 + $(find src/main/ -iname '*.hpp' | xargs cat | sed '/^\s*#/d;/^\s*$/d' | wc -l)\
 + $(find src/main/ -iname '*.cpp' | xargs cat | sed '/^\s*#/d;/^\s*$/d' | wc -l)
