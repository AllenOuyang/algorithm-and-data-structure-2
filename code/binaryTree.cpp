
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <fstream>   // ��� ������ � ���������� �������
using namespace std;

/////////////////////////////////////////////////////////
class BTree {
protected:
	bool Empty;
	int A;
	BTree* Left;
	BTree* Right;
public:
	BTree();
	BTree(BTree& BT);
	BTree(BTree* pBT);
	~BTree();
	int Depth();
	void Print() { Print(0,3); }
	bool Add(int Anew);
	bool Del(int AAA);
	BTree* ProtoMin();
private:
	void Print(int Space, int SpaceL);
};

/////////////////////////////////////////////////////////
class BTreeD : public BTree {
public:
	int nDeep;
	void Print() { Print(0,6); }
private:
	void Print(int Space, int SpaceL);
};
	
/////////////////////////////////////////////////////////
BTree::BTree() {
	Empty = true;
}

BTree::BTree(BTree& BT) {
	Empty = true;
	if (BT.Empty) return;
	Empty = false;
	A = BT.A;
	Left = new BTree(*BT.Left);
	Right = new BTree(*BT.Right);
}

BTree::BTree(BTree* pBT) {
	Empty = true;
	if (pBT->Empty) return;
	Empty = false;
	A = pBT->A;
	Left = new BTree(pBT->Left);
	Right = new BTree(pBT->Right);
}

BTree::~BTree() {
	if (Empty) return;
	delete Left;
	delete Right;
}
	
int BTree::Depth() {
	if (Empty) return -1;
	return 1+max(Left->Depth(),Right->Depth());
}

void BTree::Print (int Space, int SpaceL) {
    if (Empty)
        return;
    for (int i=0; i<Space; i++)
        cout << " ";
    cout.width(3);
    cout << A;
    Right->Print(0,SpaceL+3);
    if (Right->Empty)
        cout << endl;
    Left->Print(SpaceL,SpaceL+3);
}

bool BTree::Add(int Anew) {
	if (Empty) {
		Empty = false;
		A = Anew;
		Left = new BTree;
		Right = new BTree;
		return true;
	}
	if (Anew==A) return false;
	if (Anew<A) return Left->Add(Anew);
	return Right->Add(Anew);
}

BTree* BTree::ProtoMin() {
	if (Left->Left->Empty) return this;
	return Left->ProtoMin();
}

bool BTree::Del(int AAA) {
    if (Empty) return false;    // ������ ������� �� ������
    if (AAA<A) return Left->Del(AAA);   // ����� ������� ������ � ����� �������
    if (AAA>A) return Right->Del(AAA);
    // ����� ����� A==AAA
    if (Left->Empty && Right->Empty) {  // �� - ����
        Empty = true;
        delete Left;
        delete Right;
        return true;
    }
    if (Right->Empty) { // �������� �����������, ������� ->LeftIsEmpty() ����� �������!
                        // �.�. ����� ���-�� ����! (���������� ����, ��� �� 2-� ��������)
        A = Left->A;
        delete Right;
        BTree* oldLeft = Left;
        Right = Left->Right;
        Left = Left->Left;
        // ����� �������� �� ��������������� ������������� ������ ��� �����������
        // �� (��������� � ��++ ��� ��������) ����� ��� ������� (����� ����������!)
        oldLeft->Left = NULL;
        oldLeft->Right = NULL;
        delete oldLeft;
        return true;
    }
    // ��������! ���������� ����������� ������ (�� � ���, ������� �����) -
    // ������� 1 �������, � ���������� (��� ������� �����) �������� ������!
    if (Left->Empty) {  // �������� �����������, ������� Right->IsEmpty() ����� �������!
                        // �.�. ������ ���-�� ����! (����� �������� ���)
        A = Right->A;
        delete Left;
        BTree* oldRight = Right;
        Left = Right->Left;
        Right = Right->Right;
        oldRight->Left = NULL;
        oldRight->Right = NULL;
        delete oldRight;
        return true;
    }
    // ����� ��� ��������� �������;
    // ���� (��� �� 3-� ��������) ����������� ������� � ������ ���������
    // (� ����� ���� �� ��������: ������ ������������ ������� � ����� ���������)
    // (����� "����� ��������� ����������������" �� ����� �� ������������� - �������� � ������)
    // ��!!!! � ������� �� ����, ��� �� ��������, ���� ������� �� ������ ���� ������!!
    if (Right->Left->Empty) {  // ������ ������ �� ����
        A = Right->A;
        BTree* Tmp = Right;
        Right = Right->Right;
        Tmp->Right = NULL;
        delete Tmp;
        return true;
     }
     // ����� ���� ��������� �� "��� �����" ����������� ������� � ������ ���������
     BTree* Tmp1 = Right->ProtoMin();
     A = Tmp1->Left->A;
     BTree* Tmp2 = Tmp1->Left;
     Tmp1->Left = Tmp2->Right;
     Tmp2->Right = NULL;
     delete Tmp2;
     return true;
}

