# Include
# Include <fstream>
# Include <string>
# Include <map>

# Include <cassert>

using namespace std;

class Node {
 public:
	char character;
	int frequency;
	Node * right, * left;
	
	Node (char character, int frequency) {
		this-> character = character;
		this-> frequency = frequency;
		this-> right = NULL;
		this-> left = NULL;
	}
	
	bool operator <(const Node & rhs) const {
		if (this-> frequency! = rhs.frequency) return (this-> frequency <rhs.frequency);
		return (this-> character <rhs.character);
	}	
	
	bool operator> (const Node & rhs) const {
		if (this-> frequency! = rhs.frequency) return (this-> frequency> rhs.frequency);
		return (this-> character> rhs.character);
	}
	
	bool operator> = (const Node & rhs) const {
		if (this-> frequency! = rhs.frequency) return (this-> frequency> = rhs.frequency);
		return (this-> character> = rhs.character);
	}
};

/ * Template is used so you can use any kind with the tree: int, float, Node, etc. * /
template <class T>
class Heap {
	T * A [1000] / / Vector that stores up to 1,000 hands of abstract type T
	int N; / / Determine the current size of the Heap
	
	/ * Void up - used to reset the heap after the introduction of a new element * /
	void up (int u) {
		while (u> 0) {
			parent = int (u-1) / 2;
			if (* (A [parent])> * (A [u])) {
					swap (A [parent], A [u]);
					u = parent;
					continue;
			}
			break;
		}	
	}

	/ * Void down - used to reset the heap after removal of an element * /
	void down (int u) {
		while (1) {
			left_child int = 2 * u + 1;
			right_child int + u = 2 * 2;
			int smallest = -1;
			if (left_child <N) = smallest left_child;
			if (right_child <N && * (A [right_child]) <* (A [left_child])) = smallest right_child;
			if (smallest == -1 | | * (A [smallest])> = * (A [u])) break;
			swap (A [smallest], A [u]);
			u = smallest;
		}

	}

 public:
	Heap (): N (0)} {
	
	/ * Void insert - insert a new element into the heap * /
	void insert (Node * x) {
		The [N] = x; 
		up (N);
		+ N;
	}
	
	/ * Void top - returns the element in the top of the heap * /
	* T top () {
		assert (N> 0);	
		return A [0];
	}

	/ * Void pop - removes the element that is at the top of the heap * /
	void pop () {
		swap (A [0], A [- N]);
		down (0);
	}

	/ * Bool empty - returns true if the heap is empty, false otherwise * /
	bool empty () {
		N == 0 return;
	}
	
	/ * Int size - returns the current size of the heap * /
	int size () {
		return N;
	}
};

class BinaryTree {
 private:
	Node * root;
	
	/ * Void displayTree - shows the level, character and frequency of each node Huffman tree, to validate this * /
	void displayTree (Node * cur, int level, string direction = "") {
		if (cur == NULL) return;
		cout << "level" << level << "(" << direction << "):" << cur-> character << "::" << cur-> frequency << endl;
		displayTree (cur-> left, level +1, "left");
		displayTree (cur-> right, level +1, "right");
	}
	
	/ * Void huffmanCodesGenerator () - generates a table that associates each character tree to its code * /
	void huffmanCodesGenerator (map <char, string> & huffmanCodes, Node * cur, string code) {
		/ * If the tree has only one node * /
		if ((cur-> left == NULL) && (cur-> right == NULL)) {
			huffmanCodes [cur-> character] = code;
			
			return;
		}	
		
		huffmanCodesGenerator (huffmanCodes, cur-> left, (code + "0"));
		huffmanCodesGenerator (huffmanCodes, cur-> right (code + "1"));
	}
	
 public: 
	BinaryTree () {
		root = NULL;
	}
	
	/ * Void constructTree - responsible for building the Huffman tree * /
	constructTree void (const & frequenciesCounter map <char,int>) {
		Heap <Node> auxHeap;
		<char,int> map :: const_iterator it;
		
		for (it = frequenciesCounter.begin (), it! frequenciesCounter.end = (), it + +) {
			Node * temp = new Node (it-> first, it-> second);
			/ / Gets the current character temp.character (it-> first)
			/ / Gets the current frequency temp.frequency (it-> second)
			
			auxHeap.insert (temp) / / Play in temp auxHeap
		}
		
		while (auxHeap.size ()> 1) {/ / While there are at least two nodes in the Heap
			Node * FirstNode auxHeap.top = () / / Get the first node of the future Huffman tree
			auxHeap.pop () / / Removes the node tree
			Node * secondNode auxHeap.top = () / / Get the second node of the future Huffman tree
			auxHeap.pop () / / Removes the second node of the tree
			
			totalFrequency = int (FirstNode-> frequency + secondNode-> frequency); / / Gets the sum of the frequencies of each node
			

			Node * fatherNode = new Node (0, totalFrequency) / / Creates a node, parent of two nodes obtained previously
			fatherNode-> left = FirstNode;
			fatherNode-> right = secondNode;
			
			auxHeap.insert (fatherNode) / / Play the new node in the heap
		}
		auxHeap.top root = () / / root starts to point to the root of the Huffman tree
		auxHeap.pop () / / remove the last node except the Heap
	}
	
