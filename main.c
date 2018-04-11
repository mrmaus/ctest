#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


static char *DIR = "/xp/git/ctest/out";


/**
 * Fills in the provided buffer with random characters
 *
 * @param buf char buffer to fill in, expected to be properly pre-allocated by the caller; the buffer should be capable
 *        of taking in the string of the specified size AND the null byte in the end (meaning pre-allocated size should
 *        be at least len+1)
 *
 * @param len number of chars to fill in, starting from buffer position 0
 */
static void random_string(char *buf, size_t len) {
    const char seed[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    const int seed_len = (int) (sizeof(seed) - 1);

    int pos; // one-time instantiation

    for (int i = 0; i < len; i++) {
        pos = (int) (random() % seed_len);
        buf[i] = seed[pos];
    }

    buf[len] = '\0';
}


/**
 * todo::
 *
 * @param
 */
static char *build_token_file_path(char *dir, char *token) {
    char *full_path = malloc(strlen(dir) + 1 + strlen(token) + 1);  // DIR + '/' + FILE + '\0'

    strcpy(full_path, dir);
    strcat(full_path, "/");
    strcat(full_path, token);

    return full_path;
}


/**
 * todo:
 *
 * //todo: handle when file already exists?
 *
 * @param dir
 */
static void write_value_to_token_file(char *dir, char *token, char *value) {
    char *full_path = build_token_file_path(dir, token);

    FILE *f = fopen(full_path, "w");

    fputs(value, f);

    fclose(f);
    free(full_path);
}


/**
 * todo:
 * @param fp
 * @return
 */
long file_size(FILE *fp) {
    long prev = ftell(fp);
    fseek(fp, 0L, SEEK_END);
    long sz = ftell(fp);
    fseek(fp, prev, SEEK_SET); //go back to where we were
    return sz;
}

/**
 * todo:
 * @param dir
 * @param token
 * @return
 */
static char *read_value_from_token_file(char *dir, char *token) {
    char *full_path = build_token_file_path(dir, token);

    FILE *f;

    if ((f = fopen(full_path, "r")) == NULL) {
        return NULL;
    }

    int size = (int) file_size(f) + 1;

    char buf[size];
    fgets(buf, size, f);

    fclose(f);
    free(full_path); //todo: memory leak here!

    buf[size] = '\0';

    return buf; //todo: pass as input parameter!
}

//todo: update file timestamp!

int main() {
    srandom((unsigned) time(NULL)); //todo: should be called once per thread

    printf("Hello, World!\n");

    char token[129];
    random_string(token, 128);

//    write_value_to_token_file(DIR, token, "a646537");
    char *s = read_value_from_token_file(DIR,
                                         "EBW8JSXMrStnaVvr8Btd4IuTnwxQwkiJK3HhLsT39de9WxoUZFYRdgAqDY4X6cuE31LFitwfwAeiVs3KXPsYVQemC88z8s32kDvqWRvgfxm0PfzASPmCtqOWmMli5c8");

    printf("%s", s);

    return 0;
}