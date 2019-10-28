# Spellchecker

Harvard's CS50 assignement: implement a spellchecker using C

## About

This console application is part of an assignement for Harvard's CS50 course on edX.

The dictionary files, texts and implementation of speller.c were provided by Harvard's professors. I take no credit for those files.

**I had to implement only the dictionary.c file.**  
I chose to use a trie for its checking speed: every word being checked needs only n operations (n being the number of letters of the word).
The downside to using a trie is the number of operation needed to load/unload the dictionary into/out of memory.

## Built With

- [C language](<https://en.wikipedia.org/wiki/C_(programming_language)>)
