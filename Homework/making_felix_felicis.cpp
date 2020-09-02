#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Room {
    Room(int label) : label(label), parent_count(0), neighbors() {}
    int label;
    int parent_count;
    vector<int> neighbors;
};

class Cave {
public:
    // Room comparison functor
    class CompRoom {
    public:
        bool operator()(Room* a, Room* b) { return a->label > b->label; }
    };

    // Construct a vector of pointers to rooms
    Cave(int num_of_room) : room_list() {
        for (int i = 0; i < num_of_room; ++i) {
            room_list.push_back(new Room(i + 1));
        }
    };

    // Add a neighbor to a room
    void add_neighbor(int start, int end) {
        room_list[start - 1]->neighbors.push_back(end);
        room_list[end - 1]->parent_count++;
    }

    vector<int> topsort() const {
        priority_queue<Room*, vector<Room*>, CompRoom> min_heap;
        for (Room* roomp : room_list) {
            if (roomp->parent_count == 0) {
                min_heap.push(roomp);
            }
        }

        vector<int> result;

        while (!min_heap.empty()) {
            result.push_back(min_heap.top()->label);
            vector<int> neighbors = min_heap.top()->neighbors;
            min_heap.pop();
            for (int w : neighbors) {
                --room_list[w - 1]->parent_count;
                if (room_list[w - 1]->parent_count == 0) {
                    min_heap.push(room_list[w - 1]);
                }
            }
        }

        if (result.size() < room_list.size()) {
            return vector<int>{-1};
        }

        return result;
    }

    // Destructor
    ~Cave() {
        for (Room* roomp : room_list) {
            delete roomp;
        }
    }

private:
    vector<Room*> room_list;
};

int main() {
    int num_of_room, num_of_passage;
    cin >> num_of_room >> num_of_passage;

    Cave cave(num_of_room);
    int start, end;

    // add a neighbor to a room after reading each line
    for (int i = 0; i < num_of_passage; ++i) {
        cin >> start >> end;
        cave.add_neighbor(start, end);
    }

    for (int i : cave.topsort()) {
        cout << i << " ";
    }
    cout << endl;
}
