
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "WordTable.h"

// Initializes a word table
void wtable_init(WordTable *wtable)
{
	// Allocate and initialize space for the table
	wtable->nWords = 0;
	wtable->maxWords = 10;
	wtable->wordArray = (WordInfo *)malloc(wtable->maxWords * sizeof(WordInfo));
	for (int i = 0; i < wtable->maxWords; i++)
	{
		llist_init(&wtable->wordArray[i].positions);
	}
}

// Add word to the tableand position. Position is added to the corresponding linked list.
void wtable_add(WordTable *wtable, char *word, int position)
{
	// Find first word if it exists
	for (int i = 0; i < wtable->nWords; i++)
	{
		if (strcmp(wtable->wordArray[i].word, word) == 0)
		{
			// Found word. Add position in the list of positions
			llist_insert_last(&wtable->wordArray[i].positions, position);
			return;
		}
	}

	// Word not found.
	// Make sure that the array has space.
	// Expand the wordArray here.
	if (wtable->nWords == wtable->maxWords)
	{
		wtable->wordArray = realloc(wtable->wordArray, wtable->maxWords * sizeof(WordInfo) * 2);
		wtable->maxWords = wtable->maxWords * 2;
	}
	llist_init(&wtable->wordArray[wtable->nWords].positions);
	wtable->wordArray[wtable->nWords].word = strdup(word);
	llist_insert_last(&wtable->wordArray[wtable->nWords].positions, position);
	wtable->nWords = wtable->nWords + 1;
}

// Print contents of the table.
void wtable_print(WordTable *wtable, FILE *fd)
{

	fprintf(fd, "------- WORD TABLE -------\n");

	// Print words
	for (int i = 0; i < wtable->nWords; i++)
	{
		fprintf(fd, "%d: %s: ", i, wtable->wordArray[i].word);
		llist_print(&wtable->wordArray[i].positions);
	}
}

// Get positions where the word occurs
LinkedList *wtable_getPositions(WordTable *wtable, char *word)
{
	for (int i = 0; i < wtable->nWords; i++)
	{
		if (wtable->wordArray[i].word == word)
		{
			return &((wtable->wordArray[i]).positions);
		}
	}
	return NULL;
}

//
// Separates the string into words
//

#define MAXWORD 200
char word[MAXWORD];
int wordLength;
int wordCount;
int charCount;
int wordPos = 0;
int charPos = 0;
int isEOF = 0;
int wordStart = 1;

// It returns the next word from stdin.
// If there are no more more words it returns NULL.
// A word is a sequence of alphabetical characters.

static char *nextword(FILE *file)
{
	char *code;
	size_t n = 0;
	int c;

	if (file == NULL)
		return NULL;

	code = malloc(MAXWORD);
	// while ((c = fgetc(file)) != ' ' && c != EOF && c != '-' && c != '–' && c != '\'' && c != '\n' && c != '\t') {
	// charPos++;

	// code[n++] = (char) c;
	//}
	while ((c = fgetc(file)) != ' ')
	{
		if ((c < 65 || c > 90) && (c < 97 || c > 122))
		{
			break;
		}
		charPos++;
		code[n++] = (char)c;
	}

	charPos++;
	if (c == EOF)
	{
		return NULL;
	}
	code[n] = '\0';
	return code;
}

// Conver string to lower case
void toLower(char *s)
{
	while (*s != '\0')
	{
		if (*s >= 65 && *s <= 90)
		{
			*s = *s + 32;
		}
		s++;
	}
}

char *cleanWord(char *s)
{
	char *clean = malloc(200 * sizeof(char));
	char *destination = clean;
	int index = 0;
	while (*s != '\0')
	{
		if (*s >= 65 && *s <= 90 || *s <= 122 && *s >= 97)
		{
			*clean = *s;
			clean++;
		}
		s++;
	}
	*clean = '\0';
	return destination;
}

// Read a file and obtain words and positions of the words and save them in table.

wtable_createFromFile(WordTable *wtable, char *fileName, int verbose)
{
	FILE *fd = fopen(fileName, "r");
	if (fd == NULL)
	{
		return;
	}
	int wordPos = 0;
	int wordNum = 0;
	char *word;

	word = nextword(fd);
	while (word != NULL)
	{
		toLower(word);
		char *word1 = cleanWord(word);
		if (strlen(word1) == 0)
		{
			word = nextword(fd);
			continue;
		}
		if (verbose)
		{
			printf("%d: word=%s, pos=%d\n", wordNum++, word1, charPos - strlen(word) - 1);
		}
		wtable_add(wtable, word, charPos - strlen(word) - 1);

		word = nextword(fd);
	}
	fclose(fd);
}
int firstIsBigger(char *word1, char *word2)
{
	while (*word1 != '\0' || *word2 != '\0')
	{
		if (*word1 > *word2)
		{
			return 1;
		}
		else if (*word1 < *word2)
		{
			return 0;
		}
		word1++;
		word2++;
	}
	if (*word2 == '\0')
	{
		return 1;
	}
	if (*word1 == '\0')
	{
		return 0;
	}
}

// Sort table in alphabetical order.
void wtable_sort(WordTable *wtable)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < wtable->nWords; i++)
	{
		for (j = 0; j < wtable->nWords - 1; j++)
		{
			if (firstIsBigger(wtable->wordArray[j].word, wtable->wordArray[j + 1].word))
			{
				WordInfo info_1;
				info_1 = wtable->wordArray[j];
				wtable->wordArray[j] = wtable->wordArray[j + 1];
				wtable->wordArray[j + 1] = info_1;
			}
		}
	}
}

// Print all segments of text in fileName that contain word.
// at most 200 character. Use fseek to position file pointer.
// Type "man fseek" for more info.
int wtable_textSegments(WordTable *wtable, char *word, char *fileName)
{
	FILE *fd;
	fd = fopen(fileName, "r");
	LinkedList *list = NULL;
	ListNode *n;
	for (int i = 0; i < wtable->nWords; i++)
	{
		if (strcmp(wtable->wordArray[i].word, word) == 0)
		{
			list = &wtable->wordArray[i].positions;
			break;
		}
	}
	if (list == NULL) {
		return -1;
	}
	n = list->head;
	printf("===== Segments for word \"%s\" in book \"%s\" =====\n", word, fileName);
	while (n != NULL)
	{
		printf("---------- pos=%d-----\n", n->value);
		printf("......");
		fseek(fd, n->value, SEEK_SET);
		for (int k = 0; k < 200; k++)
		{
			char c = fgetc(fd);
			if (c == "EOF")
			{
				break;
			}
			printf("%c", c);
		}
		printf("......\n");
		n = n->next;
	}
}
