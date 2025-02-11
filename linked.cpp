#include <iostream>
#include "linked.h"
#include "fstream"
#include "iomanip"
using namespace std;

/*
 * Constructor: creates a linked list instance
 * Pre: Nothing exists (like the big bang)
 * Post: A linked list instance is created that is a doubly sorted list from the user
 * input file. It is sorted high to low by audience score AND by Rotten Tomatoes score
 */
linked::linked(){
    // get the file name from user
    string filename;
    cout << "Enter movie data file name:";
    cin >> filename;

    // create the infile pointer and open the file
    ifstream infile;
    infile.open(filename);

    // IS FILE VALID???????
    if (!infile) {
        // display error message
        cerr << "Invalid file name was entered.";
        // exit code ends the program
        exit(-1);
    }

    /// else:
    // create new temp pointer to point to new temp node
    node* temp;
    // allocate a node to it
    temp = new node;

    // get initial data point to check if valid data
    infile >> temp->year;

    // while data is valid from file
    while (!infile.eof()) {
        /// get the rest of the data
        infile >> temp->aud;            // gets audience score
        infile >> temp->rt;             // gets rt score
        infile.get();                   // gets space so that title is correct
        getline(infile, temp->title);   // gets the entire movie title

        // make next pointers null (they will be updated in the insert method)
        temp->audNext = nullptr;
        temp->rtNext = nullptr;

        // if it is the first node, make it the head
        if (this->count == 0) {
            // start head pointers
            audHead = temp;
            rtHead = temp;

            // maxstr data member is equal to this nodes title.size()
            maxstr = temp->title.size();
        }

        // else it is not the head pointer, insert to the list
        else {
            // store the longest string length for formatting
            if (temp->title.size() > maxstr)
                maxstr = temp->title.size();

            // insert the temp node
            insertAud(temp);
            // insert temp for RT
            insertRT(temp);
        }
        // update counter (you added an element)
        listcounter();

        // get year of the next data entry to see if it is valid
        temp = new node;
        // get the year for this new node
        infile >> temp->year;
    }

    // close file
    infile.close();
}

/*
 * Movie search: Takes in a string movie title and search the linked list database for the movie.
 * The method loops through the list and is doing a string comparison to see where the title is.
 * If it exists, a neatly formatted output is given to the user with all the nodes' data members
 * being displayed. If the input name is not valid, an error message is returned and the method
 * returns false.
 * * Pre: A linked list object exists, a name is being passed to the method to then search for it.
 * Post: A true or false bool is returned indicating if the title exists in the list.
 * If it does, output the films data members and return true. Else output nothing, return false.
 */
bool linked::movieSearch(const string name) const {
    // declare bracket pointers
    node* cur = audHead;
    // declare search bool
    bool found = false;

    // find the place where the movie title matches the name
    while(!found && cur){
        // while you haven't found the title
        if (cur->title != name){
            cur = cur->audNext;
        }
        else{found = true;}
    }

    // If invalid input, print statement and return out of method
    if (!found){
        // return error message
        cout << "Title Not Found" << endl;
        // return false (break out of the method)
        return false;
    }

    /// else: cur is pointer to the correct movie node

    // length is length of title
    int length = cur->title.size();

    // this gets the max length of the data and makes a string that will span exactly
    // the width of the output table
    string dashes(length+41, '-');

    // format the top title
    cout << endl;
    cout << left << setw(length+2) << "Title";
    cout << left << setw(4) << "Year";
    cout << right << setw(17) << "Audience Score";
    cout << right << setw(18) << "Rotten Tomatoes" << endl;
    cout << dashes << endl;

    // format the data being outputted
    cout << left << setw(length+2) << cur->title;
    cout << left << setw(4) << cur->year;
    cout << right << setw(14) << fixed << setprecision(1) << cur->aud << "/10";
    cout << right << setw(17) << setprecision(0) << cur->rt << "%" << endl;
    cout << dashes << endl << endl;

    // because you found the title,
    return true;
}

/* Aud top 15 output: This method loops through the first 15 elements in the audience sorted part
 * of the list and formats and outputs those values. Note that if the linked list is less than 15
 * values then it will output all of them in sorted order by audience score. This is done by just
 * doing a for loop through the linked list with stopping condition of i < count.
 * Pre:  A list exists in sorted order
 * Post: The top 15 (or less) titles are neatly outputted to a table, sorted by audience score.
 */
