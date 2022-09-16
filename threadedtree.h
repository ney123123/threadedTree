#include <iostream>
using namespace std;

template <class T>
class ThreadedTree{
    
    struct Node{
        T data_;
        Node* left_;
        Node* right_;
        bool leftIsThread;
        bool rightIsThread;
        Node(const T& data=T{},Node* left=nullptr, Node* right=nullptr){
            data_ = data;
            left_ = nullptr;
            right_ = nullptr;
            leftIsThread = true;
            rightIsThread = true;
        }
    };
    Node * root_ = nullptr;
    Node * first_ = nullptr; // smallest node
    void print(const Node* rt, int lvl)const{
        //This function won't be tested, but you may find it useful to implement this so
        //that you can see what the tree looks like.  lvl will allow you to use dashes to
        //better show shape of tree.  Feel free to modify this to print in any way that will
        //help you debug.  Feel free to copy the pretty print function from lab 8 that will draw
        //the tree (though it won't draw threads)
    }

public:
    class const_iterator{
        Node *curr_ = nullptr;
    protected:

    public:
        const_iterator(){
            curr_ = nullptr;
        }
        const_iterator(Node* n){
            curr_ = n;
        }
        
        //find the next node
        // if the right side is a thread, than its is the next node
        // if not, find the most left node in the right side
        const_iterator operator++(int){
            const_iterator temIt = const_iterator(*this);
            Node * tem = curr_;
            if(tem == nullptr){
                return const_iterator(nullptr);
            }
         
                if (tem->rightIsThread)
                {
                    curr_ = tem->right_;
                    return temIt;}
             
                
                tem=tem->right_;
                while (!tem->leftIsThread)
                { tem = tem->left_;}
            curr_ = tem;
           
                return temIt;
        }
        //find the previous node
        // if the left side is a thread, than its is the previous node
        // if not, find the most right node in the left side
        const_iterator operator--(int){
            const_iterator temIt = const_iterator(*this);
            Node * tem = this->curr_;
            
                
                if (tem->leftIsThread)
                {curr_ = tem->left_;
                    return temIt;}
             
                
                tem=tem->left_;
                while (!tem->rightIsThread)
                { tem = tem->right_;}
            this->curr_ = tem;
                return temIt;
        }
        const_iterator operator++(){
            Node * tem = this->curr_;
            
                
                if (tem->rightIsThread)
                { this->curr_ = tem->right_;
                    return const_iterator(tem->right_);}
             
                
                tem=tem->right_;
                while (!tem->leftIsThread)
                { tem = tem->left_;}
            this->curr_ = tem;
                return const_iterator(tem);
        }
      
        const_iterator operator--(){
            Node * tem = this->curr_;
            
                
                if (tem->leftIsThread)
                { this->curr_ = tem->left_;
                    return const_iterator(tem->left_);}
             
                
                tem=tem->left_;
                while (!tem->rightIsThread)
                { tem = tem->right_;}
            this->curr_ = tem;
                return const_iterator(tem);
        }
        const T& operator*() const{
            
                return curr_->data_;
        }
        bool operator==(const const_iterator& rhs) const{
            if(curr_ == nullptr && rhs.curr_ == nullptr)
                return true;
            
            else if(curr_ == nullptr && rhs.curr_ != nullptr)
                return false;
            else if(curr_ != nullptr && rhs.curr_ == nullptr)
                return false;
            else{
                return curr_->data_ == rhs.curr_->data_;}

        }
        bool operator!=(const const_iterator& rhs) const{
            if(curr_ == nullptr && rhs.curr_ == nullptr)
                return false;
            
            else if(curr_ == nullptr && rhs.curr_ != nullptr)
                return true;
            else if(curr_ != nullptr && rhs.curr_ == nullptr)
                return true;
            else{
                return curr_->data_ != rhs.curr_->data_;}

        }
        friend class ThreadedTree;
    };
    class iterator:public const_iterator{
    public:
        iterator():const_iterator(){
            this->curr_ = nullptr;
        }
        iterator(Node* n):const_iterator(){
            this->curr_ = n;
        }
        const T& operator*() const{
            return this->curr_->data_;
        }
        T& operator*(){
            return this->curr_->data_;
        }
        iterator operator++(int){
           
            iterator temIt  = iterator(this->curr_);
            Node * tem = this->curr_;
           
            if(tem == nullptr){
                return iterator(nullptr);
            }
                if (tem->rightIsThread)
                {
                    this->curr_ = tem->right_;
                    return temIt;}
             
                
                tem=tem->right_;
                while (!tem->leftIsThread)
                { tem = tem->left_;}
            this->curr_ = tem;
           
                return temIt;
            
        }
        
        iterator operator--(int){
            iterator temIt  = iterator(*this);
            Node * tem = this->curr_;
            
            
            
                if (tem->leftIsThread)
                {this->curr_ = tem->left_;
                    return temIt;}
            
                tem=tem->left_;
                while (!tem->rightIsThread)
                { tem = tem->right_;}
            this->curr_ = tem;
                return temIt;
        }
        
     
        iterator operator++(){
          
            iterator temIt  = iterator(this->curr_);
            Node * tem = this->curr_;
            
               
                if (tem->rightIsThread == true)
                    
                {this->curr_ = tem->right_;
                    return iterator(tem->right_);}
             
                
                tem=tem->right_;
                while (!tem->leftIsThread)
                { tem = tem->left_;}
            this->curr_ = tem;
           
            
                return iterator(tem);
        }
        iterator operator--(){
            Node * tem = this->curr_;
            
                
                if (tem->leftIsThread)
                {this->curr_ = tem->left_;
                    return iterator(tem->left_);}
             
                
                tem=tem->left_;
                while (!tem->rightIsThread)
                { tem = tem->right_;}
            this->curr_ = tem;
                return iterator(tem);
        }

