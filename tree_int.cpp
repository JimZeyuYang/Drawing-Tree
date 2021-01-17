#include <iostream>

typedef int tree_t;

struct treenode {
    tree_t data;
    treenode *left;
    treenode *right;
};

typedef treenode* treeptr;

void tree_draw_inorder (const treeptr& t);
void node_draw_coordinates (const treeptr& t, const tree_t& v, int& x, int& y);
treeptr tree_reflection (const  treeptr& t);
treeptr constree (tree_t el, treeptr l, treeptr r);
treeptr instree (tree_t el, treeptr t);
void findWidth (const treeptr& t, int& temp);
int findHeight (treeptr t);
int max (int x, int y);
void getPosn (treeptr t, int depth, int& x, int table[], int& width);
void getPosn (treeptr t, const tree_t& v, int depth, int& x, int& Rx, int& Ry);





int main () {
    
    treeptr t = NULL;
    
    t = instree(8, t);
    t = instree(6, t);
    t = instree(7, t);
    t = instree(2, t);
    t = instree(1, t);
    t = instree(4, t);
    t = instree(5, t);
    t = instree(3, t);
    t = instree(12, t);
    t = instree(13, t);
    t = instree(10, t);
    t = instree(11, t);
    t = instree(23, t);
    t = instree(14, t);
    t = instree(19, t);
    t = instree(20, t);
    t = instree(29, t);
    
    
    int v = 8;
    int x = 0, y = 0;
    
//    tree_draw_inorder(t);
    
//    node_draw_coordinates (t, v, x, y);
//    std::cout << x << " " << y;
    
    treeptr s = tree_reflection(t);
    
    std::cout << "Origional" << std::endl;
    tree_draw_inorder(t);
    
    std::cout << "Reflected" << std::endl;
    tree_draw_inorder(s);

    
    
    
    
    return 0;
}

void tree_draw_inorder (const treeptr& t) {
    int width = 0, height = 0;
    findWidth(t, width);
    height = findHeight(t);
    int *table = new int[height*width];
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            table[i*width+j] = -12138;
        }
    }
    
    int x = 0, y = 0;
    getPosn(t, x, y, table, width);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (table[i*width+j] == -12138) {
                std::cout << "    ";
            } else {
                std::cout << table[i*width+j] << "   ";
            }
        }
        std::cout << std::endl;
    }
}

void node_draw_coordinates (const treeptr& t, const tree_t& v, int& x, int& y) {
    int temp1 = 0, temp2 = 0;
    x = 0;
    y = 0;
    getPosn(t, v, temp1, temp2, x, y);
}

treeptr tree_reflection (const treeptr& t) {
    treeptr copyNode = NULL;
    if (t != NULL) {
        copyNode = new treenode;
        copyNode->data = t->data;
        copyNode->left = tree_reflection(t->right);
        copyNode->right = tree_reflection(t->left);
    }
    return copyNode;
}

treeptr constree (tree_t el, treeptr l, treeptr r) {
    treeptr tmp = new treenode;
    tmp->data = el;
    tmp->left = l;
    tmp->right = r;
    return tmp;
}

treeptr instree (tree_t el, treeptr t) {
    if (t == NULL) {
        return constree(el, NULL, NULL);
    } else if (el < t->data) {
        t->left = instree(el, t->left);
        return t;
    } else {
        t->right = instree(el, t->right);
        return t;
    }      
}

void findWidth (const treeptr& t, int& temp) {
    if (t != NULL) {
        findWidth(t->left, temp);
        temp++;
        findWidth(t->right, temp);
    }
}

int findHeight (treeptr t) {
    if (t == NULL) {
        return 0;
    }
    return 1 + max(findHeight(t->left), findHeight(t->right));
}

void getPosn (treeptr t, int depth, int& x, int table[], int& width) {
    if (t != NULL) {
        getPosn(t->left, depth+1, x, table, width);
        table[depth*width+x] = t->data;
        x++;
        getPosn(t->right, depth+1, x, table, width);
    }
}

void getPosn (treeptr t, const tree_t& v, int depth, int& x, int& Rx, int& Ry) {
    if (t != NULL) {
        getPosn(t->left, v, depth+1, x, Rx, Ry);
        if (t->data == v) {
            Rx = x;
            Ry = depth;
        }
        x++;
        getPosn(t->right, v, depth+1, x, Rx, Ry);
    }
}

int max (int x, int y) {
    if (x > y) {
        return x;
    }
    return y;
}