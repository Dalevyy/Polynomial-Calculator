#include "polynomial.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

/*
Description: Default constructor for the polynomial class
Parameters: None
Return Type: None
*/
polynomial::polynomial()
{
    //By default, degree and head will not contain anything
	degree = -1;
    head = nullptr;
}

/*
Description: Constructor that will deep copy a constant polynomial
object into this polynomial object
Parameters: Constant polynomial object by reference
Return Type: None
*/
polynomial::polynomial(const polynomial& poly)
{   
    node * track;
    node * trackPoly = poly.head;
	this -> degree = poly.degree;
    for(int i = 0; i <= this -> degree; i++)
    {
        if(this -> head == nullptr)
        {
            this -> head = new node;
            this -> head -> link = poly.head -> link;
            this -> head -> coefficient = poly.head -> coefficient;
            track = this -> head;
            trackPoly = trackPoly -> link;
        }
        else
        {
            track -> link = new node;
            track = track -> link;
            track -> link = nullptr;
            track -> coefficient = trackPoly -> coefficient;
            trackPoly = trackPoly -> link;
        }
    }
}

/*
Description: Constructor that will take an array of integers and convert it into
a polynomial object through the use of linked lists
Parameters: An integer array/degree representing the polynomial
Return Type: None
*/
polynomial::polynomial(int * p, int degree)
{
    //Set polynomial's degree to whatever degree was passed to constructor
	this -> degree = degree;
    //Allocate memory to the head node and store p's first value into the head
    head = new node;
    head -> coefficient = p[0];
    head -> link = nullptr;
    
    //Using a tracking node pointer to keep track of which node currently at
    node * track = head;
    //For loop that iterates through the p array
    for(int i = 1; i <= this -> degree; i++)
    {
        node * it = new node;
        //If the head node is the only node currently in the linked list
        if(head -> link == nullptr)
        {
            //Have the head node point to the new node and update tracking pointer
            head -> link = it;
            track = track -> link;
        }
        //If the head node is already pointing to another node
        else
        {
            //Have the current tracking node point to the new node and update pointer
            track -> link = it;
            track = track -> link;
        }
        //Store the current value of the array into the linked list
        it -> coefficient = p[i];
        it -> link = nullptr;
    }
} 

/*
Description: Constructor that takes a constant value and creates a linked
list for it 
Parameters: Integer representing the constant value
Return Type: None
*/	
polynomial::polynomial(int s)
{
    //Set degree to 0
	this -> degree = 0;
    //Allocate memory to a node object and store the constant value into it
    head = new node;
    head -> coefficient = s;
    head -> link = nullptr;
}

/*
Description: Destructor for the polynomial class
Parameters: None
Return Type: None
*/
polynomial::~polynomial()
{
    //Declaring an iteration pointer and having it point to head node first
	node * it = this -> head;
    //While loop to iterate until head pointer is no longer pointing to a node
    while(this -> head != nullptr)
    {
        //Will first have the head pointer point to the next node
        this -> head = this -> head -> link;
        //Then, deallocate memory that the iterator is pointing to
        it -> link = nullptr;
        delete it;
        //Finally, have iterator point to the same memory location as head is
        it = this -> head;
    }
}

