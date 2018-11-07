#include <iostream>

using namespace std;

class NotFound : public  exception{
public:
    virtual const char* what() const throw() { return "notfound"; }
};

class NoParent : public  exception{
public:
    virtual const char* what() const throw() { return "noparent"; }
};

class NoSuccessor : public  exception{
public:
    virtual const char* what() const throw() { return "nosuccessor"; }
};

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
    TItem *   Max(TItem *item);
    TItem *   Delete( TItem * item, int number );
    TItem *   GetParent( TItem * item, int number );
    TItem *   GetSuccessor( TItem * item, int number );
    TItem *   FindItem( TItem * item, int number );
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

TItem *BST::Max(TItem *item) {

    if ( item ->m_Right == nullptr )
        return item;
    Max(item ->m_Right);
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

TItem * BST::GetParent(TItem *item, int number) {

    if ( item == nullptr ){
        throw NotFound();
    }

    if ( number == ( item ->m_Number ) ){
        throw NoParent();
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
        return GetParent(item->m_Left, number);

    if ( number > ( item ->m_Number ) )
        return GetParent(item->m_Right, number);

}

TItem *BST::FindItem(TItem *item, int number) {

    if ( item == nullptr )
        return nullptr;

    if ( number == item ->m_Number )
        return item;
    if ( number < item ->m_Number )
        return FindItem( item ->m_Left, number );
    if (number > item -> m_Number )
        return  FindItem( item ->m_Right, number );
}

TItem *BST::GetSuccessor(TItem *tree, int number) {
    TItem * localTop = nullptr;
    TItem * parent = nullptr;

    localTop =  FindItem(tree, number);
    if ( localTop == nullptr ){
        throw NotFound();
    }

    if ( localTop ->m_Right != nullptr)
        return Min( localTop ->m_Right );
    try{
        parent = GetParent(tree, localTop ->m_Number);
    } catch ( const exception& e) { }

    while ( parent != nullptr && localTop == parent ->m_Right ){
        localTop = parent;
        try{
            parent = GetParent(tree, parent ->m_Number);
        } catch ( const exception& e) { parent = nullptr; }
    }

    if ( parent == nullptr ){
        throw  NoSuccessor();
    }

    return parent;
}

int main(){
    TItem * tree = nullptr, * item = nullptr;
    BST alg;

    tree = alg.Insert(tree, 2);
    tree = alg.Insert(tree, 1);
    tree = alg.Insert(tree, 4);
    tree = alg.Insert(tree, 3);
    tree = alg.Insert(tree, 5);

    item = alg.GetParent(tree, 1);
    if ( item != nullptr )cout << item ->m_Number << endl;

    try{
        item = alg.GetParent(tree, 2);
    } catch ( const exception & e ){
        cout << e.what() << endl;
    }
    if ( item != nullptr )cout << item ->m_Number << endl;

    item = alg.GetParent(tree, 3);
    if ( item != nullptr )cout << item ->m_Number << endl;

    item = alg.GetParent(tree, 4);
    if ( item != nullptr )cout << item ->m_Number << endl;

    item = alg.GetParent(tree, 5);
    if ( item != nullptr )cout << item ->m_Number << endl;

    item = alg.GetSuccessor(tree, 1);
    if ( item != nullptr )cout << item ->m_Number << endl;

    item = alg.GetSuccessor(tree, 2);
    if ( item != nullptr )cout << item ->m_Number << endl;

    item = alg.GetSuccessor(tree, 3);
    if ( item != nullptr )cout << item ->m_Number << endl;

    item = alg.GetSuccessor(tree, 4);
    if ( item != nullptr )cout << item ->m_Number << endl;

    try{
        item = alg.GetSuccessor(tree, 5);
    } catch ( const exception& e ){
        cout << e.what() << endl;
    }
    if ( item != nullptr )cout << item ->m_Number << endl;
}