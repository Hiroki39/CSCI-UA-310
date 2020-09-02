#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Room {
    Room() : status(1), parent(), neighbors() {}
    int status;  // 1-Unexplored, 0-Exploring, -1-Explored
    int parent;
    vector<int> neighbors;
};

class Cave {
public:
    // Construct a vector of pointers to rooms
    Cave(int num_of_room) : room_list() {
        for (int i = 0; i < num_of_room; ++i) {
            room_list.push_back(new Room());
        }
    };

    // Add a neighbor to a room
    void add_neighbor(int start, int end) {
        room_list[start - 1]->neighbors.push_back(end);
    }

    // Depth-first search (with call stacks)
    vector<int> dfs(int room_nbr) {
        room_list[room_nbr - 1]->status = 0;  // change the status to exploring
        for (int neighbor : room_list[room_nbr - 1]->neighbors) {
            if (room_list[neighbor - 1]->status == 1) {
                // set the parent of this neighbor
                room_list[neighbor - 1]->parent = room_nbr;
                // explore this neighbor
                vector<int> result = dfs(neighbor);

                if (result.size() > 0) {
                    // if the result vector is not empty
                    return result;
                }
            } else if (room_list[neighbor - 1]->status == 0) {
                int curr_room_nbr = room_nbr;
                vector<int> result;

                // Adding the room numbers in the loop to the vector
                while (curr_room_nbr != neighbor) {
                    result.push_back(curr_room_nbr);
                    curr_room_nbr = room_list[curr_room_nbr - 1]->parent;
                }

                result.push_back(neighbor);
                reverse(result.begin(),
                        result.end());  // reverse the vector to ensure the loop
                                        // is in the correct direction
                return result;
            }
        }
        room_list[room_nbr - 1]->status = -1;  // change the status to explored
        return vector<int>();  // if no loop found, return an empty vector
    }

    // Destructor
    ~Cave() {
        for (Room*& roomp : room_list) {
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

    vector<int> result =
        cave.dfs(1);  // depth-first search the first room to find a loop

    // output the result
    if (result.size() > 0) {
        cout << 1 << endl;
        for (int node : result) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << 0 << endl;
    }
}