void BTreeD::Print (int Space, int SpaceL) {
    if (Empty) return;
    for (int i=0; i<Space; i++) cout << " ";
    cout.width(3); cout << A << "(" << nDeep << ")";
    /*Right->Print(0,SpaceL+6);
    if (Right->Empty) cout << endl;
    Left->Print(SpaceL,SpaceL+6);*/
}

/////////////////////////////////////////////////////////
class BTreeDD {
private:
	//bool Empty; ��� ������! ������ ���� nDepth!
	int nDepth;
	int A;
	BTreeDD* Left;
	BTreeDD* Right;
public:
	BTreeDD() { nDepth = -1; }
	BTreeDD(BTreeDD& BT);
	BTreeDD(BTreeDD* pBT);
	~BTreeDD();
	int GetDepth() { return nDepth; }
	bool IsEmpty() { return nDepth<0; }
	void Print() { Print(0,6); }
	bool Yes() { return nDepth<0 || Yes(0,99); }
	bool Add(int Anew);
	bool Del(int AAA); // � ������ �� ����! ���! �� 25-26 ������
	BTreeDD* ProtoMin();
private:
	void Print(int Space, int SpaceL);
	bool Yes(int nMin, int nMax); // "��������" ���� �����������...
};
	
/////////////////////////////////////////////////////////
BTreeDD::BTreeDD(BTreeDD& BT) {
	nDepth = BT.nDepth;
	if (nDepth<0) return;
	A = BT.A;
	Left = new BTreeDD(*BT.Left);
	Right = new BTreeDD(*BT.Right);
}

BTreeDD::BTreeDD(BTreeDD* pBT) {
	nDepth = pBT->nDepth;
	if (nDepth<0) return;
	A = pBT->A;
	Left = new BTreeDD(pBT->Left);
	Right = new BTreeDD(pBT->Right);
}

BTreeDD::~BTreeDD() {
	if (nDepth<0) return;
	delete Left;
	delete Right;
}

bool BTreeDD::Add(int Anew) {
	if (nDepth<0) {
		nDepth = 0;
		A = Anew;
		Left = new BTreeDD;
		Right = new BTreeDD;
		return true;
	}
	if (Anew==A) return false;
	if (Anew<A) { if (!Left->Add(Anew))  return false; }
	else        { if (!Right->Add(Anew)) return false; }
	nDepth = max(Left->GetDepth(),Right->GetDepth())+1;
	return true;
}

void BTreeDD::Print (int Space, int SpaceL) {
    if (nDepth<0) return;
    for (int i=0; i<Space; i++) cout << " ";
    cout.width(3); cout << A << "(" << nDepth << ")";
    Right->Print(0,SpaceL+6);
    if (Right->nDepth<0) cout << endl;
    Left->Print(SpaceL,SpaceL+6);
}
	
bool BTreeDD::Yes(int nMin, int nMax) {
	if (nDepth<0) return true;
	if (A<nMin || A>nMax) return false;
	if (!Left->Yes(nMin,A-1)) return false;
	if (!Right->Yes(A+1,nMax)) return false;
	return true;
}

