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

class NoRotate : public  exception{
public:
    virtual const char* what() const throw() { return "norotate"; }
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
    TItem *   Insert( TItem * tree, int number );
    TItem *   Min( TItem * tree );
    TItem *   Max(TItem *tree);
    TItem *   Delete( TItem * tree, int number );
    TItem *   GetParent( TItem * tree, int number );
    TItem *   GetSuccessor( TItem * tree, int number );
    TItem *   FindItem( TItem * tree, int number );
    TItem *   Rotate( TItem * tree, int number, int rotate );
    //void DeleteTree( TItem * item );
private:
    int m_Size;
};

TItem * BST::Insert(TItem * tree, int number) {

    if ( tree == nullptr ){
        auto nextItem = new TItem(number);
        return nextItem;
    }

    if ( number < ( tree ->m_Number ) )
        tree->m_Left = Insert(tree->m_Left, number);

    if ( number > ( tree ->m_Number ) )
        tree->m_Right = Insert(tree->m_Right, number);

    return tree;
}

TItem *BST::Max(TItem *tree) {

    if ( tree ->m_Right == nullptr )
        return tree;
    Max(tree ->m_Right);
}

TItem *BST::Min(TItem *tree) {

    if ( tree ->m_Left == nullptr )
        return tree;
    Min(tree ->m_Left);
}

TItem *BST::Delete(TItem *tree, int number) {

    if ( tree == nullptr )
        return nullptr;

    if ( number < ( tree ->m_Number ) )
        tree->m_Left = Delete(tree->m_Left, number);

    if ( number > ( tree ->m_Number ) )
        tree->m_Right = Delete(tree->m_Right, number);

    if ( number == ( tree ->m_Number ) ){
        if ( tree->m_Right == nullptr && tree->m_Left == nullptr )
            return nullptr;
        else if ( tree->m_Left == nullptr )
            return tree->m_Right;
        else if ( tree->m_Right == nullptr )
            return tree->m_Left;
        else {
            TItem * nearItem = Min( tree -> m_Right );
            tree ->m_Number = nearItem ->m_Number;
            tree ->m_Right = Delete(tree ->m_Right, nearItem ->m_Number);
        }
    }

    return tree;
}

TItem * BST::GetParent(TItem *tree, int number) {

    if ( tree == nullptr ){
        throw NotFound();
    }

    if ( number == ( tree ->m_Number ) ){
        throw NoParent();
    }

    if ( tree ->m_Right != nullptr )
        if ( number == ( tree ->m_Right ->m_Number ) ){
            return tree;
        }

    if ( tree ->m_Left != nullptr )
        if ( number == ( tree ->m_Left ->m_Number ) ){
            return tree;
        }

    if ( number < ( tree ->m_Number ) )
        return GetParent(tree->m_Left, number);

    if ( number > ( tree ->m_Number ) )
        return GetParent(tree->m_Right, number);

}

TItem *BST::FindItem(TItem *tree, int number) {

    if ( tree == nullptr )
        return nullptr;

    if ( number == tree ->m_Number )
        return tree;
    if ( number < tree ->m_Number )
        return FindItem( tree ->m_Left, number );
    if (number > tree -> m_Number )
        return  FindItem( tree ->m_Right, number );
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

TItem *BST::Rotate(TItem *tree, int number, int rotate) {
    TItem *pointX = tree;
    TItem * pointY;
    TItem * parent;

    if (pointX == nullptr)
        return nullptr;

    while ( number != pointX->m_Number ) {
        if (number < pointX->m_Left->m_Number) {
            pointX = pointX ->m_Left;
        }

        if (number > pointX ->m_Right->m_Number){
            pointX = pointX ->m_Right;
        }
    }

    if ( rotate == 1 ){
        if ( pointX ->m_Right == nullptr )
            throw NoRotate();
        pointY = pointX -> m_Right;

        pointX -> m_Right = pointY ->m_Left;
        pointY ->m_Left = pointX;
    }

    if ( rotate == 2 ){
        if ( pointX ->m_Left == nullptr )
            throw NoRotate();
        pointY = pointX -> m_Left;

        pointX -> m_Left = pointY ->m_Right;
        pointY ->m_Right = pointX;
    }
    try {
       parent = GetParent(tree, number);
    } catch ( const exception& e ){
        tree = pointY;
        return tree;
    }


    if ( parent ->m_Right == pointX )
        parent ->m_Right = pointY;

    if ( parent ->m_Left == pointX )
        parent ->m_Left = pointY;

    return tree;
}

int main(){
    TItem * tree = nullptr, * item = nullptr;
    BST alg;

    tree = alg.Insert(tree, 3);
    tree = alg.Insert(tree, 1);
    tree = alg.Insert(tree, 4);
    tree = alg.Insert(tree, 2);

    item = alg.GetParent(tree, 1);
    if ( item != nullptr )cout << item ->m_Number << endl;

    item = alg.GetParent(tree, 2);
    if ( item != nullptr )cout << item ->m_Number << endl;

    try{
        item = alg.GetParent(tree, 3);
    } catch ( const exception & e ){
        cout << e.what() << endl;
    }
    if ( item != nullptr )cout << item ->m_Number << endl;

    item = alg.GetParent(tree, 4);
    if ( item != nullptr )cout << item ->m_Number << endl;

    tree = alg.Rotate(tree, 3, 2);

    try{
        item = alg.GetParent(tree, 1);
    } catch ( const exception & e ){
        cout << e.what() << endl;
    }
    if ( item != nullptr )cout << item ->m_Number << endl;

    item = alg.GetParent(tree, 2);
    if ( item != nullptr )cout << item ->m_Number << endl;

    item = alg.GetParent(tree, 3);
    if ( item != nullptr )cout << item ->m_Number << endl;

    item = alg.GetParent(tree, 4);
    if ( item != nullptr )cout << item ->m_Number << endl;


    try{
        item = alg.Rotate(tree, 1, 2);
    } catch ( const exception & e ){
        cout << e.what() << endl;
    }
}