/*
Description: Operator* function that will multiply a polynomial object
with another polynomial object
Parameters: Constant polynomial object 
Return Type: Polynomial object
*/
polynomial polynomial::operator*(const polynomial& rhs) const
{
    //Declaring a temporary polynomial object
	polynomial temp;
    //Declaring a node pointer to keep track of current node
    node * track;

    temp.degree = this -> degree + rhs.degree;

    //For loop designed to allocate all the memory needed for the new linked list 
    for(int i = 0; i <= temp.degree; i++)
    {
        //If statement that will check if a head node is present in the linked list
        if(temp.head == nullptr)
        {
            //Allocate memory to store a head node and make sure track is pointing to it
            temp.head = new node;
            temp.head -> coefficient = 0;
            temp.head -> link = nullptr;
            track = temp.head;
        }
        //If a head node is already present in the linked list
        else
        {
            /*
            Allocate memory and have track's link field point to the new node
            Update track, so it's now pointing to the new node as well
            */
            track -> link = new node;
            track = track -> link;
            track -> coefficient = 0;
            track -> link = nullptr;
        }
    }

    //Resetting track pointer, so it will point back to the head node
    track = temp.head;
    //Declaring a new node pointer that will serve as a reset for track pointer
    node * reset = temp.head;

    //Nested for loop that will itereate through both this/rhs linked lists 
    for(node * it1 = this -> head; it1 != nullptr; it1 = it1 -> link)
    {
        for(node * it2 = rhs.head; it2 != nullptr; it2 = it2 -> link)
        {
            /*
            Will set current track coefficient by multiplying it1/it2's current coefficients
            and adding the result to track coefficient
            */
            track -> coefficient += it1 -> coefficient * it2 -> coefficient;
            //Update track, so it's pointing to the next node in the temp polynomial object's list
            track = track -> link;
        }

        /*
        Logic Explanation:

        Let's say n = 0 where n is the current term, and the arrays in main are initially storing
        the coefficients of a polynomial from least to greatest terms. This means that for the nth
        term, we will not have to add any more values to it since we will then be increasing in
        degree value after we complete one iteration of the loop. For example, for n = 0, at most
        two terms should be multiplied together to get that term. This means that we never have to
        access that term again.

        This explains these two lines of code here. You want to make sure track is pointing to next
        node in the temp list (instead of resetting it back to temp.head), and this will be based 
        on where the reset pointer is currently pointing to which will also be updated to the next
        node in the list after each iteration of the loop.
        */

        track = reset -> link;
        reset = reset -> link;
    }

    return temp;
}

/*
Description: Operator* function that will multiply a polynomial
object with an integer value
Parameters: An integer 
Return Type: Polynomial object
*/
polynomial polynomial::operator*(int rhs) const
{
    //Calling the operator*(const polynomial& rhs) function instead
    return *this * polynomial(rhs);
}

/*
Description: Operator+ function designed to add a polynomial object 
to another polynomial object
Parameters: Constant polynomial object 
Return Type: Polynomial object
*/
polynomial polynomial::operator+(const polynomial& rhs) const
{
	polynomial temp;
    //Declaring a node pointer that will keep track of the current node
    node * track;

    if(this -> degree > rhs.degree)
    {
        //Set this degree as temp's degree if it's greater than rhs
        temp.degree = this -> degree;
    }
    else
    {   
        //Else, set rhs's degree as temp's degree if it's greater than this
        temp.degree = rhs.degree;
    }

    //For loop to allocate memory to the linked list for the temp polynomial object
    for(int i = 0; i <= temp.degree; i++)
    {
        //If memory for the head node hasn't been allocated yet
        if(temp.head == nullptr)
        {   
            //Allocate memory to create the head node and make sure track is pointing to it
            temp.head = new node;
            temp.head -> link = nullptr;
            temp.head -> coefficient = 0;
            track = temp.head;
        }
        //If memoery has already been allocated for the head node
        else
        {
            //Allocate memory for the next node and ensure everything is linked to it properly
            track -> link = new node;
            track = track -> link;
            track -> link = nullptr;
            track -> coefficient = 0;
        }
    }

    /*
    Reset track to point to head node again and declare two new pointers, each for their own
    polynomial object
    */
    track = temp.head;
    node * rhsTrack = rhs.head;
    node * thisTrack = this -> head;

    //For loop that will iterate through each node in the newly created linked list
    for(node * it = temp.head; it != nullptr; it = it -> link)
    {   
        //First, checking to see if both rhs/thisTracks haven't reached the end of their list
        if(rhsTrack != nullptr && thisTrack != nullptr)
        {
            //Add the coefficients stored in each node's coefficient together
            track -> coefficient = rhsTrack -> coefficient + thisTrack -> coefficient;
            //Update pointers
            track = track -> link;
            rhsTrack = rhsTrack -> link;
            thisTrack = thisTrack -> link;
        }
        //If the end of the linked list is hit for the right polynomial object
        else if(rhsTrack == nullptr)
        {   
            //Add the coefficient that the left polynomial object is storing into track
            track -> coefficient += thisTrack -> coefficient;
            //update pointers
            track = track -> link;
            thisTrack = thisTrack -> link;
        }
        //If the end of the linked list is hit for this polynomial object
        else
        {
            //Add the coefficient that the right polynomial object is storing into track
            track -> coefficient += rhsTrack -> coefficient;
            //Update pointers
            track = track -> link;
            rhsTrack = rhsTrack -> link;
        }
    }

    return temp;
}