/////////////////////////////////////////////////////////
class AVLTree {
private:
	int nDepth;
	int A;
	AVLTree* Left;
	AVLTree* Right;
public:
	AVLTree() { nDepth = -1; }
	AVLTree(AVLTree& BT);
	AVLTree(AVLTree* pBT);
	~AVLTree();
	int GetDepth() { return nDepth; }
	bool IsEmpty() { return nDepth<0; }
	void Print() { Print(0,6); }
	bool Yes() { return nDepth<0 || Yes(0,99); }
	bool Add(int Anew);
	bool Del(int AAA); // ����� - ������ �� �����...
	AVLTree* ProtoMin();
private:
	void Print(int Space, int SpaceL);
	bool Yes(int nMin, int nMax); // "��������" ���� �����������...
};

/////////////////////////////////////////////////////////
AVLTree::AVLTree(AVLTree& BT) {
	nDepth = BT.nDepth;
	if (nDepth<0) return;
	A = BT.A;
	Left = new AVLTree(*BT.Left);
	Right = new AVLTree(*BT.Right);
}

AVLTree::AVLTree(AVLTree* pBT) {
	nDepth = pBT->nDepth;
	if (nDepth<0) return;
	A = pBT->A;
	Left = new AVLTree(pBT->Left);
	Right = new AVLTree(pBT->Right);
}

AVLTree::~AVLTree() {
	if (nDepth<0) return;
	delete Left;
	delete Right;
}

bool AVLTree::Add(int Anew) {
	if (nDepth<0) {
		nDepth = 0;
		A = Anew;
		Left = new AVLTree;
		Right = new AVLTree;
		return true;
	}
	if (Anew==A) return false;
	if (Anew<A) { if (!Left->Add(Anew))  return false; }
	else        { if (!Right->Add(Anew)) return false; }
	nDepth = max(Left->GetDepth(),Right->GetDepth())+1;
	return true;
}

void AVLTree::Print (int Space, int SpaceL) {
    if (nDepth<0) return;
    for (int i=0; i<Space; i++)
        cout << " ";
    cout.width(3);
    cout << A << "(" << nDepth << ")";
    Right->Print(0,SpaceL+6);
    if (Right->nDepth<0)
        cout << endl;
    Left->Print(SpaceL,SpaceL+6);
}
	
bool AVLTree::Yes(int nMin, int nMax) {
	// ��������� ������� ������ ������ � ������� ��� - ������������!
	// ��� (������) ������� - ���� ��-���������� "����� � ���� ���"
	if (nDepth<0) return true;
	if (A<nMin || A>nMax) return false;
	if (fabs((Left->nDepth)-(Right->nDepth))>=2) return false; 
	if (!Left->Yes(nMin,A-1)) return false;
	if (!Right->Yes(A+1,nMax)) return false;
	return true;
}

/////////////////////////////////////////////////////////
class Tree {
private:
	int nDepth;
	int nKol;
	int A;
	Tree** SubTrees;
public:
	Tree() { nDepth = -1; }
	Tree(int A);
	~Tree() { Destroy(); }
	int GetDepth() { return nDepth; }
	bool IsEmpty() { return nDepth<0; }
	void InitSubTrees(string Str); 
		// � ��������� ���� ����� ��������� ����������� (���� ����)
		// �������, ��� ������ ������ ������ ����� ��� �� 20h �� 7Ah (�.�. �� 32 �� 7*16+10=122 �����.)
	Tree* Search(char Ch, bool bL); 
		// ���� �������-�-������� �� �������� �� ����������� ��������;
		// ��������! ���������� "������" ��������� �� ������! => ��� ��������� "�� ����.������" �� ����������!
		// bL - ���� �� ���������, ����� ��� ��� ���� (true - ����)
	void Print() { Print(0,3); }
private:
	void Destroy(); // ������� ������ ����������!
	void Print(int Space, int SpaceL);
};

Tree::Tree(int A) {
	nDepth = 0;
	nKol = 0;
	this->A = A;
}

