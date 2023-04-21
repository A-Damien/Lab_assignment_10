#include <stdio.h>
#include <stdlib.h>
#include <string.h> 


struct trie{
    struct trie *next[26];
    int isWord;
};

int search(struct trie* tree, char word[], int k){
    if(k == strlen(word)){
        return tree->isWord;
    }
    int next = word[k] - 'a';
    if(tree->next[next] == NULL){
        return 0;
    }

    return search(tree->next[next], word, k+1);

}
void insert(struct trie **ppTrie, char *word){

    struct trie *temp = *ppTrie;//temp variable
    for(int i = 0; i < strlen(word); i++){
        int ind = word[i] - 'a';
        if(temp->next[ind] == NULL){//if temp next is null, then allocate new memory to insert char
            temp->next[ind] = (struct trie *)calloc(1, sizeof(struct trie));
        }
        temp = temp->next[ind];
    }
    temp->isWord++;
}
int numberOfOccurances(struct trie *pTrie, char *word){
    struct trie *temp = pTrie;//temp variable
    for(int i = 0; i < strlen(word); i++){
        int ind = word[i] - 'a';
        if(temp->next[ind] == NULL){//if the next index is null, then the trie doesn't hold a word
            return 0;
        }
        temp = temp->next[ind];//go to next index
    }
    return temp->isWord;

}
struct trie *deallocateTrie(struct trie *pTrie){
    if(pTrie == NULL){//if trie already empty
        return NULL;
    }

    for(int i = 0; i < 26; i++){//going letter by letter, deallocating each piece of memory
        pTrie->next[i] = deallocateTrie(pTrie->next[i]);
    }

    free(pTrie);
    return NULL;
}




int main(void)
{
    // read the number of the words in the dictionary
    //  parse line  by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

    struct trie *trie = (struct trie*) calloc(1, sizeof(struct trie));//creating trie

    for(int i = 0; i < 5; i++)//filling up trie with words from 2d array
        insert(&trie, pWords[i]);

    for(int i = 0; i < 5; i++)//printing words and num occurrances
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);//deallocate trie
    if (trie != NULL)
        printf("There is an error in this program\n");
    return 0;
}
