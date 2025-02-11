#include <iostream>
#include "linked.h"
using namespace std;

int main() {

    // declare input character
    char inp;
    // create a linked object called list (creates a linked list from input file)
    linked list;

    // needed to grab the \n character after file name input
    cin.get();

    // input loop
    do {
        cout << "---------Menu------------------------------------" << endl;
        cout << "m - Search by movie title"                         << endl;
        cout << "a - List top 15 movies by Audience score"          << endl;
        cout << "r - List top 15 movies by Rotten Tomatoes score"   << endl;
        cout << "x - Display worst movie by Audience score"         << endl;
        cout << "w - Display worst movie by Rotten Tomatoes score"  << endl;
        cout << "i - Insert a new movie into the database"          << endl;
        cout << "u - Update a movie in the database"                << endl;
        cout << "d - Delete a movie in the database"                << endl;
        cout << "q - Quit"                                          << endl;
        cout << "-------------------------------------------------" << endl;
        cout << ">";        // prompt user
        cin.get(inp);       // get the input
        cin.get();          // get the '\n' character
        cout << endl;       // new line before other output

        // if input is m, call movie search
        if (inp == 'm'){
            // get the movie name from user
            string name;
            cout << "Enter movie title:";
            getline(cin, name, '\n');

            // go search for it with this method
            list.movieSearch(name);
        }
        // else if it is for aud Top 15, call that
        else if (inp == 'a'){
            list.audTop15();
        }
        // call rtTop15
        else if (inp == 'r'){
            list.rtTop15();
        }
        // call audience worst score
        else if (inp == 'x'){
            list.audWorst();
        }
        // call rt worst score
        else if (inp == 'w'){
            list.rtWorst();
        }

        // insert new movie, fill new node struct first
        else if (inp == 'i'){
            // declare temp node pointer
            node* temp = new node;

            /// enter in the data for that node
            // get the title
            string inputTitle;
            cout << "Enter movie title:";
            getline(cin, inputTitle, '\n');

            // it will point to a newly created node
            temp = list.nodeData();
            temp->title = inputTitle;

            // call the insert method with this new temp node
            list.insertAud(temp);
            list.insertRT(temp);

            // update count
            list.listcounter();

            // get new line character
            cin.get();
        }

        // delete a node
        else if (inp == 'd') {
            // get movie title from user
            string name;
            cout << "Enter movie title:";
            getline(cin, name, '\n');

            // call this method to prompt user to enter movie title. The method will display
            // the movie data, put the curTitle pointer there, and return here
            bool valid = list.movieSearch(name);

            // if it was a valid movie input
            if (valid) {
                // ask if they actually want to delete it
                cout << "Do you want to delete this movie (y/n):";
                char ans;
                cin.get(ans);
                cin.get();

                // delete that node
                if (ans == 'y' || ans == 'Y') {
                    list.deleteNode(name);
                }
            }
        }

        // update a current movie by title and then re-insert updated node
        else if (inp == 'u'){
            // get movie title from user
            string name;
            cout << "Enter movie title:";
            getline(cin, name, '\n');

            // call this method to prompt user to enter movie title. The method will display
            // the movie data, put the curTitle pointer there, and return here
            bool valid = list.movieSearch(name);

            // if they wish to continue, call the update method
            if (valid){
                // with the curTitle pointer in the accurate spot, the update function will be
                // called (delete the node at curTitle), then insert is called in update method
                list.update(name);
                // takes in \n character
                cin.get();
            }

        }

        // else it was invalid input
        else if (inp != 'q') {
            cout << "Invalid input, try again" << endl;
        }

    } while(inp != 'q');

    return 0;
}
