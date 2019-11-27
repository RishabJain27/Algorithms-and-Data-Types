//Rishab Jain,rjain9, pa3, cmps101,10/7/17
class List {

	private class Node{
      // Fields
	  private Object data;
      private Node previous;
      private Node next;
      
      // Constructor
      Node(Object data) { 
         this.data = data; 
         this.previous = null;
         this.next = null; 
      }

      // toString()
      // Overrides Object's toString() method.
      public String toString() { 
         return String.valueOf(data); 
      }

      // equals(): overrides Object's equals() method
      public boolean equals(Object x){
         boolean eq = false;
         Node that;
         if(x instanceof Node){
            that = (Node) x;
            eq = (this.data==that.data);
         }
         return eq;
      }

    }

    //private fields
    private Node front;
    private Node back;
    private Node cursor;

    private int lengthList;
    private int indexCursor;

     	List(){
    	front = null;
    	back = null;
    	cursor = null;

    	lengthList = 0;
    	indexCursor = -1;
    }

    // Access functions
    // Returns the number of elements in this List.
	int length(){
		return lengthList;
	}
	// If cursor is defined, returns the index of the cursor element,// otherwise returns -1.
	int index(){
		if(cursor != null){
			return indexCursor;
		}
		else {
			return -1;
		}
	}
	// Returns front element. Pre: length()>0
	Object front() {
		if(length() <= 0){
			throw new RuntimeException(
            "List Error: front() called on empty List");
		}
		else{
			return front.data;
		}
	}
	// Returns back element. Pre: length()>0
	Object back(){
		if(length() <= 0){
			throw new RuntimeException(
            "List Error: back() called on empty List");
		}
		else{
			return back.data;
		}

	}
	// Returns cursor element. Pre: length()>0, index()>=0
	Object get(){
		if(length() <= 0 || indexCursor < 0){
			throw new RuntimeException(
            "List Error: get() called on empty List");
		}
		else{
			return cursor.data;
		}
	}


	// Returns true if and only if this List and L are the same
 	// integer sequence. The states of the cursors in the two Lists
 	// are not used in determining equality.
	public boolean equals(Object x){
		boolean eq  = false;
      	List Q;
      	Node N, M;

      	if(x instanceof List){
        	Q = (List)x;
         N = this.front;
         M = Q.front;
         eq = (this.lengthList==Q.lengthList);
         while( eq && N!=null ){
            eq = N.equals(M);
            N = N.next;
            M = M.next;
         }
      }
      return eq;
	}

	// Manipulation procedures
	
	// Resets this List to its original empty state.
	void clear(){	
		front = null;
		back = null;
		cursor = null;

    	lengthList = 0;
    	indexCursor = -1;
	}

	//If List is non-empty, places the cursor under the front element,otherwise does nothing.
	void moveFront(){
		if(length() > 0){
			cursor = front;
			indexCursor = 0;
		}
	}

	// If List is non-empty, places the cursor under the back element, otherwise does nothing.
	void moveBack(){
		if(length() >0){
			cursor = back;
			indexCursor = length() -1;
		}
	}

	// If cursor is defined and not at front, moves cursor one step toward 
	// front of this List, if cursor is defined and at front, cursor becomes
	// undefined, if cursor is undefined does nothing.
	void movePrev(){
		if(cursor != null && indexCursor != 0){
			cursor = cursor.previous;
			indexCursor--;
		}
		else if( cursor != null && indexCursor == 0){
			cursor = null;
			indexCursor = -1;
		}
		else{
			return;
		}

	}


	// If cursor is defined and not at back, moves cursor one step toward
 	// back of this List, if cursor is defined and at back, cursor becomes
 	// undefined, if cursor is undefined does nothing.
	void moveNext(){
		if(cursor != null && indexCursor != length()-1){
			cursor = cursor.next;
			indexCursor++;
		}
		else if(cursor != null && indexCursor == length()-1){
			cursor = null;
			indexCursor = -1;
		}
		else{
			return;
		}
	}

