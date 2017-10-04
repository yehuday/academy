/* the idea is to find if a string or any of its permutations were inserted previously to our data structure */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_CHILDS	(1 << sizeof(char))


typedef struct list {
	int last;
	char c;
	int children;
	struct list *next[MAX_CHILDS];
}node;


static void print_node(node *node)
{
	int i;
	printf("%c\n", node->c);

	if (!node->children)
		return;

	for (i = 0; i < MAX_CHILDS; i++) {
		if (node->next[i] != NULL)
			print_node(node->next[i]);
	}
	return;
}

static void print_tree(node *root)
{
	printf("The string tree\n");
	
	print_node(root);
}

int main (int argc, char *argv[])
{
	node *root;
	int go_on = 1;

	root = calloc(sizeof(*root), 1);
	if (root == NULL) {
		printf(" failed to allocate root node\n");
		exit(-ENOMEM);
	}

	root->c = '#';

	printf("The permutated string challenge !\n");

	while (go_on) {
		char *line, *cmd, *str;
		size_t size;

		printf("Your next command:\n");

		getline(&line, &size, stdin);

		if (!size)
			continue;

		cmd = strsep(&line, " ");

		if (!cmd)
			continue;

		printf("command = %s", cmd);

		if (strncmp(cmd, "show", 4) == 0) {
			printf("dumping string tree\n");
			print_tree(root);
		} else if (strncmp(cmd, "insert", 6) == 0) {
			str = strsep(&line, " ");
			if (str == NULL) {
				printf("missing string in command\n");
				continue;
			}
			printf("inserting string %s\n", cmd);
		} else {
			printf("unknown command %s\n", cmd);
		}
	}
}
