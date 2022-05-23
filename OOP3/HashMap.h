#include <vector>

template<typename K, typename V>
class Pair {
public:
    K key;
    V value;
    Pair() = default;
    bool operator==(Pair const & that) {
        return (key == that.key && value == that.value);
    }
    Pair(K kluch, V znacheniye): key(kluch), value(znacheniye) {}
};

template<typename K, typename V>
class Pair_list {
public:
    std::vector<Pair<K, V>> Pairs;
    Pair_list() = default;
};

template <typename K, typename V>
class HashMap {
    friend void I_D_S_HashMap(int size);
private:
    std::vector<Pair_list<K, V>> table;
    int size;
    int non_empty_elems = 0;
    int elems = 0;
    int unique_elems = 0;
public:
    explicit HashMap(int N): size(N) {
        for (int i = 0; i < size; ++i) {
            Pair_list<K, V> pairList;
            table.push_back(pairList);
        }
    }
    HashMap(HashMap const & that): HashMap(that.size) {
        for (int i = 0; i < that.table.size(); ++i) {
            for (int j = 0; j < that.table[i].Pairs.size(); ++j) {
                add(that.table[i].Pairs[j].key, that.table[i].Pairs[j].value, false);
            }
        }
    }
    void find_key(K key) {
        std::size_t key_hash = std::hash<K>()(key);
        bool was_found = false;
        for (int i = 0; i < table[key_hash%size].Pairs.size(); ++i) {
            if (table[key_hash%size].Pairs[i].key == key) {
                std::cout << "Key: " << key << " Value: " << table[key_hash%size].Pairs[i].value << std::endl;
                was_found = true;
            }
        }
        if (!was_found) std::cout << "There is no pair with key " << key << std::endl;
    }
    bool find_value(V value) {
        for (int i = 0; i < table.size(); ++i) {
            for (int j = 0; j < table[i].Pairs.size(); ++j) {
                if (table[i].Pairs[j].value == value) return true;
            }
        }
        return false;
    }
    void add(K key, V value, bool rebuilding) {
        std::size_t key_hash = std::hash<K>()(key);
        if (table[key_hash%size].Pairs.size() == 0) {
            if (!find_value(value)) unique_elems++;
            Pair<K, V> pair(key, value);
            table[key_hash%size].Pairs.push_back(pair);
            elems++;
            non_empty_elems++;
            if (((float)non_empty_elems)/((float)size) >= 0.75 && rebuilding) rebuild();
        }
        else {
            bool changed = false;
            for (int i = 0; i < table[key_hash%size].Pairs.size(); ++i) {
                if (table[key_hash%size].Pairs[i].key == key) {
                    if (!find_value(value)) unique_elems++;
                    V temp = table[key_hash%size].Pairs[i].value;
                    table[key_hash%size].Pairs[i].value = value;
                    changed = true;
                    if (!find_value(temp)) unique_elems--;
                }
            }
            if (!changed) {
                if (!find_value(value)) unique_elems++;
                Pair<K, V> pair(key, value);
                table[key_hash%size].Pairs.push_back(pair);
                elems++;
            }
        }
    }
    void remove(K key) {
        std::size_t key_hash = std::hash<K>()(key);
        for (int i = 0; i < table[key_hash%size].Pairs.size(); ++i) {
            if (table[key_hash%size].Pairs[i].key == key) {
                V temp = table[key_hash%size].Pairs[i].value;
                table[key_hash%size].Pairs.erase(table[key_hash%size].Pairs.cbegin()+i);
                if (!find_value(temp)) unique_elems--;
                elems--;
                if (table[key_hash%size].Pairs.size() == 0) non_empty_elems--;
            }
        }
    }
    void rebuild() {
        HashMap<K, V> temp = *this;
        size *= 2;
        for (int i = 0; i < table.size(); ++i) {
            for (int j = 0; j < table[i].Pairs.size(); ++j) {
                table[i].Pairs.pop_back();
            }
        }
        for (int i = 0; i < size/2; ++i) {
            Pair_list<K, V> pairList;
            table.push_back(pairList);
        }
        non_empty_elems = 0;
        elems = 0;
        unique_elems = 0;
        for (int i = 0; i < temp.table.size(); ++i) {
            for (int j = 0; j < temp.table[i].Pairs.size(); ++j) {
                add(temp.table[i].Pairs[j].key, temp.table[i].Pairs[j].value, false);
            }
        }
    }
    int get_elems() {
        return elems;
    }
    int get_unique_elems() {
        return unique_elems;
    }

class Iterator: public std::iterator<std::input_iterator_tag, std::vector<Pair_list<K, V>>> {
    public:
        explicit Iterator(std::vector<Pair_list<K, V>> table1, Pair<K, V> & pair1, int i, int j): table(table1), pair(pair1), i(i), j(j){}
        V & operator*() {
            return pair.value;
        }
        Iterator & operator++() {
            if (j < table[i].Pairs.size() - 1) {
                j++;
                pair = table[i].Pairs[j];
                return *this;
            }
            else {
                i++;
                while (table[i].Pairs.empty()) {
                    i++;
                    if (i >= table.size()) {
                        Pair<K, V> temp(-1, -1);
                        this->pair = temp;
                        return *this;
                    }
                }
                j = 0;
                pair = table[i].Pairs[j];
                return *this;
            }
        }
        bool operator==(Iterator const & that) const {
            return pair == that.pair;
        }
        bool operator!=(Iterator const & that) const {
            return !(*this == that);
        }
    private:
        std::vector<Pair_list<K, V>> table;
        Pair<K, V> & pair;
        int i, j;
    };

