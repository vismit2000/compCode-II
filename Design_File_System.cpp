// LeetCode Biweekly Contest-7
/*
You are asked to design a file system which provides two functions:

create(path, value): Creates a new path and associates a value to it if possible and returns True. Returns False if the path 
already exists or its parent path doesn't exist.
get(path): Returns the value associated with a path or returns -1 if the path doesn't exist.
The format of a path is one or more concatenated strings of the form: / followed by one or more lowercase English letters. 
For example, /leetcode and /leetcode/problems are valid paths while an empty string and / are not.

Implement the two functions.
*/

class FileSystem {
public:
    string directoryName;
    vector <FileSystem*> subDirectories;
    int value;
    
    FileSystem() 
    {
        directoryName = "";
        subDirectories.clear();
        value = -1;
    }
    
    bool create(string path, int value) 
    {
        path = path.substr(1);
        size_t index = path.find("/");
        
        if(index == string::npos)
        {
            FileSystem *file = new FileSystem();
            file->directoryName = path;
            file->value = value;
            subDirectories.push_back(file);
            return true;
        }
        else
        {
            for(FileSystem *file : subDirectories)
            {
                if(file->directoryName == path.substr(0, index))
                {
                    return file->create(path.substr(index), value);
                }
            }
        }
        return false;
    }
    
    int get(string path) 
    {
        if(path == "")
            return -1;
        path = path.substr(1);
        size_t index = path.find("/");
        
        if(index == string::npos)
        {
            for(FileSystem *file : subDirectories)
            {
                if(file->directoryName == path)
                    return file->value;
            }
        }
        else
        {
            for(FileSystem *file : subDirectories)
            {
                if(file->directoryName == path.substr(0, index))
                    return file->get(path.substr(index));
            }     
        }   
        return -1;
    }
};

/**
 * Your FileSystem object will be instantiated and called as such:
 * FileSystem* obj = new FileSystem();
 * bool param_1 = obj->create(path,value);
 * int param_2 = obj->get(path);
 */