void Tree::InitSubTrees(string Str) {
	// ������� - ������� ��� ����� ��������� ���������� (���� ����)
	Destroy();
	// ������ - ���� ����������
	nDepth = 1;
	nKol = Str.size();
	SubTrees = NULL;
	if (nKol<=0) return; 
	SubTrees = new Tree*[nKol];
	for (int i=0; i<nKol; i++) {
		char Ch = Str[i];
		int AAA = Ch;
		if (AAA<32 || AAA>122) exit(1);
		AAA -= 32;
		SubTrees[i] = new Tree(AAA);
	}
}

void Tree::Destroy() {
	if (nDepth<0) return;
	for (int i=0; i<nKol; i++) delete SubTrees[i];
	nDepth = 0;
	nKol = 0;
}

void Tree::Print(int Space, int SpaceL) {
    if (nDepth<0) return;
    for (int i=0; i<Space; i++) cout << " ";
    cout.width(3); cout << A;
    for (int i=nKol-1; i>=0; i--) {
		SubTrees[i]->Print((i==nKol-1?0:SpaceL),SpaceL+3);
		if (i>0) cout << endl;
	}
}

Tree* Tree::Search(char Ch, bool bL) {
	if (nDepth<0) return NULL;
	int AAA = Ch-32; if ((AAA == A) && (!bL || nDepth==0)) return this;
	for (int i=0; i<nKol; i++) {
		Tree* tmp = SubTrees[i]->Search(Ch,bL);
		if (tmp!=NULL) return tmp;
	}
	return NULL;
}

/////////////////////////////////////////////////////////
//int main(int argc, char** argv) {
//	BTreeDD BT; BT.Print(); cout << endl << endl << endl;
//	BT.Add(8); //BT.Print(); cout << endl << endl << endl;
//	BT.Add(3); //BT.Print(); cout << endl << endl << endl;
//	BT.Add(10); //BT.Print(); cout << endl << endl << endl;
//	BT.Add(14); //BT.Print(); cout << endl << endl << endl;
//	BT.Add(6); //BT.Print(); cout << endl << endl << endl;
//	BT.Add(4); //BT.Print(); cout << endl << endl << endl;
//	BT.Add(7); //BT.Print(); cout << endl << endl << endl;
//	BT.Add(13); //BT.Print(); cout << endl << endl << endl;
//	BT.Add(1); BT.Print(); cout << endl << endl << endl;
//	BTreeDD BT1(BT); BT1.Print();
//	if (BT1.Yes()) cout << "yes"; else cout << "no"; cout << endl << endl << endl;
//	//
//	AVLTree AT; AT.Print(); cout << endl << endl << endl;
//	AT.Add(8); //AT.Print(); cout << endl << endl << endl;
//	AT.Add(3); //AT.Print(); cout << endl << endl << endl;
//	AT.Add(10); //AT.Print(); cout << endl << endl << endl;
//	AT.Add(14); //AT.Print(); cout << endl << endl << endl;
//	AT.Add(6); //AT.Print(); cout << endl << endl << endl;
//	AT.Add(4); //AT.Print(); cout << endl << endl << endl;
//	AT.Add(7); //AT.Print(); cout << endl << endl << endl;
//	AT.Add(13); //AT.Print(); cout << endl << endl << endl;
//	AT.Add(1); AT.Print(); cout << endl << endl << endl;
//	if (AT.Yes()) cout << "yes"; else cout << "no"; cout << endl << endl << endl;
//	AT.Add(9); AT.Print(); cout << endl << endl << endl;
//	if (AT.Yes()) cout << "yes"; else cout << "no"; cout << endl << endl << endl;
//	//
//	Tree TTT(7); TTT.Print(); cout << endl << endl;
//	TTT.InitSubTrees("rtyuiop"); TTT.Print(); cout << endl << endl;
//	Tree* pTTT = TTT.Search('y',true); pTTT->InitSubTrees("poiuytr"); TTT.Print(); cout << endl << endl;
//	return 0;
//}

