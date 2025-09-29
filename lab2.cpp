#include <iostream>
#include <string>
using namespace std;

// -----------------------------
// Data Model
// -----------------------------
struct User {
    string username;
    string password; 
    string role;
    User* next;
    
    User(const string& u, const string& p, const string& r = "viewer") {
        username = u;
        password = p;
        role = r;
        next = nullptr;
    }
};

bool insertUser(User*& head, const string& username, const string& password);
User* findUser(User* head, const string& username);
bool authenticate(User* head, const string& username, const string& password);
void printUsers(User* head);
bool removeFront(User*& head);
bool removeByUsername(User*& head, const string& username);
void clearList(User*& head);
size_t size(User* head);

int main() {
  
    // Write code here to test your implementation
    User* head = nullptr;

    insertUser(head, "Tyzaya", "COMPSCI");
    insertUser(head, "Kuromi", "ABC123");
    insertUser(head, "Sammy", "CAT123");
    insertUser(head, "Chris", "BROWN101");
    insertUser(head, "Orlando", "LOL123");


    printUsers(head);
    cout << "Size: " << size(head) << "\n";


    cout << "Authenticating the user Tyzaya: ";
    cout << (authenticate(head, "Tyzaya", "COMPSCI") ? "OK" : "FAILED.") << "\n";
    

    cout << "Deleting the front user: ";
    removeFront(head);
    printUsers(head);

    cout << "Removing the user by the name Sammy: ";
    removeByUsername(head, "Sammy");
    printUsers(head);

    cout << "Clearing the entire list...\n";
    clearList(head);
    printUsers(head);


    return 0;
}

// -----------------------------
// Core API — implement these
// -----------------------------

// Inserts a new (username, password) at the END of the list.
// If username already exists, do NOT insert a duplicate; return false.
// Otherwise insert and return true.

// Runtime: Big O(n) - May have to go through the entire list.
bool insertUser(User*& head, const string& username, const string& password) {
    if (head == nullptr){
        head = new User(username, password);
        return true;
    }
    User* current = head;
    while (current) {
        if (current -> username == username)
        return false;
        if(current ->next == nullptr)
        break;
        current = current->next;
    }
    current->next = new User(username,password);
   
    return true;
}

// Returns pointer to the node with matching username; otherwise nullptr.

// Runtime: Big O(n)
User* findUser(User* head, const string& username) {
    User* current = head;
    while (current) {
        if(current -> username == username)
        return current;
        current = current->next;
    }
    return nullptr;
}

// Returns true if (username, password) matches an existing node; false otherwise.

// Runtime: Big O(n) - Because I made this function use recursion!
bool authenticate(User* head, const string& username, const string& password) {
    User* usr = findUser(head, username);
    if (usr && usr -> password == password){
    return true;
} else {
    return false;
   }
}

// Deletes the FIRST node (head) and updates head. No-op if list is empty.
// Return true if a node was deleted, false otherwise.

// Runtime: Big O(1) - It just updates the head pointer.
bool removeFront(User*& head) {
    if (head == nullptr) {
        return false;
    } 
    User* temp = head;
    head = head -> next;
    delete temp;
    return true;
    }
// Deletes the node with matching username (first match only).
// Return true if a node was found & deleted; false if not found.

// Runtime: Big O(n)
bool removeByUsername(User*& head, const string& username) {
    if(head == nullptr){
        return false;
    }
    if(head -> username == username) {
        delete head;
        head = head -> next;
        return true;
    }
    User* current = head;
    while (current -> next) {
        if (current->next->username == username) {
            User* temp = current->next;
            current->next = current->next->next;
        delete temp;
        return true;
        }
        current = current->next;
    }
    return false;
}

// Deletes ALL nodes and sets head=nullptr.

// Runtime: Big O(n) - it deletes every node so it must traverse the entire list.
void clearList(User*& head) {
    User* current = head;
    while(current) {
        User* next = current-> next;
        delete current;
        current = next;
    }
    head = nullptr;
}

// Returns number of nodes.

// Runtime: Big O(n) - Counts every node in the list.
size_t size(User* head) {
    size_t count = 0;
    while (head) {
        count++;
        head = head-> next;
    }
    return count;
}

// Prints usernames in order, separated by " -> " then " -> NULL".
// Example: alice -> bob -> charlie -> NULL

//Runtime: Big O(n) - traverses the entire list once.
void printUsers(User* head) {
    User* current = head;
    while(current) {
        cout << current -> username << "->";
        current = current -> next;
    }
    cout << "NULL\n";
}