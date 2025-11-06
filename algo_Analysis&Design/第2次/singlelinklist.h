#include <iostream>

//Single linklist Node
class CNode {
public:
    int data;
    CNode* next;
    explicit CNode(int val) : data(val), next(nullptr) {}
    ~CNode() = default;
    CNode(const CNode&) = delete;
    CNode& operator=(const CNode&) = delete;
};

//Single linklist Class
class S_Link {
private:
    CNode* head;

public:
    S_Link();
    ~S_Link();

    void append(int value);
    void remove(int value);
    void print() const;
};

//Single linklist:Constructor
S_Link::S_Link() : head(nullptr) {}

//Single linklist:Destructor
S_Link::~S_Link() {
    CNode* curr = head;
    while (curr != nullptr) {
        CNode* temp = curr;
        curr = curr->next;
        delete temp;
    }
}

//Single linklist:Append
void S_Link::append(int value) {
    CNode* newNode = new CNode(value);
    if (head == nullptr) {
        head = newNode;
    } else {
        CNode* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
}

//Single linklist:Remove
void S_Link::remove(int value) {
    CNode* curr = head;
    CNode* prev = nullptr;

    while (curr != nullptr && curr->data != value) {
        prev = curr;
        curr = curr->next;
    }

    if (curr != nullptr) {
        if (prev == nullptr) {
            head = curr->next;
        } else {
            prev->next = curr->next;
        }
        delete curr;
    }
}

//Single linklist:Print
void S_Link::print() const {
    CNode* curr = head;
    while (curr != nullptr) {
        std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

