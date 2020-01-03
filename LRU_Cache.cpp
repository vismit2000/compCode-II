// https://leetcode.com/problems/lru-cache/

class LRUCache 
{
    int capacity;
    list <int> recent;
    unordered_map < int, int > cache;
    unordered_map < int, list <int> ::iterator > pos;
    
    void use(int key)
    {
        if(pos.count(key))
            recent.erase(pos[key]);
        
        else if(recent.size() >= capacity)
        {
            cache.erase(recent.back());
            pos.erase(recent.back());
            recent.pop_back();
        }
        
        recent.push_front(key);
        pos[key] = recent.begin();
    }
    
public:
    LRUCache(int capacity) 
    {
        this->capacity = capacity;
    }
    
    int get(int key) 
    {
        if(cache.count(key))
        {
            use(key);
            return cache[key];
        }
        return -1;
    }
    
    void put(int key, int value) 
    {
        use(key);
        cache[key] = value;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
