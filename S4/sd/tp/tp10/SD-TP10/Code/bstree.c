
#include "bstree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

void bstree_remove_node(ptrBinarySearchTree *t, ptrBinarySearchTree current);

/*------------------------  RedBlackTree  -----------------------------*/

typedef enum {red, black} NodeColor;

/*------------------------  BSTreeType  -----------------------------*/

struct _bstree {
    BinarySearchTree *parent;
    BinarySearchTree *left;
    BinarySearchTree *right;
    NodeColor color;
    int root;
};

/*------------------------  BaseBSTree  -----------------------------*/

BinarySearchTree *bstree_create() {
    return NULL;
}

/* This constructor is private so that we can maintain the oredring invariant on
 * nodes. The only way to add nodes to the tree is with the bstree_add function
 * that ensures the invariant.
 */
BinarySearchTree *bstree_cons(BinarySearchTree *left, BinarySearchTree *right, int root) {
    BinarySearchTree *t = malloc(sizeof(struct _bstree));
    t->parent = NULL;
    t->left = left;
    t->right = right;
    if (t->left != NULL)
        t->left->parent = t;
    if (t->right != NULL)
        t->right->parent = t;
    t->root = root;

    // initialisation du noeud en rouge lors de la construction d'un noeud
    t->color = red;
    return t;
}

void bstree_delete(ptrBinarySearchTree *t)
{
    // using the postix order to get through all nodes without having data leaks

    if (!bstree_empty(*t) && (*t)->left != NULL)
    {
        bstree_delete(&(*t)->left);
    }
    if (!bstree_empty(*t) && (*t)->right != NULL)
    {
        bstree_delete(&(*t)->right);
    }
    
    bstree_remove_node(t, (*t));
}

bool bstree_empty(const BinarySearchTree *t) {
    return t == NULL;
}

int bstree_root(const BinarySearchTree *t) {
    assert(!bstree_empty(t));
    return t->root;
}

BinarySearchTree *bstree_left(const BinarySearchTree *t) {
    assert(!bstree_empty(t));
    return t->left;
}

BinarySearchTree *bstree_right(const BinarySearchTree *t) {
    assert(!bstree_empty(t));
    return t->right;
}

BinarySearchTree *bstree_parent(const BinarySearchTree *t) {
    assert(!bstree_empty(t));
    return t->parent;
}

/*------------------------  BSTreeDictionary  -----------------------------*/

/* Obligation de passer l'arbre par référence pour pouvoir le modifier */
/** Version itérative de l'ajout de noeud dans un BST
 *  bstree_add: BST x int -> BST
 */
void bstree_add(ptrBinarySearchTree* t, int v)
{
    (void)t; (void)v;
    BinarySearchTree *parent;

    if (*t == NULL)
    {
        *t = bstree_cons(NULL, NULL, v);
    } else
    {
        while (*t != NULL)
        {
            parent = *t;
            if (v < (*t)->root)
            {
                t = &(*t)->left;
            } else
            {
                t = &(*t)->right;
            }
        }
        *t = bstree_cons(NULL, NULL, v);
        (*t)->parent = parent;
    }
}

bool bstree_search(const BinarySearchTree *t, int v) {
    (void)t; (void)v;

    BinarySearchTree *current_node = (BinarySearchTree *) t;

    while (current_node != NULL)
    {
        if (v == current_node->root)
        {
            return true;
        }
        
        if (v < current_node->root)
        {
            current_node = current_node->left;
        }
        if (v > current_node->root)
        {
            current_node = current_node->right;
        }
    }
    return false;
}

/** Find the successor in the child nodes
 * @param x: const pointer to the node
 * @return pointer to the successor node  
 */
BinarySearchTree *bstree_successor(const BinarySearchTree *x) {
    assert(!bstree_empty(x));

    if ( x != NULL && x->right != NULL)
    {
        x = x->right;
        while (x->left != NULL)
        {
            x = x->left;
        }
    }
    return (BinarySearchTree *)x;
}

/** Find the predecessor in the childbstree_predecessor nodes
 * @param x: const pointer to the node
 * @return pointer to the predecessor node  
 */
BinarySearchTree *bstree_predecessor(const BinarySearchTree *x) {
    assert(!bstree_empty(x));
    
    if ( x != NULL && x->left != NULL)
    {
        x = x->left;
        while (x->right != NULL)
        {
            x = x->right;
        }
    }
    return (BinarySearchTree *)x;
}

