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
                           m_Right(nullptr),
                           m_Parent(nullptr) {}
    int     m_Number;
    TItem * m_Left;
    TItem * m_Right;
    TItem * m_Parent;

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
    TItem *   Insert( TItem * tree, int number, TItem * parent );
    TItem *   Min( TItem * tree );
    TItem *   Max(TItem *tree);
    TItem *   Delete( TItem * tree, int number );
    TItem *   GetParent( TItem * tree, int number );
    TItem *   GetSuccessor( TItem * tree, int number );
    TItem *   FindItem( TItem * tree, int number );
    TItem *   Rotate( TItem * tree, int number, int rotate );
    void DeleteTree( TItem * item );
private:
    int m_Size;
};

TItem * BST::Insert(TItem * tree, int number, TItem * parent) {

    if ( tree == nullptr ){
        auto nextItem = new TItem(number);
        nextItem ->m_Parent = parent;
        return nextItem;
    }

    if ( number < ( tree ->m_Number ) )
        tree->m_Left = Insert(tree->m_Left, number, tree);

    if ( number > ( tree ->m_Number ) )
        tree->m_Right = Insert(tree->m_Right, number, tree);

    return tree;
}

TItem *BST::Max(TItem *tree) {

    if ( tree ->m_Right == nullptr )
        return tree;
    return Max(tree ->m_Right);
}

TItem *BST::Min(TItem *tree) {

    if ( tree ->m_Left == nullptr )
        return tree;
    return Min(tree ->m_Left);
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

    return nullptr;
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

    return nullptr;
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
        } catch ( const exception& e ) { parent = nullptr; }
    }

    if ( parent == nullptr ){
        throw  NoSuccessor();
    }

    return parent;
}

TItem * BST::Rotate(TItem *tree, int number, int rotate) {
    TItem *pointX = tree;
    TItem *pointY = nullptr;
    TItem * parent;

    if (pointX == nullptr)
        throw NotFound();

    pointX = FindItem(tree, number);
    if (pointX == nullptr)
        throw NotFound();

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

void BST::DeleteTree(TItem *item) {
    if ( item == nullptr ) return;

    DeleteTree(item->m_Left);
    DeleteTree(item->m_Right);

    delete item;
}

int main(){
    TItem * tree = nullptr, * item = nullptr;
    BST alg;
    int command, number, rotate;

    while( true ){
        cin >> command;
        if ( command == 6 ) break;

        cin >> number;

        switch (command){
            case 1 :
                tree = alg.Insert(tree, number, nullptr);
                break;
            case 2 :
                tree = alg.Delete(tree, number);
                break;
            case 3 :
                item = nullptr;
                try{
                    item = alg.GetParent(tree, number);
                } catch ( const exception & e ){
                    cout << e.what() << endl;
                }
                if ( item != nullptr )cout << item ->m_Number << endl;
                break;
            case 4 :
                item = nullptr;
                try{
                    item = alg.GetSuccessor(tree, number);
                } catch ( const exception & e ){
                    cout << e.what() << endl;
                }
                if ( item != nullptr )cout << item ->m_Number << endl;
                break;
            case 5 :
                cin >> rotate;
                try{
                    tree = alg.Rotate(tree, number, rotate);
                } catch ( const exception & e ){
                    cout << e.what() << endl;
                }
                break;
            default: break;
        }

    }

    alg.DeleteTree(tree);

    return 0;
}