void linked::audTop15() const {
    // this stores either 15 or the count of how many element there are.
    int max;
    // declare current pointer that will help loop for output
    node* cur = audHead;

    // if count is less than 15, max is the amount of elements in the list (count)
    if (this->count < 15)
        // max is just the amount of elements
        max = this->count;
    // else the max is 15
    else
        max = 15;

    // use string CTOR to make a string of dashes that formats the table
    // maxstr is the widest the table needs to be + 47 other spaces to be filled in
    string dashes(maxstr+47, '-');

    // format the top of the table
    cout << "Top " << max << " movies ranked by Audience Score:" << endl;
    cout << right << setw(4) << "Rank" << "  ";
    cout << left << setw(maxstr+2) << "Movie";
    cout << left << setw(4) << "Year";
    cout << right << setw(17) << "Audience Score";
    cout << right << setw(18) << "Rotten Tomatoes" << endl;
    cout << dashes << endl;

    // loop to rank the movies and output each line to create the table
    for (int i = 0; i < max; i++){
        // width of 3, right justified, with a ". " after it to format the ranking
        cout << right << setw(3) << i+1 << ".  ";
        // left justify the title with max string + 2 spaces after it
        cout << left << setw(maxstr+2) << cur->title;
        // left justify the year
        cout << left << setw(4) << cur->year;
        // right justify the audiance score, ensure it has only 1 decimal place
        cout << right << setw(14) << fixed << setprecision(1) << cur->aud << "/10";
        // right justify and ensure percent has no decimal places
        cout << right << setw(17) << setprecision(0) << cur->rt << "%" << endl;

        // move to the next node
        cur = cur->audNext;
    }
    // end output table with dashed line and endls
    cout << dashes << endl << endl;
}

/* RT top 15 output: This method loops through the first 15 elements in the rotten tomatoes sorted part
 * of the list and formats and outputs those values. Note that if the linked list is less than 15
 * values then it will output all of them in sorted order by rotten tomatoes score. This is done by just
 * doing a for loop through the linked list with stopping condition of i < count.
 * Pre:  A list exists in sorted order
 * Post: The top 15 (or less) titles are neatly outputted to a table, sorted by rotten tomatoes score.
 */
void linked::rtTop15() const {
    // this stores either 15 or the count of how many element there are (<15).
    int max;
    // declare current pointer that loops through list
    node* cur = rtHead;

    // if count is less than 15, make max equal to max length
    if (this->count < 15)
        // max is just the amount of elements
        max = this->count;
        // else the max is 15
    else
        max = 15;

    // use string CTOR to make a string of dashes to format the table
    string dashes(maxstr+47, '-');

    // format the top
    cout << "Top " << max << " movies ranked by Rotten Tomatoes:" << endl;
    cout << right << setw(4) << "Rank" << "  ";
    cout << left << setw(maxstr+2) << "Movie";
    cout << left << setw(4) << "Year";
    cout << right << setw(17) << "Audience Score";
    cout << right << setw(18) << "Rotten Tomatoes" << endl;
    cout << dashes << endl;

    for (int i = 0; i < max; i++){
        // format each movie, see top15 aud for description of each line
        cout << right << setw(3) << i+1 << ".  ";
        cout << left << setw(maxstr+2) << cur->title;
        cout << left << setw(4) << cur->year;
        cout << right << setw(14) << fixed << setprecision(1) << cur->aud << "/10";
        cout << right << setw(17) << setprecision(0) << cur->rt << "%" << endl;

        // move pointer to the next entry
        cur = cur->rtNext;
    }
    // print out the bottom dashes
    cout << dashes << endl << endl;
}

/* Worst title by Audience score rank, loops to the end of the list and then outputs that node.
 * Does a for loop with know length of the list and stops at the last node to then output the data.
 * Pre:  List exists, in sorted order.
 * Post: Worst title by audience score is outputted to the user.
 */
void linked::audWorst() const {
    // pointer for current pointer that loop through the list
    node* cur = audHead;

    // loop to end of list
    for(int i = 1; i < this->count; i++){
        cur = cur->audNext;
    }
    // go find the movie by the name and that method will output the title formatted
    movieSearch(cur->title);
}

/* Worst title by RT score rank loops to the end of the list and then outputs that node.
 * The formatted table is done by the movie search method.
 * Pre:  List exists in sorted order.
 * Post: Worst title by RT score is outputted using the movie search method.
 */
void linked::rtWorst() const {
    // pointer for current node that will loop through the list
    node* cur = rtHead;

    // loop to end of list
    for(int i = 1; i < this->count; i++){
        cur = cur->rtNext;
    }
    // output the table for the worst title
    movieSearch(cur->title);
}

/* Insert the new node in the audience sorting: With the new node created, insert it into the
 * audience score ordering. You are given the pointer to the new node, so the method loops
 * through the audience sorted part of the list, finds correct spot, and inserts it.
 * Pre: A pointer to the node that needs to be sorted into the list is passed in. That allows
 * that node to be entered correctly and still exist outside of the method. Pass by reference
 * in the sense that the data is changed in the node struct.
 * Post: The new node that is pointed to by the parameter is in the correct sorted order.
 */
void linked::insertAud(node* newNode) {
    // directional nodes for insertion
    node *cur, *prev;

    // initialize for looping through
    cur = audHead;
    prev = nullptr;

    // first node
    if (this->count == 0){
        // do nothing since it is just the head node
    }
    // if you insert at the front
    else if (newNode->aud >= audHead->aud) {
        // new node points to the old head
        newNode->audNext = audHead;
        // head pointer is now at the new node
        audHead = newNode;
    }
    // else you are inserting in the middle/back
    else {
        // you have not found the corect spot
        bool found = false;
        // while you haven't found the correct spot AND cur is not null
        while (!found && cur) {
            // if you are not at the stopping condition, carry on
            if (newNode->aud < cur->aud) {
                // move the pointers
                prev = cur;
                cur = cur->audNext;
            }
            // else stop, you found it!
            else {found = true;}
        }
        // insert the node
        prev->audNext = newNode;
        newNode->audNext = cur;
    }
}

