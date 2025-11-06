#include "singlelinklist.h"
#include "doublelinklist.h"
#include <iostream>


int main() {
    using namespace std;
    cout << "Single linklist:" << endl;
    S_Link sLink;
    sLink.append(1);
    sLink.append(2);
    sLink.append(3);
    sLink.print();
    sLink.remove(3);
    sLink.print();

    cout << "\n\n\n" << endl;
    cout << "Double linklist:" << endl;
    D_Link dLink;
    dLink.append(4);
    dLink.append(5);
    dLink.print();
    dLink.remove(5);
    dLink.print();

    return 0;
}
