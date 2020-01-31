//-----------------------------------------------------------------------------
// Alyssa Melton 
// amelton@ucsc.edu
// CS101
// 5/15/18
// List.java
//-----------------------------------------------------------------------------


public class List {
	
	//-Fields for the List class-----------------------------------------
   	
   	private Node head;     // reference to first Node in List
   	private Node tail;	   // reference to the last Node in List
   	private int numItems;  // number of items in this List.
   	private Node cursor;	// reference to Node the cursor is on.
   	private int index;

	// List()
	// constructor for the List class
	public List(){
		head = null;
		tail = null;
		numItems = 0;
		cursor = null;
		index = -1;
	}


	//-Private inner Node class------------------------------------------------

   	private class Node {
		Object data;
		Node next;
		Node before;

		Node(Object x){
			data = x;
			next = null;
			before = null;
		}

		public boolean equals(Node N){
			if(!data.equals(N.data)) return false;
			return true;
		}
   }


	//Access Functions----------------------------------------------------------

	// returns number of elements in list
	int length(){
		return numItems;
	}


	// if cursor is defined, returns the index of the cursor element,
	// otherwise returns -1
	int index(){
		return index;	
	}


	// returns front element
	// pre: length() > 0
	Object front() throws RuntimeException{
		if (length() <= 0) throw new RuntimeException("cannot front() empty List");
		return head.data;
	}

	//returns back element
	//pre: length() > 0
	Object back(){
		if (length() <= 0) System.out.println("back() cannot be called on empty list");
		return tail.data;
	}

	//returns cursor element. 
	//Pre: length()>0, index() >=0
	Object get() throws RuntimeException{
		if (cursor == null)	throw new RuntimeException("cannot get() undefined cursor");
		return cursor.data;
	}

	
	// Returns true if and only if this List and L are the same
	// integer sequence. The states of the cursors in the two Lists 
	// are not used in determining equality.
	public boolean equals(List L){
	   	if(numItems != L.numItems) return false; // number of items in this List.
		for(Node N = head, M = L.head; N != null && M != null; N = N.next, M = M.next){
			if(!((N).equals(M))) return false;
		}
		return true;
	}


	// Manipulation Procedures------------------------------------------------
	
	// resets this list to its original empty state.
	void clear(){
		numItems = 0;
		head = null;
		tail = null;
		cursor = null;
		index = -1;
	}

	// If List is non-empty, places the cursor under the front element,
	// otherwise does nothing.
	void moveFront(){
		if(length() != 0){
			cursor = head;
			index = 0;
		}
	}


	// If List is non-empty, places the cursor under the back element,
	// otherwise does nothing.
	void moveBack(){
		if (length() != 0){
			cursor = tail;
			index = numItems-1;		
		}
	}



	// If cursor is defined and not at front, moves cursor one step toward 
	// front of this List, if cursor is defined and at front, cursor becomes 
	// undefined, if cursor is undefined does nothing.
	void movePrev(){
		if (cursor != null){
			cursor = cursor.before;	
			index--;
			if(cursor == null){ index = -1; }
		}
	}



	// If cursor is defined and not at back, moves cursor one step toward 
	// back of this List, if cursor is defined and at back, cursor becomes 
	// undefined, if cursor is undefined does nothing.
	void moveNext(){
		if (cursor != null){
			cursor = cursor.next;
			index++;
			if(cursor == null){ index = -1; }
		}
	}


	// insert new element into this list. if list is non-empty,
	//insertion takes place before front element.
	void prepend(Object data){
		if (numItems == 0){
			Node N = new Node(data);
			head = N;
			tail = N;
			numItems++;
			index++;
		} else {
			Node N = new Node(data);
			head.before = N;
			N.next = head;
			head = N;
			numItems++;
			index++;
		}
	}


	//insert new element into this list. if list is non-empty,
	//insertion takes place after back element.
	void append(Object data){
		if (numItems == 0){
			Node N = new Node(data);
			head = N;
			tail = N;
			numItems++;
		} else {
			Node N = new Node(data);
			tail.next = N;
			N.before = tail;
			tail = N;
			numItems++;
		}
	}


	// insert new element before cursor.
	// pre: length() > 0, index() >=0
	void insertBefore(Object data){
		if( length() == 0 ){
			prepend(data);
		} else if (cursor == head){
			prepend(data);
		} else{
			Node N = new Node(data);
			cursor.before.next = N;
			N.before = cursor.before;
			N.next = cursor;
			cursor.before = N;
			numItems++;
			index++;
		}
	}


	//insert new element after cursor.
	//pre: length () > 0, index >=0
	void insertAfter(Object data){
		if( length() == 0 ){
			append(data);
		} else if (cursor == tail){
			append(data);
		} else {	
			Node N = new Node(data);
			N.before = cursor;
			N.next = cursor.next;
			cursor.next.before = N;
			cursor.next = N;
			numItems++;
		}
	}


	//deletes the front element.
	//pre length() >0
	void deleteFront(){
		if(length() == 1){
			clear();
		} else {
			head.next.before = null;
			head = head.next;
			numItems--;
			index--;
		}
	}



	//deletes the back element
	//pre length()>0
	void deleteBack(){
		if( length() ==1 ) {
			clear();
		} else {
			if (tail == cursor) { 
				cursor = null;
				index = -1;  
			}
			tail.before.next = null;
			tail = tail.before;
			numItems--;
		}
	}


	//deletes cursor element, making cursor undefined.
	// pre: length()>0, index() >=0
	void delete(){
		if (length() == 1){
			clear();
		} else if (cursor == head) {
			cursor.next.before = null;
			head = cursor.next;
			cursor = null;
			numItems--;
			index = -1;
		} else if (cursor == tail){
			cursor.before.next = null;
			tail = cursor.before;
			cursor = null;
			numItems--;
			index = -1;
		}
	}





	// Other Methods ---------------------------------------------------------


	// Overrides Object's toString method. Returns a String
	// representation of this List consisting of a space
	// separated sequence of integers, with front on left.
	public String toString(){
		if (numItems == 0){ 
			return ""; 
		}
		
		String s = "";
		
		for(Node N = head; N != null; N=N.next){
			s += (N.data + " "); 
		}
		return s;
	}



}