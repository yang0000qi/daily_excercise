#include <iostream>
#include <vector>

using namespace std;

#define Debug cout << __PRETTY_FUNCTION__ << ":" << __LINE__ << endl
#define MAX_SIZE 20*1024

class Support;

class CoW {
    private:
        string ldata;
        vector<int> refCnt;
        vector<Support*> ptrSpt;
    public:
        friend class Support;
        CoW()
            :ldata(), refCnt() {
                Debug;
                cout <<  "data: " << ldata.length() << endl;
                cout <<  "refCnt: " << refCnt.size() << endl;
            }
};

class Support {
    public:
        Support(CoW &cow);
        void assign(CoW &cow, string str);
};

void Support::assign(CoW &cow, string str) {
    Debug;

    if (cow.refCnt.size() > 0) {

        for (vector<Support *>::iterator it = cow.ptrSpt.begin(); 
            it != cow.ptrSpt.end(); ++it) {
                cout <<  "it*: " << *it << endl;

        }

        cow.ldata.assign(str);
        cow.refCnt.clear();
        cow.refCnt.push_back(cow.refCnt.size()+1);
    }

    //cout <<  "data: " << cow.ldata.length() << endl;
    //cout <<  "refCnt: " << cow.refCnt.size() << endl;
}

Support::Support(CoW &cow) {
    Debug;

    if (cow.refCnt.size() == 0) {
        cow.refCnt.push_back(cow.refCnt.size()+1);
        cow.ptrSpt.push_back(this);
        cow.ldata.assign(MAX_SIZE, '*');
    } else if (cow.refCnt.size() == 1) {
        cow.refCnt.push_back(cow.refCnt.size()+1);
        cow.ptrSpt.push_back(this);
    } else if (cow.refCnt.size() > 1) {
        cow.refCnt.push_back(cow.refCnt.size()+1);
        cow.ptrSpt.push_back(this);
    }
    cout <<  "data: " << cow.ldata.length() << endl;
    cout <<  "refCnt: " << cow.refCnt.size() << endl;
}

int main() {
    CoW c1;
    Support s1(c1);
    Support s2(c1);
    Support s3(c1);
    Support s4(c1);
    cout << "the following is Arpan:" << endl;
    s4.assign(c1, "Arpan0000");
    Support s6(c1);

    return 0;
}
