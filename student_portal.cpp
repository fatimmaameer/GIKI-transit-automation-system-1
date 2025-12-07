#include<iostream>
using namespace std;

struct Student{
    int studentID;
    string name;
    string dep;
    Student* right;
    Student* left;
    int height;

    Student(int id, string Name, string Dep){
        studentID = id;
        name = Name;   // FIXED
        dep = Dep;     // FIXED
        right = nullptr;
        left = nullptr;
        height = 1;
    }
};

int height(Student* s){
    if(s == nullptr){
        return 0;
    }
    return s->height;
}

void updateHeight(Student* s){
    if(s == nullptr){
        return;
    }
    s->height = 1 + max(height(s->left), height(s->right));
}

int getBalance(Student* s){
    if(s == nullptr) return 0;
    return height(s->left) - height(s->right);
}

Student* rightRotate(Student* y){
    Student* x = y->left;
    Student* temp = x->right;

    x->right = y;
    y->left = temp;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Student* leftRotate(Student* x){
    Student* y = x->right;
    Student* temp = y->left;

    y->left = x;
    x->right = temp;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Student* insert(Student* s, int id, string name, string dep){
    if(s == nullptr){
        return new Student(id, name, dep);
    }

    if(id < s->studentID){
        s->left = insert(s->left, id, name, dep);
    }
    else if(id > s->studentID){
        s->right = insert(s->right, id, name, dep);
    }
    else {
        return s; // duplicate ID not inserted
    }

    updateHeight(s);

    int balance = getBalance(s);

    // 1. Left Left Case
    if(balance > 1 && id < s->left->studentID){
        return rightRotate(s);
    }

    // 2. Right Right Case
    if(balance < -1 && id > s->right->studentID){
        return leftRotate(s);
    }

    // 3. Left Right Case
    if(balance > 1 && id > s->left->studentID){
        s->left = leftRotate(s->left);
        return rightRotate(s);
    }

    // 4. Right Left Case
    if(balance < -1 && id < s->right->studentID){
        s->right = rightRotate(s->right);
        return leftRotate(s);
    }

    return s;
}

void inorder(Student* root){
    if(root != nullptr){
        inorder(root->left);
        cout << root->studentID << " - " << root->name << " - " << root->dep << endl;
        inorder(root->right);
    }
}

int main(){
    Student* root = nullptr;

    root = insert(root, 3, "Ali", "CS");
    root = insert(root, 2, "Sara", "EE");
    root = insert(root, 1, "Usman", "ME");

    inorder(root);
}
