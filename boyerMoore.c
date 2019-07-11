#include <stdio.h>
#include <stdlib.h>

int boyerMoore(FILE *f){

    int *ult, file_size, word_size, index;
    char *file, *word;

    //tamanho do alfabeto
    ult = (int *) calloc(10, sizeof(int));
    fscanf(f,"%d %d", &file_size, &word_size);


    file = (char *) malloc(sizeof(char)*file_size);
    word = (char *) malloc(sizeof(char)*word_size);

    fscanf(f,"%s",file);
    fscanf(f,"%s",word);

    int *jump = calloc (word_size, sizeof (int));

    //pré-processamento
    //Bad character
    for (int i = 0; i < word_size; i++){
        index = (int) word[i] - 48;
        ult[index] = i;
    }

    //Good sufix
    int h, k, i, j;
    h = word_size - 1, k = h - 1;
    i = word_size - 1, j = k;
    while (h >= 0) {
        while (i >= h && j >= 0){
            if (word[i] == word[j]){--i; --j;}
            else {i = word_size - 1; j = --k;}
        }
        jump[h--] = k+1;
    }

    //buscando a palavra no texto
    int occ = 0;
    int p = word_size;
    int ci, cj;
    while (p <= file_size) {

        ci = word_size - 1;
        cj = p - 1;
        while (word[ci] == file[cj] && ci >= 0) {
            ci--;
            cj--;
        }

        if (ci < 0){
            occ++;
            printf("%d\n", p - word_size);
        }

        index = (int) file[p] - 48;


        //Qual pulo é maior?
        if (ult[index] <= jump[ci+1])
            p += word_size - ult[index];

        else{
            if (ci == word_size - 1)
                p += 1;
            else
                p += word_size - jump[ci+1];

        }
    }

    return occ;
}

int main(int argc, char const *argv[]) {

    FILE *f;
    char filename[30];


    scanf("%s", &filename[0]);
    f = fopen(filename,"r");
    boyerMoore(f);
    fclose(f);
    // printf("%d\n", occ);

    return 0;
}