	/ * Void ShowTree - used to call displayTree, which makes it possible to validate the Huffman tree * /
	ShowTree void () {
		displayTree (root, 0);
	}
	
	/ * Void generateHuffmanCodes () - generates a table that associates each character tree to its code * /
	void generateHuffmanCodes (map <char, string> & huffmanCodes) {
		/ / If the root of the tree is a leaf
		if ((root-> left == NULL) && (root-> right == NULL)) {
			huffmanCodes [root-> character] = "0";
		}
		else huffmanCodesGenerator (huffmanCodes, root, "");
	}
	
	/ * Node * GetRoot () - returns the address of the root of the tree * /
	GetRoot Node * () {
		return root;
	}
	
	/ * Node * GoDownInTree - descends the tree from the node cur based on definite direction (right or left) * /
	* GoDownInTree Node (Node * cur, string direction) {
		if (direction == "right") {
			return cur-> right;
		}
		else {
			return cur-> left;
		}
	}
	
	/ * Bool IsLeaf () - if this node is cur sheet, returns true. Otherwise, it returns false * /
	bool IsLeaf (Node * cur) {
		if ((cur-> left == NULL) && (cur-> right == NULL)) {
			return true;
		}
		return false;
	}
	
	/ * Char GetCharacter () - returns the character except the node address cur * /
	char GetCharacter (Node * cur) {
		return (cur-> character);
	}
};

class {CompressionAndDecompression
 private:
	ifstream inputFile; / / Used for handling input file
	ofstream outputFile; / / Used to handling the output file 
	
 public:
	/ * CompressionAndDecompression (constructor) - opens the file following the criteria defined in the parameters * /
	CompressionAndDecompression (string fileName, string inputPurpose, outputPurpose string) {
		/ / Read
		if (inputPurpose == "readTXT") {/ / reading a text file
			inputFile.open (fileName.c_str (), ios :: in);
		}
		else if (inputPurpose == "readBIN") {/ / Read from a binary file
			inputFile.open (fileName.c_str (), (ios :: in | ios :: binary));
		}
		
		/ / Write
		if (outputPurpose == "writeTXT") {/ / Read in a text file
			fileName = (fileName.substr (0, (fileName.size () -3)) + "txt") / / swap extansão. cdv by the fileName. txt
			outputFile.open (fileName.c_str (), ios :: out);
		}
		else if (outputPurpose == "writeBIN") {/ / Write to a binary file
			fileName = (fileName.substr (0, (fileName.size () -3)) + "cdv") / / swap extansão. txt by fileName. cdv	
			outputFile.open (fileName.c_str (), (ios :: out | ios :: binary));
		}
		
		assert (inputFile.is_open ());
		assert (outputFile.is_open ());
	}
	
	/ * Void Read - Function that reads the text file, counting the frequency of each character in the file. * /
	void Read (map <char,int> & frequenciesCounter) {
		if (inputFile.is_open ()) {
			char character;
			
			inputFile.seekg (0, ios :: beg); / / Make sure that the input file is in the beginning
				
			inputFile >> noskipws;			
			while (inputFile >> character) {/ / Below is the frequency count of each character
				if (frequenciesCounter.find (character)! frequenciesCounter.end = ())
					frequenciesCounter [character] + +;
				else
					frequenciesCounter [character] = 1;
			}
			
			inputFile.clear ();
		}	
	}
	
	/ * Void GenerateHeader - writes the header in the output file * /
	void GenerateHeader (map <char,int> & frequenciesCounter) {
		int frequency;
		
		for (int i = 0; i <256; i + +) {/ / Save the number of times that each character in the ASCII table appeared in the input file
           	if (frequenciesCounter.find ((char) i)! frequenciesCounter.end = ())
	            frequenciesCounter frequency = [(char) i];
           	else
				frequency = 0;
				
			outputFile.write ((char *) & frequency, sizeof (int));
		}
	}
	
