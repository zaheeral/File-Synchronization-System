#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int HASH_SIZE = 64;



char *hash(FILE *file){
    char *a_eof;
    char *valu_of_has = malloc(HASH_SIZE);
    char file_in[HASH_SIZE + 1];
    while((a_eof = fgets(file_in, HASH_SIZE, file)) != NULL){
        int hash_index = 0;
        int i = 0;
        for(i=0; i<strlen(file_in); i++){
        valu_of_has[hash_index] ^= file_in[i];
        hash_index++;
        if(hash_index >= HASH_SIZE){
            hash_index = 0;
            }
        }
    }
    return valu_of_has;
}



int check_hash(const char *hash1, const char *hash2, long block_size) {

    // A place holder so that the file will compile without error.
	// Replace with the correct return value.

    int e;

    for (e = 0; e < block_size; e++){
        //check to see if hashs are not empty, else they would be the entirely the same. p[3] == *(p + 3)
        if (hash1[e] != '\0' && hash2[e] != '\0')
        {
            if (hash1[e] != hash2[e])
            {
                printf("%d\n", e);
                return e;
            }
        }
    }
    printf("%ld\n", block_size);
    return block_size;
}


void show_hash(char *hash_val, long block_size) {
    for(int i = 0; i < block_size; i++) {
        printf("%.2hhx ", hash_val[i]);
    }
    printf("\n");
}







/*    //char valu_of_has[MAX_BLOCK_SIZE] = {'\0'};

    char user_input[];
    scanf("%s", user_input);

    int len = strlen( user_input );
    int i;
    for (i = 0; i < len; i++){

        printf("%c\n", user_input[i]);

        // The above is how u read character by character of the user file_in string. 
        // Now want to know if have to read character by character the valu_of_has ... and how to covert that char
        // into byte and Xor that... shud be easy... but need to know these things.
    }


    int i;
    char user_input[];
    while((user_input = getchar()) != EOF){

        scanf ("%c", user_input);

        


    }*/


















//gcc -Wall -std=c99 -o compute_hash compute_hash.c hash_functions.c 

//echo -n "ABC123123ABC" | ./compute_hash 2
