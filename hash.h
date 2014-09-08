#include <vector>
#include <functional>
#include <utility>
#include <algorithm>

using namespace std;

template <typename Key, typename Obj>
class HashTable {
  public:
    // TODO: use next prime number for sizeIn
    HashTable(int sizeIn = 101) : table (sizeIn), size(0) {}
    bool contains(const Key& key) const;
    bool insert(const Key& key, const Obj& obj);
    bool remove(const Key& key);
    Obj& operator[](const Key& key);

  private:
    vector< vector< pair<Key,Obj> > > table;
    int size;

    void clear();
    int myhash(const Key& key) const { 
        static hash<Key> hash_fn; 
        return (hash_fn(key) % table.size()); 
    }
    void rehash();
    typedef typename vector< pair<Key,Obj> >::iterator vecPairIt;
};


template<typename Key, typename Obj>
struct comp {
    comp(const Key& k) : _k(k) {}
    
    bool operator() (const pair<Key,Obj>& p) {
        return (p.first == _k);
    }

    Key _k;
};

template<typename Key, typename Obj>
Obj& HashTable<Key,Obj>::operator[](const Key& key) {
    vector< pair<Key,Obj> >& list = table[ myhash(key) ];

    vecPairIt it = find_if(list.begin(), list.end(), comp<Key,Obj>(key));

    if(it == list.end()) {
        Obj tmp;
        insert(key, tmp);
        return this->operator[](key);
    }
   
    return it->second; 
}

template <typename Key, typename Obj>
bool HashTable<Key,Obj>::insert(const Key& key, const Obj& obj) {
    vector< pair<Key,Obj> >& list = table[ myhash(key) ];
     
    if( find_if(list.begin(), list.end(), comp<Key,Obj>(key)) != list.end() ) {
        return false;
    }
    list.push_back(make_pair(key, obj));

    // TODO: certain load factor should be used
    if(++size > table.size()) {
        rehash();
    }

    return true;
}

template <typename Key, typename Obj>
bool HashTable<Key,Obj>::contains(const Key& key) const {
    const vector< pair<Key,Obj> >& list = table[ myhash(key) ];
    return( find_if(list.begin(), list.end(), comp<Key,Obj>(key)) != list.end() );
}

template <typename Key, typename Obj>
bool HashTable<Key,Obj>::remove(const Key& key) {
    vector< pair<Key,Obj> >& list = table[ myhash(key) ];
    vecPairIt it = find_if(list.begin(), list.end(), comp<Key,Obj>(key));

    // TODO: shrink table down after a certain time
    if(it != list.end()) {
        list.erase(it);
        size--;
        return true;
    }

    return false;
}

template <typename Key, typename Obj>
void HashTable<Key,Obj>::clear() {
    for(size_t i = 0; i < table.size(); ++i) {
        table[i].clear();
    }
    size = 0;
}

template <typename Key, typename Obj>
void HashTable<Key,Obj>::rehash() {
    vector< vector< pair<Key,Obj> > > oldTable = table;
   
    // TODO: resize to the next prime 
    table.resize( 2*table.size() );
    for(size_t i = 0; i < table.size(); ++i)
        table[i].clear();

    size = 0;
    for(size_t i = 0; i < oldTable.size(); ++i) {
        for(vecPairIt it = oldTable[i].begin(); it != oldTable[i].end(); ++it) {
            insert(it->first, it->second);
        }
    }
}