void bstree_swap_nodes(ptrBinarySearchTree *tree, ptrBinarySearchTree from, ptrBinarySearchTree to) {
    assert(!bstree_empty(*tree) && !bstree_empty(from) && !bstree_empty(to));
    (void)tree; (void)from; (void)to;

    int buffer = to->root;
    to->root = from->root;
    from->root = to->root;
    (void) buffer;
}

// t -> the tree to remove from, current -> the node to remove
void bstree_remove_node(ptrBinarySearchTree *t, ptrBinarySearchTree current) {
    assert(!bstree_empty(*t) && !bstree_empty(current));
    (void)t; (void)current;

    BinarySearchTree * leaf;
    BinarySearchTree ** m;

    // lien a modifier
    if ( !current->parent)
    {
        m = t;
    }
    else if ( current->parent->left == current)
    {
        m = &(current->parent->left);
    }
    else
    {
        m = &(current->parent->right);
    }

    // remove node
    if (current->left == current->right)
    {
        // case: no children, current is a leaf
        *m = NULL;
        free(current);
    }
    else if (!current->left)
    {
        // case: only right child
        *m = current->right;
        current->right->parent = current->parent;
        free(current);
    } 
    else if ( !current->right)
    {
        // case: only left child
        *m = current->left;
        current->left->parent = current->parent;
        free(current);
    } else
    {
        // case: both childs
        // leaf = bstree_successor(current);
        leaf = bstree_predecessor(current);
        if (leaf)
        {
            current->root = leaf->root;
            bstree_swap_nodes(t, leaf, current);
            bstree_remove_node(t, leaf);
        }
        
    }   
}

