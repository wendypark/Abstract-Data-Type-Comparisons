//999344958 Thien Lien

#include "BST2.h"
#include <iostream>
using namespace std;

template < class Comparable >
BinarySearchTree< Comparable >::BinarySearchTree( const Comparable & notFound ) : root( NULL ), ITEM_NOT_FOUND( notFound )
{
}


template < class Comparable >
BinarySearchTree< Comparable >::BinarySearchTree( const BinarySearchTree< Comparable> & rhs ) : root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND )
{ *this = rhs;
}


template < class Comparable >
BinarySearchTree< Comparable >::~BinarySearchTree( )
{ makeEmpty( );
}


template < class Comparable >
void BinarySearchTree< Comparable >::insert( const Comparable & x )
{ insert( x, root );
}


template < class Comparable >
void BinarySearchTree< Comparable >::remove( const Comparable & x )
{ remove( x, root );
}


template < class Comparable >
const Comparable & BinarySearchTree< Comparable >::findMin( ) const
{ return elementAt( findMin( root ) );
}


template < class Comparable >
const Comparable & BinarySearchTree< Comparable >::findMax( ) const
{ return elementAt( findMax( root ) );
}


template < class Comparable >
const Comparable & BinarySearchTree< Comparable >::find( const Comparable & x ) const
{ return elementAt( find( x, root ) );
}


template < class Comparable >
void BinarySearchTree< Comparable >::makeEmpty( )
{ makeEmpty( root );
}


template < class Comparable >
bool BinarySearchTree< Comparable >::isEmpty( ) const
{ return root == NULL;
}


template < class Comparable >
void BinarySearchTree< Comparable >::printTree( ) const
{ if ( isEmpty( ) )
     { cout << "Empty tree" << endl;
     }

  else
     {  printTree( root );
     }
}


template < class Comparable >
const BinarySearchTree< Comparable > & BinarySearchTree< Comparable >::operator=( const BinarySearchTree< Comparable > & rhs )
{ if ( this != &rhs )
     { makeEmpty( );
       root = clone( rhs.root );
     }

  return *this;
}


template < class Comparable >
const Comparable & BinarySearchTree< Comparable >::elementAt( BinaryNode< Comparable > *t ) const
{ return t == NULL ? ITEM_NOT_FOUND : t -> element;
}


template < class Comparable >
void BinarySearchTree< Comparable >::insert( const Comparable & x, BinaryNode< Comparable > * & t ) const
{ if ( t == NULL )
     { t = new BinaryNode< Comparable >( x, NULL, NULL );
     }

  else if ( x <= t -> element )
     { insert( x, t -> left );
     }

  else if ( t -> element < x )
     { insert( x, t -> right );
     }
}


template < class Comparable >
void BinarySearchTree< Comparable >::remove( const Comparable & x, BinaryNode< Comparable > * & t ) const
{ if ( t == NULL )
     { return;
     }

  if ( x < t -> element )
     { remove( x, t -> left );
     }

  else if ( t -> element < x )
     { remove( x, t -> right );
     }

  else if ( t -> left != NULL && t -> right != NULL )
     { t -> element = findMin( t -> right ) -> element;
       remove( t -> element, t -> right );
     }

  else
     { BinaryNode< Comparable > *oldNode = t;
       t = ( t -> left != NULL ) ? t -> left : t -> right;
       delete oldNode;
     }
}


template < class Comparable >
BinaryNode< Comparable > * BinarySearchTree< Comparable >::findMin( BinaryNode< Comparable > *t ) const
{ if ( t == NULL )
     { return NULL;
     }

  if ( t -> left == NULL )
     { return t;
     }

  return findMin( t -> left );
}


template < class Comparable >
BinaryNode< Comparable > * BinarySearchTree< Comparable >::findMax( BinaryNode< Comparable > *t ) const
{ if ( t != NULL )
     { while( t -> right != NULL )
            { t = t->right;
            }
     }

  return t;
}


template < class Comparable >
BinaryNode< Comparable > * BinarySearchTree< Comparable >::find( const Comparable & x, BinaryNode< Comparable > *t ) const
{ if ( t == NULL )
     { return NULL;
     }

  else if ( x < t -> element )
     { return find( x, t -> left );
     }

  else if ( t -> element < x )
     { return find( x, t -> right );
     }

  else
     { return t;
     }
}


/*NONRECURSIVE VERSION*/
/*template < class Comparable >
BinaryNode< Comparable > * BinarySearchTree< Comparable >::find( const Comparable & x, BinaryNode< Comparable > *t ) const
{ while( t != NULL )
       {  if ( x < t -> element )
             { t = t -> left;
             }

          else if( t -> element < x )
             { t = t -> right;
             }

          else
             { return t;
             }
       }

  return NULL;
}*/


template < class Comparable >
void BinarySearchTree< Comparable >::makeEmpty( BinaryNode< Comparable > * & t ) const
{ if ( t != NULL )
     { makeEmpty( t -> left );
       makeEmpty( t -> right );
       delete t;
     }

  t = NULL;
}


template < class Comparable >
BinaryNode< Comparable > * BinarySearchTree< Comparable >::clone( BinaryNode< Comparable > * t ) const
{ if ( t == NULL )
     { return NULL;
     }

  else
     { return new BinaryNode< Comparable >( t -> element, clone( t -> left ), clone( t -> right ) );
     }
}


template < class Comparable >
void BinarySearchTree< Comparable >::printTree( BinaryNode< Comparable > *t ) const
{ if ( t != NULL )
     { printTree( t -> left );
       cout << t -> element << endl;
       printTree( t -> right );
     }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template < class Comparable >
void BinarySearchTree< Comparable >::printTree( BinaryNode< Comparable > *t, const Comparable &x, const Comparable &y ) const
{ if ( t != NULL )
     { if ( t -> element > x )
       { printTree( t -> left, x, y );
       }

       printTree( t -> left, x, y );

       if ( t -> element >= x && t -> element <= y )
       { cout << t -> element << " ";
       }

       if ( t -> element < y )
       { printTree( t -> right, x, y );
       }
     }
}


template < class Comparable >
void BinarySearchTree< Comparable >::printRange( const Comparable &x, const Comparable &y ) const
{ if ( x < y )
     { printTree( root, x, y );
     }

  if ( x > y )
     { printTree( root, y, x );
     }

  cout << endl;
}

