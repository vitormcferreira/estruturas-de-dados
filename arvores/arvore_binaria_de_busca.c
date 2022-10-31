#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct btree_node {
    int key;
    struct btree_node* left;
    struct btree_node* right;
} Tbtree_node;

typedef struct btree {
    Tbtree_node* first;
} Tbtree;

void _set_if_else_eq(void* cmp1, void* cmp2,
    Tbtree_node** x1, Tbtree_node* y1,
    Tbtree_node** x2, Tbtree_node* y2) {
    if (cmp1 == cmp2)
        (*x1) = y1;
    else
        (*x2) = y2;
}

void _set_if_else_lt_int(int cmp1, int cmp2,
    Tbtree_node** x1, Tbtree_node* y1,
    Tbtree_node** x2, Tbtree_node* y2) {
    if (cmp1 < cmp2)
        (*x1) = y1;
    else
        (*x2) = y2;
}

Tbtree* create_btree() {
    Tbtree* b = malloc(sizeof(Tbtree));
    b->first = NULL;
    return b;
}

Tbtree_node* create_node(int key) {
    Tbtree_node* node = malloc(sizeof(Tbtree_node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void add(Tbtree* b, int key) {
    Tbtree_node* new = create_node(key);

    bool is_empty_tree = b->first == NULL;
    if (is_empty_tree) {
        b->first = new;
        return;
    }

    Tbtree_node* actual = b->first;
    Tbtree_node* node = NULL;

    while (actual != NULL) {
        node = actual;
        _set_if_else_lt_int(key, actual->key,
            &actual, actual->left,
            &actual, actual->right);
    }


    _set_if_else_lt_int(key, node->key,
        &node->left, new,
        &node->right, new);
}

Tbtree_node* find(Tbtree* b, int key) {
    Tbtree_node* aux = b->first;
    while (aux != NULL) {
        if (key == aux->key)
            return aux;
        _set_if_else_lt_int(key, aux->key,
            &aux, aux->left,
            &aux, aux->right);
    }
    return NULL;
}

bool _has_left_children(Tbtree_node* node) {
    return node->left != NULL;
}

bool _has_right_children(Tbtree_node* node) {
    return node->right != NULL;
}

bool _has_no_children(Tbtree_node* node) {
    return !_has_left_children(node) && !_has_right_children(node);
}

bool _has_one_children(Tbtree_node* node) {
    return (_has_left_children(node) && !_has_right_children(node)) ||
        (!_has_left_children(node) && _has_right_children(node));
}

bool _has_two_children(Tbtree_node* node) {
    return _has_left_children(node) && _has_right_children(node);
}

void _get_child_and_parent(Tbtree_node* next, Tbtree_node* aux) {
    while (next->left != NULL) {
        aux = next;
        next = next->left;
    }
}

bool _delete(Tbtree_node* parent, Tbtree_node* target) {
    if (_has_no_children(target)) {
        _set_if_else_eq(parent->left, target,
            &parent->left, NULL,
            &parent->right, NULL);
        free(target);
    }
    else {
        if (_has_one_children(target)) {
            if (_has_left_children(target))
                _set_if_else_eq(parent->left, target,
                    &parent->left, target->left,
                    &parent->right, target->left);
            else
                _set_if_else_eq(parent->right, target,
                    &parent->left, target->right,
                    &parent->right, target->right);

            free(target);
        }
        else { // 2 children
            Tbtree_node* aux = target;
            Tbtree_node* next = target->right;

            while (next->left != NULL) {
                aux = next;
                next = next->left;
            }

            target->key = next->key;
            _delete(aux, next);
        }
    }
}

bool _delete_root(Tbtree* b, Tbtree_node* target) {
    if (_has_no_children(target)) {
        b->first = NULL;
        free(target);
    }
    else {
        if (_has_one_children(target)) {
            if (_has_left_children(target))
                b->first = target->left;
            else
                b->first = target->right;

            free(target);
        }
        else { // 2 children
            Tbtree_node* aux = target;
            Tbtree_node* next = target->right;

            while (next->left != NULL) {
                aux = next;
                next = next->left;
            }

            b->first->key = next->key;
            _delete(aux, next);
        }
    }
}

bool delete(Tbtree* b, int key) {
    if (b->first == NULL) return false;

    Tbtree_node* target = b->first;
    Tbtree_node* parent = NULL;

    bool is_root_key = target->key == key;
    if (is_root_key) {
        _delete_root(b, target);
        return true;
    }

    while (target != NULL && target->key != key) {
        parent = target;
        _set_if_else_lt_int(key, target->key,
            &target, target->left,
            &target, target->right);
    }
    if (target == NULL) return false;

    _delete(parent, target);
    return true;
}

int recursive_by_level(Tbtree_node* b, int level) {
    static int control = 0;
    if (b != NULL) {
        if (control < level) {
            control++;
            int n1 = recursive_by_level(b->left, level);
            int n2 = recursive_by_level(b->right, level);
            control--;
            return n1 || n2;
        }
        printf("key=%d level=%d\n", b->key, level);
        return b->left != NULL || b->right != NULL;
    }
    return false;
}

void btree_node_walk_recursive_by_level(Tbtree_node* btree_node) {
    for (int i = 0; recursive_by_level(btree_node, i) == true; i++);
}

void main(void) {
    Tbtree* b = create_btree();

    add(b, 0);
    add(b, -5);
    add(b, 5);
    add(b, 2);
    // add(b, 6);
    delete(b, 0);

    Tbtree_node* elemento = find(b, 5);
    if (elemento != NULL) {
        printf("find\n");
        printf("%d\n", elemento->key);
        printf("%p\n", elemento->left);
        printf("%p\n", elemento->right);
    }

    printf("btree_node_walk_recursive_by_level\n");
    btree_node_walk_recursive_by_level(b->first);
    printf("\n");

}
