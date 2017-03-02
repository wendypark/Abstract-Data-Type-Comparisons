//999344958 Thien Lien ... 998938954 Wonhee Park

#include "QuadraticProbingPtr.h"

template < class HashedObj >
QuadraticPtrHashTable< HashedObj >::~QuadraticPtrHashTable()
{ for ( int i = 0; i != array.size(); i++ )
      { if ( isActive( i ) )
           { array[ i ] = NULL;
           }
      }
}


template < class HashedObj >
QuadraticPtrHashTable< HashedObj >::QuadraticPtrHashTable( const HashedObj & notFound, int size )
: array( nextPrime( size ) ), ITEM_NOT_FOUND( notFound )
{
  makeEmpty( );
}


template < class HashedObj >
bool QuadraticPtrHashTable< HashedObj >::isPrime( int n ) const
{ if( n == 2 || n == 3 )
    { return true;
    }

  if( n == 1 || n % 2 == 0 )
    { return false;
    }

  for( int i = 3; i * i <= n; i += 2 )
     { if( n % i == 0 )
         { return false;
         }
     }

  return true;
}


template < class HashedObj >
int QuadraticPtrHashTable< HashedObj >::nextPrime( int n ) const
{ if( n % 2 == 0 )
    { n++;
    }

  for( ; !isPrime( n ); n += 2 );

  return n;
}


template < class HashedObj >
int QuadraticPtrHashTable< HashedObj >::findPos( const HashedObj & x ) const
{ int collisionNum = 0;
  int currentPos = hash( x, array.size( ) );

  while( array[ currentPos ] != NULL && array[ currentPos ] != &x )
       { currentPos += 2 * ++collisionNum - 1;
         if( currentPos >= array.size( ) )
           { currentPos -= array.size( );
           }
       }

  return currentPos;
}


template < class HashedObj >
int QuadraticPtrHashTable< HashedObj >::hash( int key, int tableSize ) const
{ if( key < 0 ) key = -key;

  return key % tableSize;
}


template < class HashedObj >
void QuadraticPtrHashTable< HashedObj >::insert( const HashedObj & x )
{ int currentPos = findPos( x );

  if( isActive( currentPos ) )
    { return;
    }

  array[ currentPos ] = &x;

  if( ++currentSize > array.size( ) / 2 )
    { rehash( );
    }
}


template < class HashedObj >
void QuadraticPtrHashTable< HashedObj >::rehash( )
{ vector< const HashedObj* > oldArray = array;

  array.resize( nextPrime( 2 * oldArray.size( ) ) );
  
  for( int j = 0; j < array.size( ); j++ )
     { array[ j ] = NULL;
     }

  currentSize = 0;

  for( int i = 0; i < oldArray.size( ); i++ )
     { if ( oldArray[ i ] != NULL )
          { insert( *oldArray[ i ] );
          }
     }
}


template < class HashedObj >
void QuadraticPtrHashTable< HashedObj >::remove( const HashedObj & x )
{ int currentPos = findPos( x );
  
  if( isActive( currentPos ) )
    { array[ currentPos ] = NULL;
    }
}


template < class HashedObj >
const HashedObj & QuadraticPtrHashTable< HashedObj >::find( const HashedObj & x ) const
{ int currentPos = findPos( x );

  return isActive( currentPos ) ? *array[ currentPos ] : ITEM_NOT_FOUND;
}


template < class HashedObj >
void QuadraticPtrHashTable< HashedObj >::makeEmpty( )
{ currentSize = 0;

  for( int i = 0; i < array.size( ); i++ )
     { array[ i ] = NULL;
     }
}


template < class HashedObj >
const QuadraticPtrHashTable< HashedObj > & QuadraticPtrHashTable< HashedObj >::operator=( const QuadraticPtrHashTable< HashedObj > & rhs )
{ if( this != &rhs )
    { array = rhs.array;
      currentSize = rhs.currentSize;
    }

  return *this;
}


template < class HashedObj >
bool QuadraticPtrHashTable< HashedObj >::isActive( int currentPos ) const
{ if ( array[ currentPos ] != NULL )
     { return true;
     }

  else
     { return false;
     }
}


template < class HashedObj >
int QuadraticPtrHashTable< HashedObj >::hash( const string & key, int tableSize ) const
{ int hashVal = 0;

  for( int i = 0; i < key.length( ); i++ )
     { hashVal = 37 * hashVal + key[ i ];
     }

  hashVal %= tableSize;

  if( hashVal < 0 )
    { hashVal += tableSize;
    }

  return hashVal;
}