void bstree_remove(ptrBinarySearchTree *t, int v) {
    (void)t; (void)v;

    ptrBinarySearchTree current = *t;

    while (current)
    {
        if (current->root == v)
        {
            bstree_remove_node(t, current);
            return;
        }

        if (v < current->root)
        {
            /* go left */
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
}

/*------------------------  BSTreeVisitors  -----------------------------*/

void bstree_depth_prefix(const BinarySearchTree *t, OperateFunctor f, void *userData) {
    (void)t; (void) f; (void)userData;

    f(t, userData);
    if (t->left != NULL)
    {
        bstree_depth_prefix(t->left, f, userData);
    }
    if (t->right != NULL)
    {
        bstree_depth_prefix(t->right, f, userData);
    }
}

/**
 * Permet l'affichage croissant des valeurs d'un BST
 */
void bstree_depth_infix(const BinarySearchTree *t, OperateFunctor f, void *userData) {
    (void)t; (void) f; (void)userData;

    if (t->left != NULL)
    {
        bstree_depth_infix(t->left, f, userData);
    }
    f(t, userData);
    if (t->right != NULL)
    {
        bstree_depth_infix(t->right, f, userData);
    }
}

void bstree_depth_postfix(const BinarySearchTree *t, OperateFunctor f, void *userData) {
    (void)t; (void) f; (void)userData;
    if (t->left != NULL)
    {
        bstree_depth_postfix(t->left, f, userData);
    }
    if (t->right != NULL)
    {
        bstree_depth_postfix(t->right, f, userData);
    }
    f(t, userData);
}


void bstree_iterative_depth_infix(const BinarySearchTree *t, OperateFunctor f, void *userData) {
    (void)t; (void) f; (void)userData;

    /* // using morris traversal

    // destroying the pointers, to fix

    BinarySearchTree *previous = NULL;
    BinarySearchTree *current = (BinarySearchTree *) t;   
    
    while (current != NULL)
    {
        if (current->left == NULL)
        {
            f(current ,userData);
            current = current->right;
        }
        else
        {
            previous = current->left;
            while (previous->right != NULL && previous->right != current)
            {
                previous = previous->right;
            }
            if (previous->right == NULL)
            {
                previous->right = current;
                current = current->left;
            }
            else
            { // revert
                previous->right = NULL;
                f(current, userData);
                current = current->right;
            }            
        }        
    } */
    BinarySearchTree *previous = NULL;
    BinarySearchTree *current = (BinarySearchTree *) t;   
    BinarySearchTree *next = NULL;
    

    while (current != NULL)
    {
        if (previous == current->parent)
        {
            previous = current;
            next = current->left;
        }
        if (next == NULL || previous == current->left)
        {
            f(current ,userData);
            previous = current;
            next = current->right;
        }
        if (next == NULL || previous == current->right)
        {
            previous = current;
            next = current->parent;
        }
        current = next;
    }
}

void bstree_iterative_breadth_prefix(const BinarySearchTree *t, OperateFunctor f, void *userData) {
    (void)t; (void) f; (void)userData;

    Queue *queue = createQueue();

    BinarySearchTree *current_node;
    
    if (t != NULL)
    {
        queue = queuePush(queue, t);
    }
    
    while (!queueEmpty(queue))
    {
        current_node = (BinarySearchTree *) queueTop(queue);
        f(current_node, userData);
        queue = queuePop(queue);

        if (current_node->left != NULL)
        {
            queue = queuePush(queue, current_node->left);
        }
        if (current_node->right != NULL)
        {
            queue = queuePush(queue, current_node->right);
        }        
    }
    deleteQueue(&queue);
}

/*------------------------  BSTreeIterator  -----------------------------*/

struct _BSTreeIterator {
    /* the collection the iterator is attached to */
    const BinarySearchTree *collection;
    /* the first element according to the iterator direction */
    const BinarySearchTree *(*begin)(const BinarySearchTree *);
    /* the current element pointed by the iterator */
    const BinarySearchTree *current;
    /* function that goes to the next element according to the iterator direction */
    BinarySearchTree *(*next)(const BinarySearchTree *);
};

/* minimum element of the collection */
const BinarySearchTree *goto_min(const BinarySearchTree *e) {
	(void)e;

    while (e->left != NULL)
    {
        e = e->left;
    }
	return e;
}

/* maximum element of the collection */
const BinarySearchTree *goto_max(const BinarySearchTree *e) {
	(void)e;

    while (e->right != NULL)
    {
        e = e->right;
    }
	return e;
}

/* constructor */
BSTreeIterator *bstree_iterator_create(const BinarySearchTree *collection, IteratorDirection direction) {
	(void)collection; (void)direction;

    BSTreeIterator * bst_iterator = malloc(sizeof(struct _BSTreeIterator));

    bst_iterator->collection = collection;

    if (direction == backward)
    {
        bst_iterator->begin = goto_max;
        bst_iterator->next = bstree_parent;
    } else if (direction == forward)
    {
        bst_iterator->begin = goto_min;
        bst_iterator->next = bstree_right;
    }

    bst_iterator->current = collection;
    

	return bst_iterator;
}

/* destructor */
void bstree_iterator_delete(ptrBSTreeIterator *i) {
    free(*i);
    *i = NULL;
}

BSTreeIterator *bstree_iterator_begin(BSTreeIterator *i) {
    i->current = i->begin(i->collection);
    return i;
}

bool bstree_iterator_end(const BSTreeIterator *i) {
    return i->current == NULL;
}

BSTreeIterator *bstree_iterator_next(BSTreeIterator *i) {
    i->current = i->next(i->current);
    return i;
}

const BinarySearchTree *bstree_iterator_value(const BSTreeIterator *i) {
    return i->current;
}

/*------------------------  RedBlackTree operations  -----------------------------*/

void leftrotate(BinarySearchTree *x)
{
    BinarySearchTree * y = x->right;
    BinarySearchTree *x_buffer = x;
    
    // le fils droit de x devient le fils gauche de y
    x->right = y->left;
    if (y->left != NULL)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL)
    {
        x = y;
    }
    else if (x == x->parent->left)
    { // sinon on remplace x par y
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    
    // on attache x à gauche de y
    y->left = x_buffer;
    x_buffer->parent = y;
}

void rightrotate(BinarySearchTree *y)
{
    BinarySearchTree *x = y->left;
    BinarySearchTree *y_buffer = y;

    y->left = x->right;

    if (x->right != NULL)
    {
        x->right->parent = y;
    }

    x->parent = y->parent;
    if (x->parent == NULL)
    {
        y = x;
    }
    else if (y == y->parent->left)
    { // sinon on remplace y par x
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }
    // on attache y à droite de x
    x->right = y_buffer;
    y_buffer->parent = x;
}

void testrotateleft(BinarySearchTree *t)
{
    leftrotate(t);
}

void testrotateright(BinarySearchTree *t)
{
    rightrotate(t);
}


/*------------------------  RedBlackTree Dot format  -----------------------------*/

void printNode(const BinarySearchTree *t, void *out)
{
    FILE *file = (FILE *) out;

    printf("%d ", bstree_root(t));
    fprintf(file, "\tn%d [style=filled, fillcolor=red, label=\"{{<parent>}|%d|{<left>|<right>}}\"];\n",
            bstree_root(t), bstree_root(t));

    if (bstree_left(t)) {
        fprintf(file, "\tn%d:left:c -> n%d:parent:c [headclip=false, tailclip=false]\n",
                bstree_root(t), bstree_root(bstree_left(t)));
    } else {
        fprintf(file, "\tlnil%d [style=filled, fillcolor=grey, label=\"NIL\"];\n", bstree_root(t));
        fprintf(file, "\tn%d:left:c -> lnil%d:n [headclip=false, tailclip=false]\n",
                bstree_root(t), bstree_root(t));
    }
    if (bstree_right(t)) {
        fprintf(file, "\tn%d:right:c -> n%d:parent:c [headclip=false, tailclip=false]\n",
                bstree_root(t), bstree_root(bstree_right(t)));
    } else {
        fprintf(file, "\trnil%d [style=filled, fillcolor=grey, label=\"NIL\"];\n", bstree_root(t));
        fprintf(file, "\tn%d:right:c -> rnil%d:n [headclip=false, tailclip=false]\n",
                bstree_root(t), bstree_root(t));
    }
}

void rbtree_export_dot(const  BinarySearchTree *t, FILE *file)
{
    fprintf(file , "digraph  RedBlackTree  {\n\tgraph[ranksep =0.5];\n\tnode [shape = record ];\n\n");
    bstree_iterative_depth_infix(t, printNode , file);
    fprintf(file , "\n}\n");
}

ptrBinarySearchTree grandparent(ptrBinarySearchTree n)
{
    return n->parent->parent;
}

ptrBinarySearchTree uncle(ptrBinarySearchTree n)
{
    BinarySearchTree *gp = grandparent(n);
    
    if (gp->left == n->parent)
    {
        return gp->right;
    }
    else
    {
        return gp->left;
    }
}


ptrBinarySearchTree fixredblack_insert_case2_left(ptrBinarySearchTree x)
{
    BinarySearchTree *pp = grandparent(x);
    // x fils gauche de p
    if (x->parent->left == x)
    {
        // rotation droite en pp
        rightrotate(pp);
        //p.color -> black
        x->parent->color = black;
        // pp.color -> red
        pp->color = red;
        return x;
    }
    
    // x fils droit de p
    // rotation gauche en p
    leftrotate(x->parent);
    return fixredblack_insert_case2_left(x);
}

ptrBinarySearchTree fixredblack_insert_case2_right(ptrBinarySearchTree x)
{
    BinarySearchTree *pp = grandparent(x);
    // x fils droit de p
    if (x->parent->right == x)
    {
        // rotation gauche en pp
        leftrotate(pp);
        //p.color -> black
        x->parent->color = black;
        // pp.color -> red
        pp->color = red;
        return x;
    }
    
    // x fils gauche de p
    // rotation droite en p
    rightrotate(x->parent);
    return fixredblack_insert_case2_right(x);
}

ptrBinarySearchTree fixredblack_insert_case2(ptrBinarySearchTree x)
{
    BinarySearchTree *pp = grandparent(x);
    // p fils gauche de pp
    if (pp->left == x->parent)
    {
        return fixredblack_insert_case2_left(x);
    }
    // p fils droit de pp
    return fixredblack_insert_case2_right(x);
}

// explicit declaration
ptrBinarySearchTree fixredblack_insert(ptrBinarySearchTree x);

ptrBinarySearchTree fixredblack_insert_case1(ptrBinarySearchTree x)
{
    // cas 1: le frere f de p est rouge, (f est donc l'oncle de x)
    BinarySearchTree *pp = grandparent(x);
    BinarySearchTree *uncle_x = uncle(x);

    if (uncle_x->color == red)
    {
        // f et p deviennent noir
        //p:
        x->parent->color = black;
        //f:
        uncle_x->color = black;
        // et pp devient rouge
        pp->color = red;
        return fixredblack_insert(pp);
    }
    return fixredblack_insert_case2(x);
    
}

ptrBinarySearchTree fixredblack_insert_case0(ptrBinarySearchTree x)
{
    // cas 0: le pere et la racine de l'arbre, on recolore la racine
    if (x->parent->parent == NULL)
    {
        // on recolore:
        x->parent->color = black;
        return x;
    }
    return fixredblack_insert_case1(x);
}

ptrBinarySearchTree fixredblack_insert(ptrBinarySearchTree x)
{
    assert(x->color == red);

    if (x->parent->color == red)
    {
        // recoloration
        return fixredblack_insert_case0(x);
    }
    // pas de recoloration nécessaire
    return x;
}
