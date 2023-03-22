#include "../libraries/bstree.h"
#include "../libraries/hashtab.h"

#define MAX_KEYS 200000
#define MAX_KEY_LENGTH 20


int main()
{
    char key[MAX_KEY_LENGTH];
    FILE *f = fopen("Keys.txt", "r");

    for(int i = 0; i < MAX_KEYS && !feof(f); i++){
        fgets(key, MAX_KEY_LENGTH, f);
        key[strcspn(key, "\n")] = '\0';
        //printf("%s\n", key);
    } 

    fclose(f);

    printf("<==BSTREE==>\n");

    struct bstree *tree, *node1;
    tree = bstree_create("Koala", 12);
    bstree_add(tree, "Flamingo", 1);
    bstree_add(tree, "Fox", 14);
    node1 = bstree_lookup(tree, "Fox");
    printf("Found value for key %s: %d\n", node1->key, node1->value);
    node1 = bstree_min(tree);
    printf("Minimal key: %s, value: %d\n", node1->key, node1->value);

    printf("<==HASHTAB==>\n");

    struct listnode *node2;
    hashtab_init(hashtab);
    hashtab_add(hashtab, "Ocelot", 17);
    hashtab_add(hashtab, "Flamingo", 4);
    hashtab_add(hashtab, "Fox", 14);
    node2 = hashtab_lookup(hashtab, "Flamingo");
    if (node2 != NULL)
    printf("Node: %s, %d\n", node2->key, node2->value);

    return 0;
}