	// Insert new element into this List. If List is non-empty,
 	// insertion takes place before front element.
	void prepend(Object data){
		Node temp = new Node(data);
		
		if(lengthList == 0){
			front = temp;
			back = temp;
			lengthList++;
		}
		else{
			front.previous = temp;
			temp.next = front;
			front = temp;
			
			if(cursor != null){
				indexCursor++;
			}
			lengthList++;
		}
	}

	// Insert new element into this List. If List is non-empty,
 	// insertion takes place after back element.
	void append(Object data){
		Node temp = new Node(data);
		if(lengthList == 0){
			back = temp;
			front = temp;
			lengthList++;

		}
		else{
			back.next = temp;
			temp.previous = back;
			back = temp;
			lengthList++;
		}

	}


	// Insert new element before cursor.
 	// Pre: length()>0, index()>=0
	void insertBefore(Object data){
		Node temp = new Node(data);
		if(length() <= 0 ||  index() < 0){
			throw new RuntimeException(
            "List Error: insertBefore() called on empty List");
		}
		else if(cursor == front){
			temp.previous = null;
			temp.next = cursor;
			cursor.previous = temp;

			front = temp;

			indexCursor++;
			lengthList++;
		}
		else{

			temp.next = cursor;
			temp.previous = cursor.previous;
			cursor.previous.next = temp;
			cursor.previous = temp;

			cursor = temp;
			indexCursor++;
			lengthList++;
		}
	}


	// Inserts new element after cursor.
	// Pre: length()>0, index()>=0
	void insertAfter(Object data){
		Node temp = new Node(data);
		if(length() <= 0 || index() < 0){
			throw new RuntimeException(
            "List Error: insertAfter() called on empty List");
		}
		else if( cursor == back){
			temp.next = null;
			temp.previous = cursor;
			cursor.next = temp;
			back = temp;

			lengthList++;
		}
		else{
			temp.previous = cursor;
			temp.next = cursor.next;
			cursor.next.previous = temp;
			cursor.next = temp;
		
			lengthList++;

		}


	}

	// Deletes the front element. Pre: length()>0
	void deleteFront(){
		if(length() <= 0){
			throw new RuntimeException(
            "List Error: deleteFront() called on empty List");	
		}
		else if(length() == 1){
			front = null;
			back = null;

			indexCursor = -1;
			lengthList--;
		}
		else{
			front = front.next;
			front.previous = null;

			indexCursor--;
			lengthList--;

		}

	}

	// Deletes the back element. Pre: length()>0
	void deleteBack(){
		if(length() <= 0){
			throw new RuntimeException(
            "List Error: deleteBack() called on empty List");
		}
		else if(length() == 1){
			front = null;
			back = null;
			
			lengthList=0;
			indexCursor= -1;
		}
		else{
			if(cursor == back){
				indexCursor = -1;
			}
			back = back.previous;
			back.next = null;	
			lengthList--;
		}
	}

	// Deletes cursor element, making cursor undefined.
 	// Pre: length()>0, index()>=0
 	void delete(){
 		if(length() < 0 && index() <0){
 			throw new RuntimeException(
            "List Error: delete() called on empty List");
 		}
 		else if(cursor == front){
 			deleteFront();
 		}
 		else if(cursor == back){
 			deleteBack();
 		}
 		else{
 			cursor.next.previous = cursor.previous;
 			cursor.previous.next = cursor.next;
 			
 			cursor = null;
 			indexCursor = -1;
 			lengthList--;
 		}
 	}

 	// Overrides Object's toString method. Returns a String
 	// representation of this List consisting of a space
	// separated sequence of integers, with front on left.
 	public String toString(){
 		StringBuffer sb = new StringBuffer();
      	Node N = front;
      	while(N!=null){
        	sb.append(N.toString());

		if(N.next != null){
        		sb.append(" ");
		}
       		 N = N.next;
      }
    	return new String(sb);
 	}

 	/*// Returns a new List representing the same integer sequence as this
 	// List. The cursor in the new list is undefined, regardless of the
 	// state of the cursor in this List. This List is unchanged.
 	List copy(){
 		List list = new List();
 		Node temp = front;

 		while( temp != null){
 			list.append(temp.data);
 			temp = temp.next;
 		}

 		return list;
 	}*/

}
