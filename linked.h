/* Project 3 - Linked List
 * Ethan Perry
 * Files:     linked.h - This file. Holds the class definition of the object instance that will
                         store the linked list from the user input. It also holds the node struct
                         definition.
            linked.cpp - This file stores the implementation of all the methods defined in the
                         linked.h file.
              main.cpp - This holds the user input loop (menu), calls the correct methods based
                         off of the input, and ends the program when 'q' is entered.

 * Description: This program takes a user inputted, flat csv file that has a space delimiter.
 * Each movie entry has a publication year, audience score (0.0-10.0), Rotten Tomatoes (RT)
 * score (0-100%) and, of course, the films title. The linked list has a sorted order by
 * audience score AND by RT scores. After the linked list is created in the two respective
 * sorted orders, the user is prompted with a suite of options.
    * (m) - A movie can be found by getting the title from the user and searching the database (LL).
      If it is valid, the movie will be outputted, if not, the method will return an error message.
    * (a)/(r) - The user may choose to see the top 15 movies sorted by either audience score or RT
      score which is outputted in a neatly organized table. (a = top15 Audience, r = top15 RT)
    * (x)/(w) - The worst movie by audience or RT scores can be retrieved from the database and outputted.
    * (i) - A movie may be inserted into the database. The user is prompted to enter data for a new entry,
      and it is then inserted into the correct spot for both the Audience and RT sorted order.
    * (u) - Similar to insert, a movie that exists in the list may be updated. The user is prompted
      to enter the title, it is then found in the list. All the data is updated by the user and
      will be put back into the correct order for both sortings according to the input.
    * (d) - Delete allows the user to enter a movie title, and if it is valid, will be deleted from
      the list, and the list will be sorted correctly after removing that title.
    * (q) - quit stops the program.

 * Input: The first and most important input is the correctly formatted csv file. If no such file exists
 * and error message is returned and the program ends. It is then up to the user to select any of the
 * choices outlined above to manipulate / display the data from the input file that is in the sorted list.
 * the final input (assuming nothing invalid haults the program) is q to quit out and end.

 * Output: The output will be any of the various options above with defined output. The top 15 tables for
 * both orders, worst movie by both metrics, output by movie title search, etc. All is described above.
 */

#include <iostream>
using namespace std;

#ifndef P3_LINKED_H
#define P3_LINKED_H

// node struct definition
struct node {
    string title;       // holds the string movie title
    int year;           // holds the year
    float aud, rt;      // holds the audience and RT scores respectively
    node* audNext;      // next pointer for the audience score sorting
    node* rtNext;       // next pointer for the Rotten Tomatoes score sorting
};

// linked list class definition that holds the movie data
class linked {
    node* audHead;      // head pointer for the audience score sorting
    node* rtHead;       // head pointers for the RT score sorting
    int count = 0;      // holds the number of nodes (linked list with 3 nodes means count = 3)
    int maxstr = 0;     // holds the lengths of the longest movie string (used in table output)
public:
    // constructor that reads in the data from user input file and creates the sorted LL
    linked();

    // uses movie string param to find appropriate node to then display it
    bool movieSearch(string) const;

    // finds the top 15 movies based on Aud score and displays them
    void audTop15() const;
    // finds the top 15 movies based on RT score and displays them
    void rtTop15() const;

    // this displays worst movie by Aud score
    void audWorst() const;
    // this displays worst movie by RT score
    void rtWorst() const;

    // this takes a newly created node and inserts it correctly into the list
    void insertAud(node*);
    // insert the new node into the RT ordering
    void insertRT(node*);

    // updates the data of a pre-existing movie in the database
    void update(string);

    // deletes a node from the list and ends with list in correct order
    void deleteNode(string);

    // input new nodes data
    node* nodeData();

    // increments the list counter by 1 (useful in main)
    void listcounter();
};

#endif //P3_LINKED_H