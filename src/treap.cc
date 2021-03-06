/*
 * Implementation of the Treap balanced tree.
 * By richardxx, 2012.9
 */
#include "treap.hh"
#include <vector>

using namespace std;


static struct TreapNode* 
rotate_left( struct TreapNode *p )
{
  struct TreapNode *t;
  
  t = p -> right;
  p -> right = t -> left;
  t -> left = p;
  
  return t; 
}

static struct TreapNode* 
rotate_right( struct TreapNode *p )
{
  struct TreapNode *t;

  t = p -> left;
  p -> left = t -> right;
  t -> right = p;

  return t;
}

static void dfs_visit_tree( TreapNode *p, TREAP_VISITOR fp_visitor, void* par )
{
   if ( p == NULL ) return;
  
  if ( p->left != NULL )
    dfs_visit_tree( p->left, fp_visitor, par );
  
  fp_visitor( p, par );
  
  if ( p->right != NULL )
    dfs_visit_tree( p->right, fp_visitor, par );
}

// -------------------------------------------------------

// A Non-recursive procedure to find the position where a new segment lives in
Point* find_treap( struct TreapNode *p, int y )
{
  int diff;
  struct TreapNode *ans = NULL;

  while (p) {
    // We compare with the lower bound
    diff = p->data->y1 - y;
    if ( diff <= 0 ) {
      ans = p;
      if ( diff == 0 ) break;
      p = p -> right;
    }
    else {
      p = p -> left;
    }
  }
  
  return ans ? ans->data : NULL;
}

// We sort the treap nodes by the lower y axis of the contained shapes
struct TreapNode* 
insert_treap( struct TreapNode* p, Point *r )
{
  if ( p == NULL ) {
    // Now we create a new tree node
    p = new TreapNode(r);
  }
  else {
    if ( r->y1 < p->data->y1 ) {
      p->left = insert_treap( p->left, r );
      if ( p->left->rkey < p->rkey ) p = rotate_right( p );
    }
    else {
      p->right = insert_treap( p->right, r );
      if ( p->right->rkey < p->rkey ) p = rotate_left( p );
    }
  }
  
  return p;
}
 
// Inorder traversal, for the reason of speeding up the index load
void visit_treap( struct TreapNode *p, TREAP_VISITOR fp_visitor, void* par )
{
  dfs_visit_tree( p, fp_visitor, par );
}

