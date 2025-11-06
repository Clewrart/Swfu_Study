#include <iostream>

//Double linklist Node
class DNode {
public:
    int data;
    DNode* prev;
    DNode* next;

    explicit DNode(int val) : data(val), prev(nullptr), next(nullptr) {}
    ~DNode() = default;
    DNode(const DNode&) = delete;
    DNode& operator=(const DNode&) = delete;
};

//Double linklist Classss
class D_Link {
private:
    DNode* head;

public:
    D_Link();
    ~D_Link();

    void append(int value);
    void remove(int value);
    void print() const;
};

//Double linklist:Constructor
D_Link::D_Link() : head(nullptr) {}

//Double linklist:Destructor
D_Link::~D_Link() {
    DNode* curr = head;
    while (curr != nullptr) {
        DNode* temp = curr;
        curr = curr->next;
        delete temp;
    }
}

//Double linklist:Append
void D_Link::append(int value) {
    DNode* newNode = new DNode(value);
    if (head == nullptr) {
        head = newNode;
    } else {
        DNode* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = newNode;
        newNode->prev = curr;
    }
}

//Double linklist:Remove
void D_Link::remove(int value) {
    DNode* curr = head;
    while (curr != nullptr && curr->data != value) {
        curr = curr->next;
    }

    if (curr != nullptr) {
        if (curr->prev != nullptr) {
            curr->prev->next = curr->next;
        } else {
            head = curr->next;
        }

        if (curr->next != nullptr) {
            curr->next->prev = curr->prev;
        }

        delete curr;
    }
}

//Double linklist:Print
void D_Link::print() const {
    DNode* curr = head;
    while (curr != nullptr) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}
