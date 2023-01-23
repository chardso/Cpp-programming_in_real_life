    #include<stdio.h> 
     
    int main(int argc, char **argv) 
    { 
    	char sArrInitials[4] = {'\0', '\0', '\0', '\0'}; 
    	 
    	printf("What are your initials?  Enter them here: "); 
    	scanf("%3s", sArrInitials); 
     
    	if(sArrInitials[3] != '\0') 
    		sArrInitials[3] = '\0'; 
     
    	printf("\nNice to meet you, %s!\n", sArrInitials); 
     
    	return(0); 
    }


Explanation:

Line 1: includes the standard io header file which allows for the printf and scanf functions to be used

Line 3–16: defines the main function which is the function called when you type into the command prompt or double click on AskInitials.exe. I will now proceed to break down the main function’s body inside

Line 5: declares and defines/initializes a character array(a string so to speak) called sArrInitials. I used s because it’s a string and Arr because it’s an array Call it whatever you want - as long as it makes some degree of sense. I initialize the array then to all null(‘\0’) values - I’ll explain why in a later line.

Line 6: Blank line - for formatting but unnecessary

Line 7: prints/displays the prompt to the user to the standard output stream(stdout). I could have replaced the printf function with fprintf and given the first parameter as stdout or some other FILE handle, but printf automatically assumes stdout by default.

Line 8: acquires/gets the input as a string, putting it into sArrInitials. The reason I initialized the array to be all nulls at first is because in this line, let’s say the user typed in only 2 characters instead of 3 - maybe they don’t have a middle name? like for me it would be SF if just the first name and last name - In that case, it would read - S…F…(null)…(undefined). The value of %3s in the scanf arguments says to get a string no larger than 3 characters. This way the rest of the string’s array cells after the end of the string will be known - to be null for sure. I guess it’s unnecessary but helps for readability.

Line 9: Blank line - for formatting but unnecessary

Lines 10–11: This tests in case for some odd reason the last character in the array is not null - then it will set it to be null so the string is null terminated as C needs it to be able to be read. This is somewhat unnecessary because scanf will almost always null terminate the string and we also have the initialization to all nulls but I’m extra redundant for a reason and this is not a hard program :-P

Line 12: Blank line - for formatting but unnecessary

Line 13: prints to the standard output(stdout) the initials with some leading text as well. There is a new line character(\n) at the end of the string because if you don’t do that, the command prompt when you exit back to the command line will be immediately after your output so you’d see for my initials:

    Nice to meet you, SF!C:\> 

for a DOS system and the cursor waiting for you to enter a command lol

LIne 14: Blank line - for formatting but unnecessary

Line 15: returns success (0) leaving the main function and exiting the program back to the command prompt.


If one were to refactor this program, they would probably put some parts of this into supplemental custom user defined functions although the functions would be so small (1–3 lines + braces and function declaration) that it makes little sense. It might be like this:

void clearInitials(char *sArrInitials) 
{ 
	if(sArrInitials != '\0') 
		{ 
		free(sArrInitials); 
		 
		sArrInitials = '\0'; 
		} 
} 
 
void displayInitials(const char *sArrInitials) 
{ 
	printf("\nNice to meet you, %s!\n", sArrInitials); 
} 
 
void displayPrompt() 
{ 
	printf("What are your initials?  Enter them here: "); 
} 
 
char *getInitials() 
{ 
	char *sArrInitials = calloc(4, sizeof(char)); 
 
	scanf("%3s", sArrInitials); 
 
	return(validateInitials(sArrInitials)); 
} 

Then the main function would be as such:
    int main(int argc, char **argv) 
    { 
    	char *sArrInitials = '\0'; 
    	 
    	displayPrompt(); 
    	sArrInitials = getInitials(); 
     
    	displayInitials(sArrInitials); 
    	 
    	clearInitials(); 
     
    	return(0); 
    } 