/* Insert the new node in the Rotten Tomatoes sorting: With the new node created, insert it
 * into the RT score ordering. You are given the pointer to the new node, so the method loops
 * through the Rotten Tomatoes sorted part of the list, finds correct spot, and inserts it.
 * Pre: A pointer to the node that needs to be sorted into the list is passed in. That allows
 * that node to be entered correctly and still exist outside of the method. Pass by reference
 * in the sense that the data is changed in the node struct.
 * Post: The new node that is pointed to by the parameter is in the correct sorted order.
 */
void linked::insertRT(node* newNode) {
    // directional nodes for insertion
    node *cur, *prev;

    // initialize for looping through
    cur = rtHead;
    prev = nullptr;

    // first node
    if (this->count == 0){
        // do nothing since you are at the head
    }
    // if you insert at the front
    else if (newNode->rt >= rtHead->rt) {
        // new node rtNext pointer will point to the current head
        newNode->rtNext = rtHead;
        // rtHead will point at the new node
        rtHead = newNode;
    }
    // else you are inserting to the middle/back
    else {
        // you have not found it yet
        bool found = false;
        // while you have not found it AND cur is not null
        while (!found && cur) {
            // if you are not at the stopping condition, carry on
            if (newNode->rt < cur->rt){
                // move the pointers
                prev = cur;
                cur = cur->rtNext;
            }
            // else you found it
            else {found = true;}
        }
        // insert the node
        prev->rtNext = newNode;
        newNode->rtNext = cur;
    }

}

/* Delete node: this takes a string input movie title, searches for it in the list, then
 * if it finds a valid node with that title, deletes it and resorts the list.
 * Pre: Linked list object exists and a string input for the title needing deletion is passed.
 * Post: The list is updated in sorted order with the deleted node no longer there.
 */
void linked::deleteNode(const string inputName){
    /// declare pointers to find correct deletion spots
    node* prev = nullptr;
    node* cur = audHead;

    // declare search bool
    bool found = false;

    // if it is the head item
    if (audHead->title == inputName){
        // head should be deleted, so make head point to the next thing
        audHead = cur->audNext;
    }
    // else not at the head
    else {
        // while you have not found it and cur is not null
        while (!found && cur) {
            // if not at stopping condition, carry on
            if (cur->title != inputName) {
                // move pointers
                prev = cur;
                cur = cur->audNext;
            }
            // else you found it!
            else { found = true; }
        }
        // update list
        prev->audNext = cur->audNext;
    }

    /********************************************************/

    // fix rt list links from deletion
    prev = nullptr;
    cur = rtHead;

    // declare search bool
    found = false;

    // if deleting at the head, make head point to the next thing
    if (rtHead->title == inputName){
        rtHead = cur->rtNext;
    }

    // else not at the head
    else {
        // while you have not found it AND cur is valid
        while (!found && cur) {
            // if not at the stopping condition, carry on
            if (cur->title != inputName) {
                // move pointers
                prev = cur;
                cur = cur->rtNext;
            }
            // else, you found it!
            else { found = true; }
        }

        // relink the list
        prev->rtNext = cur->rtNext;
    }

    // decrement the count since you have one less element now
    this->count--;

    // delete the old pointer
    delete cur;
}

/* Update: This method is linked with the delete method. When the user wants to update an entry,
 * it is first found by movie tile search, then deleted, then inserted into the list.
 * This method uses nodeData() to collect the new info, deleteNode to delete the old
 * movie node, and insert methods to resort the list.
 * Pre:  List object and input string name that is being updated.
 * Post: An existing entry has its values updated and is resorted into the list.
 */
void linked::update(const string inputName) {
    // increment the count since you are inserting a new node
    listcounter();

    /// go get the data
    // create new node pointer
    node* temp;
    // this will pointer to the new node being created
    temp = nodeData();
    // this take the current title you are at and copies the title over
    temp->title = inputName;

    // delete node with this name
    deleteNode(inputName);

    // go insert the newly updates node
    insertAud(temp);
    insertRT(temp);
}

/* Node data creates a node instance and fills it with all the member data except for the title.
 * It turns out that the implementation of the title can be done right after this method call
 * throughout the program. It then returns the pointer to that new node.
 * Pre: No relevant pre condition.
 * Post: A node pointer is created, filled with data, and then returned to where it is called.
 */
node* linked::nodeData(){
    // create new node pointer
    node* temp;
    // this will pointer to the new node being created
    temp = new node;

    // collect the data
    cout << "Audience score:";
    cin >> temp->aud;
    cout << "Rotten Tomatoes score:";
    cin >> temp->rt;
    cout << "Release year:";
    cin >> temp->year;

    // make the other pointers null
    temp->audNext = nullptr;
    temp->rtNext = nullptr;

    return temp;
}

/* This updates the count data member. Since it is used in the main input loop */
void linked::listcounter(){
    this->count++;
}