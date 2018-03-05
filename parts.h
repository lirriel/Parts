// parts.h

#ifndef _PARTS_H_
#define _PARTS_H_

#include <vector>
#include <map>
#include <string>

// using namespace std;


//**************** Part ****************
class Part  {
private:
    typedef std::map<Part*, int> NodeToCount;

public:
	std::string name;       // name of a part
    Part* parent;           // part's parent
	NodeToCount subparts;   // subparts of the current part with their number

    /**
     * Constructor with no parameters
     */
    Part() : parent(0), name("") {};

    /**
     * Constructor
     * @param n name of a part
     */
	Part(const std::string& n) : parent(0), name(n) {};


    /**
     * Current destructor does nothing as all parts are deleted in a NameContainer
     */
    ~Part() {}


    /**
     *
     * @param p
     */
    void setParent(Part* p)
    {
        parent = p;
    }

    /**
     * Copy constructor creates a copy of a \c other object
     */
    Part( const Part& other ) : name( other.name ), parent( other.parent ), subparts(other.subparts) { }

    /**
     * Assignment operation
     * @return creates a copy of a \c other object
     */
    Part& operator=( const Part& other );

    /**
     * Prints out the information about subparts of this part
     */
	void describe();

    /**
     * Counts amount of parts \c p
     * @param p supposed to be current part's subpart
     * @return number of parts \c p in a subtree of the current part ( 0 if not a child )
     */
	int countHowMany(const Part* p); // добавить родителя
};


//**************** NameContainer ****************
class NameContainer  {
public:
    /**
     * Constructor
     */
	NameContainer() {};

    /**
     * Destructor frees memory for all parts created in a map
     */
    ~NameContainer();

    /**
     * Copy constructor creates a copy of a \c other object
     */
    NameContainer( const NameContainer& other) : _nameMap(other._nameMap) { }

    /**
     * Assignment operation
     * @return creates a copy of a \c other object
     */
    NameContainer&operator=(const NameContainer& other);

    /**
     * Adds new part to \c _nameMap and as a subpart to another part
     * @param part supposed to be in a _nameMap already
     * can be absent so is added too in that case
     * @param quantity number of \c subpart
     * @param subpart new part to be added
     */
    void addPart(const std::string& part, int quantity, const std::string& subpart);

    /**
     * Find a part in a \c _nameMap by its name or create a new part if not present
     * @return part with a name \c name
     */
    Part* lookup(const std::string& name);
        
    // You can add some methods here 
        
private:
    typedef std::map<std::string, Part*> NameToNode;
    NameToNode _nameMap;                                // list of parts by their names

};

#endif //