clearInitials tests if the sArrInitials passed to it is null and if not then it frees the memory and sets it to null so it won’t be re-freed multiple times.
displayPrompt just does the printf line
getInitials declares and defines/instantiates it’s local copy of the sArrInitials array using the library function calloc which allocates the memory for the array and then sets every element to null. Then it does the scanf line then returns whatever the validateInitialsfunction returns.
validateInitials does the if statement from lines 10–11 from above and returns the array passed to it after ensuring it’s properly null terminated

After calling each function respectively, clearInitials must be then called to avoid memory leaks and free the memory allocated for the array holding the initials. For the functions calloc and free, the header file stdlib.h will need to be included at the top of the file as well.

One could also create a sort of stepping block to C++ object oriented programming and create a structure in C like this:
    

    typedef struct 
    { 
    	char *msPrompt; 
    	char *msInitials; 
    	char *msInitialsPosttext, *msInitialsPretext; 
    } structInitials;
The typedef creates a sort of alias so whenever the string structInitials is used/seen, it equates exactly to the structure definition. Note, none of the character pointers are defined so they are unknown addresses at this point. The m prefix to the internal variable names stands for “member”

Then we can create a sort of constructor:

    structInitials constructInitialsStructure() 
    { 
    	structInitials objInitials; 
     
    	objInitials.msPrompt = "What are your initials?  Enter them here: "; 
    	objInitials.msInitialsPretext = "\nNice to meet you, "; 
    	objInitials.msInitialsPosttext = "!\n"; 
    	objInitials.msInitials = calloc(4, sizeof(char)); 
     
    	return(objInitials); 
    } 

and a destructor:

    structInitials destructInitialsStructure(structInitials objInitials) 
    { 
    	if(objInitials.msInitials != '\0') 
    		free(objInitials.msInitials); 
     
    	return(objInitials); 
    } 

Now the only problem with these last 2 functions is that they return as tructure which will require the C compiler/runtime to make a temporary copy of the structure before returning and then it’s presumed that whatever called them would set the structure return value to a local variable. Thankfully, the structure isn’t big so copying it should be a piece of cake but it’s bad practice overall but I’m trying to demonstrate how one could make this more towards object oriented programming and C++ while still staying in the confines of the C language.

Now the functions will slightly change and here below is the whole program in the pseudo OOP form:

    #include<stdio.h> 
    #include<stdlib.h> 
     
    typedef struct 
    { 
    	char *msPrompt; 
    	char *msInitials; 
    	char *msInitialsPosttext, *msInitialsPretext; 
    } structInitials; 
     
    structInitials constructInitialsStructure(); 
    structInitials destructInitialsStructure(structInitials objInitials); 
    void displayInitials(const structInitials *ptrInitials); 
    void displayPrompt(const structInitials *ptrInitials); 
    void getInitials(const structInitials *ptrInitials); 
    void validateInitials(const structInitials *ptrInitials); 
     
    structInitials constructInitialsStructure() 
    { 
    	structInitials objInitials; 
     
    	objInitials.msPrompt = "What are your initials?  Enter them here: "; 
    	objInitials.msInitialsPretext = "\nNice to meet you, "; 
    	objInitials.msInitialsPosttext = "!\n"; 
    	objInitials.msInitials = calloc(4, sizeof(char)); 
     
    	return(objInitials); 
    } 
     
    structInitials destructInitialsStructure(structInitials objInitials) 
    { 
    	if(objInitials.msInitials != '\0') 
    		free(objInitials.msInitials); 
     
    	return(objInitials); 
    } 
     
    void displayInitials(const structInitials *ptrInitials) 
    { 
    	printf("%s%s%s", ptrInitials->msInitialsPretext, ptrInitials->msInitials, ptrInitials->msInitialsPosttext); 
    } 
     
    void displayPrompt(const structInitials *ptrInitials) 
    { 
    	printf("%s", ptrInitials->msPrompt); 
    } 
     
    void getInitials(const structInitials *ptrInitials) 
    { 
    	scanf("%3s", ptrInitials->msInitials); 
     
    	validateInitials(ptrInitials); 
    } 
     
    void validateInitials(const structInitials *ptrInitials) 
    { 
    	if(ptrInitials->msInitials[3] != '\0') 
    		ptrInitials->msInitials[3] = '\0'; 
    } 
     
    int main(int argc, char **argv) 
    { 
    	structInitials objInitials = constructInitialsStructure(); 
    	 
    	displayPrompt(&objInitials); 
    	getInitials(&objInitials); 
     
    	displayInitials(&objInitials); 
     
    	destructInitialsStructure(objInitials); 
     
    	return(0); 
    } 