    Iterator begin() {
        int temp;
        for (int i = 0; i < table.size(); ++i) {
            if (!table[i].Pairs.empty()) {temp = i;break;}
        }
        return Iterator(table, table[temp].Pairs[0], temp, 0);
    }
    Iterator end() {
        if (elems <= 1) return begin();
        int temp_i, temp_j;
        for (int i = table.size()-1; i >= 0; --i) {
            if (!table[i].Pairs.empty()) {temp_i = i;temp_j = table[i].Pairs.size()-1;break;}
        }
        return ++Iterator(table, table[temp_i].Pairs[0], temp_i, temp_j);
    }
    void print_all() {
        for (auto iter = begin(); iter != end() ; ++iter) {
            std::cout << *iter << std::endl;
        }
    }
    ~HashMap() = default;
};

template<typename K, typename V>
void I_D_S_HashMap(int size) {
    HashMap<K, V> hashMap(size);
    char command;
    for (int i = 0; i < size; ++i) {
        std::cin >> command;
        if (command == 'A') {
            K key;
            V value;
            std::cin >> key >> value;
            hashMap.add(key, value, true);
        }
        else if (command == 'R') {
            K key;
            std::cin >> key;
            hashMap.remove(key);
        }
    }
    std::cout << hashMap.get_elems() << " " << hashMap.get_unique_elems();
}

template <typename K, typename V>
class MultiHashMap {
    friend void I_D_S_HashMap(int size);
private:
    std::vector<Pair_list<K, V>> table;
    int size;
    int non_empty_elems = 0;
    int elems = 0;
    int unique_elems = 0;
public:
    explicit MultiHashMap(int N): size(N) {
        for (int i = 0; i < size; ++i) {
            Pair_list<K, V> pairList;
            table.push_back(pairList);
        }
    }
    MultiHashMap(MultiHashMap const & that): MultiHashMap(that.size) {
        for (int i = 0; i < that.table.size(); ++i) {
            for (int j = 0; j < that.table[i].Pairs.size(); ++j) {
                add(that.table[i].Pairs[j].key, that.table[i].Pairs[j].value);
            }
        }
    }
    bool find_key(K key, bool print) {
        std::size_t key_hash = std::hash<K>()(key);
        for (int i = 0; i < table[key_hash%size].Pairs.size(); ++i) {
            if (table[key_hash%size].Pairs[i].key == key) {
                if (print) std::cout << "Key: " << key << " Value: " << table[key_hash%size].Pairs[i].value << std::endl;
                return true;
            }
        }
    }
    bool find_value(V value) {
        for (int i = 0; i < table.size(); ++i) {
            for (int j = 0; j < table[i].Pairs.size(); ++j) {
                if (table[i].Pairs[j].value == value) return true;
            }
        }
        return false;
    }
    void add(K key, V value) {
        std::size_t key_hash = std::hash<K>()(key);
        if (table[key_hash%size].Pairs.empty()) non_empty_elems++;
        Pair<K, V> pair(key, value);
        table[key_hash%size].Pairs.push_back(pair);
        if (((float)non_empty_elems)/((float)size) >= 0.75) rebuild();
    }
    void remove(K key) {
        std::size_t key_hash = std::hash<K>()(key);
        for (int i = table[key_hash%size].Pairs.size()-1; i >= 0; ++i) {
            if (table[key_hash%size].Pairs[i].key == key) {
                table[key_hash%size].Pairs.erase(table[key_hash%size].Pairs.cbegin()+i);
                if (table[key_hash%size].Pairs.empty()) non_empty_elems--;
            }
        }
    }
    void rebuild() {
        HashMap<K, V> temp = *this;
        size *= 2;
        for (int i = 0; i < table.size(); ++i) {
            for (int j = 0; j < table[i].Pairs.size(); ++j) {
                table[i].Pairs.pop_back();
            }
        }
        for (int i = 0; i < temp.table.size(); ++i) {
            for (int j = 0; j < temp.table[i].Pairs.size(); ++j) {
                add(temp.table[i].Pairs[j].key, temp.table[i].Pairs[j].value);
            }
        }
    }
    void get_elems_by_key(K key) {
        for (int i = 0; i < table.size(); ++i) {
            for (int j = 0; j < table[i].Pairs.size(); ++j) {
                find_key(key, true);
            }
        }
    }
    int count_elems_by_key(K key) {
        int count = 0;
        for (int i = 0; i < table.size(); ++i) {
            for (int j = 0; j < table[i].Pairs.size(); ++j) {
                if (find_key(key, false)) count++;
            }
        }
        return count;
    }
    int get_elems() {
        return elems;
    }
    int get_unique_elems() {
        return unique_elems;
    }
    ~MultiHashMap() = default;
};