        friend class ThreadedTree;
    };

    ThreadedTree(){
    }
    void printInOrder(Node* subroot)const{
        if(subroot){
            printInOrder(subroot->left_);
            std::cout << subroot->data_ << " ";
            printInOrder(subroot->right_);
        }
    }
    void insert(const T& data){
        
        Node *tem = root_;
            Node *par = nullptr;
        
        //finding the suitable place for the new element, and also locate its parent node
            while (tem != nullptr)
            { par = tem;
                if (data < tem->data_)
                {
                    if (!tem->leftIsThread)
                        tem = tem->left_;
                    else
                        break;
                }
                else
                       {
                           if (!tem->rightIsThread)
                               tem = tem->right_;
                           else
                               break;
                       }
                   }Node *tmp = new Node(data);
                // if it is the first node, put it in root_
                   if (par == nullptr)
                   {
                       
                       tmp->left_ = nullptr;
                       tmp->right_ = nullptr;
                       root_ = tmp;
                   }
        //if it is the right child of the parent node,
                   else if (data < par->data_)
                   {
                       tmp->right_ = par;
                       if(par->left_ == nullptr){  // if the parent was the smallest
                           tmp->left_ = nullptr;
                       }
                       else{// get parent's left thread, put it in child's left side
                       tmp->left_ = par->left_;
                       }
                       
                       par->leftIsThread = false;
                       par->left_ = tmp;
                   }
                   else
                      {
                          tmp->left_ = par;
                          if(par->right_ == nullptr){// if the parent was the biggest
                              tmp->right_ = nullptr;
                          }
                          else{// get parent's right thread, put it in child's right side
                          tmp->right_ = par->right_;
                          }
                          
                          par->rightIsThread = false;
                          par->right_ = tmp;
                      }
       
        // update the first_
        if(first_ == nullptr || tmp->data_ < first_->data_ ){
            first_ = tmp;
        }
        
        
    }
   // recursively finding the matching, if not match return end()
    iterator find(const T& key){
        return find(key,root_);
    }
    iterator find(const T& key,Node* sub){
        if(sub!= nullptr){
            if(sub->data_< key  && !sub->rightIsThread){
                return find(key,sub->right_);
            }
            else if(key< sub->data_ && !sub->leftIsThread){
                return find(key,sub->left_);
            }
            else if(key == sub->data_){
                return iterator(sub);
            }
            else {
                return end();
            }
        }
        return end();
        
    }
   // recursively finding the matching, if not match return end()
    const_iterator find(const T& key) const{
    
        return find(key,root_);
    }
    
    const_iterator find(const T& key,  Node* sub) const{
        if(sub!= nullptr){
            if(sub->data_< key  && !sub->rightIsThread){
                return find(key,sub->right_);
            }
            else if(key< sub->data_ && !sub->leftIsThread){
                return find(key,sub->left_);
            }
            else if(key == sub->data_){
                return const_iterator(sub);
            }
            else {
                return cend();
            }
        }
        return cend();
    }
    //create a iterator have the first node
    iterator begin(){
        if(!root_){
            return iterator(nullptr);
        }
        return iterator(first_);
    }
    //create a iterator where have a node that left point to the last node in the tree
    iterator end(){
        if(!root_){
            return iterator(nullptr);
        }
        Node *biggest = root_;
        while(biggest->right_ != nullptr){
            biggest = biggest->right_;
        }
        Node *tem = new Node();
        tem->left_ = biggest;
        return iterator(tem);
    }
    //create a iterator have the first node
    const_iterator cbegin()const{
        if(!root_){
            return const_iterator(nullptr);
        }
        return const_iterator(first_);
    }
    //create a iterator where have a node that left point to the last node in the tree
    const_iterator cend() const{
        if(!root_){
            return const_iterator(nullptr);
        }
        Node *biggest = root_;
        while(biggest->right_ != nullptr){
            biggest = biggest->right_;
        }
        Node *tem = new Node();
        tem->left_ = biggest;
        return const_iterator(tem);
    }
    void print() const{
        //this function won't be tested, but you may wish to implement this
        //to help you debug.  You won't need to implement this for submission
    }
    
    //recurively count node
    int size() const{
        int sum = 0;
        
        return size(root_,sum);

    }
    int size(Node* sub,int& sum) const{
        if(sub != nullptr){
          
            sum++;
                    if(  sub->right_ != nullptr && !sub->rightIsThread){
                        sum = size(sub->right_, sum);
                         
                    }
                    if(sub->left_ != nullptr && !sub->leftIsThread){
                        sum = size(sub->left_, sum);
                        
                    }
        }
        else{
            return 0;
        }
        return sum;
        

    }
    //check if root_ is empty
    bool empty() const{
        return root_ == nullptr;
    }
    
    
    //delete every node by iteration
    ~ThreadedTree(){
        
        Node* tem = first_;
        iterator it = iterator(tem);
        while(it.curr_ != nullptr){
            Node *tem2 = it.curr_;
            \
            it++;
            
            delete tem2;
        }
        
    }
};
