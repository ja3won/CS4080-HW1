#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char *text;            // value stored in this node
    struct Node *previous; // previous node in the list
    struct Node *next;     // next node in the list
} Node;

// Insert a new node either at the front or after a given location.
void insert(Node **head, Node *location, const char *text)
{
    Node *new_node = malloc(sizeof(*new_node));
    new_node->text = malloc(strlen(text) + 1);
    strcpy(new_node->text, text);

    if (location != NULL)
    {
        new_node->previous = location;
        new_node->next = location->next;

        if (location->next != NULL)
        {
            location->next->previous = new_node;
        }

        location->next = new_node;
        return;
    }

    new_node->previous = NULL;
    new_node->next = *head;

    if (*head != NULL)
    {
        (*head)->previous = new_node;
    }

    *head = new_node;
}

// Search the list for the first node whose text matches the target.
Node *find(Node *head, const char *text)
{
    for (Node *current = head; current != NULL; current = current->next)
    {
        if (strcmp(current->text, text) == 0)
        {
            return current;
        }
    }

    return NULL;
}

// Remove target from the list and free its memory.
void delete(Node **head, Node *target)
{
    if (target->previous == NULL)
    {
        *head = target->next;
    }
    else
    {
        target->previous->next = target->next;
    }

    if (target->next != NULL)
    {
        target->next->previous = target->previous;
    }

    free(target->text);
    free(target);
}

// Print each node along with pointers to its neighbors.
void dump(Node *head)
{
    for (Node *current = head; current != NULL; current = current->next)
    {
        printf("%p [previous %p next %p] %s\n",
               (void *)current,
               (void *)current->previous,
               (void *)current->next,
               current->text);
    }
}

int main(void)
{
    puts("Hello, world!");

    // Build a small doubly linked list and then delete one element.
    Node *head = NULL;
    insert(&head, NULL, "four");
    insert(&head, NULL, "one");
    insert(&head, find(head, "one"), "two");
    insert(&head, find(head, "two"), "three");

    dump(head);

    puts("-- delete one --");
    delete(&head, find(head, "one"));
    dump(head);

    return 0;
}