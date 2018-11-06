#include <iostream>

using namespace std;

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
    BST() : m_Head(nullptr), m_Size(0) {}
    ~BST();
    void Insert( int number );
    void Delete( int number );
    void PrintParent( int number );
    void PrintSuccessor( int number );
    void Rotate( int number, int rotate );
    void printTree();
private:
    TItem * m_Head;
    int m_Size;
};

BST::~BST() {

}

void BST::Insert(int number) {


}

void BST::Delete(int number) {

}

void BST::PrintParent(int number) {

}

void BST::PrintSuccessor(int number) {

}

void BST::Rotate(int number, int rotate) {

}

void BST::printTree() {

}


int main(){



}