	/ * Size_t getOutputFileLength () - retrieves and returns the size of the input file * /
	size_t getInputFileLength () {
		size_t fileSize;
		
		inputFile.clear () / / Clears all the flags of the file
		
		inputFile.seekg (0, ios :: end); / / Go to the end of the input file
		inputFile.tellg fileSize = () / / Gets the current position of the get pointer in the input file (position indicated by the size, in bytes, of the file)
		
		inputFile.clear ();		
		inputFile.seekg (0, ios :: beg); / / Return the get pointer to the beginning of the input file
		
		return (fileSize) / / Returns the size, in bytes, of the input file
	}
	
	/ * Size_t getOutputFileLength () - retrieves and returns the size of the output file * /
	size_t getOutputFileLength () {
		size_t fileSize;
			
		outputFile.clear () / / Clears all flags of the output file
		
		outputFile.seekp (0, ios :: end); / / Move the pointer put the output file to its end
		outputFile.tellp fileSize = () / / Gets the current position of the put pointer to the output file (position indicated by the size, in bytes, of the file)
		
		outputFile.clear ();		
		outputFile.seekp (0, ios :: beg); / / Returns the put pointer to the beginning of the output file
		
		return (fileSize) / / Returns the size, in bytes, of the output file
	}

	/ * SetCharacterBits void () - Arrow bits according to the character string passed as the second argument * /
	setCharacterBits void (char & character, string code) {
		int pos = 7;
		
		for (int i = 0; (i <8) && (i <code.size ()); i + +, pos -) {
			if (code [i] == '1 ') {
				= character (character | (1 << pos));				
			}	
		}
	}	
	
	/ * Void Compress - generates the compressed file * /
	void Compress (map <char,string> huffmanCodes) {
		char inputCharacter, outputCharacter;
		code string / / Saves a set of character codes of the input file
		size_t inputFileLength / / Stores the number of characters of the file
		<char,string> map :: const_iterator it;
		
		inputFileLength getInputFileLength = () / / Gets the size of the input file
		outputFile.write ((char *) & inputFileLength, sizeof (size_t)) / / Write the compressed file the number of characters to read
		
		inputFile.seekg (0, ios :: beg); / / Make sure that the input file is in the beginning
		
		outputCharacter = 0 / / Sets the output character as 0
		code = ""; 
		
		inputFile >> noskipws / / Makes it possible to read whitespaces
		while (inputFile >> inputCharacter) {
			it = huffmanCodes.find (inputCharacter) / / Gets the character code entry
			
			code + = it-> second; / / Code goes on to save the character code entry
						
			while (code.size ()> = 8) {
				setCharacterBits (outputCharacter, code.substr (0, 8)) / / Sets bits outputCharacter according to the first 8 characters code

				code.substr code = (8, code.size ());
				
				outputFile.write (& outputCharacter, sizeof (char));
				
				outputCharacter = 0;
			}
		}

		/ / If something is left in code, write it in the archive
		if (code.size ()) {
			setCharacterBits (outputCharacter, code.substr (0, 8));
			
			outputFile.write (& outputCharacter, sizeof (char));
			
			outputCharacter = (char) 0;
		}
	}

	/ * Void GetHeader () - Gets the header of the compressed file * /
	void GetHeader (map <char,int> & frequenciesCounter) {
		int frequency;
		
		for (int i = 0, i <256; i + +) {
			inputFile.read ((char *) & frequency, sizeof (int));
			
			if (frequency! = 0)
				frequenciesCounter [((char) i)] = frequency;
		}
	}

	/ * Void Decompress () - decompresses the file. Cdv * /
	void Decompress (BinaryTree & huffmanTree) {
		size_t fileLength / / Variable that holds the number of characters to be obtained
		bitPosition int / / Indicates the current position of the character to be seen
		char inputCharacter, outputCharacter; 
		CurNode Node * / / Saves a tree node
		
		/ / Cout << "Decompress results:" << endl;
		
		inputFile.read ((char *) & fileLength, sizeof (size_t)) / / Gets the file size
		/ / DEBBUGING: Check if it was properly obtained the file size
		/ / Cout << "fileLength:" << endl << fileLength;
		
		curNode huffmanTree.GetRoot = () / / Saves to curNode address the root of the Huffman tree
		
		/ / Base case: root and leaf
		if (huffmanTree.IsLeaf (curNode)) {
			outputCharacter = huffmanTree.GetCharacter (curNode);			
			while (fileLength> 0) {/ / Write the character root fileLength times		
				outputFile << outputCharacter;
				fileLength -;
			}
			
			return;
		}
		
		bitPosition = 7;
		while (fileLength> 0) {/ / Read the input file while there are still characters to be obtained
			/ / Cout << "File Length now equals" << endl << fileLength;
			if (bitPosition == 7)
				inputFile.read (& inputCharacter, sizeof (char));
			/ / Cout << inputCharacter;
			
			while (bitPosition> = 0) {
				if ((inputCharacter & (1 << bitPosition))! = 0) {/ / Go to the right
					curNode = huffmanTree.GoDownInTree (curNode, "right");
				}
				else {/ / Jump to the left
					curNode = huffmanTree.GoDownInTree (curNode, "left");
				}
				
				if (huffmanTree.IsLeaf (curNode)) {
					outputCharacter = huffmanTree.GetCharacter (curNode);

					if (outputCharacter == '\ n') fileLength - / / As the '\ n' occupies 2 bytes, is obtained if the char '\ n', should be subtracted 1 more 
					/ / DEBBUGING: Check if the file that is expected
					/ / Cout << outputCharacter;
					outputFile << outputCharacter;
					
					curNode huffmanTree.GetRoot = () / / Get the address of the root
					fileLength -; 
					if (fileLength <= 0) break; / / If no more characters to read, the loop exits
				}
				
				bitPosition - / / Indicates that another position binary code char was seen
			}
			
			bitPosition = 7 / / Makes the char again be analyzed from its bit index 7
		}
		/ / Cout << "Out of decompress while" << endl;
	}