/*
Description: Operator+ function that will add a polynomial object
to an integer value
Parameters: An integer
Return Type: Polynomial object
*/
polynomial polynomial::operator+(int rhs) const
{
    //Calling the operator+(const polynomial& rhs) function instead
	return *this + polynomial(rhs);
}

/*
Description: Operator= function that will deep copy a polynomial object into this polynomial
object aka the result polynomial object in main
Parameters: Constant polynomial object which was derived from a different operator function
Return Type: Constant polynomial object 
*/
const polynomial& polynomial::operator=(const polynomial& rhs)
{
	this -> degree = rhs.degree;

    node * it = this -> head;
    node * del = this -> head;
    //While loop that will run until iterator reaches a null memory location
    while(it != nullptr)
    {   
        //Deallocare memory from the "result" polynomial in main, so a new result can be outputted
        it = it -> link;
        del -> link = nullptr;
        delete del;
        del = it;
    }
    this -> head = nullptr;

    /*
    Declaring two pointers to keep track of each polynomial objects node
    
    rhsTrack tracks the current node of the rhs polynomial object
    thisTrack tracks the current node of the polynomial object getting a deep copy of rhs
    */
    node * rhsTrack, * thisTrack = nullptr;

    //For loop to iterate based on this degree
    for(int i = 0; i <= this -> degree; i++)
    {
        //If this linked list doesn't have a head node yet
        if(this -> head == nullptr)
        {
            //Allocate memory for the head node and store the relevant value into it
            this -> head = new node;
            this -> head -> coefficient = rhs.head -> coefficient;
            this -> head -> link = nullptr;
            //Make sure both track pointers are pointing to their respective head nodes
            rhsTrack = rhs.head;
            thisTrack = this -> head;

        }
        //If a head node is already present in the linked list
        else
        {
            //Allocate memory for a new node and have thisTrack then point to it
            thisTrack -> link = new node;
            thisTrack = thisTrack -> link;
            //Make sure rhsTrack is pointing to the next node that will have the correct value
            rhsTrack = rhsTrack -> link;
            //Deep copy rhsTrack's coefficient field into thisTracks's coefficient field
            thisTrack -> coefficient = rhsTrack -> coefficient;
            thisTrack -> link = nullptr;
        }
    }

    return *this;
}

/*
Description: Operator= function that will turn an integer into a polynomial object
Parameters: An integer
Return Type: A constant polynomial object by reference
*/
const polynomial& polynomial::operator=(int rhs)
{
    //Set degree to 0
	this -> degree = 0;
    //Allocate memory to a node object and store the constant value into it
    head = new node;
    head -> coefficient = rhs;
    head -> link = nullptr;

    return *this;
}

/*
Description: Operator- function designed to flip the signs of each coefficient
stored in the polynomial's linked list
Parameters: None
Return Type: Polynomial object
*/
polynomial polynomial::operator-() const
{
    //Calling deep copy constructor  to deep copy this values into new polynomial object
    polynomial temp(*this);
    
    //For loop designed to multiple -1 by each coefficient field in the new linked list
	for(node * it = temp.head; it != nullptr; it = it -> link)
    {
        it -> coefficient *= -1;
    }

    return temp;
}

