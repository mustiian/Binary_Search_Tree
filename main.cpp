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
    TItem *   Delete( TItem * item, int number );
    TItem *   PrintParent( TItem * item, int number );
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

TItem *BST::Delete(TItem *item, int number) {

    if ( item == nullptr )
        return nullptr;

    if ( number < ( item ->m_Number ) )
        item->m_Left = Delete(item->m_Left, number);

    if ( number > ( item ->m_Number ) )
        item->m_Right = Delete(item->m_Right, number);

    if ( number == ( item ->m_Number ) ){
        if ( item->m_Right == nullptr && item->m_Left == nullptr )
            return nullptr;
        else if ( item->m_Left == nullptr )
            return item->m_Right;
        else if ( item->m_Right == nullptr )
            return item->m_Left;
        else {
            TItem * nearItem = Min( item -> m_Right );
            item ->m_Number = nearItem ->m_Number;
            item ->m_Right = Delete(item ->m_Right, nearItem ->m_Number);
        }
    }

    return item;
}

TItem * BST::PrintParent(TItem *item, int number) {

    if ( item == nullptr ){
        cout << "notfound" << endl;
        return nullptr;
    }

    if ( number == ( item ->m_Number ) ){
        cout <<"noparent" << endl;
        return nullptr;
    }

    if ( item ->m_Right != nullptr )
        if ( number == ( item ->m_Right ->m_Number ) ){
            return item;
        }

    if ( item ->m_Left != nullptr )
        if ( number == ( item ->m_Left ->m_Number ) ){
            return item;
        }

    if ( number < ( item ->m_Number ) )
        return PrintParent(item->m_Left, number);

    if ( number > ( item ->m_Number ) )
        return PrintParent(item->m_Right, number);
}

int main(){
    TItem * tree = nullptr, * tmp = nullptr;
    BST alg;

    tree = alg.Insert(tree, 30);
    tree = alg.Insert(tree, 10);
    tree = alg.Insert(tree, 20);
    tree = alg.Insert(tree, 25);

    tmp = alg.PrintParent(tree, 10);
    if ( tmp != nullptr )
        cout << tmp ->m_Number << endl;

    tmp = alg.PrintParent(tree, 20);
    if ( tmp != nullptr )
        cout << tmp ->m_Number << endl;

    tmp = alg.PrintParent(tree, 30);
    if ( tmp != nullptr )
        cout << tmp ->m_Number << endl;

    tmp = alg.PrintParent(tree, 25);
    if ( tmp != nullptr )
        cout << tmp ->m_Number << endl;

    tmp = alg.PrintParent(tree, 1000);
    if ( tmp != nullptr )
        cout << tmp ->m_Number << endl;
}