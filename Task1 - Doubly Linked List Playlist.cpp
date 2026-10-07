#include <iostream>
#include <string>
#include <limits>
using namespace std;

//data storage requirment
struct songNode {
    songNode* prev;
    int id;
    string name;
    string duration;
    songNode* next;
};

//playlist class to mange dll
class playlist {
private:
    songNode* first = nullptr;
    songNode* last = nullptr;
    songNode* current = nullptr;

public:
    //1.add song
    void addSong() {
        songNode* newNode = new songNode();

        cout << "Enter Song ID: ";
        cin >> newNode->id;

        //clear input bufffer so getline dont skip
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Song Name: ";
        getline(cin, newNode->name);

        cout << "Enter Duration (mm:ss): ";
        getline(cin, newNode->duration);

        newNode->prev = nullptr;
        newNode->next = nullptr;

        //if playlist is empty
        if (first == nullptr) {
            first = newNode;
            last = newNode;
            current = newNode;
            cout << "Playlist created and first song added." << endl;
        } 
        else {
            last->next = newNode;
            newNode->prev = last;
            last = newNode;
            cout << "Song added at the end of playlist." << endl;
        }
    }

    //2.delete song
    void deleteSongById() {
        if (first == nullptr) {
            cout << "Playlist is empty." << endl;
            return;
        }

        int delete_id;
        cout << "Enter Song ID to delete: ";
        cin >> delete_id;

        songNode* temp = first;
        while (temp != nullptr && temp->id != delete_id) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Song with given ID not found." << endl;
            return;
        }

        //unlikng left side
        if (temp == first) {
            first = temp->next;
        } else {
            temp->prev->next = temp->next;
        }

        //delinking right side
        if (temp == last) {
            last = temp->prev;
        } else {
            temp->next->prev = temp->prev;
        }

        //update current pointer if deleating playing track
        if (current == temp) {
            current = first;
        }

        delete temp;
        cout << "Song deleted successfully." << endl;
    }

    //3. display foward
    void displayForward() {
        if (first == nullptr) {
            cout << "Playlist is empty." << endl;
            return;
        }

        cout << "Playlist (Forward)" << endl;
        songNode* temp = first;
        while (temp != nullptr) {
            cout << "ID: " << temp->id << " | Name: " << temp->name << " | Duration: " << temp->duration << endl;
            temp = temp->next;
        }
    }

    //4. display backward
    void displayBackward() {
        if (last == nullptr) {
            cout << "Playlist is empty." << endl;
            return;
        }

        cout << "\n--- Playlist (Backward) ---" << endl;
        songNode* temp = last;
        while (temp != nullptr) {
            cout << "ID: " << temp->id << " | Name: " << temp->name << " | Duration: " << temp->duration << endl;
            temp = temp->prev;
        }
    }

    //5. serch song by id
    void searchSongById() {
        if (first == nullptr) {
            cout << "Playlist is empty." << endl;
            return;
        }

        int search_id;
        cout << "Enter Song ID to search: ";
        cin >> search_id;

        songNode* temp = first;
        while (temp != nullptr) {
            if (temp->id == search_id) {
                cout << "\nSong Found!" << endl;
                cout << "ID: " << temp->id << endl;
                cout << "Name: " << temp->name << endl;
                cout << "Duration: " << temp->duration << endl;
                return;
            }
            temp = temp->next;
        }

        cout << "Song with ID " << search_id << " not found." << endl;
    }

    //6.play next 
    void playNext() {
        if (first == nullptr) {
            cout << "Playlist is empty." << endl;
            return;
        }

        if (current == nullptr) {
            current = first;
        } else if (current->next != nullptr) {
            current = current->next;
        } else {
            current = first; // wrap around to start
        }

        cout << "Now Playing: " << current->name << " (ID: " << current->id << ")" << endl;
    }

    //7.play prvious
    void playPrevious() {
        if (first == nullptr) {
            cout << "Playlist is empty." << endl;
            return;
        }

        if (current == nullptr) {
            current = last;
        } else if (current->prev != nullptr) {
            current = current->prev;
        } else {
            current = last; // wrap around to end
        }

        cout << "Now Playing: " << current->name << " (ID: " << current->id << ")" << endl;
    }

    //8.reverse play list
    void reversePlaylist() {
        if (first == nullptr || first == last) {
            cout << "Playlist is empty or has only 1 song." << endl;
            return;
        }

        songNode* temp = nullptr;
        songNode* move = first;

        //swaping prev and next pointers
        while (move != nullptr) {
            temp = move->prev;
            move->prev = move->next;
            move->next = temp;
            move = move->prev; //move moves foward using updated prev
        }

        //swaping first and last
        songNode* oldFirst = first;
        first = last;
        last = oldFirst;

        if (current != nullptr) {
            current = first;
        }

        cout << "Playlist reversed successfully." << endl;
    }

    //print menu option
    void printMenu() {
        cout << "\n===== Playlist Management System =====" << endl;
        cout << "1. Add Song" << endl;
        cout << "2. Delete Song" << endl;
        cout << "3. Display Playlist Forward" << endl;
        cout << "4. Display Playlist Backward" << endl;
        cout << "5. Search Song" << endl;
        cout << "6. Play Next Song" << endl;
        cout << "7. Play Previous Song" << endl;
        cout << "8. Reverse Playlist" << endl;
        cout << "9. Exit" << endl;
        cout << "-------------------------------------" << endl;
        cout << "Enter choice: ";
    }
};

int main() {
    playlist myPlaylist;
    int choice;

    while (true) {
        myPlaylist.printMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                myPlaylist.addSong();
                break;
            case 2:
                myPlaylist.deleteSongById();
                break;
            case 3:
                myPlaylist.displayForward();
                break;
            case 4:
                myPlaylist.displayBackward();
                break;
            case 5:
                myPlaylist.searchSongById();
                break;
            case 6:
                myPlaylist.playNext();
                break;
            case 7:
                myPlaylist.playPrevious();
                break;
            case 8:
                myPlaylist.reversePlaylist();
                break;
            case 9:
                cout << "Exiting playlist system. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Try again." << endl;
                break;
        }
    }

    return 0;
}