/*
Description: Operator- function that will subtract one polynomial
object from another polynomial object
Parameters: Constant polynomial object by reference
Return Type: Polynomial object
*/
polynomial polynomial::operator-(const polynomial& rhs) const
{
    polynomial temp;
    node * track = nullptr;

    if(this -> degree > rhs.degree)
    {
        //Set this degree as temp's degree if it's greater than rhs
        temp.degree = this -> degree;
    }
    else
    {   
        //Else, set rhs's degree as temp's degree if it's greater than this
        temp.degree = rhs.degree;
    }
	//For loop to allocate memory to the linked list for the temp polynomial object
    for(int i = 0; i <= temp.degree; i++)
    {
        //If memory for the head node hasn't been allocated yet
        if(temp.head == nullptr)
        {   
            //Allocate memory to create the head node and make sure track is pointing to it
            temp.head = new node;
            temp.head -> link = nullptr;
            temp.head -> coefficient = 0;
            track = temp.head;
        }
        //If memory has already been allocated for the head node
        else
        {
            //Allocate memory for the next node and ensure everything is linked to it properly
            track -> link = new node;
            track = track -> link;
            track -> link = nullptr;
            track -> coefficient = 0;
        }
    }

    //Reset tracking pointer and declare two new tracking pointers to use
    track = temp.head;
    node * rhsTrack = rhs.head;
    node * thisTrack = this -> head;

    //For loop that iterates through each node in the linked list 
    for(node * it = temp.head; it != nullptr; it = it -> link)
    {   
        //First, checking to see if both rhs/thisTracks haven't reached the end of their list
        if(rhsTrack != nullptr && thisTrack != nullptr)
        {
            //Subtract rhs's coefficient field from thisTrack's coefficient field
            track -> coefficient = thisTrack -> coefficient - rhsTrack -> coefficient;
            //Update pointers
            track = track -> link;
            rhsTrack = rhsTrack -> link;
            thisTrack = thisTrack -> link;
        }
        //If the end of the linked list is hit for the right polynomial object
        else if(rhsTrack == nullptr)
        {   
            /*
            Add the coefficient that the left polynomial object is storing into track. You do not
            need to subtract here since it's on the left side of the subtraction symbol
            */
            track -> coefficient = thisTrack -> coefficient;
            //update pointers
            track = track -> link;
            thisTrack = thisTrack -> link;
        }
        //If the end of the linked list is hit for this polynomial object
        else
        {
            //Subtract the coefficient that the right polynomial object is storing into track
            track -> coefficient -= rhsTrack -> coefficient;
            //Update pointers
            track = track -> link;
            rhsTrack = rhsTrack -> link;
        }
    }

    return temp;
}
	
/*
Description: Operator- function that will subtract an integer 
from a polynomial object
Parameters: An integer
Return Type: Polynomial object
*/
polynomial polynomial::operator-(int rhs) const
{
    //Calling operator-(const polynomial& rhs) function instead
	return *this - polynomial(rhs);
}