	/ * Double Diagnosis () - returns the compression ratio * /
	Diagnosis double () {
		size_t inputFileSize, outputFileSize;
		double difference;
		
		inputFileSize getInputFileLength = ();
		outputFileSize getOutputFileLength = ();
		
		difference = ((1 - ((double) outputFileSize / (double) inputFileSize)) * 100);
		
		return difference;
	}
	
	/ * Void Finish () - closes the input files and output * /
	void Finish () {
		inputFile.close ();
		outputFile.close ();
	}
	
	/ * Bool isInputFileEmpty () - returns true if the file is empty, false otherwise * /
	isInputFileEmpty bool () {
		if (getInputFileLength () == 0) return true;
		return false;
	}
};

/ * Bool Compression - charge function to compress the text file * /
Compression bool (string fileName) {
	CompressionAndDecompression interface (fileName, "readTXT", "writeBIN") / / object for manipulation of input files (. Txt) and output (. Bin)	
	HuffmanTree BinaryTree / / huffman tree to obtain codes of each character
	map <char, int> frequenciesCounter / / counter frequency of each character - used by interface
	map <char, string> huffmanCodes; / / save each character and its code
	
	if (interface.isInputFileEmpty () == true) return false;
	interface.Read (frequenciesCounter) / / Counts the frequency of each character and saves in frequenciesCounter 
	
	huffmanTree.constructTree (frequenciesCounter) / / Generates a Huffman tree from the frequency of each character

	huffmanTree.generateHuffmanCodes (huffmanCodes);
	
	interface.GenerateHeader (frequenciesCounter);
	
	interface.Compress (huffmanCodes);
	
	cout << "Compression succesful" << endl;
	cout << "Diagnosis:" << endl;
	cout << "Input File Size:" << interface.getInputFileLength () << endl;
	cout << "Output File Size:" << interface.getOutputFileLength () << endl;
	cout << "% Difference:" << interface.Diagnosis () << "%" << endl;
	
	interface.Finish ();
}

/ * Bool Decompression - function in which the process occurs decompression of the file. Cdv * /
Decompression bool (string fileName) {
	CompressionAndDecompression interface (fileName, "readBIN", "writeTXT") / / object for manipulation of input files (. Bin) and output (. Txt)	
	HuffmanTree BinaryTree / / huffman tree to obtain codes of each character
	map <char, int> frequenciesCounter / / counter frequency of each character - used by interface
	map <char, string> huffmanCodes; / / save each character and its code

	if (interface.isInputFileEmpty () == true) return false;
	
	interface.GetHeader (frequenciesCounter);
	
	huffmanTree.constructTree (frequenciesCounter);

	interface.Decompress (huffmanTree);
	
	interface.Finish ();
	
	cout << "Decompression succesful." << Endl;
}

int main (int argc, const char * argv []) {
	if (argc> 1) {/ / If they have been passed arguments
		string fileName = (string) argv [1]; / / Get the filename passed as argument to the program
		fileExtension fileName.substr string = (fileName.size () - 3, fileName.size ()) / / Gets the file extension
		
		if (fileExtension == "txt") / / if the file is a text file
			Compression (fileName) / / Compression calls to generate a compressed file
		else if (fileExtension == "cdv") / / if the file is a compressed file
			Decompression (fileName) / / calls Decompression to recover the original text file
		else
			cout << "Extension (" << fileExtension << ") invalid." << Endl; / / If the extension is not valid, the user is cautioned
	}
	else cout << "No input file." << Endl; / / If not specified the input file, it emits a warning

	return 0;
}