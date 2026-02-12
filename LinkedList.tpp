template <typename T>
LinkedList<T>::LinkedList()
: head(nullptr) { }

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& copyObj) {
    copy(copyObj);
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template <typename T>
void LinkedList<T>::append(const T& elem) {
    Node* n = new Node(elem);

    if (head == nullptr) {
        head = n;
    }
    else {
        Node* curr = head;

        while (curr->next != nullptr) {
            curr = curr->next;
        }

        curr->next = n;
    }

    this->length++;
}

template <typename T>
void LinkedList<T>::clear() {
    Node* prev = nullptr;

    while (head != nullptr) {
        prev = head;
        head = head->next;
        delete prev;
    }

    this->length = 0;
}

template <typename T>
void LinkedList<T>::copy(const LinkedList<T>& copyObj) {
    // TODO

    if (copyObj.head == nullptr){ //checks if other list is empty or not 
        throw string("copy: error, other list is empty");
    }

    //copy first node and put it into newHead
    Node* newHead = new Node(copyObj.head->value);
    newHead -> next = nullptr;
    newHead -> prev = nullptr;
    ++this->length;

    //create a curr pointer to traverse the other list(starting from 2nd node)
    Node* otherCurr = copyObj.head -> next;

    //create a curr pointer to traverse new list
    Node* newCurr = newHead;

    //copy rest of list
    while (otherCurr != nullptr){

        //creates a dynamic newNode to store pointer and value of copied data from old list
        Node* newNode = new Node(otherCurr-> value);

        //links newNode to curr list
        newNode -> next = nullptr;
        newNode -> prev = newCurr;
        newCurr -> next = newNode;

        //move both pointer forward(otherCurr is one node ahead of newCurr)
        otherCurr = otherCurr -> next;
        newCurr = newCurr -> next; // or alternatively, newCurr = newNode

        ++this->length;
    }

}

template <typename T>
T LinkedList<T>::getElement(int position) const {
    if (position < 0 || position >= this->length) {
        throw string("getElement: error, position out of bounds");
    }
    
    Node* curr = head;

    for (int i = 0; i < position; i++) {
        curr = curr->next;
    }

    return curr->value;
}

template <typename T>
int LinkedList<T>::getLength() const {
    return this->length;
}

template <typename T>
void LinkedList<T>::insert(int position, const T& elem) {
    // TODO
    if (position < 0 || position >= this -> length) throw string("remove: error, position out of bounds"); // checks for out of bounds

    Node* curr = head;
    Node* newNode = new Node(elem);
    int count = 0;

    if (head == nullptr){ //if list is EMPTY, will just act like append
        head = newNode;
        head -> next = nullptr;
        head -> prev = nullptr;
        ++this->length;
        return;
    }

    if (count == position){ //insert at position 0
        newNode -> next = head;
        newNode -> prev = nullptr;
        head -> prev = newNode;
        newNode = head;
        ++this->length;
        return;
    }

    if (position == this->length){
        
        //traverses to last node
        while (curr != nullptr){
            curr = curr -> next;
        }
        //inserts or appends last node
        curr -> next = curr;
        newNode -> prev = curr;
        newNode -> next = nullptr;
        ++this->length;
        return;
    }

    while (curr != nullptr && count < position){ //traverses to node that needs deleting
        curr = curr -> next;
        ++count;
    }

    //inserts before the curr
    newNode -> prev = curr -> prev;
    newNode -> next = curr;
    curr -> prev -> next = newNode;
    curr -> prev = newNode;

    ++this->length;
    

}

template <typename T>
bool LinkedList<T>::isEmpty() const {
    return this->length == 0;
}

template <typename T>
void LinkedList<T>::remove(int position) {
    // TODO
    if (head == nullptr) throw string ("remove: error, list does not exist"); // checks if list exists

    if (position < 0 || position >= this -> length) throw string("remove: error, position out of bounds"); // checks for out of bounds

    Node* curr = head;
    Node* temp;
    int count = 0;

    

    while (curr != nullptr && count < position){ //traverses to node that needs deleting
        
        curr = curr -> next;
        ++count;

    }
        //curr would be at the correct node to delete
        if (count == position){
            
            if (curr -> prev == nullptr){ // first node
            
               head = curr -> next;
                
               if (head != nullptr){
                    head -> prev = nullptr;
                }

               delete curr;
               --this->length;

            } else if (curr -> next == nullptr){ // last node

                curr -> prev -> next = nullptr;
                delete curr;
                --this->length;

            } else { //removes middle node

            curr -> prev -> next = curr -> next;
            curr -> next -> prev = curr -> prev;
            delete curr;
            --this->length;

        }
        
        
    }

}

template <typename T>
void LinkedList<T>::replace(int position, const T& elem) {
    if (position < 0 || position >= this->length) {
        throw string("replace: error, position out of bounds");
    }

    Node* curr = head;

    for (int i = 0; i < position; i++) {
        curr = curr->next;
    }

    curr->value = elem;
}

template <typename T>
ostream& operator<<(ostream& outStream, const LinkedList<T>& myObj) {
    if (myObj.isEmpty()) {
        outStream << "List is empty, no elements to display.\n";
    }
    else {
        typename LinkedList<T>::Node* curr = myObj.head;
        while (curr != nullptr) {
            outStream << curr->value;
            if (curr->next != nullptr) {
                outStream << " --> ";
            }
            curr = curr->next;
        }
        outStream << endl;
    }

    return outStream;
}