To write this in pure C++, it would be more like:

Initials.h:

    #include<iostream> 
    #include<string> 
     
    using namespace std; 
     
    class Initials 
    { 
    	string msInitials, msPostText, msPreText, msPrompt; 
    public: 
    	Initials(); 
    	Initials(const string &sInitials); 
    	Initials(const string &sPrompt); 
    	Initials(const string &sPrompt, const string &sPreText, const string &sPostText); 
    	Initials(const string &sPrompt, const string &sPreText, const string &sPostText, const string &sInitials); 
    	Initials(const Initials &refInitials); 
    	~Initials(); 
     
    	void displayInitials(); 
    	void displayPrompt(); 
    	void processInitials(); 
     
    	string &getInitials() const; 
    	string &getPostText() const; 
    	string &getPreText() const; 
    	string &getPrompt() const; 
     
    	void setInitials(const string &sInitials); 
    }; 

Initials.cpp:
    #include "Initials.h" 
     
    Initials::Initials()  
    	: 	msPrompt("\nWhat are your initials?  Enter them here: ") 
    	,	msPreText("\nNice to meet you, ") 
    	,	msPostText("!\n") 
    	,	msInitials("") 
    { } 
     
    Initials::Initials(const string &sInitials) 
    	:	msInitials(sInitials) 
    	,	msPrompt("\nWhat are your initials?  Enter them here: ") 
    	,	msPreText("\nNice to meet you, ") 
    	,	msPostText("!\n") 
    { } 
     
    Initials::Initials(const string &sPrompt) 
    	: 	msPrompt(sPrompt) 
    	,	msPreText("\nNice to meet you, ") 
    	,	msPostText("!\n") 
    	,	msInitials("") 
    { } 
     
    Initials::Initials(const string &sPrompt, const string &sPreText, const string &sPostText) 
    	:	msPrompt(sPrompt), msPreText(sPreText) 
    	,	msPostText(sPostText), msInitials("") 
    { } 
     
    Initials::Initials(const Initials &refInitials) 
    	: 	msInitials(refInitials.getInitials()) 
    	,	msPrompt(refInitials.getPrompt()) 
    	,	msPreText(refInitials.getPreText()) 
    	,	msPostText(refInitials(getPostText()) 
    { } 
     
    Initials::~Initials() 
    { | 
     
    void Initials::displayInitials() 
    { 
    	cout << getPreText() << getInitials() << getPostText() << endl; 
    } 
     
    void Initials::displayPrompt() 
    { 
    	cout << getPrompt(); 
    | 
     
    void Initials::processInitials() 
    { 
    	cin >> getInitials(); 
    } 
     
    string &Initials::getInitials() const 
    { 
    	return(msInitials); 
    } 
     
    string &Initials::getPostText() const 
    { 
    	return(msPostText); 
    } 
     
    string &Initials::getPreText() const 
    { 
    	return(msPreText); 
    } 
     
    string &Initials::getPrompt() const 
    { 
    	return(msPrompt); 
    } 
     
    void Initials::setInitials(const string &sInitials) 
    { 
    	msInitials = sInitials; 
    } 
    
    Now let me explain this:

The 5 functions named Initials with various number and in one case type of arguments - are called constructors. The constructor without any arguments is called the default constructor - which would be called if you just did this:

    Initials objInitials; 

without any arguments. It’s important to include one of these for many reasons out of the scope of this discussion as it deals with child classes and that sort. The constructor with the argument of another Initials object as an argument is called a copy constructor. The argument has an ampersand(&) before he argument name because it’s a reference. It’s like a pointer but it’s accessed as if it were a value. In a way it’s an alias to something else so when you access the reference it’s as if you’re accessing the actual value - whereas a pointer is a value holding an address to another value in memory. The copy constructor is used to copy things transparently - like similar to the structure example above how the construct and destruct functions returned value objects of the structure - the C compiler would automatically copy the object. Well C++ also will automatically copy the object unless you have the copy constructor defined but hidden with regard to access, another topic for another time.

The function with the tilde(~) in front of it is called the destructor - It automatically will destroy the object when it goes out of scope or if it was dynamically instantiated, when it’s deleted with the delete statement.

Then you have a series of functions you have already seen - but if you’ll note, they don’t have any return type because nothing needs to be returned as everything is kept in the Initials class. The only function in that group of 3 that you don’t know probably is processInitials, which does the same thing as the scanf function from above but in the C++ method. We don’t need to hard code the array to be a specific length. std::string objects automatically resize so you’ll never have the pesky errors going past the end of an array bounds with the strings of that type. Sure someone could be a smartass and enter instead of initials, the Declaration of independence or the United States Constitution or some 300 page novel even but it’ll work here unless you want to add code to restrict that in which case you could put an if statement after that line to test the length of the string and either send the user back to re-enter or just cut it off after that point where you want it done.

Finally we have the getters and a setter - The setter isn’t used I just noticed but I’ll keep it in for good measure because you could use it. You would have to create a local string variable in processInitials and then call setInitials passing in the local string variable - it’s that simple.

If you note in the header file for the class, there is a public: keyword - In C++ classes are by default private - so those variables are inaccessible from outside the class and you must use the getters and setters to access them.

Now what uses the Initials class though? We have 2 choices - either directly from the main function - or - create another class to go between. I’m going to do the 2nd choice:

App.h:
#incude "initials.h" 
 
class App 
{ 
	Initials mObjInitials; 
public: 
	App(); 
	~App(); 
 
	Initials &getInitials() const; 
	void run() const; 
};

App.cpp:

    App::App() 
    { } 
     
    App::~App() 
    { } 
     
    Initials &Initials::getInitials() const 
    { 
    	return(mObjInitials); 
    } 
     
    void App::run() const 
    { 
    	getInitials().displayPrompt(); 
    	getInitials().processInitials(); 
    	getInitials().displayInitials(); 
    } 

This simply defines an Initials class object privately, then a default constructor that does nothing as the default constructor of Initials will be automatically called by the compiler/runtime, a destructor which does nothing because everything has its own destructor to take care of things so it’s not really needed but here for appearance, a getter to get the Initials object, and then a function run() that just does what the previous main function did. Now we will code the new main function in C++ -

Main.cpp:
    #include "App.h" 
     
    int main(int argc, char **argv) 
    { 
    	App objApp; 
     
    	objApp.run(); 
     
    	return(0); 
    } 

There's nothing really to explain for this file as it's just calling the run function after creating the App object and after run is called and done, it returns 0 for success. Now one could wrap a try catch around the objApp.run() and return -1 or whatever else in the catch if App.run actually ever threw any exceptions (designated errors basically).

So now you know how to do this in C, a pseudo OOP C, and then in C++ if you cared. As you’ll notice, the C++ is actually smaller than the C version w/ functions but all you really need is the first program written here where everything is in the main() method - but when I was in college trying to test out of Introduction to C++, I was required to take the course anyhow because I put everything in the one function when it was pathetically simple such as this so I’m showing the first program, and how one might improve it.

C programming can do more than that.
follow my github account if you get this content useful.

   
