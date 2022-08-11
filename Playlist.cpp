//
// Student ID: 20522682
//


#include "Playlist.h"



bool Playlist::Song_Entry::set_id(int id){
    if (id >= 0) {
        _id = id;
        return true;
    } else {
        return false;
    }
}

bool Playlist::Song_Entry::set_name(std::string name){
    if (name != "") {
        _name = name;
        return true;
    } else {
        return false;
    }
}

//Playlist::Node::~Node(){
//    Node *currNode = new Node;
//    Node *nextNode = new Node;
//    
//    currNode = this->get_next();
//    nextNode = NULL;
//    
//    while(currNode != NULL){
//        nextNode = currNode->get_next();
//        
//        delete currNode;
//        currNode = nextNode;
//    }
//}
Playlist::Playlist(){
    Node *temp = new Node(Song_Entry(-1, "HEAD"));
    _head = temp;
    _tail = temp;
    _prev_to_current = temp;
    _size = 0;
}

Playlist::~Playlist(){
//    _head->~Node();
    delete _head;
    _size = 0;
}


Playlist *Playlist::insert_at_cursor(const Playlist::Song_Entry &s){
    Node *cur = new Node;
    cur->get_song() = s;
    cur->insert_next(_prev_to_current->get_next());
    
    if (cur->get_song().set_id(s.get_id())) {
        if (_prev_to_current->get_next() == NULL) {
            _prev_to_current->insert_next(cur);
            _tail = _prev_to_current->get_next();
        } else {
            _prev_to_current->insert_next(cur);
        }
        _size++;
        return this;
    } else {
        return NULL;
    }
    
    
}

Playlist *Playlist::push_back(const Song_Entry& s){
    Node *old = _prev_to_current;
    
    if (s.get_id() >= 0){
        _prev_to_current = _tail;
        insert_at_cursor(s);
        _prev_to_current = old;
        
        return this;
    } else {
        return NULL;
    }

}

Playlist *Playlist::push_front(const Song_Entry& s){
    Node *old = _prev_to_current;
    
    if (s.get_name() != ""){
        _prev_to_current = _head;
        insert_at_cursor(s);
        _prev_to_current = old;
        
        return this;
    } else {
        return NULL;
    }

}

Playlist *Playlist::advance_cursor(){
    if (_prev_to_current == _tail){
        return nullptr;
    } else {
        _prev_to_current = _prev_to_current->get_next();
        
        return this;
    }
}


Playlist *Playlist::circular_advance_cursor(){
    if (_prev_to_current->get_next()->get_next() == NULL){
        _prev_to_current = _head;
    } else {
        if (_prev_to_current == _tail){
            return nullptr;
        } else {
            _prev_to_current = _prev_to_current->get_next();
            
            return this;
        }
    }
    return this;
}

Playlist::Song_Entry& Playlist::get_current_song() const{
    if (_prev_to_current->get_next() != NULL){
        return _prev_to_current->get_next()->get_song();
    } else {
        return this->_head->get_song();
    }
}

Playlist *Playlist::remove_at_cursor(){
    
    if (_prev_to_current != _tail){
        _prev_to_current->remove_next();
        _size--;
        
        return this;
    } else {
        return NULL;
    }

}

Playlist *Playlist::rewind(){
    _prev_to_current = _head;
    return this;
}

Playlist *Playlist::clear(){
    
    while (_head->get_next() != NULL) {
        _head->remove_next();
        _size--;
    }
    
    _prev_to_current = _head;
    _tail = _head;
//    _head-> = nullptr;

    return this;
}

Playlist::Song_Entry& Playlist::find_by_id(int id) const{
    Node* stop_point = _head;
    
    for (size_t i = 0; i < _size; i++) {
        if (stop_point->get_next() == nullptr) {
            return this->_head->get_song();
        }
        if (stop_point->get_next()->get_song().get_id() == id) {
            return stop_point->get_next()->get_song();
        }else {
            stop_point = stop_point->get_next();
        }
    }
    return this->_head->get_song();
}

Playlist::Song_Entry& Playlist::find_by_name(string id) const{
    Node* stop_point = _head;
    
    for (size_t i = 0; i < _size; i++) {
        if (stop_point->get_next() == nullptr) {
            return this->_head->get_song();
        }
        if (stop_point->get_next()->get_song().get_name() == id) {
            return stop_point->get_next()->get_song();
        }else {
            stop_point = stop_point->get_next();
        }
    }
    return this->_head->get_song();
}

string Playlist::to_string() const{
    std::string answer = "Playlist: " + std::to_string(_size) + " entries.\n";
    
    Node* stop_point = _head->get_next();
    
    int _num = 0;
    
    while (stop_point != NULL) {
        answer += "{ id: ";
        answer += std::to_string(stop_point->get_song().get_id());
        answer += ", name: ";
        answer += stop_point->get_song().get_name();
        if (stop_point == _prev_to_current){
            if (stop_point == _tail){
                answer += " } [P][T]\n";
                stop_point = stop_point->get_next();
                _num++;
            } else {
                answer += " } [P]\n";
                stop_point = stop_point->get_next();
                _num++;
            }
        } else if (stop_point == _tail){
            answer += " } [T]\n";
            stop_point = stop_point->get_next();
            _num++;
        } else {
            answer += " }\n";
            stop_point = stop_point->get_next();
            _num++;
        }
        if (_num == 25) {
            answer += "...\n";
            break;
        }
    }
    return answer;
}