/*
Description: Operator<< function that will output a polynomial object in the form
that is more appropriate for a polynomial(so ax^n + bx^n-1... etc.)
Parameters: Ostream object alongside a constant polynomial object
Return Type: Ostream object by reference
*/
ostream& operator<<(ostream& out, const polynomial& rhs)
{ 
    //Declaring two pointers that will be used to access node coefficient fields
    polynomial::node * track = rhs.head;
    polynomial::node * tail = rhs.head;

    //While loop designed to find the tail pointer of rhs's linked list
    while(tail -> link != nullptr)
    {   
        //Will update tail pointer until tail -> link isn't pointing to anything
        tail = tail -> link;
    }

    //For loop that will iterate through each node in rhs's linked list
    for(int i = rhs.degree; i >= 0; i--)
    {
        //If the tail pointer is pointing to the head node (end of output)
        if(rhs.head == tail)
        {   
            //Output either a negative or plus sign based on coefficient stored in tail
            if(tail -> coefficient < 0 && i != rhs.degree)
            {
                out << " - ";
            }
            else if(i != rhs.degree)
            {
                out << " + ";
            }
            //Output the absolute value of tail's coefficient and then break out of the loop
            out << abs(tail -> coefficient) << " ";
            break;
        }

        //While loop that will iterate until track's link field is pointing to the tail
        while(track -> link != tail)
        {
            /*
            Track is needed so the tail pointer can point to the previous node since 
            the linked list needs to be printed backwards
            */
            track = track -> link;
        }

        //First, checking to see if tail is not storing anything in its coefficient field
        if(tail -> coefficient == 0)
        {
            //If it's not storing a value, then update the pointers and go to next iteration
            tail = track;
            track = rhs.head;
            continue;
        }

        //Second, checking to see if a 1 is stored in tail's coefficient field
        if(abs(tail -> coefficient) == 1)
        {
            //If -1 is stored, then output just a - sign without the 1
            if(tail -> coefficient == -1)
            {   
                //If statements here because I care about additional whitespace LOL
                if(i == rhs.degree)
                {
                    out << "-";
                }
                else
                {
                    out << " - ";
                }
            }
            //Else, just output a positive sign when it's not the first term being outputted)
            else if(i != rhs.degree)
            {
                out << " + ";
            }
        }

        //Third, checking to see if tail is storing a negative value
        else if(tail -> coefficient < 0)
        {   
            //If it is, then check if it's the first iteration of the loop
            if(i == rhs.degree)
            {
                //Print out coefficient without adding a negative sign
                out << tail -> coefficient;
            }
            //If it's not the first iteration of the loop
            else
            {
                //Print out a negative sign first, then print out the coefficient's absolute value
                out << " - " << abs(tail -> coefficient);
            }
        }

        //If tail isn't storing a negative value, then it's storing a positive value
        else
        {   
            //Checking to see if this is the loop's first iteration
            if(i == rhs.degree)
            {
                //Print out coefficient without a plus 
                out << tail -> coefficient;
            }
            //If it's not the first iteration
            else
            {
                //Print out a plus sign first, then print out the coefficient's absolute value
                out << " + " << tail -> coefficient;
            }
        }

        //Lastly, checking to see if tail coefficient isn't 0, so an x can be printed out
        if(tail -> coefficient != 0)
        {
            //If the loop is at its second to last iteration
            if(i == 1)
            {
                //Print out an x without a exponent
                out << "x";
            }
            //For all other iterations
            else
            {
                //Print out an x with an exponent
                out << "x^" << i;
            }
        }

        //Update pointers 
        tail = track;
        track = rhs.head;
    }

    return out;
}

/*
Description: Friend operator+ function that will add an 
integer with a polynomial object
Parameters: An integer and a constant polynomial object by 
reference
Return Type: Polynomial object
*/
polynomial operator+(int lhs, const polynomial& rhs)
{
    //Calling operator+(const polynomial& rhs) function instead
	return polynomial(lhs) + rhs;
}

/*
Description: Friend operator* function that will multiply
an integer with a polynomial object
Parameters: An integer and a constant polynomial object 
by reference
Return Type: Polynomial object
*/
polynomial operator*(int lhs, const polynomial& rhs)
{
    //Calling operator*(const polynomial& rhs) function instead
	return polynomial(lhs) * rhs;
}

/*
Description: Friend operator- function that will subtract
a polynomial object from an integer
Parameters: An integer and a constant polynomial object
by reference
Return Type: Polynomial object
*/
polynomial operator-(int lhs, const polynomial& rhs)
{
    //Calling operator-(const polynomial& rhs) function instead
	return polynomial(lhs) - rhs;
}
