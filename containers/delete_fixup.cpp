void delete_fixup(Node *x)
{
    rbTree *root = 0;
    while (x->parent != NULL && x->color == BLACK)
    {
        if (x == x->p->left)
        {
            Node *w = x->p->right;
            // type 1
            if (w->color == RED)
            {
                w->color = BLACK;
                x->p->color = RED;
                left_rotate(x->p);
                w = x->p->right;
            }
            // type 2
            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->p;
            }
            else
            {
                // type 3
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(w);
                    w = x->p->right;
                }
                // type 4
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                left_rotate(x->p);
                x = root;
            }
        }
        else
        {
            Node *w = x->p->left;
            // type 1
            if (w->color == RED)
            {
                w->color = BLACK;
                x->p->color = RED;
                right_rotate(x->p);
                w = x->p->left;
            }
            // type 2
            if (w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                x = x->p;
            }
            else
            {
                // type 3
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(w);
                    w = x->p->left;
                }
                // type 4
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                right_rotate(x->p);
                x = root;
            }//double black right of parent
        }
    }
    x->color = BLACK;
}
;