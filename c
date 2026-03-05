#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;
};

struct paragraph {
    struct sentence* data;
    int sentence_count;
};

struct document {
    struct paragraph* data;
    int paragraph_count;
};

struct document get_document(char* text) {

    struct document doc;
    int pcount = 0;

    char *p = strtok(text, "\n");
    char *paragraphs[10];

    while(p){
        paragraphs[pcount++] = p;
        p = strtok(NULL, "\n");
    }

    doc.paragraph_count = pcount;
    doc.data = malloc(pcount * sizeof(struct paragraph));

    for(int i=0;i<pcount;i++){

        char *sentences[50];
        int scount = 0;

        char *s = strtok(paragraphs[i], ".");
        while(s){
            sentences[scount++] = s;
            s = strtok(NULL, ".");
        }

        doc.data[i].sentence_count = scount;
        doc.data[i].data = malloc(scount * sizeof(struct sentence));

        for(int j=0;j<scount;j++){

            char *words[50];
            int wcount = 0;

            char *w = strtok(sentences[j], " ");
            while(w){
                words[wcount++] = w;
                w = strtok(NULL, " ");
            }

            doc.data[i].data[j].word_count = wcount;
            doc.data[i].data[j].data = malloc(wcount * sizeof(struct word));

            for(int k=0;k<wcount;k++){
                doc.data[i].data[j].data[k].data = malloc(strlen(words[k]) + 1);
                strcpy(doc.data[i].data[j].data[k].data, words[k]);
            }
        }
    }

    return doc;
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
    return Doc.data[n-1].data[m-1].data[k-1];
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) {
    return Doc.data[m-1].data[k-1];
}

struct paragraph kth_paragraph(struct document Doc, int k) {
    return Doc.data[k-1];
}
