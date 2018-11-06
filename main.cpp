#include <iostream>

using namespace std;

struct TItem;

struct TItem{
    TItem ( int number ) : m_Number(number) ,
                           m_Left(nullptr),
                           m_Right(nullptr) {}
    int     m_Number;
    TItem * m_Left;
    TItem * m_Right;

    friend ostream& operator <<( ostream &os, const TItem * rhs){
        if ( rhs == nullptr )
            return os;
        os << rhs->m_Number << " Left: "   << rhs->m_Left-> m_Number
                           << " Right: "  << rhs->m_Right-> m_Number << endl;
        return os;
    }
};

class BST{
public:
    BST() :  m_Size(0) {}
    TItem *   Insert( TItem * item, int number );
    TItem *   Min( TItem * item );
    //TItem * Delete( TItem * item, int number );
    //void PrintParent( TItem * item, int number );
    //void PrintSuccessor( TItem * item, int number );
    //void Rotate( TItem * item, int number, int rotate );
    //void printTree( TItem * item );
    //void DeleteTree( TItem * item );
private:
    int m_Size;
};

TItem * BST::Insert(TItem * item, int number) {

    if ( item == nullptr ){
        auto nextItem = new TItem(number);
        return nextItem;
    }

    if ( number < ( item ->m_Number ) )
        item->m_Left = Insert(item->m_Left, number);

    if ( number > ( item ->m_Number ) )
        item->m_Right = Insert(item->m_Right, number);

    return item;
}

TItem *BST::Min(TItem *item) {

    if ( item ->m_Left == nullptr )
        return item;
    Min(item ->m_Left);
}

int main(){
    TItem * tree = nullptr;
    BST alg;

    tree = alg.Insert(tree, 30);
    tree = alg.Insert(tree, 10);
    tree = alg.Insert(tree, 20);
    tree = alg.Insert(tree, 25);

}